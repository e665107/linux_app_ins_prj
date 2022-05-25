-
#ifndef _HSM_TRANSPORT_H
#define _HSM_TRANSPORT_H

#include <t690.h>
#include <sysdep.h>

/* Service type(bit 0~2) */
#define PTR_SERVICE_TYPE_CIPHER         0x0
#define PTR_SERVICE_TYPE_HASH           0x1
#define PTR_SERVICE_TYPE_AUTH           0x2
#define PTR_SERVICE_TYPE_AEAD           0x3
#define PTR_SERVICE_TYPE_ZUC            0x4
#define PTR_SERVICE_TYPE_IPSEC          0x6
#define PTR_SERVICE_TYPE_BYPASS         0x7

/* Last(bit 3) */
#define PTR_LAST_NULL                   0x0
#define PTR_LAST_LAST                   0x1

/* First(bit 4) */
#define PTR_FIRST_NULL                  0x0
#define PTR_FIRST_FIRST                 0x1

/* Addr list(bit 5) */
#define PTR_ADDR_TYPE_FLAT              0x0
#define PTR_ADDR_TYPE_SGL               0x1

/* Cipher algorithm(bit 6~9) */
#define PTR_CIPHER_ALG_NULL             0x0
#define PTR_CIPHER_ALG_SM4              0x1
#define PTR_CIPHER_ALG_SM7              0x2
#define PTR_CIPHER_ALG_AES128           0x3
#define PTR_CIPHER_ALG_AES192           0x4
#define PTR_CIPHER_ALG_AES256           0x5
#define PTR_CIPHER_ALG_DES              0x6
#define PTR_CIPHER_ALG_3DES             0x7
#define PTR_CIPHER_ALG_BASE64           0x8
#define PTR_CIPHER_ALG_ZUC_EEA3         0x9

/* Cipher mode(bit 10~13) */
#define PTR_CIPHER_MODE_NULL            0x0
#define PTR_CIPHER_MODE_ECB             0x1
#define PTR_CIPHER_MODE_CBC             0x2
#define PTR_CIPHER_MODE_CFB             0x3
#define PTR_CIPHER_MODE_OFB             0x4
#define PTR_CIPHER_MODE_CTR             0x5
#define PTR_CIPHER_MODE_XTS             0x6
#define PTR_CIPHER_MODE_GCM             0x7
#define PTR_CIPHER_MODE_CCM             0x8

/* Hash algorithm(bit14~17) */
#define PTR_HASH_ALG_NULL               0x0
#define PTR_HASH_ALG_SM3                0x1
#define PTR_HASH_ALG_MD5                0x2
#define PTR_HASH_ALG_SHA1               0x3
#define PTR_HASH_ALG_SHA224             0x4
#define PTR_HASH_ALG_SHA256             0x5
#define PTR_HASH_ALG_SHA384             0x6
#define PTR_HASH_ALG_SHA512             0x7
#define PTR_HASH_ALG_GHASH              0x8

/* Auth mode(bit 18~20) */
#define PTR_AUTH_MODE_NULL              0x0
#define PTR_AUTH_MODE_HMAC              0x1
#define PTR_AUTH_MODE_CBC_MAC           0x2
#define PTR_AUTH_MODE_XCBC_MAC          0x3
#define PTR_AUTH_MODE_GMAC              0x4
#define PTR_AUTH_MODE_GCM               0x5
#define PTR_AUTH_MODE_CCM               0x6
#define PTR_AUTH_MODE_ZUC_EIA           0x7

/* Init(bit 21) */
#define PTR_INIT_NULL                   0x0
#define PTR_INIT_INIT                   0x1

/* Finish(bit 22) */
#define PTR_FINISH_NULL                 0x0
#define PTR_FINISH_FINISH               0x1

/* Aead mode(bit 23~24) */
#define PTR_AEAD_MODE_NULL              0x0
#define PTR_AEAD_MODE_ETM               0x1
#define PTR_AEAD_MODE_MTE               0x2

/* Aead tag(bit 25~26) */
#define PTR_AEAD_TAG_16                 0x0
#define PTR_AEAD_TAG_12                 0x1
#define PTR_AEAD_TAG_8                  0x2
#define PTR_AEAD_TAG_4                  0x3

/* Operation(bit 27) */
#define PTR_OPERATION_ENCRYPT           0x0
#define PTR_OPERATION_DECRYPT           0x1

