
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "msg.h"
#include "ipc_slave.h"
#include "hashtable.h"
#include "crypto.h"
#include "packet_frame.h"
#include "in_cksum.h"
#include "inet.h"
#ifdef OUT_OF_ORDER
#include "fifo.h"
#endif

#define IPSEC_MAX_SA_COUNT      32
#define IPSEC_MAX_RX_IP_COUNT   32

#define F_TCP_CKSUM             1
#define F_UDP_CKSUM             2

#define MSG_HEADER sizeof(uint64_t)

typedef struct {
    uint32_t ipaddr[4];
} RX_IP_SATypedef;

typedef struct {
    struct hlist_node hlist;
    uint32_t spi;
    uint32_t iptbl_ind;
    uint32_t key[4];
    uint32_t salt;
} RX_SATypedef;

typedef struct {
    uint32_t key[4];
    uint32_t salt;
} TX_SATypedef;

uint32_t Cross_Features = 0;
__exdata RX_IP_SATypedef ip_tbl[IPSEC_MAX_RX_IP_COUNT];
__exdata RX_SATypedef rx_tbl[IPSEC_MAX_SA_COUNT];
__exdata TX_SATypedef tx_tbl[IPSEC_MAX_SA_COUNT];
__exdata DEFINE_HASHTABLE(rx_sa_list, 5);

#ifdef OUT_OF_ORDER
DECLARE_KFIFO(out_of_order, intptr_t, MSG_NUM);
#endif

#ifdef DEBUG
#define Dump_IP  Dump_UINT_ARRAY
#define Dump_KEY Dump_UINT_ARRAY

const char *Dump_UINT_ARRAY(const uint32_t array[])
{
    int i, pos = 0;
    static char buf[64];

    for (i = 0; i < 4; i++)
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%08x", array[i]);

    return buf;
}

