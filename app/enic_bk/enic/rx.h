#ifndef __RX_H
#define __RX_H

#include "stdbool.h"
#include "job.h"

typedef struct {
    uint32_t desc0;  /* same with soc*/
    uint32_t desc1;  /* same with soc [31:16] for ipsec fragment */
    uint32_t desc2;  /* same with soc x86 buffer address*/
    uint32_t desc3;  /* same with soc x86 buffer address*/
    uint32_t desc4;  /* same with soc*/
    uint32_t desc5;  /* same with soc*/
    uint32_t desc6;  /* same with soc [31:16] for pkt total len */
    uint32_t desc7;  /* same with soc*/
    uint32_t desc8;  /* ipsec err indicate */
    uint64_t desc9;  /* buffer in ram */
    uint32_t desc10; /* dest list header */
    uint32_t desc11; /* pointer to next shadow descriptor */
} NIC_RXDescTypeDef;


/*** Exported_Functions ***/
void RX_DescChainInit(intptr_t base, int16_t num);
bool RX_GetPipelineStatus(int32_t gmac, int32_t qid);
int32_t RX_SetRSSRedirectionTable(uint8_t *tbl);
bool RX_IsNeedIPsecOffload(GMAC_RXDescTypeDef *desc);
uint32_t RX_GetDestQueue(GMAC_RXDescTypeDef *desc);
uint32_t RX_ShadowDescUnused(int32_t gmac, int32_t qid);
void RX_CleanShadowDesc(int32_t gmac, int32_t qid);

void RX_PktEnqueue(LIST_HeadTypeDef *list, NIC_RXDescTypeDef *desc);
void RX_PktDequeue(LIST_HeadTypeDef *list, NIC_RXDescTypeDef *desc);

int32_t RX_RequestIPsecDec(int32_t gmac, int32_t qid, void *data);
void *RX_MakePCIEDmaDescriptor(uint32_t dma_id, intptr_t *src, intptr_t *dst, uint32_t len);
int32_t RX_FetchDesc(int32_t gmac, int32_t qid);
int32_t RX_FillDMARing(int32_t gmac, int32_t qid, NIC_RXDescTypeDef *sdesc);
int32_t RX_FlushData(int32_t gmac, int32_t qid, NIC_RXDescTypeDef *msg);
void *RX_FillUpShadowDesc(int32_t gmac, int32_t qid, GMAC_RXDescTypeDef *desc);
int32_t RX_FlushIPsecPkt(int32_t gmac, int32_t qid, void *msg);
int32_t RX_NextStep(int32_t gmac, int32_t qid, JOB_TypeDef *current_job);

extern NIC_RXDescTypeDef rxdesc_shadow[NIC_QPAIR_NUM][NIC_SHADOW_RXDESC_PER_QUEUE];
#endif
