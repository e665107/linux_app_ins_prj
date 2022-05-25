#ifndef __T690_PHY_H
#define __T690_PHY_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "t690.h"



typedef enum {
	PHY_Speed_1000M = 0x00,
	PHY_Speed_100M = 0x01,
	PHY_Speed_10M = 0x02,
	PHY_Speed_Auto = 0x03
} PHYSpeed_TypeDef;

typedef enum {
	PHY_FullDuplex = 0x00,
	PHY_HalfDuplex = 0x01,
} PHYDuplex_TypeDef;

typedef enum {
	PHY_NoLink = 0x00,
	PHY_Link = 0x01,
} PHYLinked_TypeDef;

typedef struct {
	PHYLinked_TypeDef Linked;
	PHYDuplex_TypeDef Duplex;
	PHYSpeed_TypeDef Speed;
} PHY_LinkStatusTypeDef;

/* Generic MII registers. */
#define PHY_MII_BMCR		0x00 /* Basic mode control register */
#define PHY_MII_BMSR		0x01 /* Basic mode status register  */
#define PHY_MII_PHYSID1		0x02 /* PHYS ID 1                   */
#define PHY_MII_PHYSID2		0x03 /* PHYS ID 2                   */
#define PHY_MII_ADVERTISE	0x04 /* Advertisement control reg   */
#define PHY_MII_LPA			0x05 /* Link partner ability reg    */
#define PHY_MII_EXPANSION	0x06 /* Expansion register          */
#define PHY_MII_CTRL1000	0x09 /* 1000BASE-T control          */
#define PHY_MII_STAT1000	0x0a /* 1000BASE-T status           */
#define PHY_MII_MMD_CTRL	0x0d /* MMD Access Control Register */
#define PHY_MII_MMD_DATA	0x0e /* MMD Access Data Register */
#define PHY_MII_ESTATUS		0x0f /* Extended Status             */
#define PHY_MII_DCOUNTER	0x12 /* Disconnect counter          */
#define PHY_MII_FCSCOUNTER	0x13 /* False carrier counter       */
#define PHY_MII_NWAYTEST	0x14 /* N-way auto-neg test reg     */
#define PHY_MII_RERRCOUNTER 0x15 /* Receive error counter       */
#define PHY_MII_SREVISION	0x16 /* Silicon revision            */
#define PHY_MII_RESV1		0x17 /* Reserved...                 */
#define PHY_MII_LBRERROR	0x18 /* Lpback, rx, bypass error    */
#define PHY_MII_PHYADDR		0x19 /* PHY address                 */
#define PHY_MII_RESV2		0x1a /* Reserved...                 */
#define PHY_MII_TPISTATUS	0x1b /* TPI status for 10mbps       */
#define PHY_MII_NCONFIG		0x1c /* Network interface config    */

/* private MII registers */
#define PHY_MII_CONTROL2 0x1F /* PHY control 2 */

/* Basic mode control register. */
#define PHY_MII_BMCR_RESV	   0x003f /* Unused...                   */
#define PHY_MII_BMCR_SPEED1000 0x0040 /* MSB of Speed (1000)         */
#define PHY_MII_BMCR_CTST	   0x0080 /* Collision test              */
#define PHY_MII_BMCR_FULLDPLX  0x0100 /* Full duplex                 */
#define PHY_MII_BMCR_ANRESTART 0x0200 /* Auto negotiation restart    */
#define PHY_MII_BMCR_ISOLATE   0x0400 /* Isolate data paths from MII */
#define PHY_MII_BMCR_PDOWN	   0x0800 /* Enable low power state      */
#define PHY_MII_BMCR_ANENABLE  0x1000 /* Enable auto negotiation     */
#define PHY_MII_BMCR_SPEED100  0x2000 /* Select 100Mbps              */
#define PHY_MII_BMCR_LOOPBACK  0x4000 /* TXD loopback bits           */
#define PHY_MII_BMCR_RESET	   0x8000 /* Reset to default state      */
#define PHY_MII_BMCR_SPEED10   0x0000 /* Select 10Mbps               */

