-
#ifndef _CRYPTO_H
#define _CRYPTO_H

#include <stdbool.h>

#include "priv.h"

#define IV_MAX              12

typedef void (*CY_SymCbFunc)(intptr_t callbackTag,
                             int status,
                             bool verifyResult);

typedef struct
{
    uint8_t direction;
    uint8_t *key;
    uint32_t keyLen;
    uint8_t iv[IV_MAX];
    uint32_t ivLen;
    uint8_t *aad;
    uint32_t aadLen;
    bool verifyDigest;
    uint8_t *digest;
    uint32_t digestLen;
} CY_Sym_OpDataTypedef;

void CY_Initialize(void);
void CY_SymPerformOp(const CY_SymCbFunc symCb, intptr_t callbackTag,
                     const CY_Sym_OpDataTypedef *opData,
                     BufferListTypedef *srcBuffer,
                     BufferListTypedef *dstBuffer);

#endif /* _CRYPTO_H */
