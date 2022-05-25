-
#include "fifo.h"
#include "crypto.h"
#include "hsm_transport.h"

#define FIFO_SIZE               16
#define SERVICE_NUM             3

#define CONTENT_DESC_MAX_SIZE   256
typedef struct {
    uint8_t reserved[CONTENT_DESC_MAX_SIZE];
    CY_SymCbFunc symCb;
    intptr_t callbackTag;
    CY_Sym_OpDataTypedef opData;
    uint64_t privateMetaData[6];
} CY_SymCookieTypedef;

typedef struct {
    uint32_t symCSR;
    CY_SymCookieTypedef symCookie[FIFO_SIZE];
    DECLARE_KFIFO(symRing, DescTypedef, FIFO_SIZE);
} CY_ServiceTypedef;

static CY_ServiceTypedef CY_Service[SERVICE_NUM];

#ifdef DEBUG
static const char *ServiceType2str[] = {
    "cipher mode",
    "hash mode",
    "auth mode",
    "aead mode",
    "ZUC mode",
    "reserve",
    "IPsec mode",
    "Bypass mode"
};

static const char *CipherAlg2str[] = {
    "NULL",
    "SM4",
    "SM7",
    "AES128",
    "AES192",
    "AES256",
    "DES",
    "3DES",
    "BASE64",
    "ZUC_EEA3"
};

static const char *CipherMode2str[] = {
    "NULL",
    "ECB",
    "CBC",
    "CFB",
    "OFB",
    "CTR",
    "XTS",
    "GCM",
    "CCM"
};

static const char *HashAlg2str[] = {
    "NULL",
    "SM3",
    "MD5",
    "SHA1",
    "SHA224",
    "SHA256",
    "SHA384",
    "SHA512",
    "GHASH"
};

static const char *AuthMode2str[] = {
    "NULL",
    "HMAC",
    "CMAC",
    "XCBC_MAC",
    "GMAC",
    "GCM",
    "CCM",
    "ZUC_EIA"
};

static const char *AeadMode2str[] = {
    "NULL",
    "ETM",
    "MTE"
};

static const char *AeadTag2str[] = {
    "16",
    "12",
    "8",
    "4"
};

static const char *Operation2str[] = {
    "Encrypt",
    "Decrypt"
};

static const char *CtxCtrl2str[] = {
    "External CTX, Not Save, Writeback",
    "External CTX, Save, Not Writeback",
    "Internal CTX, Save, Not Writeback",
    "Internal CTX, Not Save, Writeback"
};

static const char *KeyMode2str[] = {
    "External plaintext key, saved in context",
    "External ciphertext key, saved in context",
    "Use internal key, key ID saved in the context"
};