/* Basic mode status register. */
#define PHY_MII_BMSR_ERCAP		  0x0001 /* Ext-reg capability          */
#define PHY_MII_BMSR_JCD		  0x0002 /* Jabber detected             */
#define PHY_MII_BMSR_LSTATUS	  0x0004 /* Link status                 */
#define PHY_MII_BMSR_ANEGCAPABLE  0x0008 /* Able to do auto-negotiation */
#define PHY_MII_BMSR_RFAULT		  0x0010 /* Remote fault detected       */
#define PHY_MII_BMSR_ANEGCOMPLETE 0x0020 /* Auto-negotiation complete   */
#define PHY_MII_BMSR_RESV		  0x00c0 /* Unused...                   */
#define PHY_MII_BMSR_ESTATEN	  0x0100 /* Extended Status in R15      */
#define PHY_MII_BMSR_100HALF2	  0x0200 /* Can do 100BASE-T2 HDX       */
#define PHY_MII_BMSR_100FULL2	  0x0400 /* Can do 100BASE-T2 FDX       */
#define PHY_MII_BMSR_10HALF		  0x0800 /* Can do 10mbps, half-duplex  */
#define PHY_MII_BMSR_10FULL		  0x1000 /* Can do 10mbps, full-duplex  */
#define PHY_MII_BMSR_100HALF	  0x2000 /* Can do 100mbps, half-duplex */
#define PHY_MII_BMSR_100FULL	  0x4000 /* Can do 100mbps, full-duplex */
#define PHY_MII_BMSR_100BASE4	  0x8000 /* Can do 100mbps, 4k packets  */

/* Advertisement control register. */
#define PHY_MII_ADVERTISE_SLCT			0x001f /* Selector bits               */
#define PHY_MII_ADVERTISE_CSMA			0x0001 /* Only selector supported     */
#define PHY_MII_ADVERTISE_10HALF		0x0020 /* Try for 10mbps half-duplex  */
#define PHY_MII_ADVERTISE_1000XFULL		0x0020 /* Try for 1000BASE-X full-duplex */
#define PHY_MII_ADVERTISE_10FULL		0x0040 /* Try for 10mbps full-duplex  */
#define PHY_MII_ADVERTISE_1000XHALF		0x0040 /* Try for 1000BASE-X half-duplex */
#define PHY_MII_ADVERTISE_100HALF		0x0080 /* Try for 100mbps half-duplex */
#define PHY_MII_ADVERTISE_1000XPAUSE	0x0080 /* Try for 1000BASE-X pause    */
#define PHY_MII_ADVERTISE_100FULL		0x0100 /* Try for 100mbps full-duplex */
#define PHY_MII_ADVERTISE_1000XPSE_ASYM 0x0100 /* Try for 1000BASE-X asym pause */
#define PHY_MII_ADVERTISE_100BASE4		0x0200 /* Try for 100mbps 4k packets  */
#define PHY_MII_ADVERTISE_PAUSE_CAP		0x0400 /* Try for pause               */
#define PHY_MII_ADVERTISE_PAUSE_ASYM	0x0800 /* Try for asymetric pause     */
#define PHY_MII_ADVERTISE_RESV			0x1000 /* Unused...                   */
#define PHY_MII_ADVERTISE_RFAULT		0x2000 /* Say we can detect faults    */
#define PHY_MII_ADVERTISE_LPACK			0x4000 /* Ack link partners response  */
#define PHY_MII_ADVERTISE_NPAGE			0x8000 /* Next page bit               */

#define PHY_ADVERTISE_FULL (PHY_MII_ADVERTISE_100FULL | PHY_MII_ADVERTISE_10FULL | PHY_MII_ADVERTISE_CSMA)

#define PHY_ADVERTISE_ALL                                                                                              \
	(PHY_MII_ADVERTISE_10HALF | PHY_MII_ADVERTISE_10FULL | PHY_MII_ADVERTISE_100HALF | PHY_MII_ADVERTISE_100FULL)

/* Link partner ability register. */
#define PHY_MII_LPA_SLCT			0x001f /* Same as advertise selector  */
#define PHY_MII_LPA_10HALF			0x0020 /* Can do 10mbps half-duplex   */
#define PHY_MII_LPA_1000XFULL		0x0020 /* Can do 1000BASE-X full-duplex */
#define PHY_MII_LPA_10FULL			0x0040 /* Can do 10mbps full-duplex   */
#define PHY_MII_LPA_1000XHALF		0x0040 /* Can do 1000BASE-X half-duplex */
#define PHY_MII_LPA_100HALF			0x0080 /* Can do 100mbps half-duplex  */
#define PHY_MII_LPA_1000XPAUSE		0x0080 /* Can do 1000BASE-X pause     */
#define PHY_MII_LPA_100FULL			0x0100 /* Can do 100mbps full-duplex  */
#define PHY_MII_LPA_1000XPAUSE_ASYM 0x0100 /* Can do 1000BASE-X pause asym*/
#define PHY_MII_LPA_100BASE4		0x0200 /* Can do 100mbps 4k packets   */
#define PHY_MII_LPA_PAUSE_CAP		0x0400 /* Can pause                   */
#define PHY_MII_LPA_PAUSE_ASYM		0x0800 /* Can pause asymetrically     */
#define PHY_MII_LPA_RESV			0x1000 /* Unused...                   */
#define PHY_MII_LPA_RFAULT			0x2000 /* Link partner faulted        */
#define PHY_MII_LPA_LPACK			0x4000 /* Link partner acked us       */
#define PHY_MII_LPA_NPAGE			0x8000 /* Next page bit               */

