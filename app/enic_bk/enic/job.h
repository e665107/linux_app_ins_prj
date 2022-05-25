#ifndef __JOB_H
#define __JOB_H

#include "nic.h"
#include "list.h"

#define JOB_PENDING_LIST_HAS_PRIO (0 << 1)

typedef enum
{
    JOB_TX_DESC_FETCH = 1,
    JOB_TX_DATA_FETCH,
    JOB_TX_DESC_FLUSH,
    JOB_TX_IPSEC_ENC,
    JOB_TX_GMAC_SEND,
    JOB_TX_MAX,

    JOB_RX_DESC_FETCH,
    JOB_RX_IPSEC_DEC,
    JOB_RX_IPSEC_DATA_FLUSH,
    JOB_RX_DESC_DATA_FLUSH,
    JOB_RX_GMAC_CLEAN,
    JOB_RX_IPSEC_CLEAN,
    JOB_RX_MAX,

    JOB_CMD_DESC_FETCH,
    JOB_CMD_DATA_FETCH,
    JOB_CMD_FLUSH,
    JOB_CMD_MAX,

    JOB_NONE
} JOB_NameTypeDef;

typedef enum
{
    RSN_OK,
    RSN_DMA_BUSY,
    RSN_DMA_RING_FULL,
    RSN_GMAC_TX_RING_FULL,
    RSN_PBUF_NOT_AVAIL,
    RSN_MSG_RING_FULL,
    RSN_SHADOW_RING_FULL,
    RSN_ALREADY_SUSPEND,
    RSN_X86_DESC_EMPTY,
    RSN_FRAME_INFO_NOT_AVAIL,
    RSN_FRAME_SEG_NOT_AVAIL,
    RSN_UNKOWN
}JOB_PendingReasonTypeDef;

typedef struct
{
    uint32_t gmac;
    uint32_t qid;
    JOB_NameTypeDef type;
    JOB_PendingReasonTypeDef reason;
    struct list_head list;
} JOB_TypeDef;

typedef struct {
    uint32_t flag;
    struct list_head wait_list;
} JOB_PendingListTypeDef;

extern JOB_PendingListTypeDef wait_dma_done_list;
extern JOB_PendingListTypeDef wait_gmac_tx_done_list;
extern JOB_PendingListTypeDef wait_ipsec_req_done_list;
extern JOB_PendingListTypeDef wait_txdesc_flush_done_list[NIC_QPAIR_NUM];
extern JOB_PendingListTypeDef wait_rxdesc_flush_done_list;
extern JOB_PendingListTypeDef wait_rx_tail_update_list[NIC_QPAIR_NUM];

int JOB_Assign(int gmac, int qid, JOB_NameTypeDef type, void *para);
int JOB_Suspend(JOB_PendingListTypeDef *list, int gmac, int qid, JOB_NameTypeDef type, JOB_PendingReasonTypeDef reason);
void JOB_Resume(JOB_PendingListTypeDef *list);
void JOB_PendingListInit(JOB_PendingListTypeDef *list, uint32_t flag);
#endif