/* ctx_ctrl mode(bit 28~29) */
#define PTR_EX_CTX_NO_SAVE_WB           0x0
#define PTR_EX_CTX_SAVE_NO_WB           0x1
#define PTR_IN_CTX_SAVE_NO_WB           0x2
#define PTR_IN_CTX_NO_SAVE_WB           0x3

/* key mode(bit 30~31) */
#define PTR_KEY_EXT_DECRYPT_KEY         0x0
#define PTR_KEY_EXT_ENCRYPT_KEY         0x1
#define PTR_KEY_INT_ENCRYPT_KEY         0x2

/* comm header0 bit pos */
#define PTR_SERVICE_TYPE_BITPOS         0
#define PTR_LAST_BITPOS                 3
#define PTR_FIRST_BITPOS                4
#define PTR_SGL_TYPE_BITPOS             5
#define PTR_CIPHER_ALG_BITPOS           6
#define PTR_CIPHER_MODE_BITPOS          10
#define PTR_HASH_ALG_BITPOS             14
#define PTR_AUTH_MODE_BITPOS            18
#define PTR_INIT_BITPOS                 21
#define PTR_FINISH_BITPOS               22
#define PTR_AEAD_MODE_BITPOS            23
#define PTR_AEAD_TAG_BITPOS             25
#define PTR_OPERATION_BITPOS            27
#define PTR_CTX_CTRL_BITPOS             28
#define PTR_KEY_MODE_BITPOS             30

/* comm header0 mask */
#define PTR_SERVICE_TYPE_MASK           0x7
#define PTR_LAST_MASK                   0x1
#define PTR_FIRST_MASK                  0x1
#define PTR_SGL_TYPE_MASK               0x1
#define PTR_CIPHER_ALG_MASK             0xF
#define PTR_CIPHER_MODE_MASK            0xF
#define PTR_HASH_ALG_MASK               0xF
#define PTR_AUTH_MODE_MASK              0x7
#define PTR_INIT_MASK                   0x1
#define PTR_FINISH_MASK                 0x1
#define PTR_AEAD_MODE_MASK              0x3
#define PTR_AEAD_TAG_MASK               0x3
#define PTR_OPERATION_MASK              0x1
#define PTR_CTX_CTRL_MASK               0x3
#define PTR_KEY_MODE_MASK               0x3

#define FW_PTR_SERVICE_TYPE_SET(hdr, val)                                      \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_SERVICE_TYPE_BITPOS,                                         \
              PTR_SERVICE_TYPE_MASK)

#define FW_PTR_LAST_SET(hdr, val)                                              \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_LAST_BITPOS,                                                 \
              PTR_LAST_MASK)

#define FW_PTR_FIRST_SET(hdr, val)                                             \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_FIRST_BITPOS,                                                \
              PTR_FIRST_MASK)

#define FW_PTR_SGL_TYPE_SET(hdr, val)                                          \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_SGL_TYPE_BITPOS,                                             \
              PTR_SGL_TYPE_MASK)

#define FW_PTR_CIPHER_ALG_SET(hdr, val)                                        \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_CIPHER_ALG_BITPOS,                                           \
              PTR_CIPHER_ALG_MASK)

#define FW_PTR_CIPHER_MODE_SET(hdr, val)                                       \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_CIPHER_MODE_BITPOS,                                          \
              PTR_CIPHER_MODE_MASK)

#define FW_PTR_HASH_ALG_SET(hdr, val)                                          \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_HASH_ALG_BITPOS,                                             \
              PTR_HASH_ALG_MASK)

#define FW_PTR_AUTH_MODE_SET(hdr, val)                                         \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_AUTH_MODE_BITPOS,                                            \
              PTR_AUTH_MODE_MASK)

#define FW_PTR_INIT_SET(hdr, val)                                              \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_INIT_BITPOS,                                                 \
              PTR_INIT_MASK)

#define FW_PTR_FINISH_SET(hdr, val)                                            \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_FINISH_BITPOS,                                               \
              PTR_FINISH_MASK)

#define FW_PTR_AEAD_MODE_SET(hdr, val)                                         \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_AEAD_MODE_BITPOS,                                            \
              PTR_AEAD_MODE_MASK)

#define FW_PTR_AEAD_TAG_SET(hdr, val)                                          \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_AEAD_TAG_BITPOS,                                             \
              PTR_AEAD_TAG_MASK)

#define FW_PTR_OPERATION_SET(hdr, val)                                         \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_OPERATION_BITPOS,                                            \
              PTR_OPERATION_MASK)

