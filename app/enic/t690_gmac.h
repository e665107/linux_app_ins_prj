#ifndef __T690_GMAC_H
#define __T690_GMAC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "t690.h"
#include "t690_phy.h"

typedef struct
{
    uint32_t GMAC_FrameSegsNum;
    uint32_t GMAC_FrameLen;
    uint32_t Idx;
} GMAC_FrameHandleTypeDef;


typedef struct
{
    struct
    {
        uint32_t bufsize : 17; /* Transmit buffer size in byte */
        uint32_t lts : 1;      /* Last Transmit Segment descriptor */
        uint32_t fts : 1;      /* First Transmit Segment descriptor */
        uint32_t rsvd : 12;    /* Reserved */
        uint32_t own : 1;      /* Reserved */
    } TxDesc0;
    struct
    {
        uint32_t rsvd0 : 2;    /* Reserved */
        uint32_t tcpcs_en : 1; /* TCP checksum offload enable */
        uint32_t udpcs_en : 1; /*  UDP checksum offload enable */
        uint32_t ipcs_en : 1;  /*  IP checksum offload enable */
        uint32_t llc_pkt : 1;  /* The LLC packet is IEEE 802.3/802.2/SNAP format packet */
        uint32_t rsvd : 26;    /* Reserved */
    } TxDesc1;
    uint32_t TxDesc2; /* Reserved */
    uint32_t TxDesc3; /* High bits of Transmit buffer base address */
    uint32_t TxDesc4; /* Low bits of Transmit buffer base address */
    struct
    {
        uint32_t l2_len : 7; /* MAC Header Length */
        uint32_t l3_len : 9; /* IP header length */
        uint32_t l4_len : 8; /* L4 header length */
        uint32_t rsvd : 8;   /* Reserved */
    } TxDesc5;
    uint32_t TxDesc6; /* Reserved */
    uint32_t TxDesc7; /* Reserved */
} __attribute__((aligned(4))) GMAC_TXDescTypeDef;

typedef struct
{
    struct
    {
        uint32_t pkt_len : 14;     /* Packet length */
        uint32_t multicast : 1;    /* Multicast frame */
        uint32_t broadcast : 1;    /* Broadcast frame */
        uint32_t rx_err : 1;       /* Receive error */
        uint32_t crc_err : 1;      /* CRC error */
        uint32_t ftl : 1;          /* Frame Too Long */
        uint32_t runt : 1;         /* Runt packet */
        uint32_t rx_odd_nb : 1;    /* Receive Odd Nibbles */
        uint32_t fifo_full : 1;    /* fifo full */
        uint32_t pause_opcode : 1; /* Pause frame OP code */
        uint32_t pause_frame : 1;  /* Pause frame */
        uint32_t lrs : 1;          /* Last Receive Segment descriptor */
        uint32_t frs : 1;          /* First Receive Segment descriptor  */
        uint32_t rsvd : 5;         /* Reserved */
        uint32_t own : 1;          /* owner */
    } RxDesc0;
    struct
    {
        uint32_t l2_pkt : 1;     /* It indicates that the packet is an L2 packet */
        uint32_t ipsec_pkt : 1;  /* It indicates that the packet as the IPsec packet */
        uint32_t ipv4_type : 1;  /* It indicates the L3 header is an IPv4 header */
        uint32_t ipv6_type : 1;  /* It indicates the L3 header is an IPv6 header */
        uint32_t tcp_type : 1;   /* It indicates the L4 header is an TCP header */
        uint32_t udp_type : 1;   /* It indicates the L4 header is an UDP header */
        uint32_t snap_pkt : 1;   /* The packet is IEEE 802.3/802.2/SNAP format packet */
        uint32_t llc_pkt : 1;    /* The packet is IEEE 802.3 format packet */
        uint32_t mf : 1;         /* More Fragment */
        uint32_t tcpcs_fail : 1; /* TCP checksum failure */
        uint32_t udpcs_fail : 1; /* IDP checksum failure */
        uint32_t ipcs_fail : 1;  /* IP checksum failure */
        uint32_t ptp_rx_timestamp : 2; /* PTP frame timestamp type */
        uint32_t rsvd0 : 1;            /* Reserved */
        uint32_t ipsec_type : 1; /* It indicates the IPsec packet type is an AH type */
        uint32_t rsvd : 16;      /* Reserved */
    } RxDesc1;
    uint32_t RxDesc2; /* High bits of Receive buffer base address */
    uint32_t RxDesc3; /* Low bits of Receive buffer base address */

    uint32_t RxDesc4; /* Reserved */
    uint32_t RxDesc5; /* Reserved */
    uint32_t RxDesc6; /* rss type*/
    uint32_t RxDesc7; /* RSS hash value */
} __attribute__((aligned(4))) GMAC_RXDescTypeDef;


