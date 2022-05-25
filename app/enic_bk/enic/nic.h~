#ifndef __NIC_H
#define __NIC_H

#include "t690.h"
#include "freg.h"

#define GMAC0                      0
#define GMAC1                      1

#define NIC_PRINT                  0
#define MSG_PRINT                  0
#define CMD_PRINT                  0
#define FREG_PRINT                 0
#define TX_PRINT                   0
#define GENERAL_PRINT              0
#define JOB_PRINT                  0
#define RX_PRINT                   0

#define NIC_PF_NUM                 1
#define NIC_USING_GMAC0            1
#define NIC_USING_GMAC1            0

#define NIC_INT_USING_MSI          0
#define NIC_INT_USING_LEGACY       0

#define NIC_QPAIR_NUM               1
#define NIC_SHADOW_TXDESC_PER_QUEUE 4
#define NIC_SHADOW_RXDESC_PER_QUEUE 4
#define NIC_GMAC_TXDESC_NUM         (NIC_SHADOW_TXDESC_PER_QUEUE * NIC_QPAIR_NUM)
#define NIC_GMAC_RXDESC_NUM         (NIC_SHADOW_RXDESC_PER_QUEUE * NIC_QPAIR_NUM)

#define NIC_DMA_IN_CH_NUM           2
#define NIC_DMA_OUT_CH_NUM          2
#define NIC_DMA_CH_NUM              (NIC_DMA_IN_CH_NUM + NIC_DMA_OUT_CH_NUM)
#define NIC_PER_DMA_DESC_NUM        (NIC_SHADOW_TXDESC_PER_QUEUE)

#define NIC_PBUF_NUM                2
#define NIC_PBUF_LEN                100

#define NIC_AT_TABLE_ENTIES         40
#define NIC_REAL_REG_SPACE          0xD00

/* fake register base address in RAM, total size = 1K, 512B per GMAC, upward grow*/
#define NIC_FREG_RAM_SPACE_PER_PF   (512)
#define NIC_FREG_AT_OFFSET          (10)

/* PCIe related configures */
#define NIC_PCIE_P0_BAR0_LEN        (4096)
#define NIC_PCIE_P0_BAR2_LEN        (4096)
#define NIC_PCIE_P1_BAR0_LEN        (4096)
#define NIC_PCIE_P1_BAR2_LEN        (4096)
#define NIC_PCIE_MSIX_LEN           (1024)
#define NIC_PCIE_MSI_TBL_OFFSET     (0)
#define NIC_PCIE_MSI_PBA_OFFSET     (NIC_PCIE_MSI_TBL_OFFSET + 512)

#define NIC_PIPELINE_STOPPED        0
#define NIC_PIPELINE_STARTED        (!(NIC_PIPELINE_STOPPED))

#define TIHGBE_RETA_SIZE 128

/*
 *	IEEE 802.3 Ethernet magic constants.  The frame sizes omit the preamble
 *	and FCS/CRC (frame check sequence).
 */
#define ETH_ALEN      6       /* Octets in one ethernet addr */
#define ETH_TLEN      2       /* Octets in ethernet type field */
#define ETH_HLEN      14      /* Total octets in header. */
#define ETH_ZLEN      60      /* Min. octets in frame sans FCS */
#define ETH_DATA_LEN  1500    /* Max. octets in payload */
#define ETH_FRAME_LEN 1514    /* Max. octets in frame sans FCS */
#define ETH_FCS_LEN   4       /* Octets in the FCS */
#define ETH_MIN_MTU   68      /* Min IPv4 MTU per RFC791 */
#define ETH_MAX_MTU   0xFFFFU /* 65535, same as IP_MAX_MTU */

#define VLAN_HLEN     4  /* The additional bytes required by VLAN (in addition to the Ethernet header) */
#define VLAN_ETH_HLEN 18 /* Total octets in header */
#define VLAN_ETH_ZLEN 64 /* Min. octets in frame sans FCS */

/*
 * According to 802.3ac, the packet can be 4 bytes longer. --Klika Jan
 */
#define VLAN_ETH_DATA_LEN  1500 /* Max. octets in payload */
#define VLAN_ETH_FRAME_LEN 1518 /* Max. octets in frame sans FCS */
#define VLAN_MAX_DEPTH     8    /* Max. number of nested VLAN tags parsed */

/* rx weight */
#define NIC_RX_WEIGHT 16
#endif