void Dump_Descriptor(DescTypedef *desc)
{
    Ring_ContextTypedef *ctx;

    DUMPL("Descriptor", (const uint8_t *)desc, sizeof(DescTypedef));

    printf("  Request Header \n"
           "    ServiceType: %s \n"
           "    Last: %s \n"
           "    First: %s \n"
           "    AddrList: %s \n"
           "    CipherAlg: %s \n"
           "    CipherMode: %s \n"
           "    HashAlg: %s \n"
           "    AuthMode: %s \n"
           "    Init: %s \n"
           "    Finish: %s \n"
           "    AeadMode: %s \n"
           "    AeadTag: %s \n"
           "    Operation: %s \n"
           "    CtxCtrl: %s \n"
           "    KeyMode: %s \n",
           ServiceType2str[FW_PTR_SERVICE_TYPE_GET(desc->hdr)],
           FW_PTR_LAST_GET(desc->hdr) ? "true" : "false",
           FW_PTR_FIRST_GET(desc->hdr) ? "true" : "false",
           FW_PTR_SGL_TYPE_GET(desc->hdr) ? "list" : "addr",
           CipherAlg2str[FW_PTR_CIPHER_ALG_GET(desc->hdr)],
           CipherMode2str[FW_PTR_CIPHER_MODE_GET(desc->hdr)],
           HashAlg2str[FW_PTR_HASH_ALG_GET(desc->hdr)],
           AuthMode2str[FW_PTR_AUTH_MODE_GET(desc->hdr)],
           FW_PTR_INIT_GET(desc->hdr) ? "true" : "false",
           FW_PTR_FINISH_GET(desc->hdr) ? "true" : "false",
           AeadMode2str[FW_PTR_AEAD_MODE_GET(desc->hdr)],
           AeadTag2str[FW_PTR_AEAD_TAG_GET(desc->hdr)],
           Operation2str[FW_PTR_OPERATION_GET(desc->hdr)],
           CtxCtrl2str[FW_PTR_CTX_CTRL_GET(desc->hdr)],
           KeyMode2str[FW_PTR_KEY_MODE_GET(desc->hdr)]);

    printf("  Request Plaintext \n");

    switch (FW_PTR_SGL_TYPE_GET(desc->hdr)) {
    case PTR_ADDR_TYPE_FLAT:
        break;
    case PTR_ADDR_TYPE_SGL:
        printf("    src buffer number: %llu \n",
               (desc->mid.srcData & 0xFFFF000000000000ULL) >> 48);
        printf("    dst buffer number: %llu \n",
               (desc->mid.dstData & 0xFFFF000000000000ULL) >> 48);
        break;
    default:
        printf("ERROR: does not support this addr type\n");
        break;
    }

    printf("  Request Context \n");

    ctx = &desc->context;
    DUMPL("    SymKey",
          (const uint8_t *)ctx->contextAddr, 32);
    DUMPL("    J0",
          (const uint8_t *)(ctx->contextAddr + AEAD_CTX_J0_OFFSET), 16);
    DUMPL("    AAD",
          (const uint8_t *) * ((uint64_t *)(ctx->contextAddr + AEAD_CTX_AAD_ADDR_OFFSET)),
          *((uint64_t *)(ctx->contextAddr + AEAD_CTX_AAD_BITS_OFFSET)));
    return;
}
#endif

__STATIC_FORCEINLINE
int Get_Next_Service_Num(void)
{
    /* FIXME */
    return 0;
}

__STATIC_FORCEINLINE
void CY_Desc_CmnHdrWrite(DescTypedef *desc,
                         const CY_Sym_OpDataTypedef *opData)
{
#if 0
    FW_PTR_SERVICE_TYPE_SET(desc->hdr, PTR_SERVICE_TYPE_AEAD);
    FW_PTR_LAST_SET(desc->hdr, PTR_LAST_LAST);
    FW_PTR_FIRST_SET(desc->hdr, PTR_FIRST_FIRST);
    FW_PTR_CIPHER_ALG_SET(desc->hdr, PTR_CIPHER_ALG_AES128);
    FW_PTR_CIPHER_MODE_SET(desc->hdr, PTR_CIPHER_MODE_GCM);
    FW_PTR_HASH_ALG_SET(desc->hdr, PTR_HASH_ALG_NULL);
    FW_PTR_AUTH_MODE_SET(desc->hdr, PTR_AUTH_MODE_GCM);
    FW_PTR_INIT_SET(desc->hdr, PTR_INIT_INIT);
    FW_PTR_FINISH_SET(desc->hdr, PTR_FINISH_FINISH);
    FW_PTR_AEAD_MODE_SET(desc->hdr, PTR_AEAD_MODE_ETM);
    FW_PTR_AEAD_TAG_SET(desc->hdr, PTR_AEAD_TAG_16);
    FW_PTR_OPERATION_SET(desc->hdr, PTR_OPERATION_ENCRYPT);
    FW_PTR_CTX_CTRL_SET(desc->hdr, PTR_EX_CTX_NO_SAVE_WB);
    FW_PTR_KEY_MODE_SET(desc->hdr, PTR_KEY_EXT_DECRYPT_KEY);
    printf("header0 = 0x%08x (%u) \n",
           desc->hdr.header0, desc->hdr.header0);
#endif
    desc->hdr.header0 = 0x00f41cdb;
    FW_PTR_OPERATION_SET(desc->hdr, opData->direction);
    return;
}

