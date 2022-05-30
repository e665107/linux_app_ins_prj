
#ifdef TEST

#include "msg.h"
#include "priv.h"
#include "ipsec.h"
#include "sw_timer.h"

uint32_t zerobuf[4] = {0, 0, 0, 0};

uint32_t K[4] = {0xbbaa9988, 0xffeeddcc, 0x33221100, 0x77665544};

uint32_t IP[4] = {0x0a000002, 0xdeadbeef, 0xdeadbeef, 0xdeadbeef};

unsigned char skbuf[] = {
    0xd2, 0xf9, 0x79, 0xf8, 0x82, 0xa1, 0xe2, 0x72, 0xc1, 0x2b, 0x87, 0xe5, 0x08, 0x00, 0x45, 0x00,
    0x00, 0x64, 0xf1, 0x74, 0x40, 0x00, 0x40, 0x32, 0x34, 0xf1, 0x0a, 0x00, 0x00, 0x02, 0x0a, 0x00,
    0x00, 0x01, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x01, 0x5a, 0x34, 0xa5, 0x4a, 0xf0, 0xc2,
    0x90, 0x35, 0xb1, 0x3e, 0x8c, 0xd1, 0xa2, 0xc6, 0x42, 0x88, 0x00, 0x00, 0x00, 0x00, 0xa0, 0x02,
    0xfa, 0xf0, 0x8a, 0xbe, 0x00, 0x00, 0x02, 0x04, 0x05, 0xb4, 0x04, 0x02, 0x08, 0x0a, 0x7a, 0x4d,
    0x10, 0xa3, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x03, 0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x06, 0x06, 0x75, 0x53, 0x33, 0x3f, 0x5a, 0x01, 0x9d, 0x1a, 0xe9, 0xd1, 0xad, 0x49, 0x62, 0xb3,
    0xc0, 0x62,
};

unsigned char skbuf_rx[] = {
    0xe2, 0x72, 0xc1, 0x2b, 0x87, 0xe5, 0xd2, 0xf9,
    0x79, 0xf8, 0x82, 0xa1, 0x08, 0x00, 0x45, 0x00,
    0x00, 0x64, 0x00, 0x00, 0x40, 0x00, 0x40, 0x32,
    0x26, 0x66, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00,
    0x00, 0x02, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00,
    0x00, 0x01, 0x1e, 0xd0, 0xa0, 0xe2, 0x3d, 0x4a,
    0xbd, 0x34, 0x2c, 0xdf, 0xe4, 0x49, 0xbd, 0x92,
    0x7a, 0xa2, 0x2d, 0x94, 0xf7, 0xf4, 0x5f, 0x11,
    0x31, 0xea, 0xdd, 0x79, 0x92, 0xd3, 0x54, 0x71,
    0x7d, 0x5f, 0x7d, 0xec, 0xee, 0x02, 0xa9, 0x5a,
    0x5d, 0x14, 0x39, 0x36, 0x83, 0x9f, 0xb3, 0x44,
    0x52, 0x73, 0xa0, 0xb1, 0xe2, 0x06, 0x45, 0x19,
    0x06, 0x2c, 0x18, 0x06, 0x59, 0xce, 0x98, 0x4a,
    0x57, 0x78, 0x28, 0xca, 0x84, 0x42, 0xa2, 0xe1,
    0xdd, 0x4a, 0xaa, 0xbb, 0xcc, 0xdd
};

struct SA_TX_TestCase {
    int type;
    uint32_t saInd;
    const uint32_t *key;
    uint32_t salt;
} SA_TX_TestCases[] = {
    {
        .type      = MSG_TX_SA_ADD,
        .saInd     = 0,
        .key       = K,
        .salt      = 0xdeadbeef,
    },
    {
        .type      = MSG_TX_SA_DEL,
        .saInd     = 0,
        .key       = zerobuf,
        .salt      = 0,
    },
    { 0 }
};

struct SA_RX_TestCase {
    int type;
    uint32_t saInd;
    uint32_t spi;
    const uint32_t *ip;
    const uint32_t *key;
    uint32_t salt;
    uint32_t iptblInd;
} SA_RX_TestCases[] = {
    {
        .type      = MSG_RX_SA_ADD,
        .saInd     = 0,
        .spi       = 0x00001000,
        .ip        = IP,
        .key       = K,
        .salt      = 0xffeeddcc,
        .iptblInd  = 0,
    },
    {
        .type      = MSG_RX_SA_DEL,
        .saInd     = 0,
        .spi       = 0,
        .ip        = zerobuf,
        .key       = zerobuf,
        .salt      = 0xffeeddcc,
        .iptblInd  = 0,
    },
    { 0 }
};

