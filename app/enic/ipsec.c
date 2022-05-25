-
#include <stdint.h>
#include <string.h>

#include "common.h"
#include "msg.h"
#include "ipc_slave.h"
#include "frame.h"
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

typedef struct
{
    uint32_t ipaddr[4];
} RX_IP_SATypedef;

typedef struct
{
    struct hlist_node hlist;
    uint32_t spi;
    uint32_t iptbl_ind;
    uint32_t key[4];
    uint32_t salt;
} RX_SATypedef;

typedef struct
{
    uint32_t key[4];
    uint32_t salt;
} TX_SATypedef;

uint32_t Cross_Features = 0;
__exdata RX_IP_SATypedef ip_tbl[IPSEC_MAX_RX_IP_COUNT];
__exdata RX_SATypedef rx_tbl[IPSEC_MAX_SA_COUNT];
__exdata TX_SATypedef tx_tbl[IPSEC_MAX_SA_COUNT];
__exdata DEFINE_HASHTABLE(rx_sa_list, 10);

#ifdef OUT_OF_ORDER
DECLARE_KFIFO(out_of_order, intptr_t, 128);
#endif

#ifdef DEBUG
int Dump_MSG_UINT(char *dest, int destLen,
                  const uint32_t *src, int srcLen)
{
    int i, pos = 0;

    for (i = 0; i < srcLen; i++)
        pos += snprintf(dest + pos, destLen - pos, "%08x", src[i]);

    return pos;
}