__STATIC_FORCEINLINE
void CY_Desc_BufferListWrite(const BufferListTypedef *userBufferList,
                             uint64_t *bufListAlignedAddr)
{
#define SET_FLAT_BUFFER(addr, size)                                            \
    ((uint64_t)(addr) | (((uint64_t)(size) << 48) & 0xFFFF000000000000ULL))

    uint32_t numBuffers = 0;
    uint64_t bufListDescAddr = 0;
    const FlatBufferTypedef *currUserFlatBuffer = NULL;
    uint64_t *currFlatBufDesc = NULL;

    numBuffers = userBufferList->numBuffers;
    currUserFlatBuffer = userBufferList->buffers;

    /* Get the address of this descriptor */
    bufListDescAddr = (uint64_t)userBufferList->privateMetaData;
    if (__rv_unlikely(0 == bufListDescAddr)) {  /* INVALID ADDRESS */
        printf("ERROR: Unable to get the address of the metadata \n");
        return;
    }
    *bufListAlignedAddr = SET_FLAT_BUFFER(bufListDescAddr, numBuffers);

    currFlatBufDesc = (uint64_t *)bufListDescAddr;
    while (0 != numBuffers) {
        *currFlatBufDesc = SET_FLAT_BUFFER(currUserFlatBuffer->data,
                                           currUserFlatBuffer->dataLen);
        currFlatBufDesc++;
        currUserFlatBuffer++;
        numBuffers--;
    }

    return;
}

__STATIC_FORCEINLINE
void CY_Desc_CmnMidWrite(DescTypedef *desc,
                         BufferListTypedef *srcBuffer,
                         BufferListTypedef *dstBuffer,
                         uint64_t privateMetaData[])
{
    uint64_t srcAddr = 0;
    uint64_t dstAddr = 0;

    srcBuffer->privateMetaData = privateMetaData;
    dstBuffer->privateMetaData = privateMetaData;

    CY_Desc_BufferListWrite(srcBuffer, &srcAddr);
    CY_Desc_BufferListWrite(dstBuffer, &dstAddr);

    desc->mid.srcData = srcAddr;
    desc->mid.dstData = dstAddr;
    FW_PTR_SGL_TYPE_SET(desc->hdr, PTR_ADDR_TYPE_SGL);
    return;
}

__STATIC_FORCEINLINE
void CY_Desc_CmnContentWrite(DescTypedef *desc,
                             intptr_t cookie)
{
    desc->context.contextAddr = cookie;
    return;
}

__STATIC_FORCEINLINE
void CY_Desc_CookieParamsPopulate(CY_SymCookieTypedef *cookie,
                                  const CY_SymCbFunc symCb,
                                  intptr_t callbackTag,
                                  const CY_Sym_OpDataTypedef *opData)
{
    uint8_t *J0 = NULL;

    cookie->symCb            = symCb;
    cookie->callbackTag      = callbackTag;
    cookie->opData.digest[0]    = opData->digest[0];
    cookie->opData.digest[1]    = opData->digest[1];

    cookie->opData.digestLen[0] = opData->digestLen[0];
    cookie->opData.digestLen[1] = opData->digestLen[1];

    /* symmetric key */
    memcpy(cookie->reserved, opData->key, opData->keyLen);

    /* J0 = IV || 0^31 || 1, J0(16 bytes) = IV(12 bytes) + counter(4 bytes) */
    J0 = cookie->reserved + AEAD_CTX_J0_OFFSET;
    memcpy(J0, opData->iv, opData->ivLen);
    *(J0 + 15) = 1;

    /* aad and aad_len */
    *((uint64_t *)(cookie->reserved + AEAD_CTX_AAD_BITS_OFFSET)) = opData->aadLen;
    *((uint64_t *)(cookie->reserved + AEAD_CTX_AAD_ADDR_OFFSET)) = (intptr_t)opData->aad;

    return;
}

/**
 *  without spinlock
 *  only aes128-gcm
 */