#define FW_PTR_CTX_CTRL_SET(hdr, val)                                          \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_CTX_CTRL_BITPOS,                                             \
              PTR_CTX_CTRL_MASK)

#define FW_PTR_KEY_MODE_SET(hdr, val)                                          \
    SET_FIELD((hdr).header0,                                                   \
              val,                                                             \
              PTR_KEY_MODE_BITPOS,                                             \
              PTR_KEY_MODE_MASK)

#define FW_PTR_SERVICE_TYPE_GET(hdr)                                           \
    GET_FIELD((hdr).header0,                                                   \
              PTR_SERVICE_TYPE_BITPOS,                                         \
              PTR_SERVICE_TYPE_MASK)

#define FW_PTR_LAST_GET(hdr)                                                   \
    GET_FIELD((hdr).header0,                                                   \
              PTR_LAST_BITPOS,                                                 \
              PTR_LAST_MASK)

#define FW_PTR_FIRST_GET(hdr)                                                  \
    GET_FIELD((hdr).header0,                                                   \
              PTR_FIRST_BITPOS,                                                \
              PTR_FIRST_MASK)

#define FW_PTR_SGL_TYPE_GET(hdr)                                               \
    GET_FIELD((hdr).header0,                                                   \
              PTR_SGL_TYPE_BITPOS,                                             \
              PTR_SGL_TYPE_MASK)

#define FW_PTR_CIPHER_ALG_GET(hdr)                                             \
    GET_FIELD((hdr).header0,                                                   \
              PTR_CIPHER_ALG_BITPOS,                                           \
              PTR_CIPHER_ALG_MASK)

#define FW_PTR_CIPHER_MODE_GET(hdr)                                            \
    GET_FIELD((hdr).header0,                                                   \
              PTR_CIPHER_MODE_BITPOS,                                          \
              PTR_CIPHER_MODE_MASK)

#define FW_PTR_HASH_ALG_GET(hdr)                                               \
    GET_FIELD((hdr).header0,                                                   \
              PTR_HASH_ALG_BITPOS,                                             \
              PTR_HASH_ALG_MASK)

#define FW_PTR_AUTH_MODE_GET(hdr)                                              \
    GET_FIELD((hdr).header0,                                                   \
              PTR_AUTH_MODE_BITPOS,                                            \
              PTR_AUTH_MODE_MASK)

#define FW_PTR_INIT_GET(hdr)                                                   \
    GET_FIELD((hdr).header0,                                                   \
              PTR_INIT_BITPOS,                                                 \
              PTR_INIT_MASK)

#define FW_PTR_FINISH_GET(hdr)                                                 \
    GET_FIELD((hdr).header0,                                                   \
              PTR_FINISH_BITPOS,                                               \
              PTR_FINISH_MASK)

#define FW_PTR_AEAD_MODE_GET(hdr)                                              \
    GET_FIELD((hdr).header0,                                                   \
              PTR_AEAD_MODE_BITPOS,                                            \
              PTR_AEAD_MODE_MASK)

#define FW_PTR_AEAD_TAG_GET(hdr)                                               \
    GET_FIELD((hdr).header0,                                                   \
              PTR_AEAD_TAG_BITPOS,                                             \
              PTR_AEAD_TAG_MASK)

#define FW_PTR_OPERATION_GET(hdr)                                              \
    GET_FIELD((hdr).header0,                                                   \
              PTR_OPERATION_BITPOS,                                            \
              PTR_OPERATION_MASK)

#define FW_PTR_CTX_CTRL_GET(hdr)                                               \
    GET_FIELD((hdr).header0,                                                   \
              PTR_CTX_CTRL_BITPOS,                                             \
              PTR_CTX_CTRL_MASK)

#define FW_PTR_KEY_MODE_GET(hdr)                                               \
    GET_FIELD((hdr).header0,                                                   \
              PTR_KEY_MODE_BITPOS,                                             \
              PTR_KEY_MODE_MASK)

/* AEAD contest offset index*/
#define AEAD_CTX_SYM_KEY_OFFSET             0
#define AEAD_CTX_RESERVED_OFFSET            32
#define AEAD_CTX_J0_OFFSET                  64
#define AEAD_CTX_HMAC_KEY_OFFSET            80
#define AEAD_CTX_HMAC_DIGEST_OFFSET         144
#define AEAD_CTX_PAD_TYPE_OFFSET            200
#define AEAD_CTX_PAD_BYTE_OFFSET            204
#define AEAD_CTX_AAD_BITS_OFFSET            208
#define AEAD_CTX_AAD_ADDR_OFFSET            216