void Dump_MSG(intptr_t msg)
{
    switch (*(uint32_t *)msg) {
    case MSG_RX_SA_ADD: {
        MSG_RxSAMsgTypeDef *rsa = (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

        printf("xfrm ip add index %u addr 0x%s\n",
               rsa->iptbl_ind, Dump_IP(rsa->ipaddr));
        printf("xfrm state add index %u spi 0x%08x salt 0x%08x dec 0x%s\n",
               rsa->sa_ind, rsa->spi, rsa->salt, Dump_KEY(rsa->key));
    }
    break;
    case MSG_TX_SA_ADD: {
        MSG_TxSAMsgTypeDef *tsa = (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

        printf("xfrm state add index %u salt 0x%08x enc 0x%s\n",
               tsa->sa_ind, tsa->salt, Dump_KEY(tsa->key));
    }
    break;
    case MSG_RX_SA_DEL: {
        MSG_RxSAMsgTypeDef *rsa = (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

        printf("xfrm ip del index %u addr 0x%s\n",
               rsa->iptbl_ind, Dump_IP(rsa->ipaddr));
        printf("xfrm state del index %u spi 0x%08x salt 0x%08x dec 0x%s\n",
               rsa->sa_ind, rsa->spi, rsa->salt, Dump_KEY(rsa->key));
    }
    break;
    case MSG_TX_SA_DEL: {
        MSG_TxSAMsgTypeDef *tsa = (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

        printf("xfrm state del index %u salt 0x%08x enc 0x%s\n",
               tsa->sa_ind, tsa->salt, Dump_KEY(tsa->key));
    }
    break;
    case MSG_ENC: {
    }
    break;
    case MSG_DEC: {
    }
    break;
    case MSG_RX_SA_ADD_DONE:
        break;
    case MSG_TX_SA_ADD_DONE: {
        MSG_TxSAMsgTypeDef *tsa = (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

        printf("xfrm state add index %u done\n", tsa->sa_ind);
    }
    break;
    case MSG_RX_SA_DEL_DONE:
        break;
    case MSG_TX_SA_DEL_DONE:
        break;
    case MSG_ENC_DONE: {
        MSG_ENCMsgTypeDef *enc = (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);
        printf("xfrm encryption (%p) done \n", (void *)enc->frm);
    }
    break;
    case MSG_DEC_DONE: {
        const char *status;
        MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

        switch (GET_FIELD(dec->desc->desc8, 1, 0x3)) {
        case SECERR_OK:
            status = "ok";
            break;
        case SECERR_INVAL:
            status = "Protocol not available";
            break;
        case SECERR_INVAL_LEN:
            status = "Length not supported";
            break;
        case SECERR_INVAL_AUTH:
            status = "Authentication error";
            break;
        default:
            status = "unknown";
            break;
        }

        printf("xfrm decryption (%p) done, status: %s \n",
               (void *)(intptr_t)dec->desc->desc9,
               status);
    }
    break;
    default:
        printf("unknown msg type, abort!!");
        break;
    }

    return;
}
#endif

__STATIC_FORCEINLINE
void IPSec_Send_Msg(intptr_t msg)
{
#ifdef DEBUG
    Dump_MSG(msg);
#endif
    //IPC_Msg_Send(msg);
    return;
}

__STATIC_FORCEINLINE
void IPSec_Send(intptr_t msg)
{
#ifdef OUT_OF_ORDER
    intptr_t m;

    while (!kfifo_peek(&out_of_order, &m)) {
        switch (*(uint32_t *)m) {
        case MSG_ENC_DONE:
        case MSG_DEC_DONE:
            IPSec_Send_Msg(m);
            kfifo_skip_out(&out_of_order);
            break;
        default:
            return;
        }
    }
#else
    IPSec_Send_Msg(msg);
#endif
    return;
}

__STATIC_FORCEINLINE
void SA_RX_Insert(MSG_RxSAMsgTypeDef *rsa)
{
    int i;

    /* save SA IP addr info */
    for (i = 0; i < 4; i++)
        ip_tbl[rsa->iptbl_ind].ipaddr[i] = rsa->ipaddr[i];

    /* save SA info - SPI(in bigendian), ipidx, key, salt */
    rx_tbl[rsa->sa_ind].spi = rsa->spi;
    rx_tbl[rsa->sa_ind].iptbl_ind = rsa->iptbl_ind;
    for (i = 0; i < 4; i++)
        rx_tbl[rsa->sa_ind].key[i] = rsa->key[i];
    rx_tbl[rsa->sa_ind].salt = rsa->salt;

    return;
}

__STATIC_FORCEINLINE
void SA_TX_Insert(MSG_TxSAMsgTypeDef *tsa)
{
    int i;

    for (i = 0; i < 4; i++)
        tx_tbl[tsa->sa_ind].key[i] = tsa->key[i];
    tx_tbl[tsa->sa_ind].salt = tsa->salt;

    return;
}

__STATIC_FORCEINLINE
void SA_ADD(intptr_t msg, int direction)
{
    switch (direction) {
    case INBOUND: {
        MSG_RxSAMsgTypeDef *rsa = (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

        SA_RX_Insert(rsa);
        /* hash the new entry for faster search in Rx path */
        hash_add(rx_sa_list, &rx_tbl[rsa->sa_ind].hlist, rsa->spi);

        /* done */
        *(uint32_t *)msg = MSG_RX_SA_ADD_DONE;
    }
    break;
    case OUTBOUND: {
        MSG_TxSAMsgTypeDef *tsa = (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

        SA_TX_Insert(tsa);
        /* done */
        *(uint32_t *)msg = MSG_TX_SA_ADD_DONE;
    }
    break;
    }

    IPSec_Send_Msg(msg);
    return;
}

__STATIC_FORCEINLINE
void SA_DEL(intptr_t msg, int direction)
{
    switch (direction) {
    case INBOUND: {
        MSG_RxSAMsgTypeDef *rsa = (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

        SA_RX_Insert(rsa);
        hash_del(&rx_tbl[rsa->sa_ind].hlist);

        /* done */
        *(uint32_t *)msg = MSG_RX_SA_DEL_DONE;
    }
    break;
    case OUTBOUND: {
        MSG_TxSAMsgTypeDef *tsa = (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

        SA_TX_Insert(tsa);
        /* done */
        *(uint32_t *)msg = MSG_TX_SA_DEL_DONE;
    }
    break;
    }

    IPSec_Send_Msg(msg);
    return;
}

__STATIC_FORCEINLINE
RX_SATypedef *Find_RX_SA(uint32_t *daddr, uint32_t spi, int ip4)
{
    RX_SATypedef *rsa, *ret = NULL;

    hash_for_each_possible(rx_sa_list, rsa, hlist, spi) {
        if (spi == rsa->spi &&
            ((ip4 && *daddr == ip_tbl[rsa->iptbl_ind].ipaddr[0]) ||
             (!ip4 && !memcmp(daddr, ip_tbl[rsa->iptbl_ind].ipaddr,
                              sizeof(ip_tbl[rsa->iptbl_ind].ipaddr))))) {
            ret = rsa;
            break;
        }
    }

    return ret;
}

__STATIC_FORCEINLINE
uint16_t TCP_Cksum(void)
{
    return 0;
}

__STATIC_FORCEINLINE
uint16_t UDP_Cksum(void)
{
    /* FIXME */
    return 0;
}

__STATIC_FORCEINLINE
void IPSec_CallbackInternal(intptr_t callbackTag,
                            bool verifyResult)
{
    return;
}

void IPSec_CallbackFn(intptr_t callbackTag,
                      int status,
                      bool verifyResult)
{
#ifdef DEBUG
    bool ret = false;

    ret = (status == STATUS_SUCCESS) && verifyResult ? true : false;
    if (__rv_unlikely(ret == false))
        printf("ERROR: IPSec failed (status %d, verifyResult %d)\n",
               status, verifyResult);
#endif

    switch (*(uint32_t *)callbackTag) {
    case MSG_ENC:
        *(uint32_t *)callbackTag = MSG_ENC_DONE;
        break;
    case MSG_DEC:
        IPSec_CallbackInternal(callbackTag, verifyResult);
        *(uint32_t *)callbackTag = MSG_DEC_DONE;
        break;
    default:
        printf("Bogus MSG type \n");
        break;
    }

    IPSec_Send(callbackTag);
    return;
}

/*
 * Encapsulating Security Protocol Processing
 * Transport Mode Processing
 *
 *            BEFORE APPLYING ESP
 *        ----------------------------
 *   IPv4 |orig IP hdr  |     |      |
 *        |(any options)| TCP | Data |
 *        ----------------------------
 *
 *            AFTER APPLYING ESP
 *        -------------------------------------------------
 *   IPv4 |orig IP hdr  | ESP |     |      | ESP     | ESP|
 *        |(any options)| Hdr | TCP | Data | Trailer | ICV|
 *        -------------------------------------------------
 *                            |<---- encryption ---->|
 *                      |<-------- integrity ------->|
 *
 *  Crypto engines:
 *       For ESP encryption and authentication: AES-128-GCM (128-bit key)
 */
__STATIC_FORCEINLINE
void ESP_TRANSPORT(frameTableTypeDef *ftable)
{
    return;
}

__STATIC_FORCEINLINE
void IPSec_Encryption(intptr_t msg)
{
    return;
}

__STATIC_FORCEINLINE
void IPSec_Decryption(intptr_t msg)
{
    int i = 0, ret;
    frameTableTypeDef ftable;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);
    NIC_RXDescTypeDef *desc = dec->desc;

    ftable.direction    = INBOUND;
    ftable.nents        = dec->segs;
    ftable.containedLen = GET_FIELD(desc->desc6, 16, 0xffff);

    do {
        ftable.frame[i].data    = (uint8_t *)(intptr_t)desc->desc9;
        ftable.frame[i].dataLen = GET_FIELD(desc->desc0, 0, 0x3fff);
        desc = (NIC_RXDescTypeDef *)(intptr_t)desc->desc11;
    } while (++i < dec->segs);
    ftable.frame[i - 1].dataLen -= 4; /* CRC */

    ret = Dissect_Frame(&ftable);
    if ((!!ret))
        goto drop;

#if 0
    /* Main Features */
    ESP_TRANSPORT(&ftable,
                  Find_RX_SA(ftable.frame[0].ip.dst,
                             ntoh32(ftable.frame[0].esp.hdr),
                             ftable.frame[0].eth.type == AT_IPv4 ? 1 : 0)
                 );
#endif
    return;

drop:
    *(uint32_t *)msg = MSG_DEC_DONE;
    SET_FIELD(dec->desc->desc8, ret, 1, 0x3);
    IPSec_Send_Msg(msg);
    return;
}

/* as quickly as you can,
 * Do not care about whether it looks ugly
 */
void IPSec_Loop(intptr_t msg)
{
#ifdef DEBUG
    Dump_MSG(msg);
#endif

    switch (*(uint32_t *)msg) {
    case MSG_RX_SA_ADD:
        SA_ADD(msg, INBOUND);
        break;
    case MSG_TX_SA_ADD:
        SA_ADD(msg, OUTBOUND);
        break;
    case MSG_RX_SA_DEL:
        SA_DEL(msg, INBOUND);
        break;
    case MSG_TX_SA_DEL:
        SA_DEL(msg, OUTBOUND);
        break;
    case MSG_ENC:
        IPSec_Encryption(msg);
        break;
    case MSG_DEC:
        IPSec_Decryption(msg);
        break;
    default:
        break;
    }

    return;
}