void CY_SymPerformOp(const CY_SymCbFunc symCb, intptr_t callbackTag,
                     const CY_Sym_OpDataTypedef *opData,
                     BufferListTypedef *srcBuffer,
                     BufferListTypedef *dstBuffer)
{
    int serviceNum;
    DescTypedef desc;
    CY_ServiceTypedef *service;
    CY_SymCookieTypedef *cookie;

    /* get service handle */
    serviceNum = Get_Next_Service_Num();
    service = &CY_Service[serviceNum];

    /* get cookie and fill it in */
    cookie = &service->symCookie[kfifo_poke_in(&service->symRing)];
    CY_Desc_CookieParamsPopulate(cookie, symCb, callbackTag, opData);

    /* get descriptor and fill it in */
    CY_Desc_CmnHdrWrite(&desc, opData);
    CY_Desc_CmnMidWrite(&desc, srcBuffer, dstBuffer, cookie->privateMetaData);
    CY_Desc_CmnContentWrite(&desc, (intptr_t)cookie);
    kfifo_put(&service->symRing, desc);

#ifdef DEBUG
    printf("Perform symmetric crypto operation on the service%d \n", serviceNum);
    Dump_Descriptor(&desc);
#endif

    /* send the message to the HSM */
    WRITE_RING_CSR_TAIL(service->symCSR, kfifo_poke_in(&service->symRing));
    return;
}

__STATIC_FORCEINLINE
void CY_SymCb_ProcessCallbackInternal(intptr_t opaqueData)
{
    bool respStatusOkFlag = true;
    int status = STATUS_SUCCESS;
    CY_SymCookieTypedef *cookie = (CY_SymCookieTypedef *)opaqueData;

    if (cookie->opData.verifyDigest) {
        if (__rv_unlikely(0 != memcmp(cookie->opData.digest,
                                      cookie->reserved + AEAD_CTX_HMAC_DIGEST_OFFSET,
                                      cookie->opData.digestLen)))
            respStatusOkFlag = false;
    } else {
        memcpy(cookie->opData.digest,
               cookie->reserved + AEAD_CTX_HMAC_DIGEST_OFFSET,
               cookie->opData.digestLen);
    }

    if ((STATUS_SUCCESS == status) && (true != respStatusOkFlag)) {
        printf("ERROR: response status value not as expected");
        status = STATUS_FAIL;
    }

    cookie->symCb(cookie->callbackTag,
                  status,
                  respStatusOkFlag);
    return;
}
#if 0
__INTERRUPT void SYMINT_Q0_IRQHandler(void)
{
    while (READ_RING_CSR_HEADER_INDEX(CY_Service[0].symCSR) !=
           kfifo_poke_out(&CY_Service[0].symRing)) {
        DescTypedef desc;
        kfifo_get(&CY_Service[0].symRing, &desc);
        CY_SymCb_ProcessCallbackInternal(desc.s.opaqueData);
    }
}

__INTERRUPT void SYMINT_Q1_IRQHandler(void)
{
    while (READ_RING_CSR_HEADER_INDEX(CY_Service[1].symCSR) !=
           kfifo_poke_out(&CY_Service[1].symRing)) {
        DescTypedef desc;
        kfifo_get(&CY_Service[1].symRing, &desc);
        CY_SymCb_ProcessCallbackInternal(desc.s.opaqueData);
    }
}

__INTERRUPT void SYMINT_Q2_IRQHandler(void)
{
    while (READ_RING_CSR_HEADER_INDEX(CY_Service[2].symCSR) !=
           kfifo_poke_out(&CY_Service[2].symRing)) {
        DescTypedef desc;
        kfifo_get(&CY_Service[2].symRing, &desc);
        CY_SymCb_ProcessCallbackInternal(desc.s.opaqueData);
    }
}
#endif
__STATIC_FORCEINLINE
void CY_ServiceInitialize(CY_ServiceTypedef *service,
                          uint32_t pkCSR,
                          uint32_t symCSR,
                          uint32_t ctrlCSR)
{
    /* init sym ring */
    service->symCSR = symCSR;
    /* set descriptor's count and size */
    WRITE_RING_CSR_DESC_CTRL(symCSR, 16, FIFO_SIZE);
    /* set descriptor's base address */
    WRITE_RING_CSR_BASE(symCSR, (intptr_t)kfifo_prepare(&service->symRing));
    /* set the coalescence timer */
    WRITE_RING_CSR_INC(symCSR, 0x00ff04);
    /* enable ring */
    WRITE_RING_CSR_QUEUE_CTRL(symCSR, 1);
    /* disable interrupt */
    WRITE_RING_CSR_QUEUE_IE(symCSR, 1);
    return;
}