void Dump_MSG(intptr_t msg)
{
    switch (*(uint32_t *)msg)
    {
        case MSG_RX_SA_ADD:
            {
                char buf[64];
                MSG_RxSAMsgTypeDef *rsa =
                        (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_RX_SA_ADD:working\n");

                Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->ipaddr) * 8 + 2 + 1,
                              rsa->ipaddr, ARRAY_SIZE(rsa->ipaddr));
                printf("xfrm ip add index %u addr 0x%s\n",
                       rsa->iptbl_ind, buf);

                Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->key) * 8 + 2 + 1,
                              rsa->key, ARRAY_SIZE(rsa->key));
                printf("xfrm state add index %u spi 0x%08x salt 0x%08x dec 0x%s\n",
                       rsa->sa_ind, rsa->spi, rsa->salt, buf);

            }
            break;
        case MSG_TX_SA_ADD:
            {
                char buf[64];
                MSG_TxSAMsgTypeDef *tsa =
                        (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_TX_SA_ADD:working\n");

                Dump_MSG_UINT(buf, ARRAY_SIZE(tsa->key) * 8 + 2 + 1,
                              tsa->key, ARRAY_SIZE(tsa->key));

                printf("xfrm state add index %u salt 0x%08x enc 0x%s\n",
                       tsa->sa_ind, tsa->salt, buf);
            }
            break;
        case MSG_RX_SA_DEL:
            {
                char buf[64];
                MSG_RxSAMsgTypeDef *rsa =
                        (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_RX_SA_DEL:working\n");

                Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->ipaddr) * 8 + 2 + 1,
                              rsa->ipaddr, ARRAY_SIZE(rsa->ipaddr));
                printf("xfrm ip add index %u addr 0x%s\n",
                       rsa->iptbl_ind, buf);

                Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->key) * 8 + 2 + 1,
                              rsa->key, ARRAY_SIZE(rsa->key));
                printf("xfrm state add index %u spi 0x%08x salt 0x%08x dec 0x%s\n",
                       rsa->sa_ind, rsa->spi, rsa->salt, buf);
            }
            break;
        case MSG_TX_SA_DEL:
            {
                char buf[64];
                MSG_TxSAMsgTypeDef *tsa =
                        (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_TX_SA_DEL:working\n");

                Dump_MSG_UINT(buf, ARRAY_SIZE(tsa->key) * 8 + 2 + 1,
                              tsa->key, ARRAY_SIZE(tsa->key));

                printf("xfrm state del index %u salt 0x%08x enc 0x%s\n",
                       tsa->sa_ind, tsa->salt, buf);

            }
            break;
        case MSG_ENC:
            {
                skbufTypeDef skb;
                Packet_InfoTypeDef pinfo;
                MSG_ENCMsgTypeDef *enc = (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);

                skb.data        = enc->frm;
                skb.dataLen     = GET_FIELD(enc->desc->desc0, 0, 0x1ffff);
                pinfo.direction = OUTBOUND;

                printf("xfrm encryption (%p) \n", (void *)enc->frm);
                DUMPL("SKB", skb.data, skb.dataLen);
                Dissect_Frame(&skb, &pinfo);
            }
            break;
        case MSG_DEC:
            {
                skbufTypeDef skb;
                Packet_InfoTypeDef pinfo;
                MSG_DECMsgTypeDef *dec =
                        (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_DEC:working\n");

                skb.data    = (uint8_t *)(intptr_t)dec->desc->desc9;
                skb.dataLen = GET_FIELD(dec->desc->desc0, 0, 0x3fff);
                pinfo.direction = INBOUND;
                pinfo.segs      = dec->segs;


                printf("xfrm decryption (%p) \n", (void *)dec->desc->desc9);
                DUMPL("SKB", skb.data, skb.dataLen);
                Dissect_Frame(&skb, &pinfo);
            }
            break;
        case MSG_RX_SA_ADD_DONE:
            break;
        case MSG_TX_SA_ADD_DONE:
            break;
        case MSG_RX_SA_DEL_DONE:
            break;
        case MSG_TX_SA_DEL_DONE:
            break;
        case MSG_ENC_DONE:
            {
                MSG_ENCMsgTypeDef *enc = (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);
                printf("xfrm encryption (%p) done\n", (void *)enc->frm);
            }
            break;
        case MSG_DEC_DONE:
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
    /* IPC_Msg_Send(msg); */
    return;
}

__STATIC_FORCEINLINE
void IPSec_Send(intptr_t msg)
{
#ifdef OUT_OF_ORDER
    intptr_t m;

    while (!kfifo_peek(&out_of_order, &m))
    {
        switch (*(uint32_t *)m)
        {
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
    switch (direction)
    {
        case INBOUND:
            {
                MSG_RxSAMsgTypeDef *rsa =
                        (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

                SA_RX_Insert(rsa);
                /* hash the new entry for faster search in Rx path */
                hash_add(rx_sa_list, &rx_tbl[rsa->sa_ind].hlist, rsa->spi);

                /* done */
                *(uint32_t *)msg = MSG_RX_SA_ADD_DONE;
            }
            break;
        case OUTBOUND:
            {
                MSG_TxSAMsgTypeDef *tsa =
                        (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

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
    switch (direction)
    {
        case INBOUND:
            {
                MSG_RxSAMsgTypeDef *rsa =
                        (MSG_RxSAMsgTypeDef *)(msg + MSG_HEADER);

                SA_RX_Insert(rsa);
                hash_del(&rx_tbl[rsa->sa_ind].hlist);

                /* done */
                *(uint32_t *)msg = MSG_RX_SA_DEL_DONE;
            }
            break;
        case OUTBOUND:
            {
                MSG_TxSAMsgTypeDef *tsa =
                        (MSG_TxSAMsgTypeDef *)(msg + MSG_HEADER);

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

    hash_for_each_possible(rx_sa_list, rsa, hlist, spi)
    {
        if (spi == rsa->spi &&
            ((ip4 && *daddr == ip_tbl[rsa->iptbl_ind].ipaddr[0]) ||
             (!ip4 && !memcmp(daddr, ip_tbl[rsa->iptbl_ind].ipaddr,
                              sizeof(ip_tbl[rsa->iptbl_ind].ipaddr)))))
        {
            ret = rsa;
            break;
        }
    }

    return ret;
}

__STATIC_FORCEINLINE
uint16_t TCP_Cksum(frameTableTypeDef *frameTable )
{
    VecTypeDef cksumVec[4];
    uint32_t phdr[2];
    AddressTypeDef src, dst;
    uint16_t computedCksum;

    setAddress(&src, pinfo->addressType, 4, skb->data + pinfo->ethLen + IPH_SRC);
    setAddress(&dst, pinfo->addressType, 4, skb->data + pinfo->ethLen + IPH_DST);

    /* Set up the fields of the pseudo-header. */
    SET_CKSUM_VEC_PTR(cksumVec[0], (const uint8_t *)src.data, src.len);
    SET_CKSUM_VEC_PTR(cksumVec[1], (const uint8_t *)dst.data, dst.len);
    switch (pinfo->addressType)
    {
        case AT_IPv4:
            phdr[0] = htonl((IP_PROTO_TCP << 16) + (pinfo->espPayloadLen[0] - pinfo->espTrailerLen - *(pinfo->espTrailer)));

            SET_CKSUM_VEC_PTR(cksumVec[2], (const uint8_t *)phdr, 4);
            break;
        case AT_IPv6:
            break;
        default:
            /* runs only atop IPv4 and IPv6.... */
            goto drop;
    }
    SET_CKSUM_VEC_PTR(cksumVec[3], pinfo->espPayload, pinfo->espPayloadLen[0] - pinfo->espTrailerLen - *(pinfo->espTrailer));
    printf("Padding Len:%u\n, espTrailerLen Len:%u\n, espPayload Len:%u\n",
           *(pinfo->espTrailer), pinfo->espTrailerLen, pinfo->espPayloadLen[0]);
    computedCksum = inCksum(cksumVec, 4);
#ifdef DEBUG
    printf("TCP checksum: 0x%04x \n", htons(computedCksum));
#endif
    return htons(computedCksum);

drop:
    return 0;
}

__STATIC_FORCEINLINE
uint16_t UDP_Cksum(frameTableTypeDef *frameTable)
{
    /* FIXME */
    return 0;
}

__STATIC_FORCEINLINE
void IPSec_CallbackInternal(intptr_t callbackTag,
                            bool verifyResult)
{
    skbufTypeDef skb;
    Packet_InfoTypeDef pinfo;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(callbackTag + MSG_HEADER);

    skb.data    = (uint8_t *)(intptr_t)dec->desc->desc9;
    skb.dataLen = GET_FIELD(dec->desc->desc0, 0, 0x3fff);
    Dissect_Frame(&skb, &pinfo);

    switch (pinfo.ipProto)
    {
        case IP_PROTO_TCP:
            if (Cross_Features & F_TCP_CKSUM)
                if (__rv_unlikely(*(uint16_t *)(skb.data + pinfo.ethLen + IPH_SUM) !=
                                  TCP_Cksum(&skb, &pinfo)))
                    SET_FLAG(dec->desc->desc1, 9);
            break;
        case IP_PROTO_UDP:
            if (Cross_Features & F_UDP_CKSUM)
                if (__rv_unlikely(*(uint16_t *)(skb.data + pinfo.ethLen + IPH_SUM) !=
                                  UDP_Cksum(&skb, &pinfo)))
                    SET_FLAG(dec->desc->desc1, 10);
            break;
    }

    /* AUTH */
    if (!verifyResult)
        SET_FIELD(dec->desc->desc8, SECERR_INVAL_AUTH, 1, 0x3);

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

    switch (*(uint32_t *)callbackTag)
    {
        case MSG_ENC:
            *(uint32_t *)callbackTag = MSG_ENC_DONE;
            break;
        case MSG_DEC:
            IPSec_CallbackInternal(callbackTag, verifyResult);
            *(uint32_t *)callbackTag = MSG_DEC_DONE;
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
void ESP_TRANSPORT(frameTableTypeDef *frameTable, void *sa)
{
    const uint32_t *key;
    const uint32_t *salt;
    uint32_t i;
    BufferListTypedef bufList;
    CY_Sym_OpDataTypedef opData;
    espHdrPacket *espHdr = NULL;

    if (__rv_unlikely(NULL == sa)) {
        printf("bad state \n");
        return;
    }

    switch (pinfo->direction) {
        case INBOUND: {      /* decryption */
            RX_SATypedef *rsa = (RX_SATypedef *)sa;

            key = rsa->key;
            salt = &rsa->salt;
            opData.direction   = INBOUND;
        }
            break;
        case OUTBOUND: {     /* encryption */
            TX_SATypedef *tsa = (TX_SATypedef *)sa;

            key = tsa->key;
            salt = &tsa->salt;
            opData.direction   = OUTBOUND;
        }
            break;
    }

    /* buffer list */
#if 0
    bufList.numBuffers = 1;
    bufList.buffers[0].data    = pinfo->espPayload;
    bufList.buffers[0].dataLen = pinfo->espPayloadLen;
#endif
    bufList.numBuffers = pinfo->segs;  /* consider change */

    sg_copy_buffer(frameTable, &bufList);
#if 0
    for (i = 0; i < bufList.numBuffers; i++) {
            bufList.buffers[i].data    = pinfo->espPayload[i];
            bufList.buffers[i].dataLen = pinfo->espPayloadLen[i];
    }
#endif
    /* aad */
    opData.aad       = pinfo->espHdr;/* not change */
    opData.aadLen    = pinfo->espHdrLen;/* not change */
    /* digest */
    opData.digest[0]    = pinfo->espICV[0];
    opData.digestLen[0] = pinfo->espICVLen[0];
    opData.digest[1]    = pinfo->espICV[1];
    opData.digestLen[1] = pinfo->espICVLen[1];

    /* key */
    opData.key       = (uint8_t *)key;
    opData.keyLen    = 16;
    /* Noce format, must be twelve octets */
    opData.ivLen     = IV_MAX;
    memcpy(opData.iv, salt, 4);
    memcpy(opData.iv + 4, pinfo->espIV, pinfo->espIVLen);

#ifdef OUT_OF_ORDER
    kfifo_put(&out_of_order, skb->opaque);
#endif
    /* perform */
    CY_SymPerformOp(IPSec_CallbackFn, skb->opaque, &opData, &bufList, &bufList);
    return;
}

__STATIC_FORCEINLINE
void IPSec_Encryption(intptr_t msg)
{
    skbufTypeDef skb;
    Packet_InfoTypeDef pinfo;
    MSG_ENCMsgTypeDef *enc = (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);

    if ((!!!GET_FLAG(enc->desc->desc8, 0)))
        goto done;

    switch (GET_FIELD(enc->desc->desc8, 20, 0x1))
    {
        case 1:                     /* ESP */
            skb.data            = enc->frm;
            skb.dataLen         = GET_FIELD(enc->desc->desc0, 0, 0x1ffff);
            skb.opaque          = msg;

            pinfo.direction     = OUTBOUND;
            pinfo.addressType   = AT_IPv4;        /* default */
            pinfo.ethLen        = GET_FIELD(enc->desc->desc5, 0, 0x7f);
            pinfo.ipLen         = GET_FIELD(enc->desc->desc5, 7, 0x1ff);

            /* get esp info */
            pinfo.espBufLen     = GET_FIELD(enc->desc->desc5, 16, 0xff);
            pinfo.espHdrLen     = 8;
            pinfo.espIVLen      = 8;
            pinfo.espTrailerLen = 2;
            pinfo.espICVLen[0]     = GET_FIELD(enc->desc->desc8, 11, 0x1ff) -
                                  pinfo.espTrailerLen;
            pinfo.espPayloadLen[0] = pinfo.espBufLen -
                                     pinfo.espHdrLen -
                                     pinfo.espIVLen -
                                     pinfo.espICVLen[0];
            pinfo.espBuf        = skb.data + pinfo.ethLen + pinfo.ipLen;
            pinfo.espHdr        = pinfo.espBuf;
            pinfo.espIV         = pinfo.espHdr + pinfo.espHdrLen;
            pinfo.espPayload[0]    = pinfo.espBuf +
                                  pinfo.espHdrLen +
                                  pinfo.espIVLen;
            pinfo.espTrailer    = pinfo.espBuf +
                                  pinfo.espHdrLen +
                                  pinfo.espIVLen +
                                  (pinfo.espPayloadLen[0] - pinfo.espTrailerLen);
            pinfo.espICV[0]        = pinfo.espBuf +
                                  pinfo.espHdrLen +
                                  pinfo.espIVLen +
                                  pinfo.espPayloadLen[0];

            /* Cross Features: We haven't turned checksum checking off; checksum it. */
            switch (*(pinfo.espTrailer + 1))
            {
                case IP_PROTO_TCP:
                    if (!!GET_FLAG(enc->desc->desc1, 2))
                        *(uint16_t *)(skb.data + pinfo.ethLen + IPH_SUM) =
                                TCP_Cksum(&skb, &pinfo);
                    break;
                case IP_PROTO_UDP:
                    if (!!GET_FLAG(enc->desc->desc1, 3))
                        *(uint16_t *)(skb.data + pinfo.ethLen + IPH_SUM) =
                                UDP_Cksum(&skb, &pinfo);
                    break;
            }

            /* Main Features */
            ESP_TRANSPORT(&skb, &pinfo, &tx_tbl[GET_FIELD(enc->desc->desc8, 1, 0x3ff)]);
            break;
        default:
            goto done;
    }

    return;

done:
    *(uint32_t *)msg = MSG_ENC_DONE;
    IPSec_Send_Msg(msg);
    return;
}

#if 0
__STATIC_FORCEINLINE
void IPSec_Decryption(intptr_t msg)
{
    int ret;
    skbufTypeDef skb;
    Packet_InfoTypeDef pinfo;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

    skb.data        = (uint8_t *)(intptr_t)dec->desc->desc9;
    skb.dataLen     = GET_FIELD(dec->desc->desc0, 0, 0x3fff);
    skb.opaque      = msg;
    pinfo.direction = INBOUND;

    ret = Dissect_Frame(&skb, &pinfo);
    /* if ((!!ret)) */
    /*     goto drop; */

    /* Main Features */
    ESP_TRANSPORT(&skb, &pinfo,
                  Find_RX_SA(pinfo.dst,
                             ntoh32(pinfo.espHdr),
                             pinfo.addressType == AT_IPv4 ? 1 : 0)
                  );
    return;

drop:
    *(uint32_t *)msg = MSG_ENC_DONE;
    SET_FIELD(dec->desc->desc8, ret, 1, 0x3);
    IPSec_Send_Msg(msg);
    return;
}
#endif


__STATIC_FORCEINLINE
void IPSec_Decryption(intptr_t msg)
{
    int ret;
    frameTableTypeDef frameTable;

    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

    frameTable.frame[0].origData        = (uint8_t *)(intptr_t)dec->desc->desc9;
    frameTable.frame[0].origDataLen     = GET_FIELD(dec->desc->desc0, 0, 0x3fff);
    frameTable.direction = INBOUND;
    frameTable.origNents = dec->segs;

    ret = Dissect_Frame(&frameTable);
    /* if ((!!ret)) */
    /*     goto drop; */

    /* Main Features */
    ESP_TRANSPORT(&frameTable,
                  Find_RX_SA(pinfo.dst,
                             ntoh32(pinfo.espHdr),
                             pinfo.addressType == AT_IPv4 ? 1 : 0)
                  );
    return;

drop:
    *(uint32_t *)msg = MSG_ENC_DONE;
    SET_FIELD(dec->desc->desc8, ret, 1, 0x3);
    IPSec_Send_Msg(msg);
    return;
}


/* as quickly as you can,
 * Do not care about whether it looks ugly */
void IPSec_Loop(intptr_t msg)
{
#ifdef DEBUG
    Dump_MSG(msg);
#endif
    switch (*(uint32_t *)msg)
    {
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


void Rx_SA_Find(uint32_t *daddr, uint32_t spi, int ip4)
{
    char buf[64];
    RX_SATypedef * rsa;
    printf("Rx_SA_Find:working\n");

    rsa = Find_RX_SA(daddr, spi,  ip4);
    if(NULL == rsa)
    {
        printf("Rx_SA_Find:found nothing\n");
        return;
    }

    printf("Rx_SA_Find:found matching\n");

    /* Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->key) * 8 + 2 + 1, */
    /*               rsa->key, ARRAY_SIZE(rsa->key)); */
    printf("xfrm state ip table index %u spi 0x%08x salt 0x%08x \n",
           rsa->iptbl_ind, rsa->spi, rsa->salt);

}