typedef enum
{
    GMAC_RCV_CRC_ERR_FRAME, /* receive crc error frame */
    GMAC_RCV_RUNT_FRAME,    /* receice runt frame */
} GMAC_RuntimeFlagTypeDef;

typedef struct
{
    uint32_t GMAC_DescNum; /* descriptor number */
    uint32_t GMAC_DescSz;  /* descriptor size (unit:bytes) */
    uint32_t GMAC_DescNtc; /* next desc to clean */
    uint32_t GMAC_DescNtu; /* next desc to use */
    uint32_t GMAC_FreeDescNum;
    union
    {
        GMAC_TXDescTypeDef *GMAC_TxDescBase;
        GMAC_RXDescTypeDef *GMAC_RxDescBase;
    };
} GMAC_RingTypeDef;

#define GMAC_NUMS      2
#define GMAC_QUEUE_NUM 1
#define GMAC_CLOCK     40000000

/**
 * GMAC id
 */
#define GMAC0 0
#define GMAC1 1

/**
 * Queue id
 */
#define GMAC_QUEUE0 0
#define GMAC_QUEUE1 1
#define GMAC_QUEUE2 2
#define GMAC_QUEUE3 3
#define GMAC_QUEUE4 4
#define GMAC_QUEUE5 5
#define GMAC_QUEUE6 6
#define GMAC_QUEUE7 7

/**
 * desc size in bytes
 */
#define GMAC_TX_DESC_BYTES 32
#define GMAC_RX_DESC_BYTES 32

#define GMAC_BASE(x)             ((x) == 0 ? (uint64_t)GMAC0_BASE : (uint64_t)GMAC1_BASE)
#define IS_GMAC_INDEX(__INDEX__) (((__INDEX__) == GMAC0) || ((__INDEX__) == GMAC1))

/**
  * @}
  */

/** @defgroup GMAC_Speed
  * @{
  */