struct ENC_TestCase {
    int type;
    unsigned char *plaintext;
    uint32_t psize;
    uint32_t l2Len;
    uint32_t l3Len;
    uint32_t l4Len;
    bool     tcpCksum;
    uint32_t saInd;
    uint32_t espLen;
} ENC_TestCases[] = {
    {
        .type      = MSG_ENC,
        .plaintext = skbuf,
        .psize     = sizeof(skbuf),
        .l2Len     = 14,
        .l3Len     = 20,
        .l4Len     = 80,
        .tcpCksum  = true,
        .saInd     = 0,
        .espLen    = 18,
    },
    { 0 }
};

typedef struct{
    uint32_t seg_len;
    unsigned char *seg_buf;
}String_TypeDef;

struct DEC_TestCase {
    int type;
    unsigned char *plaintext;
    uint32_t psize;
    uint32_t segs;
    String_TypeDef segment[6];
    uint32_t l2Len;
    uint32_t l3Len;
    uint32_t l4Len;
    bool     tcpCksum;
    uint32_t saInd;
    uint32_t espLen;
} DEC_TestCases[] = {
#if 0
    {
        .type      = MSG_DEC,
        .plaintext = skbuf_rx,
        .psize     = sizeof(skbuf_rx) - 4,
        .segs      = 1,
        .segment = {
            {
                .seg_len = sizeof(skbuf_rx),
                .seg_buf = skbuf_rx,
            },
        },
        .l2Len     = 14,
        .l3Len     = 20,
        .l4Len     = 80,
        .tcpCksum  = true,
        .saInd     = 0,
        .espLen    = 18,
    },
#endif
#if 0
    {
        .type      = MSG_DEC,
        .plaintext = skbuf_rx,
        .psize     = sizeof(skbuf_rx) - 4,
        .segs      = 2,
        .segment = {
            {
                .seg_len = 112,
                .seg_buf = skbuf_rx,
            },
            {
                .seg_len = sizeof(skbuf_rx) - 112,
                .seg_buf = skbuf_rx + 112,
            }
        },
        .l2Len     = 14,
        .l3Len     = 20,
        .l4Len     = 80,
        .tcpCksum  = true,
        .saInd     = 0,
        .espLen    = 18,
    },
#endif
#if 0
    {
        .type      = MSG_DEC,
        .plaintext = skbuf_rx,
        .psize     = sizeof(skbuf_rx) - 4,
        .segs      = 3,
        .segment = {
            {
                .seg_len = 50,
                .seg_buf = skbuf_rx,
            },
            {
                .seg_len = 50,
                .seg_buf = skbuf_rx + 50,
            },
            {
                .seg_len = sizeof(skbuf_rx) - 100,
                .seg_buf = skbuf_rx + 100,
            },
        },
        .l2Len     = 14,
        .l3Len     = 20,
        .l4Len     = 80,
        .tcpCksum  = true,
        .saInd     = 0,
        .espLen    = 18,
    },
#endif
#if 1
    {
        .type      = MSG_DEC,
        .plaintext = skbuf_rx,
        .psize     = sizeof(skbuf_rx) - 4,
        .segs      = 6,
        .segment = {
            {
                .seg_len = 50,
                .seg_buf = skbuf_rx,
            },
            {
                .seg_len = 10,
                .seg_buf = skbuf_rx + 50,
            },
            {
                .seg_len = 10,
                .seg_buf = skbuf_rx + 60,
            },
            {
                .seg_len = 10,
                .seg_buf = skbuf_rx + 70,
            },
            {
                .seg_len = 25,
                .seg_buf = skbuf_rx + 80,
            },
            {
                .seg_len = sizeof(skbuf_rx) - 105,
                .seg_buf = skbuf_rx + 105,
            },
        },
        .l2Len     = 14,
        .l3Len     = 20,
        .l4Len     = 80,
        .tcpCksum  = true,
        .saInd     = 0,
        .espLen    = 18,
    }
#endif
};