#if 0
__STATIC_FORCEINLINE
void CY_ECLICInitialize(uint16_t irq,
                        uint8_t irqLevel,
                        uint8_t irqPriority,
                        FunctionalState state,
                        Core_Type type)
{
    ECLIC_IRQInitTypeDef ECLIC_IRQInitStructure;

    ECLIC_IRQInitStructure.ECLIC_IRQn        = irq;
    ECLIC_IRQInitStructure.ECLIC_IRQLevel    = irqLevel;
    ECLIC_IRQInitStructure.ECLIC_IRQPriority = irqPriority;
    ECLIC_IRQInitStructure.ECLIC_IRQCmd      = state;
    ECLIC_IRQInitStructure.ECLIC_CORE        = type;
    ECLIC_IRQInit(&ECLIC_IRQInitStructure);
    return;
}
#endif

#ifdef DEBUG
void Dump_Ring(uint32_t csr)
{
    printf("Bus width:            32 \n"
           "Big/Little endian:    little endian \n"
           "Base address:         0x%x \n"
           "    reg name      offset    value \n"
           "        QC        0x00      0x%08x\n"
           "        QIER      0x04      0x%08x\n"
           "        QISR      0x08      0x%08x\n"
           "        QLSR      0x0c      0x%08x\n"
           "        INTC      0x10      0x%08x\n"
           "        DC        0x14      0x%08x\n"
           "        RINGBL    0x20      0x%08x\n"
           "        RINGBH    0x24      0x%08x\n"
           "        RINGHD    0x28      0x%08x\n"
           "        RINGTL    0x2c      0x%08x\n"
           "        BC        0x30      0x%08x\n"
           "        TC        0x34      0x%08x\n"
           "        FI        0x38      0x%08x\n",
           csr,
           READ_RING_CSR_QUEUE_CTRL(csr),
           READ_RING_CSR_QUEUE_IE(csr),
           READ_RING_CSR_QUEUE_ISR(csr),
           READ_RING_CSR_QUEUE_LSR(csr),
           READ_RING_CSR_INTC(csr),
           READ_RING_CSR_DESC_CTRL(csr),
           READ_RING_CSR_BASE_L(csr),
           READ_RING_CSR_BASE_H(csr),
           READ_RING_CSR_HEADER_INDEX(csr),
           READ_RING_CSR_TAIL_INDEX(csr),
           READ_RING_CSR_BUFFER_CTRL(csr),
           READ_RING_CSR_TPH_CTRL(csr),
           READ_RING_CSR_FUNC_ID(csr));
    return;
}
#endif

void CY_Initialize(void)
{
    CY_ServiceInitialize(&CY_Service[0], HSMPK0_BASE, HSMSYM0_BASE, HSMCTRL0_BASE);
    /* CY_ECLICInitialize(SYMINT_Q0_IRQn, 0, 0, ENABLE, CCORE); */

    CY_ServiceInitialize(&CY_Service[1], HSMPK1_BASE, HSMSYM1_BASE, HSMCTRL1_BASE);
    /* CY_ECLICInitialize(SYMINT_Q1_IRQn, 0, 0, ENABLE, CCORE); */

    CY_ServiceInitialize(&CY_Service[2], HSMPK2_BASE, HSMSYM2_BASE, HSMCTRL2_BASE);
    /* CY_ECLICInitialize(SYMINT_Q2_IRQn, 0, 0, ENABLE, CCORE); */

#ifdef DEBUG
    Dump_Ring(HSMSYM0_BASE);
    Dump_Ring(HSMSYM1_BASE);
    Dump_Ring(HSMSYM2_BASE);
#endif
    return;
}
