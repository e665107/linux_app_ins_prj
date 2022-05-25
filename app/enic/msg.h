-#ifndef __MSG_H
#define __MSG_H

#include "nic.h"
#include "tx.h"
#include "rx.h"

#define MSG_NUM             128

#define SECERR_OK           0x0
#define SECERR_INVAL        0x1  /* Invalid IPsec Protocol */
#define SECERR_INVAL_LEN    0x2
#define SECERR_INVAL_AUTH   0x3

typedef enum
{
    MSG_ENC,
    MSG_DEC,
    MSG_ENC_DONE,
    MSG_DEC_DONE,

    MSG_RX_SA_ADD,
    MSG_TX_SA_ADD,
    MSG_RX_SA_ADD_DONE,
    MSG_TX_SA_ADD_DONE,

    MSG_RX_SA_DEL,
    MSG_TX_SA_DEL,
    MSG_RX_SA_DEL_DONE,
    MSG_TX_SA_DEL_DONE,

    MSG_RX_CHECKSUM_SET,
} MSG_TYPETypeDef;

typedef struct
{
    uint32_t gmac;
    /* original queue id */
    uint32_t qid;
    /* desc0 address */
    TX_DescTypeDef *desc;
    /* frame data address */
    uint8_t *frm;
} MSG_ENCMsgTypeDef;

typedef struct
{
    uint32_t gmac;
    uint32_t qid;
    uint32_t segs;
    NIC_RXDescTypeDef *desc;
} MSG_DECMsgTypeDef;

typedef struct
{
    uint32_t sa_ind;
    uint32_t spi;
    uint32_t ipaddr[4];
    uint32_t key[4];
    uint32_t salt;
    uint32_t iptbl_ind;
} MSG_RxSAMsgTypeDef;

typedef struct
{
    uint32_t sa_ind;
    uint32_t key[4];
    uint32_t salt;
} MSG_TxSAMsgTypeDef;

typedef struct
{
    uint32_t gmac;
    uint32_t qid;
    uint32_t *desc;
    /* frame data address */
    uint8_t *frm;
} MSG_ENCDoneMsgTypeDef;

typedef struct
{
    uint32_t gmac;
    uint32_t qid;
    uint32_t segs;
    uint32_t *desc;
} MSG_DECDoneMsgTypeDef;

typedef struct
{
    uint32_t gmac;
    uint32_t qid;
    uint32_t rx_checksum;
} MSG_RxChecksumMsgTypeDef;

typedef struct
{
    uint32_t type;
    uint32_t retval;
    union
    {
        MSG_ENCMsgTypeDef enc_msg;

        MSG_DECMsgTypeDef dec_msg;

        MSG_TxSAMsgTypeDef txsa_msg;

        MSG_RxSAMsgTypeDef rxsa_msg;

        MSG_RxChecksumMsgTypeDef chkmum_msg;

        uint8_t raw[16];
    } u;
} MSG_TypeDef;

int MSG_ToSlave(MSG_TypeDef *msg);
int MSG_ToMaster(MSG_TypeDef *msg);
#endif
