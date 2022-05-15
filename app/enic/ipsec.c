
#include <stdint.h>
#include <string.h>

#include "msg.h"
#include "ipc_slave.h"
#include "frame.h"
#include "hashtable.h"
#include "crypto.h"
#include "packet_frame.h"
#include "in_cksum.h"
#include "inet.h"
#include "common.h"
#ifdef OUT_OF_ORDER
#include "fifo.h"
#endif

#define DEBUG
#define IPSEC_MAX_SA_COUNT      32
#define IPSEC_MAX_RX_IP_COUNT   32

#define MSG_HEADER      sizeof(uint64_t)

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
    {
        pos += snprintf(dest + pos, destLen - pos,
                        "%08x",
                        src[i]);
    }

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
                FrameTypeDef frame;
                MSG_ENCMsgTypeDef *enc =
                    (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_ENC:working\n");

                frame.skBuf.data    = enc->frm;
                frame.skBuf.dataLen = GET_FIELD(enc->desc->desc0, 0, 0x1ffff);
                frame.ipsec.direction = OUTBOUND;

                printf("xfrm encryption (%p) \n", (void *)enc->frm);
                DUMPL("SKB", frame.skBuf.data, frame.skBuf.dataLen);
                Dissect_Frame(&frame);
            }
            break;
        case MSG_DEC:
            {
                FrameTypeDef frame;
                MSG_DECMsgTypeDef *dec =
                        (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

                printf("MSG_DEC:working\n");

                frame.skBuf.data    = dec->desc->desc9;
                frame.skBuf.dataLen = GET_FIELD(dec->desc->desc0, 0, 0x1ffff);
                frame.ipsec.direction = INBOUND;

                printf("xfrm decryption (%p) \n", (void *)dec->desc->desc9);
                DUMPL("SKB", frame.skBuf.data, frame.skBuf.dataLen);
                Dissect_Frame(&frame);
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
                MSG_ENCMsgTypeDef *enc =
                    (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);
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
void TCP_UDP_Cksum(FrameTypeDef *frame)
{
    VecTypeDef cksumVec[4];
    uint32_t phdr[2];
    AddressTypeDef src;
    AddressTypeDef dst;
    uint16_t computedCksum;

    setAddress(&src,
               frame->ip.addressType,
               4,
               frame->skBuf.data + frame->eth.len + IPH_SRC);
    setAddress(&dst,
               frame->ip.addressType,
               4,
               frame->skBuf.data + frame->eth.len + IPH_DST);

    /* Set up the fields of the pseudo-header. */
    SET_CKSUM_VEC_PTR(cksumVec[0], (const uint8_t *)src.data, src.len);
    SET_CKSUM_VEC_PTR(cksumVec[1], (const uint8_t *)dst.data, dst.len);
    switch (frame->ip.addressType)
    {
        case AT_IPv4:
            phdr[0] = htonl((IP_PROTO_TCP << 16) + frame->ipsec.espPayloadLen);
            SET_CKSUM_VEC_PTR(cksumVec[2], (const uint8_t *)phdr, 4);
            break;
        case AT_IPv6:
            break;
        default:
            /* runs only atop IPv4 and IPv6.... */
            goto drop;
    }
    SET_CKSUM_VEC_PTR(cksumVec[3],
                      frame->ipsec.espPayload,
                      frame->ipsec.espPayloadLen);
    computedCksum = inCksum(cksumVec, 4); /* htonl */

    *(uint16_t *)(frame->skBuf.data + frame->eth.len + IPH_SUM) =
        htons(computedCksum);

#ifdef DEBUG
    printf("TCP/UDP checksum: 0x%04x \n", htons(computedCksum));
#endif
    return;

drop:
    return;
}

void IPSec_callbackFn(intptr_t callbackTag)
{
    switch (*(uint32_t *)callbackTag)
    {
        case MSG_ENC:
            *(uint32_t *)callbackTag = MSG_ENC_DONE;
            break;
        case MSG_DEC:
            /* TCP/UDP checksum */
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
void ESP_TRANSPORT(FrameTypeDef *frame, int direction, void *sa)
{
    const uint32_t *key;
    const uint32_t *salt;
    FlatBufferTypedef buf[6];
    BufferListTypedef bufList;
    CY_Sym_OpDataTypedef opData;
    IPSecTypeDef *ipsec = &frame->ipsec;
    espHdrPacket *espHdr = NULL;
    /* iphdr *ip4 = NULL; */
    /* void *daddr; */
    /* bool ip4; */
#if 0
    switch (direction) {
        case INBOUND:        /* decryption */
            espHdr = ipsec->espBuf;
            if(frame->addressType == AT_IPv4)
            {
                ip4 = (struct iphdr *)(frame->skBuf.data +  frame->L2LEN);
                ip4 = TRUE;
                daddr = &ip4->daddr;
            }
            if(NULL == Find_RX_SA(daddr, espHdr->spi, ip4))
                return;
    }
#endif
    switch (direction)
    {
        case INBOUND:        /* decryption */
            {
                RX_SATypedef *rsa = (RX_SATypedef *)sa;

                /* buffer list */
                opData.direction   = INBOUND;
                key = rsa->key;
                salt = &rsa->salt;
            }
            break;
        case OUTBOUND:       /* encryption */
            {
                TX_SATypedef *tsa = (TX_SATypedef *)sa;

                buf[0].data        = ipsec->espPayload;
                buf[0].dataLen     = ipsec->espPayloadLen + ipsec->espTrailerLen;
                bufList.numBuffers = 1;
                bufList.Buffers    = buf;

                opData.direction   = OUTBOUND;
                key = tsa->key;
                salt = &tsa->salt;
            }
            break;
    }

    /* aad */
    opData.aad       = ipsec->espBuf;
    opData.aadLen    = ipsec->espHdrLen;
    /* digest */
    opData.digest    = ipsec->espICV;
    opData.digestLen = ipsec->espICVLen;
    /* key */
    opData.key       = (uint8_t *)key;
    opData.keyLen    = 16;
    /* Noce format, must be twelve octets */
    opData.ivLen     = IV_MAX;
    memcpy(opData.iv, salt, 4);
    memcpy(opData.iv + 4, ipsec->espBuf + ipsec->espHdrLen, 8);

#ifdef OUT_OF_ORDER
    kfifo_put(&out_of_order, frame->opaque);
#endif
    /* perform */
    /* CY_SymPerformOp(IPSec_callbackFn, frame->opaque, */
    /*                         &opData, &bufList, &bufList); */
    return;
}

__STATIC_FORCEINLINE
void IPSec_Encryption(intptr_t msg)
{
    FrameTypeDef frame;
    MSG_ENCMsgTypeDef *enc = (MSG_ENCMsgTypeDef *)(msg + MSG_HEADER);

    if ((!!!GET_FLAG(enc->desc->desc8, 0)))
        goto done;

    switch (GET_FIELD(enc->desc->desc8, 20, 0x1))
    {
        case 1:                  /* ESP */
            {
                IPSecTypeDef *ipsec  = &frame.ipsec;

                frame.skBuf.data     = enc->frm;
                frame.skBuf.dataLen  = GET_FIELD(enc->desc->desc0, 0, 0x1ffff);
                frame.eth.len        = GET_FIELD(enc->desc->desc5, 0, 0x7f);
                frame.ip.addressType = AT_IPv4;        /* default */
                frame.ip.len         = GET_FIELD(enc->desc->desc5, 7, 0x1ff);

                ipsec->espBuf        = frame.skBuf.data +
                                       frame.eth.len +
                                       frame.ip.len;
                ipsec->espBufLen     = GET_FIELD(enc->desc->desc5, 16, 0xff);
                ipsec->espHdrLen     = 8;
                ipsec->espIVLen      = 8;
                ipsec->espTrailerLen = 2;
                ipsec->espPayload    = ipsec->espBuf +
                                       ipsec->espHdrLen +
                                       ipsec->espIVLen;
                ipsec->espPayloadLen = ipsec->espBufLen -
                                       ipsec->espHdrLen -
                                       ipsec->espIVLen -
                                       GET_FIELD(enc->desc->desc8, 11, 0x1ff);
                ipsec->espICV        = ipsec->espBuf +
                                       ipsec->espHdrLen +
                                       ipsec->espIVLen +
                                       ipsec->espPayloadLen +
                                       ipsec->espTrailerLen;
                ipsec->espICVLen     = GET_FIELD(enc->desc->desc8, 11, 0x1ff) -
                                       ipsec->espTrailerLen;

                /* Cross Features */
                if ((!!GET_FLAG(enc->desc->desc1, 2)) ||
                        (!!GET_FLAG(enc->desc->desc1, 3)))
                {
                    /* We haven't turned checksum checking off; checksum it. */
                    TCP_UDP_Cksum(&frame);
                }

                /* Main Features */
                frame.opaque = msg;
                ESP_TRANSPORT(&frame,
                              OUTBOUND,
                              &tx_tbl[GET_FIELD(enc->desc->desc8, 1, 0x3ff)]);
            }
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

__STATIC_FORCEINLINE
void IPSec_Decryption(intptr_t msg)
{
    int ret;
    FrameTypeDef frame;
    MSG_DECMsgTypeDef *dec = (MSG_DECMsgTypeDef *)(msg + MSG_HEADER);

    frame.skBuf.data = dec->desc->desc9;
    ret = Dissect_Frame(&frame);
    if ((!!ret))
        goto drop;

    /* Main Features */
    ESP_TRANSPORT(&frame,
                  INBOUND,
                  Find_RX_SA(frame.ip.ipDst,
                             *(uint32_t *)frame.ipsec.espBuf,
                             frame.ip.addressType == AT_IPv4 ? 1 : 0)
                 );
    return;

drop:
    *(uint32_t *)msg = MSG_ENC_DONE;
    SET_FIELD(dec->desc[0].desc8, ret, 1, 0x3);
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

    Dump_MSG_UINT(buf, ARRAY_SIZE(rsa->key) * 8 + 2 + 1,
                  rsa->key, ARRAY_SIZE(rsa->key));
    printf("xfrm state ip table index %u spi 0x%08x salt 0x%08x \n",
           rsa->iptbl_ind, rsa->spi, rsa->salt);

}