MSG_TypeDef gMSG;
TX_DescTypeDef txDesc;
NIC_RXDescTypeDef rxDesc[6];
void sample_SATest(void)
{
    int i;
    const struct SA_TX_TestCase *t1;
    const struct SA_RX_TestCase *t2;

    for (t1 = SA_TX_TestCases; t1->type; t1++) {

        memset(&gMSG, 0, sizeof(MSG_TypeDef));
        gMSG.type = t1->type;
        gMSG.u.txsa_msg.sa_ind = t1->saInd;
        gMSG.u.txsa_msg.salt = t1->salt;
        for (i = 0; i < 4; i++)
            gMSG.u.txsa_msg.key[i] = t1->key[3 - i];

        IPSec_Loop((intptr_t)&gMSG);
    }

    for (t2 = SA_RX_TestCases; t2->type; t2++) {

        memset(&gMSG, 0, sizeof(MSG_TypeDef));
        gMSG.type = t2->type;
        gMSG.u.rxsa_msg.sa_ind = t2->saInd;
        gMSG.u.rxsa_msg.spi = t2->spi;
        for (i = 0; i < 4; i++)
            gMSG.u.rxsa_msg.ipaddr[i] = t2->ip[3 - i];
        for (i = 0; i < 4; i++)
            gMSG.u.rxsa_msg.key[i] = t2->key[3 - i];
        gMSG.u.rxsa_msg.salt = t2->salt;
        gMSG.u.rxsa_msg.iptbl_ind = t2->iptblInd;

        IPSec_Loop((intptr_t)&gMSG);
    }

    return;
}

void sample_EncTest(void)
{
    const struct ENC_TestCase *t;

    for (t = ENC_TestCases; t->type; t++) {

        memset(&gMSG, 0, sizeof(MSG_TypeDef));
        gMSG.type = t->type;
        SET_FIELD(txDesc.desc0, t->psize, 0, 0x1ffff);  /* set tx buf size */
        SET_FIELD(txDesc.desc5, t->l2Len, 0, 0x7f);     /* set L2LEN */
        SET_FIELD(txDesc.desc5, t->l3Len, 7, 0x1ff);    /* set L3LEN */
        SET_FIELD(txDesc.desc5, t->l4Len, 16, 0xff);    /* set L4LEN */
        if (t->tcpCksum)
            SET_FLAG(txDesc.desc1, 2);                  /* set TCP checksum offload enable */
        SET_FLAG(txDesc.desc8, 0);                      /* set offload */
        SET_FLAG(txDesc.desc8, 20);                     /* set ipsec type=esp */
        SET_FIELD(txDesc.desc8, t->saInd, 1, 0x3ff);    /* set IPSec sa index */
        SET_FIELD(txDesc.desc8, t->espLen, 11, 0x1ff);  /* set IPSec esp len */
        gMSG.u.enc_msg.desc = &txDesc;
        gMSG.u.enc_msg.frm = t->plaintext;

        IPSec_Loop((intptr_t)&gMSG);
    }

    return;
}

#if 1
void sample_DecTest(void)
{
    uint32_t i;
    const struct DEC_TestCase *t;
    NIC_RXDescTypeDef *desc;
    for (t = DEC_TestCases; t->type; t++) {
        memset(&gMSG, 0, sizeof(MSG_TypeDef));
        SET_FIELD(rxDesc[0].desc6, t->psize, 16, 0xffff);  /* set rx buf size */
        gMSG.u.dec_msg.segs = t->segs;
        gMSG.type = t->type;

        for (i = 0; i < t->segs - 1; ++i) {
            rxDesc[i].desc11 = (intptr_t)(&rxDesc[i+1]);
        }

        for (i = 0; i < t->segs; ++i) {
            SET_FIELD(rxDesc[i].desc0, t->segment[i].seg_len, 0, 0x1ffff);  /* set rx seg size */
            rxDesc[i].desc9 = (intptr_t)t->segment[i].seg_buf;
        }

        gMSG.u.dec_msg.desc = (NIC_RXDescTypeDef * )rxDesc;
        printf("Dec msg segs:%d\n", t->segs);
        IPSec_Loop((intptr_t)&gMSG);
    }
}
#endif

#if 0
void sample_DecTest(void)
{
    uint32_t i;
    const struct DEC_TestCase *t;

    for (t = DEC_TestCases; t->type; t++) {
        NIC_RXDescTypeDef *desc = rxDesc;

        memset(&gMSG, 0, sizeof(MSG_TypeDef));
        SET_FIELD(rxDesc[0].desc6, t->psize, 16, 0xffff);  /* set rx buf size */
        gMSG.u.dec_msg.segs = t->segs;
        gMSG.type = t->type;

        desc[0].desc11 = (intptr_t)(desc + 1);

        for (i = 0; i < t->segs; i++) {
            SET_FIELD(desc[i].desc0, t->segment[i].seg_len, 0, 0x1ffff);
            desc[i].desc9 = (intptr_t)t->segment[i].seg_buf;
            desc[i].desc11 = (intptr_t)(desc + 1);
        }

        gMSG.u.dec_msg.desc = (NIC_RXDescTypeDef *)desc;
        IPSec_Loop((intptr_t)&gMSG);
    }
}
#endif
void sampleTest(void)
{
    /* sample_SATest(); */
    /* sample_EncTest(); */
    sample_DecTest();
    return;
}

#endif
