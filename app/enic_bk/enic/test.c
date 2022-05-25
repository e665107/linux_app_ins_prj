
#include "test.h"
#ifdef TEST

#include "msg.h"
#include "priv.h"
#include "ipsec.h"
#include "sw_timer.h"

static void sample_SARxLookupTest(void)
{

    MSG_TypeDef msg;

    unsigned char key[16] = {
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xdd, 0xee, 0xff,
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
    };

    unsigned char salt[4] = {
        0xff, 0xee, 0xdd, 0xcc,
    };

    /* case3: rx sa add */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_ADD;
    msg.u.rxsa_msg.sa_ind = 0;
    msg.u.rxsa_msg.spi = 0x00001000;
    msg.u.rxsa_msg.ipaddr[0] = 0x0a000002;
    memcpy(msg.u.rxsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.rxsa_msg.salt, salt, sizeof(salt));
    msg.u.rxsa_msg.iptbl_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    Rx_SA_Find(msg.u.rxsa_msg.ipaddr,  msg.u.rxsa_msg.spi, 1);

    /* case4: rx sa del */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_DEL;
    msg.u.rxsa_msg.sa_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    Rx_SA_Find(msg.u.rxsa_msg.ipaddr,  msg.u.rxsa_msg.spi, 1);
    return;
}

static void sample_SATest(void)
{
    MSG_TypeDef msg;

    unsigned char key[16] = {
        0x88, 0x99, 0xaa, 0xbb,
        0xcc, 0xdd, 0xee, 0xff,
        0x00, 0x11, 0x22, 0x33,
        0x44, 0x55, 0x66, 0x77,
    };

    unsigned char salt[4] = {
        0xff, 0xee, 0xdd, 0xcc,
    };

    /* case1: tx sa add */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_TX_SA_ADD;
    msg.u.txsa_msg.sa_ind = 0;
    memcpy(msg.u.txsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.txsa_msg.salt, salt, sizeof(salt));
    IPSec_Loop((intptr_t)&msg);

    /* case2: tx sa del */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_TX_SA_DEL;
    msg.u.txsa_msg.sa_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    /* case3: rx sa add */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_ADD;
    msg.u.rxsa_msg.sa_ind = 0;
    msg.u.rxsa_msg.spi = 0x00001000;
    msg.u.rxsa_msg.ipaddr[0] = 0x0a000002;
    memcpy(msg.u.rxsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.rxsa_msg.salt, salt, sizeof(salt));
    msg.u.rxsa_msg.iptbl_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    /* case4: rx sa del */
    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_DEL;
    msg.u.rxsa_msg.sa_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    return;
}

static void sample_EncTest(void)
{
    unsigned char key[16] = {
        0xd6, 0x4a, 0x41, 0x04,
        0x88, 0x87, 0xaf, 0xdb,
        0xb1, 0x11, 0xe1, 0x4c,
        0x68, 0x4c, 0x82, 0x7d,
    };

    unsigned char salt[4] = {
        0xd0, 0xc6, 0x93, 0x3d,
    };

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

    MSG_TypeDef msg;
    TX_DescTypeDef desc;

    msg.type = MSG_TX_SA_ADD;
    msg.u.txsa_msg.sa_ind = 0;
    memcpy(msg.u.txsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.txsa_msg.salt, salt, sizeof(salt));
    IPSec_Loop((intptr_t)&msg);

    msg.type = MSG_ENC;
    SET_FIELD(desc.desc0, sizeof(skbuf), 0, 0x1ffff);   /* set tx buf size */
    SET_FIELD(desc.desc5, 14, 0, 0x7f);                 /* set L2LEN */
    SET_FIELD(desc.desc5, 20, 7, 0x1ff);                /* set L3LEN */
    SET_FIELD(desc.desc5, 80, 16, 0xff);                /* set L4LEN */
    SET_FLAG(desc.desc1, 2);                            /* set TCP checksum offload enable */
    SET_FLAG(desc.desc8, 0);                            /* set offload */
    SET_FLAG(desc.desc8, 20);                           /* set ipsec type=esp */
    SET_FIELD(desc.desc8, 0, 1, 0x3ff);                 /* set IPSec sa index */
    SET_FIELD(desc.desc8, 18, 11, 0x1ff);               /* set IPSec esp len */
    msg.u.enc_msg.desc = &desc;
    msg.u.enc_msg.frm = skbuf;
    IPSec_Loop((intptr_t)&msg);

    return;
}