/* Ring Csrs offsets */
#define RING_CSR_QUEUE_CTRL                 0x00
#define RING_CSR_QUEUE_IE                   0x04
#define RING_CSR_QUEUE_ISR                  0x08
#define RING_CSR_QUEUE_LSR                  0x0C
#define RING_CSR_INTC                       0x10
#define RING_CSR_DESC_CTRL                  0x14
#define RING_CSR_RING_BASE_L                0x20
#define RING_CSR_RING_BASE_H                0x24
#define RING_CSR_RING_HEADER_INDEX          0x28
#define RING_CSR_RING_TAIL_INDEX            0x2C
#define RING_CSR_BUFFER_CTRL                0x30
#define RING_CSR_TPH_CTRL                   0x34
#define RING_CSR_FUNC_ID                    0x38

#define WRITE_RING_CSR_QUEUE_CTRL(csr, value)                                  \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_QUEUE_CTRL, (value));                         \
    } while (0)

#define WRITE_RING_CSR_QUEUE_IE(csr, value)                                    \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_QUEUE_IE, (value));                           \
    } while (0)

#define WRITE_RING_CSR_INC(csr, value)                                         \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_INTC, (value) << 8);                          \
    } while (0)

#define WRITE_RING_CSR_DESC_CTRL(csr, size, count)                             \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_DESC_CTRL, ((size) << 12) | (count));         \
    } while (0)

#define WRITE_RING_CSR_BASE(csr, value)                                        \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_RING_BASE_L, (value));                        \
        write32((csr) + RING_CSR_RING_BASE_H, 0);                              \
    } while (0)

#define WRITE_RING_CSR_TAIL(csr, value)                                        \
    do                                                                         \
    {                                                                          \
        write32((csr) + RING_CSR_RING_TAIL_INDEX, (value));                    \
    } while (0)

#define READ_RING_CSR_QUEUE_CTRL(csr)                                          \
    read32((csr) + RING_CSR_QUEUE_CTRL)

#define READ_RING_CSR_QUEUE_IE(csr)                                            \
    read32((csr) + RING_CSR_QUEUE_IE)

#define READ_RING_CSR_QUEUE_ISR(csr)                                           \
    read32((csr) + RING_CSR_QUEUE_ISR)

#define READ_RING_CSR_QUEUE_LSR(csr)                                           \
    read32((csr) + RING_CSR_QUEUE_LSR)

#define READ_RING_CSR_INTC(csr)                                                \
    read32((csr) + RING_CSR_INTC)

#define READ_RING_CSR_DESC_CTRL(csr)                                           \
    read32((csr) + RING_CSR_DESC_CTRL)

#define READ_RING_CSR_BASE_L(csr)                                              \
    read32((csr) + RING_CSR_RING_BASE_L)

#define READ_RING_CSR_BASE_H(csr)                                              \
    read32((csr) + RING_CSR_RING_BASE_H)

#define READ_RING_CSR_HEADER_INDEX(csr)                                        \
    read32((csr) + RING_CSR_RING_HEADER_INDEX)

#define READ_RING_CSR_TAIL_INDEX(csr)                                          \
    read32((csr) + RING_CSR_RING_TAIL_INDEX)

#define READ_RING_CSR_BUFFER_CTRL(csr)                                         \
    read32((csr) + RING_CSR_BUFFER_CTRL)

#define READ_RING_CSR_TPH_CTRL(csr)                                            \
    read32((csr) + RING_CSR_TPH_CTRL)

#define READ_RING_CSR_FUNC_ID(csr)                                             \
    read32((csr) + RING_CSR_FUNC_ID)

typedef struct {
    uint32_t header0;
    uint32_t header1;
} Ring_HdrTypedef;

typedef struct {
    uint64_t srcData;
    uint64_t dstData;
} Ring_MidTypedef;

typedef struct {
    uint64_t contextAddr;
} Ring_ContextTypedef;

typedef struct {
    /* LWs 0-1 */
    Ring_HdrTypedef hdr;

    /* LWs 2-5 */
    Ring_MidTypedef mid;

    /* LWs 6-7 */
    Ring_ContextTypedef context;

    /* LWs 8-15 */
    struct {
        uint64_t opaqueData;
        uint64_t resrvd1;
        uint64_t resrvd2;
        uint64_t resrvd3;
    } s;

} DescTypedef;

#endif /* _HSM_TRANSPORT_H */