#define PHY_LPA_DUPLEX (PHY_MII_LPA_10FULL | PHY_MII_LPA_100FULL)
#define PHY_LPA_100	   (PHY_MII_LPA_100FULL | PHY_MII_LPA_100HALF | PHY_MII_LPA_100BASE4)

/* Expansion register for auto-negotiation. */
#define PHY_MII_EXPANSION_NWAY		  0x0001 /* Can do N-way auto-nego      */
#define PHY_MII_EXPANSION_LCWP		  0x0002 /* Got new RX page code word   */
#define PHY_MII_EXPANSION_ENABLENPAGE 0x0004 /* This enables npage words    */
#define PHY_MII_EXPANSION_NPCAPABLE	  0x0008 /* Link partner supports npage */
#define PHY_MII_EXPANSION_MFAULTS	  0x0010 /* Multiple faults detected    */
#define PHY_MII_EXPANSION_RESV		  0xffe0 /* Unused...                   */

#define PHY_MII_ESTATUS_1000_XFULL 0x8000 /* Can do 1000BX Full */
#define PHY_MII_ESTATUS_1000_XHALF 0x4000 /* Can do 1000BX Half */
#define PHY_MII_ESTATUS_1000_TFULL 0x2000 /* Can do 1000BT Full          */
#define PHY_MII_ESTATUS_1000_THALF 0x1000 /* Can do 1000BT Half          */

/* N-way test register. */
#define PHY_MII_NWAYTEST_RESV1	  0x00ff /* Unused...                   */
#define PHY_MII_NWAYTEST_LOOPBACK 0x0100 /* Enable loopback for N-way   */
#define PHY_MII_NWAYTEST_RESV2	  0xfe00 /* Unused...                   */

/* 1000BASE-T Control register */
#define PHY_MII_ADVERTISE_1000FULL	  0x0200 /* Advertise 1000BASE-T full duplex */
#define PHY_MII_ADVERTISE_1000HALF	  0x0100 /* Advertise 1000BASE-T half duplex */
#define PHY_MII_CTL1000_AS_MASTER	  0x0800
#define PHY_MII_CTL1000_ENABLE_MASTER 0x1000

/* 1000BASE-T Status register */
#define PHY_MII_LPA_1000LOCALRXOK 0x2000 /* Link partner local receiver status */
#define PHY_MII_LPA_1000REMRXOK	  0x1000 /* Link partner remote receiver status */
#define PHY_MII_LPA_1000FULL	  0x0800 /* Link partner 1000BASE-T full duplex */
#define PHY_MII_LPA_1000HALF	  0x0400 /* Link partner 1000BASE-T half duplex */

/* Flow control flags */
#define PHY_FLOW_CTRL_TX 0x01
#define PHY_FLOW_CTRL_RX 0x02



/* PHY_MII_CTRL1000 masks */
#define PHY_MII_1000BTCR_1000FD 0x0200
#define PHY_MII_1000BTCR_1000HD 0x0100

/* PHY_MII_STAT1000 masks */
#define PHY_MII_1000BTSR_MSCF	0x8000
#define PHY_MII_1000BTSR_MSCR	0x4000
#define PHY_MII_1000BTSR_LRS	0x2000
#define PHY_MII_1000BTSR_RRS	0x1000
#define PHY_MII_1000BTSR_1000FD 0x0800
#define PHY_MII_1000BTSR_1000HD 0x0400

/* phy EXSR */
#define PHY_MII_ESTATUS_1000XF 0x8000
#define PHY_MII_ESTATUS_1000XH 0x4000