static void sample_DecTest(void)
{
    unsigned char key[16] = {
        0xd6, 0x4a, 0x41, 0x04,
        0x88, 0x87, 0xaf, 0xdb,
        0xb1, 0x11, 0xe1, 0x4c,
        0x68, 0x4c, 0x82, 0x7d,
    };

    unsigned char skbuf[] = {
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
        0xdd, 0x4a
    };

    unsigned char salt[4] = {
        0xd0, 0xc6, 0x93, 0x3d,
    };

    MSG_TypeDef msg;
    NIC_RXDescTypeDef desc;

    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_ADD;
    msg.u.rxsa_msg.sa_ind = 0;
    msg.u.rxsa_msg.spi = 0x00001001;
    msg.u.rxsa_msg.ipaddr[0] = 0x0a000002;
    memcpy(msg.u.rxsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.rxsa_msg.salt, salt, sizeof(salt));
    msg.u.rxsa_msg.iptbl_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    msg.type = MSG_DEC;
    SET_FIELD(desc.desc0, sizeof(skbuf), 0, 0x3fff);   /* set rx buf size */
    msg.u.dec_msg.desc = &desc;
    msg.u.dec_msg.desc->desc9 = (intptr_t)skbuf;
    IPSec_Loop((intptr_t)&msg);

    return;
}

static void sample_OneMsgMultiSlices_DecTest(void)
{
    unsigned char key[16] = {
        0xd6, 0x4a, 0x41, 0x04,
        0x88, 0x87, 0xaf, 0xdb,
        0xb1, 0x11, 0xe1, 0x4c,
        0x68, 0x4c, 0x82, 0x7d,
    };

    unsigned char skbuf_first_seg[] = {
        0xe2, 0x72, 0xc1, 0x2b, 0x87, 0xe5, 0xd2, 0xf9,
        0x79, 0xf8, 0x82, 0xa1, 0x08, 0x00, 0x45, 0x00,
        0x00, 0x64, 0x00, 0x00, 0x40, 0x00, 0x40, 0x32,
        0x26, 0x66, 0x0a, 0x00, 0x00, 0x01, 0x0a, 0x00,
        0x00, 0x02, 0x00, 0x00, 0x10, 0x01, 0x00, 0x00,
        0x00, 0x01, 0x1e, 0xd0, 0xa0, 0xe2, 0x3d, 0x4a,
        0xbd, 0x34, 0x2c, 0xdf, 0xe4, 0x49, 0xbd, 0x92,
        0x7a, 0xa2, 0x2d, 0x94, 0xf7, 0xf4, 0x5f, 0x11,
    };

    unsigned char skbuf_second_seg[] = {
        0x31, 0xea, 0xdd, 0x79, 0x92, 0xd3, 0x54, 0x71,
        0x7d, 0x5f, 0x7d, 0xec, 0xee, 0x02, 0xa9, 0x5a,
    };

    unsigned char skbuf_third_seg[] = {
        0x5d, 0x14, 0x39, 0x36, 0x83, 0x9f, 0xb3, 0x44,
        0x52, 0x73, 0xa0, 0xb1, 0xe2, 0x06, 0x45, 0x19,
        0x06, 0x2c, 0x18, 0x06, 0x59, 0xce, 0x98, 0x4a,
        0x57, 0x78, 0x28, 0xca, 0x84, 0x42, 0xa2, 0xe1,
        0xdd, 0x4a
    };

    unsigned char salt[4] = {
        0xd0, 0xc6, 0x93, 0x3d,
    };

    MSG_TypeDef msg;
    NIC_RXDescTypeDef desc_first;
    NIC_RXDescTypeDef desc_second;
    NIC_RXDescTypeDef desc_third;

    memset(&msg, 0, sizeof(MSG_TypeDef));
    msg.type = MSG_RX_SA_ADD;
    msg.u.rxsa_msg.sa_ind = 0;
    msg.u.rxsa_msg.spi = 0x00001001;
    msg.u.rxsa_msg.ipaddr[0] = 0x0a000002;
    memcpy(msg.u.rxsa_msg.key, key, sizeof(key));
    memcpy(&msg.u.rxsa_msg.salt, salt, sizeof(salt));
    msg.u.rxsa_msg.iptbl_ind = 0;
    IPSec_Loop((intptr_t)&msg);

    msg.type = MSG_DEC;
    SET_FIELD(desc_first.desc0, sizeof(skbuf_first_seg), 0, 0x3fff);   /* set rx buf size */
    SET_FIELD(desc_second.desc0, sizeof(skbuf_second_seg), 0, 0x3fff);   /* set rx buf size */
    SET_FIELD(desc_third.desc0, sizeof(skbuf_third_seg), 0, 0x3fff);   /* set rx buf size */

    desc_first.desc11 = (intptr_t)(&desc_second);
    desc_second.desc11 = (intptr_t)(&desc_third);
    desc_first.desc9 = (intptr_t)(&skbuf_first_seg);
    desc_second.desc9 = (intptr_t)(&skbuf_second_seg);
    desc_third.desc9 = (intptr_t)(&skbuf_third_seg);

    msg.u.dec_msg.desc = &desc_first;
    msg.u.dec_msg.segs = 3;


    IPSec_Loop((intptr_t)&msg);

    return;
}

void sampleTest(void)
{
    /* sample_SATest(); */
    /* sample_SARxLookupTest(); */
    /* sample_EncTest(); */
    /* sample_DecTest(); */
    sample_OneMsgMultiSlices_DecTest();
    return;
}

#endif