#define GMAC_Speed_10M   ((uint32_t)0x00000000)
#define GMAC_Speed_100M  ((uint32_t)0x02000000)
#define GMAC_Speed_1000M ((uint32_t)0x03000000)
#define IS_GMAC_SPEED(SPEED)                                                             \
    (((SPEED) == GMAC_Speed_10M) || ((SPEED) == GMAC_Speed_100M) ||                      \
     ((SPEED) == GMAC_Speed_1000M))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup GMAC_Duplex
  * @{
  */
#define GMAC_Duplex_Full ((uint32_t)0x00000000)
#define GMAC_Duplex_Half ((uint32_t)0x04000000)

#define IS_GMAC_DUPLEX(DUPLEX)                                                           \
    (((DUPLEX) == GMAC_Duplex_Full) || ((DUPLEX) == GMAC_Duplex_Half))

/**
  * @}
  */

/** @defgroup GMAC_SYS_Interrupts
  * @{
  */
#define GMAC_IT_PDELAY_RESP_OUT ((uint32_t)0x01000000) // (1 << 24)
#define GMAC_IT_PDELAY_RESP_IN  ((uint32_t)0x00800000) // (1 << 23)
#define GMAC_IT_PDELAY_REQ_OUT  ((uint32_t)0x00400000) // (1 << 22)
#define GMAC_IT_PDELAY_REQ_IN   ((uint32_t)0x00200000) // (1 << 21)
#define GMAC_IT_DELAY_REQ_OUT   ((uint32_t)0x00100000) // (1 << 20)
#define GMAC_IT_DELAY_REQ_IN    ((uint32_t)0x00080000) // (1 << 19)
#define GMAC_IT_SYNC_OUT        ((uint32_t)0x00040000) // (1 << 18)
#define GMAC_IT_SYNC_IN         ((uint32_t)0x00020000) // (1 << 17)
#define GMAC_IT_TSU_SEC_INC     ((uint32_t)0x00010000) // (1 << 16)
#define GMAC_IT_RX_LPI_IN       ((uint32_t)0x00001000) // (1 << 12)
#define GMAC_IT_RX_LPI_EXIT     ((uint32_t)0x00000800) // (1 << 11)
#define GMAC_IT_PHYSTS_CHG      ((uint32_t)0x00000200) // (1 << 9)
#define GMAC_IT_BUS_ERR         ((uint32_t)0x00000100) // (1 << 8)
#define GMAC_IT_TPKT_LOST       ((uint32_t)0x00000080) // (1 << 7)

#define IS_GMAC_IT(IT)                                                                   \
    (((IT) == GMAC_IT_PDELAY_RESP_OUT) || ((IT) == GMAC_IT_PDELAY_RESP_IN) ||            \
     ((IT) == GMAC_IT_PDELAY_REQ_OUT) || ((IT) == GMAC_IT_PDELAY_REQ_IN) ||              \
     ((IT) == GMAC_IT_DELAY_REQ_OUT) || ((IT) == GMAC_IT_DELAY_REQ_IN) ||                \
     ((IT) == GMAC_IT_SYNC_OUT) || ((IT) == GMAC_IT_SYNC_IN) ||                          \
     ((IT) == GMAC_IT_TSU_SEC_INC) || ((IT) == GMAC_IT_RX_LPI_IN) ||                     \
     ((IT) == GMAC_IT_RX_LPI_EXIT) || ((IT) == GMAC_IT_PHYSTS_CHG) ||                    \
     ((IT) == GMAC_IT_BUS_ERR) || ((IT) == GMAC_IT_TPKT_LOST))

#define IS_GMAC_GET_IT IS_GMAC_IT

/**
  * @}
  */

/** @defgroup GMAC_QUEUE_Interrupts
  * @{
  */
#define GMAC_Q_IT_TX_PKT_LOST ((uint32_t)0x00000008) // (1 << 3)
#define GMAC_Q_IT_TX_PKT_CMPL ((uint32_t)0x00000004) // (1 << 2)
#define GMAC_Q_IT_RX_PKT_LOST ((uint32_t)0x00000002) // (1 << 1)
#define GMAC_Q_IT_RX_PKT_CMPL ((uint32_t)0x00000001) // (1 << 0)

#define IS_GMAC_Q_IT(IT)                                                                 \
    (((IT) == GMAC_Q_IT_TX_PKT_LOST) || ((IT) == GMAC_Q_IT_TX_PKT_CMPL) ||               \
     ((IT) == GMAC_Q_IT_RX_PKT_LOST) || ((IT) == GMAC_Q_IT_RX_PKT_CMPL))

#define IS_GMAC_GET_Q_IT IS_GMAC_Q_IT

/**
  * @}
  */


/** @defgroup GMAC_WOL_EVENT_
  * @{
  */
#define GMAC_WOL_EVENT_MAGICPKT ((uint32_t)0x00000004) // (1 << 2)

#define IS_GMAC_WOL_EVENT(x) (((x) == GMAC_WOL_EVENT_MAGICPKT))

#define IS_GMAC_GET_WOL_EVENT IS_GMAC_WOL_EVENT

/**
  * @}
  */

/** @defgroup GMAC_WOL_OUTPUT_SIGNAL_
  * @{
  */
#define GMAC_WOL_OUTPUT_SIGNAL_MASK      ((uint32_t)0x3000000) // (3 << 24)
#define GMAC_WOL_OUTPUT_SIGNAL_ACT_HIGH  ((uint32_t)0)         // (0 << 24)
#define GMAC_WOL_OUTPUT_SIGNAL_ACT_LOW   ((uint32_t)0x1000000) // (1 << 24)
#define GMAC_WOL_OUTPUT_SIGNAL_PULSE_POS ((uint32_t)0x2000000) // (2 << 24)
#define GMAC_WOL_OUTPUT_SIGNAL_PULSE_NEG ((uint32_t)0x3000000) // (3 << 24)

#define IS_GMAC_WOL_OUTPUT_SIGNAL(SIGNAL)                                                \
    (((SIGNAL) == GMAC_WOL_OUTPUT_SIGNAL_ACT_HIGH) ||                                    \
     ((SIGNAL) == GMAC_WOL_OUTPUT_SIGNAL_ACT_LOW) ||                                     \
     ((SIGNAL) == GMAC_WOL_OUTPUT_SIGNAL_PULSE_POS) ||                                   \
     ((SIGNAL) == GMAC_WOL_OUTPUT_SIGNAL_PULSE_NEG))

/**
  * @}
  */

/** @defgroup GMAC_RECV_FILTER_
  * @{
  */
#define GMAC_RECV_FILTER_BCAST ((uint32_t)0x00000800) /* Accept Broadcast Frames Enable */
#define GMAC_RECV_FILTER_MCAST ((uint32_t)0x00000400) /* Accept Multicast Frames Enable */
#define GMAC_RECV_FILTER_MHASH ((uint32_t)0x00000200) /* Accept Multicast Hash Filter Frames */
#define GMAC_RECV_FILTER_ADDR  ((uint32_t)0x00000010) /* Accept unicast Frames Enable */

#define IS_GMAC_RECV_FILTER(FILTER)                                                      \
    (((FILTER) == GMAC_RECV_FILTER_BCAST) || ((FILTER) == GMAC_RECV_FILTER_MCAST) ||     \
     ((FILTER) == GMAC_RECV_FILTER_MHASH) || ((FILTER) == GMAC_RECV_FILTER_ADDR))
/**
  * @}
  */

/** @defgroup GMAC_FILTER_DIR_
  * @{
  */
#define GMAC_ADDR_FILTER_DIR_SRC ((uint32_t)0x00000000)
#define GMAC_ADDR_FILTER_DIR_DST ((uint32_t)0x00010000)
#define IS_GMAC_ADDR_FILTER_DIR(DIR)                                                     \
    (((DIR) == GMAC_ADDR_FILTER_DIR_SRC) || ((DIR) == GMAC_ADDR_FILTER_DIR_DST))

/**
  * @}
  */

/** @defgroup GMAC_ADDR_FILTER_MODE_
  * @{
  */
#define GMAC_ADDR_FILTER_MODE_NORMAL  ((uint32_t)0x00000000)
#define GMAC_ADDR_FILTER_MODE_INVERSE ((uint32_t)0x00020000)
#define GMAC_ADDR_FILTER_MODE(MODE)                                                      \
    (((MODE) == GMAC_ADDR_FILTER_MODE_NORMAL) ||                                         \
     ((MODE) == GMAC_ADDR_FILTER_MODE_INVERSE))

/**
  * @}
  */

/** @defgroup CHKSUM_OFFLOAD_
  * @{
  */
#define CHKSUM_OFFLOAD_UDP_TX ((uint32_t)0x00000080)
#define CHKSUM_OFFLOAD_UDP_RX ((uint32_t)0x00000040)
#define CHKSUM_OFFLOAD_TCP_TX ((uint32_t)0x00000020)
#define CHKSUM_OFFLOAD_TCP_RX ((uint32_t)0x00000010)
#define CHKSUM_OFFLOAD_IP4_TX ((uint32_t)0x00000008)
#define CHKSUM_OFFLOAD_IP4_RX ((uint32_t)0x00000004)
#define CHKSUM_OFFLOAD_IP6_TX ((uint32_t)0x00000002)
#define CHKSUM_OFFLOAD_IP6_RX ((uint32_t)0x00000001)

#define IS_MAC_CHKSUM_OFFLOAD(OFFLOAD)                                                   \
    (((OFFLOAD) == CHKSUM_OFFLOAD_UDP_TX) || ((OFFLOAD) == CHKSUM_OFFLOAD_UDP_RX) ||     \
     ((OFFLOAD) == CHKSUM_OFFLOAD_TCP_TX) || ((OFFLOAD) == CHKSUM_OFFLOAD_TCP_RX) ||     \
     ((OFFLOAD) == CHKSUM_OFFLOAD_IP4_TX) || ((OFFLOAD) == CHKSUM_OFFLOAD_IP4_RX) ||     \
     ((OFFLOAD) == CHKSUM_OFFLOAD_IP6_TX) || ((OFFLOAD) == CHKSUM_OFFLOAD_IP6_RX))

/**
  * @}
  */

/** @defgroup GMAC_RSS_TYPE_
  * @{
  */
#define GMAC_RSS_TYPE_MAC_ADDR    ((uint32_t)0x00000400) // (1 << 10)
#define GMAC_RSS_TYPE_IPV4_TCP    ((uint32_t)0x00000200) // (1 << 9)
#define GMAC_RSS_TYPE_IPV4        ((uint32_t)0x00000100) // (1 << 8)
#define GMAC_RSS_TYPE_IPV6_TCP_EX ((uint32_t)0x00000080) // (1 << 7)
#define GMAC_RSS_TYPE_IPV6_EX     ((uint32_t)0x00000040) // (1 << 6)
#define GMAC_RSS_TYPE_IPV6        ((uint32_t)0x00000020) // (1 << 5)
#define GMAC_RSS_TYPE_IPV6_TCP    ((uint32_t)0x00000010) // (1 << 4)
#define GMAC_RSS_TYPE_IPV4_UDP    ((uint32_t)0x00000008) // (1 << 3)
#define GMAC_RSS_TYPE_IPV6_UDP    ((uint32_t)0x00000004) // (1 << 2)
#define GMAC_RSS_TYPE_IPV6_UDP_EX ((uint32_t)0x00000002) // (1 << 1)

#define IS_GMAC_RSS_TYPE(TYPE)                                                           \
    ((((TYPE) == GMAC_RSS_TYPE_MAC_ADDR)) || (((TYPE) == GMAC_RSS_TYPE_IPV4_TCP)) ||     \
     (((TYPE) == GMAC_RSS_TYPE_IPV4)) || (((TYPE) == GMAC_RSS_TYPE_IPV6_TCP_EX)) ||      \
     (((TYPE) == GMAC_RSS_TYPE_IPV6_EX)) || (((TYPE) == GMAC_RSS_TYPE_IPV6)) ||          \
     (((TYPE) == GMAC_RSS_TYPE_IPV6_TCP)) || (((TYPE) == GMAC_RSS_TYPE_IPV4_UDP)) ||     \
     (((TYPE) == GMAC_RSS_TYPE_IPV6_UDP)) || (((TYPE) == GMAC_RSS_TYPE_IPV6_UDP_EX)))

/**
  * @}
  */

/** @defgroup GMAC_RXDES1_PTP_
  * @{
  */
#define GMAC_RXDES1_PTP_NO_TMSTMP    ((uint32_t)0x00001000)
#define GMAC_RXDES1_PTP_EVENT_TMSTMP ((uint32_t)0x00002000)
#define GMAC_RXDES1_PTP_PEER_TMSTMP  ((uint32_t)0x00003000)

/**
  * @}
  */

/* function export */

void GMAC_Init(uint32_t GMAC_ID);
void GMAC_DeInit(uint32_t GMAC_ID);
void GMAC_RuntPaddingCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_TxPktCrcAppendCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_SetTxWriteBackThreshold(uint32_t GMAC_ID, uint8_t Threshold);
uint8_t GMAC_GetTxWriteBackThreshold(uint32_t GMAC_ID);
void GMAC_SetTxWriteBackTimeout(uint32_t GMAC_ID, uint16_t Timeout);
uint16_t GMAC_GetTxWriteBackTimeout(uint32_t GMAC_ID);
void GMAC_SetTxFetchThreshold(uint32_t GMAC_ID, uint32_t QUEUE_ID, uint8_t Threshold);
uint8_t GMAC_GetTxFetchThreshold(uint32_t GMAC_ID, uint32_t QUEUE_ID);
void GMAC_SetTxFetchTimeout(uint32_t GMAC_ID, uint32_t QUEUE_ID, uint16_t Timeout);
uint8_t GMAC_GetTxFetchTimeout(uint32_t GMAC_ID, uint32_t QUEUE_ID);
void GMAC_SetRxWriteBackThreshold(uint32_t GMAC_ID, uint8_t Threshold);
uint8_t GMAC_GetRxWriteBackThreshold(uint32_t GMAC_ID);
void GMAC_SetRxWriteBackTimeout(uint32_t GMAC_ID, uint16_t Timeout);
uint16_t GMAC_GetRxWriteBackTimeout(uint32_t GMAC_ID);
void GMAC_SetRxFetchThreshold(uint32_t GMAC_ID, uint32_t QUEUE_ID, uint8_t Threshold);
uint8_t GMAC_GetRxFetchThreshold(uint32_t GMAC_ID, uint32_t QUEUE_ID);
void GMAC_SetRxFetchTimeout(uint32_t GMAC_ID, uint32_t QUEUE_ID, uint16_t Timeout);
uint16_t GMAC_GetRxFetchTimeout(uint32_t GMAC_ID, uint32_t QUEUE_ID);
uint32_t GMAC_GetHardwareRevision(uint32_t GMAC_ID);
uint32_t GMAC_GetHardwareFeature(uint32_t GMAC_ID);
void GMAC_RxCRCErrorFrameCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_RxRuntFrameCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_SetTxInterruptCoalesceThreshold(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                          uint8_t Threshold);
uint8_t GMAC_GetTxInterruptCoalesceThreshold(uint32_t GMAC_ID, uint8_t QUEUE_ID);
void GMAC_SetRxInterruptCoalesceThreshold(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                          uint8_t Threshold);
uint8_t GMAC_GetRxInterruptCoalesceThreshold(uint32_t GMAC_ID, uint8_t QUEUE_ID);
void GMAC_SysITConfig(uint32_t GMAC_ID, uint32_t GMAC_SYS_IT, FunctionalState NewState);
ITStatus GMAC_GetSysITStatus(uint32_t GMAC_ID, uint32_t GMAC_SYS_IT);
void GMAC_ClearSysITPendingBit(uint32_t GMAC_ID, uint32_t GMAC_SYS_IT);
void GMAC_SetEEEWakeupCounter(uint32_t GMAC_ID, uint16_t WakeupCounter);
uint16_t GMAC_GetEEEWakeupCounter(uint32_t GMAC_ID);
void GMAC_EEEWakeupSendLPI(uint32_t GMAC_ID);

uint16_t GMAC_ReadPHYRegister(uint32_t GMAC_ID, uint16_t PHYReg);
void GMAC_WritePHYRegister(uint32_t GMAC_ID, uint16_t PHYReg, uint16_t PHYValue);
void GMAC_PHYAddressConfig(uint32_t GMAC_ID, int32_t PHYAddress);
int32_t GMAC_GetPHYAddress(uint32_t GMAC_ID);
int32_t GMAC_PHYManagementDataClockConfig(uint32_t GMAC_ID, uint32_t Freq);
void GMAC_PHYPowerDownCmd(uint32_t GMAC_ID, FunctionalState NewState);

void GMAC_FilterConfig(uint32_t GMAC_ID, uint32_t GMAC_FILTER_TYPE,
                       FunctionalState NewState);
uint8_t GMAC_McastHashTblConfig(uint32_t GMAC_ID, const uint8_t *MACAddr);
void GMAC_GetMcastHashTbl(uint32_t GMAC_ID, uint32_t *Math0, uint32_t *Math1);

void GMAC_UcastFilterModeConfig(uint32_t GMAC_ID, uint32_t FilterDir,
                                uint32_t FilterMode);
void GMAC_GetUcastFilterMode(uint32_t GMAC_ID, uint32_t *FilterDir, uint32_t *FilterMode);

void GMAC_UcastFilterMACAddressConfig(uint32_t GMAC_ID, uint8_t FilterId,
                                      uint8_t MACAddr[6]);
void GMAC_GetUcastFilterMACAddress(uint32_t GMAC_ID, uint8_t FilterId,
                                   uint8_t MACAddr[6]);
void GMAC_UcastFilterCmd(uint32_t GMAC_ID, uint8_t FilterId, FunctionalState NewState);
void GMAC_IncreaseIFG(uint32_t GMAC_ID, uint8_t IFGCount);
void GMAC_DecreaseIFG(uint32_t GMAC_ID, uint8_t IFGCount);
uint8_t GMAC_GetIFGCount(uint32_t GMAC_ID);
void GMAC_JumboFrameCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_MACAddressConfig(uint32_t GMAC_ID, const uint8_t *MACAddr);
void GMAC_GetMACAddress(uint32_t GMAC_ID, uint8_t *MACAddr);

void GMAC_FlowCtrlConfig(uint32_t GMAC_ID, uint16_t PauseTime, uint8_t JamLen);
void GMAC_SendFlowControlPauseFrame(uint32_t GMAC_ID);
void GMAC_FlowCtrlCmd(uint32_t GMAC_ID, FunctionalState NewState);

void GMAC_ChecksumOffloadConfig(uint32_t GMAC_ID, uint32_t GMAC_CHKSUM_TYPE,
                                FunctionalState NewState);


void GMAC_SpeedConfig(uint32_t GMAC_ID, uint32_t SPEED);
void GMAC_DuplexConfig(uint32_t GMAC_ID, uint32_t DUPLEX);
uint64_t GMAC_GetStatistics(uint32_t GMAC_ID);

void GMAC_SetWakeUpEvent(uint32_t GMAC_ID, uint32_t Event);
uint32_t GMAC_GetWakeUpEvent(uint32_t GMAC_ID);
void GMAC_EnterWakeUpDetection(uint32_t GMAC_ID);
void GMAC_ExitWakeUpDetection(uint32_t GMAC_ID);
FlagStatus GMAC_GetWakeUpEventStatus(uint32_t GMAC_ID, uint32_t GMAC_WOL_WakeUpEvent);
void GMAC_SetWakeUpOutputSignalType(uint32_t GMAC_ID, uint32_t SignalType);
uint32_t GMAC_GetWakeUpOutputSignalType(uint32_t GMAC_ID);


void GMAC_TransmissionCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_ReceptionCmd(uint32_t GMAC_ID, FunctionalState NewState);
ErrorStatus GMAC_TxQueueInit(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint8_t *DescBuf,
                             uint32_t DescNum);
ErrorStatus GMAC_RxQueueInit(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint8_t *DescBuf,
                             uint32_t DescNum);
void GMAC_RxBufferSizeConfig(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint32_t Size);
int32_t GMAC_AttachRxDescBuffer(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint8_t *Buf,
                                uint32_t DescIdx);

void GMAC_QueueTransmissionCmd(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                               FunctionalState NewState);
void GMAC_QueueReceptionCmd(uint32_t GMAC_ID, uint8_t QUEUE_ID, FunctionalState NewState);
void GMAC_QueueITConfig(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint32_t GMAC_QUEUE_IT,
                        FunctionalState NewState);
ITStatus GMAC_GetQueueITStatus(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                               uint32_t GMAC_QUEUE_IT);
void GMAC_ClearQueueITPendingBit(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                 uint32_t GMAC_QUEUE_IT);
uint32_t GMAC_GetTxUnusedDescNum(uint32_t GMAC_ID, uint8_t QUEUE_ID);
GMAC_TXDescTypeDef *GMAC_GetTxNextToUseDesc(uint32_t GMAC_ID, uint8_t QUEUE_ID);

int32_t GMAC_AttachTxFrameBufToDesc(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                    GMAC_TXDescTypeDef *Desc, uint8_t *FrameData,
                                    uint32_t FrameLen);
int32_t GMAC_TxKickoff(uint32_t GMAC_ID, uint8_t QUEUE_ID);
uint8_t *GMAC_PollTxTransmittedFrame(uint32_t GMAC_ID, uint8_t QUEUE_ID, GMAC_TXDescTypeDef *txdesc);
void GMAC_DetachTxFrameBufFromDesc(uint32_t GMAC_ID, uint8_t QUEUE_ID, uint8_t *Buf);
int32_t GMAC_PollRxReceivedFrame(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                 GMAC_FrameHandleTypeDef *FrameHandle);
uint8_t *GMAC_LockAndDetachRxFrameSegBuf(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                         GMAC_FrameHandleTypeDef FrameHandle,
                                         uint32_t SegIdx, uint32_t *SegLen);
GMAC_RXDescTypeDef *GMAC_GetRxFrameSegDesc(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                                           GMAC_FrameHandleTypeDef FrameHandle,
                                           uint32_t SegIdx);
void GMAC_AttachRxFrameSegBuf(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                              GMAC_FrameHandleTypeDef FrameHandle, uint32_t SegIdx,
                              uint8_t *Buf);
void GMAC_UnlockRxFrameSegBuf(uint32_t GMAC_ID, uint8_t QUEUE_ID,
                              GMAC_FrameHandleTypeDef FrameHandle, uint32_t SegIdx);

void GMAC_RSSCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_RSSTypeConfig(uint32_t GMAC_ID, uint32_t RSS_TYPE, FunctionalState NewState);
uint32_t GMAC_GetRSSType(uint32_t GMAC_ID);
void GMAC_SetRSSRandomKey(uint32_t GMAC_ID, uint32_t *Key);
void GMAC_GetRSSRandomKey(uint32_t GMAC_ID, uint32_t *Key);

void GMAC_PTPCmd(uint32_t GMAC_ID, FunctionalState NewState);
void GMAC_SetPTPTxUnicastIPDestinationAddress(uint32_t GMAC_ID, uint32_t IPAddress);
uint32_t GMAC_GetPTPTxUnicastIPDestinationAddress(uint32_t GMAC_ID);
void GMAC_SetPTPRxUnicastIPDestinationAddress(uint32_t GMAC_ID, uint32_t IPAddress);
uint32_t GMAC_GetPTPRxUnicastIPDestinationAddress(uint32_t GMAC_ID);
void GMAC_SetPTPBaseTime(uint32_t GMAC_ID, uint32_t Second, uint32_t Nanosecond,
                         uint32_t NanoNanosecond);
void GMAC_GetPTPBaseTime(uint32_t GMAC_ID, uint32_t *Second, uint32_t *Nanosecond,
                         uint32_t *NanoNanosecond);
void GMAC_SetPTPBaseTimeClockPeriod(uint32_t GMAC_ID, uint32_t Nanosecond,
                                    uint32_t NanoNanosecond);
void GMAC_IncreasePTPBaseTimer(uint32_t GMAC_ID, uint32_t Nanosecond);
void GMAC_DecreasePTPBaseTimer(uint32_t GMAC_ID, uint32_t Nanosecond);
void GMAC_GetPTPBaseTimerClockPeriod(uint32_t GMAC_ID, uint32_t *Nanosecond,
                                     uint32_t *NanoNanosecond);
uint32_t GMAC_GetPTPRxFrameTimestampSecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPRxFrameTimestampNanosecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPRxPeerTimestampSecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPRxPeerTimestampNanosecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPTxFrameTimestampSecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPTxFrameTimestampNanosecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPTxPeerTimestampSecond(uint32_t GMAC_ID);
uint32_t GMAC_GetPTPTxPeerTimestampNanosecond(uint32_t GMAC_ID);

void GMAC_DumpReg(uint32_t GMAC_ID);

#ifdef __cplusplus
}
#endif

#endif /*__T690_GMAC_H */


/************************ (C) COPYRIGHT TIH *****END OF FILE*******************/