/* Indicates what features are supported by the interface. */
#define PHY_SUPPORTED_10baseT_Half		(1 << 0)
#define PHY_SUPPORTED_10baseT_Full		(1 << 1)
#define PHY_SUPPORTED_100baseT_Half		(1 << 2)
#define PHY_SUPPORTED_100baseT_Full		(1 << 3)
#define PHY_SUPPORTED_1000baseT_Half	(1 << 4)
#define PHY_SUPPORTED_1000baseT_Full	(1 << 5)
#define PHY_SUPPORTED_Autoneg			(1 << 6)
#define PHY_SUPPORTED_TP				(1 << 7)
#define PHY_SUPPORTED_AUI				(1 << 8)
#define PHY_SUPPORTED_MII				(1 << 9)
#define PHY_SUPPORTED_FIBRE				(1 << 10)
#define PHY_SUPPORTED_BNC				(1 << 11)
#define PHY_SUPPORTED_10000baseT_Full	(1 << 12)
#define PHY_SUPPORTED_Pause				(1 << 13)
#define PHY_SUPPORTED_Asym_Pause		(1 << 14)
#define PHY_SUPPORTED_2500baseX_Full	(1 << 15)
#define PHY_SUPPORTED_Backplane			(1 << 16)
#define PHY_SUPPORTED_1000baseKX_Full	(1 << 17)
#define PHY_SUPPORTED_10000baseKX4_Full (1 << 18)
#define PHY_SUPPORTED_10000baseKR_Full	(1 << 19)
#define PHY_SUPPORTED_10000baseR_FEC	(1 << 20)
#define PHY_SUPPORTED_1000baseX_Half	(1 << 21)
#define PHY_SUPPORTED_1000baseX_Full	(1 << 22)

/* Indicates what features are advertised by the interface. */
#define PHY_ADVERTISED_10baseT_Half		 (1 << 0)
#define PHY_ADVERTISED_10baseT_Full		 (1 << 1)
#define PHY_ADVERTISED_100baseT_Half	 (1 << 2)
#define PHY_ADVERTISED_100baseT_Full	 (1 << 3)
#define PHY_ADVERTISED_1000baseT_Half	 (1 << 4)
#define PHY_ADVERTISED_1000baseT_Full	 (1 << 5)
#define PHY_ADVERTISED_Autoneg			 (1 << 6)
#define PHY_ADVERTISED_TP				 (1 << 7)
#define PHY_ADVERTISED_AUI				 (1 << 8)
#define PHY_ADVERTISED_MII				 (1 << 9)
#define PHY_ADVERTISED_FIBRE			 (1 << 10)
#define PHY_ADVERTISED_BNC				 (1 << 11)
#define PHY_ADVERTISED_10000baseT_Full	 (1 << 12)
#define PHY_ADVERTISED_Pause			 (1 << 13)
#define PHY_ADVERTISED_Asym_Pause		 (1 << 14)
#define PHY_ADVERTISED_2500baseX_Full	 (1 << 15)
#define PHY_ADVERTISED_Backplane		 (1 << 16)
#define PHY_ADVERTISED_1000baseKX_Full	 (1 << 17)
#define PHY_ADVERTISED_10000baseKX4_Full (1 << 18)
#define PHY_ADVERTISED_10000baseKR_Full	 (1 << 19)
#define PHY_ADVERTISED_10000baseR_FEC	 (1 << 20)
#define PHY_ADVERTISED_1000baseX_Half	 (1 << 21)
#define PHY_ADVERTISED_1000baseX_Full	 (1 << 22)

typedef struct {

	int32_t (*PHY_Init)(uint32_t GMAC_ID);
	void (*PHY_DeInit)(uint32_t GMAC_ID);

	uint32_t (*PHY_GetMDCFreq)(uint32_t GMAC_ID);

	void (*PHY_ITConfig)(uint32_t GMAC_ID, uint32_t PHY_IT);
	ITStatus (*PHY_GetITStatus)(uint32_t GMAC_ID, uint32_t PHY_IT);
	void (*PHY_ClearITPendingBit)(uint32_t GMAC_ID, uint32_t PHY_IT);

	void (*PHY_SpeedDuplexConfig)(uint32_t GMAC_ID, PHYSpeed_TypeDef Speed, PHYDuplex_TypeDef Duplex);

	PHY_LinkStatusTypeDef (*PHY_GetLinkStatus)(uint32_t GMAC_ID);

} PHY_OperationsTypeDef;

#ifdef __cplusplus
}
#endif

#endif /*__T690_PHY_H */

/************************ (C) COPYRIGHT TIH *****END OF FILE*******************/
