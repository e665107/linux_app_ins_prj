/*
 * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
 * Copyright (c) 2019 Nuclei Limited. All rights reserved.
 * Copyright (c) 2021 TIH Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/******************************************************************************
 * @file     t690.h
 * @brief    NMSIS Nuclei NX Core Peripheral Access Layer Header File for
 *           Device T690
 * @version  V1.10
 * @date     30. July 2021
 ******************************************************************************/

#ifndef __T690_H__   
#define __T690_H__

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup TIH
  * @{
  */

/** @addtogroup T690
  * @{
  */

/** @addtogroup Configuration_of_NMSIS
  * @{
  */
/** \brief SoC Download mode definition */
/* TODO: device vendor can extend more download modes */
typedef enum {
    DOWNLOAD_MODE_FLASHXIP = 0,         /*!< Flashxip download mode */
    DOWNLOAD_MODE_FLASH = 1,            /*!< Flash download mode */
    DOWNLOAD_MODE_ILM = 2,              /*!< ilm download mode */
    DOWNLOAD_MODE_DDR = 3,              /*!< ddr download mode */
    DOWNLOAD_MODE_MAX,
} DownloadMode_Type;

typedef enum {
    MCORE = 0,                          /*!< Main-Core */
    CCORE = 1,                          /*!< Co-Core */
    CORE_MAX,
} Core_Type;

/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn {
/* ========================================  Nuclei N/NX Specific Interrupt Numbers  ========================================= */
    Reserved0_IRQn            =   0,              /*!<  Internal reserved */
    Reserved1_IRQn            =   1,              /*!<  Internal reserved */
    Reserved2_IRQn            =   2,              /*!<  Internal reserved */
    SysSoft_IRQn              =   3,              /*!<  System Software Interrupt */
    Reserved3_IRQn            =   4,              /*!<  Internal reserved */
    Reserved4_IRQn            =   5,              /*!<  Internal reserved */
    Reserved5_IRQn            =   6,              /*!<  Internal reserved */
    SysTimer_IRQn             =   7,              /*!<  System Timer Interrupt */
    Reserved6_IRQn            =   8,              /*!<  Internal reserved */
    Reserved7_IRQn            =   9,              /*!<  Internal reserved */
    Reserved8_IRQn            =  10,              /*!<  Internal reserved */
    Reserved9_IRQn            =  11,              /*!<  Internal reserved */
    Reserved10_IRQn           =  12,              /*!<  Internal reserved */
    Reserved11_IRQn           =  13,              /*!<  Internal reserved */
    Reserved12_IRQn           =  14,              /*!<  Internal reserved */
    Reserved13_IRQn           =  15,              /*!<  Internal reserved */
    Reserved14_IRQn           =  16,              /*!<  Internal reserved */
    Reserved15_IRQn           =  17,              /*!<  Internal reserved */
    Reserved16_IRQn           =  18,              /*!<  Internal reserved */

/* ===========================================  T690 Specific Interrupt Numbers  ============================================= */
    SYMINT_Q0_IRQn            =  19,              /*!< HSM XXX Queue 0 Interrupt */
    SYMINT_Q1_IRQn            =  20,              /*!< HSM XXX Queue 0 Interrupt */
    SYMINT_Q2_IRQn            =  21,              /*!< HSM XXX Queue 0 Interrupt */
    MB_CTRL0_IRQn             =  22,              /*!< HSM Mailbox Ctrl 0 Interrupt */
    MB_CTRL1_IRQn             =  23,              /*!< HSM Mailbox Ctrl 1 Interrupt */
    MB_CTRL2_IRQn             =  24,              /*!< HSM Mailbox Ctrl 2 Interrupt */
    MB_PK0_IRQn               =  25,              /*!< HSM Mailbox PK 0 Interrupt */
    MB_PK1_IRQn               =  26,              /*!< HSM Mailbox PK 1 Interrupt */
    MB_PK2_IRQn               =  27,              /*!< HSM Mailbox PK 2 Interrupt */
    SECMON_IRQn               =  28,              /*!< HSM Security Monitor Interrupt */  
    USB3_IRQn                 =  34,              /*!< USB 3.0 global Interrupt */  
    GMAC0_IRQn                =  35,              /*!< GMAC0 global Interrupt */  
    GMAC0_Q0_RX_IRQn          =  36,              /*!< GMAC0 Queue 0 RX Interrupt */  
    GMAC0_Q0_TX_IRQn          =  37,              /*!< GMAC0 Queue 0 TX Interrupt */  
    GMAC0_Q1_RX_IRQn          =  38,              /*!< GMAC0 Queue 1 RX Interrupt */  
    GMAC0_Q1_TX_IRQn          =  39,              /*!< GMAC0 Queue 1 TX Interrupt */  
    GMAC0_Q2_RX_IRQn          =  40,              /*!< GMAC0 Queue 2 RX Interrupt */  
    GMAC0_Q2_TX_IRQn          =  41,              /*!< GMAC0 Queue 2 TX Interrupt */  
    GMAC0_Q3_RX_IRQn          =  42,              /*!< GMAC0 Queue 3 RX Interrupt */  
    GMAC0_Q3_TX_IRQn          =  43,              /*!< GMAC0 Queue 3 TX Interrupt */  
    GMAC1_IRQn                =  44,              /*!< GMAC1 global Interrupt */  
    GMAC1_Q0_RX_IRQn          =  45,              /*!< GMAC1 Queue 0 RX Interrupt */  
    GMAC1_Q0_TX_IRQn          =  46,              /*!< GMAC1 Queue 0 TX Interrupt */  
    GMAC1_Q1_RX_IRQn          =  47,              /*!< GMAC1 Queue 1 RX Interrupt */  
    GMAC1_Q1_TX_IRQn          =  48,              /*!< GMAC1 Queue 1 TX Interrupt */  
    GMAC1_Q2_RX_IRQn          =  49,              /*!< GMAC1 Queue 2 RX Interrupt */  
    GMAC1_Q2_TX_IRQn          =  50,              /*!< GMAC1 Queue 2 TX Interrupt */  
    GMAC1_Q3_RX_IRQn          =  51,              /*!< GMAC1 Queue 3 RX Interrupt */  
    GMAC1_Q3_TX_IRQn          =  52,              /*!< GMAC1 Queue 3 TX Interrupt */  
    PCIE_DMA0_END_IRQn        =  71,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA1_END_IRQn        =  72,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA2_END_IRQn        =  73,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA3_END_IRQn        =  74,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA0_ERR_IRQn        =  79,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA1_ERR_IRQn        =  80,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA2_ERR_IRQn        =  81,              /*!< PCIE XXX Interrupt */  
    PCIE_DMA3_ERR_IRQn        =  82,              /*!< PCIE XXX Interrupt */  
    PCIE_AXI_POST_ERR_IRQn    =  87,              /*!< PCIE XXX Interrupt */  
    PCIE_AXI_FETCH_ERR_IRQn   =  88,              /*!< PCIE XXX Interrupt */  
    PCIE_AXI_DISC_ERR_IRQn    =  89,              /*!< PCIE XXX Interrupt */  
    PCIE_AXI_DOORBELL_IRQn    =  90,              /*!< PCIE XXX Interrupt */  
    PCIE_PCIE_POST_ERR_IRQn   =  91,              /*!< PCIE XXX Interrupt */  
    PCIE_PCIE_FETCH_ERR_IRQn  =  92,              /*!< PCIE XXX Interrupt */  
    PCIE_PCIE_DISC_ERR_IRQn   =  93,              /*!< PCIE XXX Interrupt */  
    PCIE_PCIE_DOORBEL_IRQn    =  94,              /*!< PCIE XXX Interrupt */  
    PCIE_INTA_IRQn            =  95,              /*!< PCIE XXX Interrupt */  
    PCIE_INTB_IRQn            =  96,              /*!< PCIE XXX Interrupt */  
    PCIE_INTC_IRQn            =  97,              /*!< PCIE XXX Interrupt */  
    PCIE_INTD_IRQn            =  98,              /*!< PCIE XXX Interrupt */  
    PCIE_MSI_RCV_IRQn         =  99,              /*!< PCIE XXX Interrupt */  
    PCIE_AER_EVT_IRQn         =  100,             /*!< PCIE XXX Interrupt */  
    PCIE_PM_EVT_IRQn          =  101,             /*!< PCIE XXX Interrupt */  
    PCIE_SYS_ERR_IRQn         =  102,             /*!< PCIE XXX Interrupt */  
    PCIE_FLR_IRQn             =  103,             /*!< PCIE XXX Interrupt */  
    PCIE_ERR_IRQn             =  104,             /*!< PCIE XXX Interrupt */  
    PCIE_AT_IRQn              =  105,             /*!< PCIE XXX Interrupt */  
    PCIE_VPD_IRQn             =  106,             /*!< PCIE XXX Interrupt */  
    MINTC_IRQn                =  107,             /*!< MINTC global Interrupt */  
    DDR_ECC_IRQn              =  108,             /*!< DDR ECC Interrupt */  
    DDR_IRQn                  =  109,             /*!< ddr global interrupt */  
    DMA0_IRQn                 =  119,             /*!< DMA0 global Interrupt */ 
    DMA1_IRQn                 =  120,             /*!< DMA1 global Interrupt */ 
    FMC0_IRQn                 =  121,             /*!< FMC0 global Interrupt */ 
    FMC1_IRQn                 =  122,             /*!< FMC1 global Interrupt */ 
    SDIO0_IRQn                =  123,             /*!< SDHC0 global Interrupt */
    SDIO1_IRQn                =  124,             /*!< SDHC1 global Interrupt */
    SDIO2_IRQn                =  125,             /*!< SDHC2 global Interrupt */
    SDDC_IRQn                 =  126,             /*!< SDDC global Interrupt */ 
    USB2_IRQn                 =  127,             /*!< USB2 global Interrupt */ 
    MAC0_IRQn                 =  131,             /*!< MAC0 global Interrupt */ 
    MAC1_IRQn                 =  132,             /*!< MAC1 global Interrupt */ 
    LTDC_IRQn                 =  135,             /*!< LTDC global Interrupt */  
    TIM0_IRQn                 =  147,             /*!< TIM0 global Interrupt */ 
    TIM1_IRQn                 =  148,             /*!< TIM1 global Interrupt */ 
    TIM2_IRQn                 =  149,             /*!< TIM2 global Interrupt */ 
    TIM3_IRQn                 =  150,             /*!< TIM3 global Interrupt */ 
    TIM4_IRQn                 =  151,             /*!< TIM4 global Interrupt */ 
    TIM5_IRQn                 =  152,             /*!< TIM5 global Interrupt */ 
    TIM6_IRQn                 =  153,             /*!< TIM6 global Interrupt */ 
    TIM7_IRQn                 =  154,             /*!< TIM7 global Interrupt */ 
    TIM8_IRQn                 =  155,             /*!< TIM8 global Interrupt */ 
    TIM9_IRQn                 =  156,             /*!< TIM9 global Interrupt */ 
    TIM10_IRQn                =  157,             /*!< TIM10 global Interrupt */
    TIM11_IRQn                =  158,             /*!< TIM11 global Interrupt */
    TIM12_IRQn                =  159,             /*!< TIM12 global Interrupt */
    TIM13_IRQn                =  160,             /*!< TIM13 global Interrupt */
    TIM14_IRQn                =  161,             /*!< TIM14 global Interrupt */
    TIM15_IRQn                =  162,             /*!< TIM15 global Interrupt */
    WDG0_EARLY_IRQn           =  163,             /*!< WatchDog0 Early Interrupt */
    WDG0_IRQn                 =  164,             /*!< WatchDog0 Interrupt */
    WDG1_EARLY_IRQn           =  165,             /*!< WatchDog1 Early Interrupt */
    WDG1_IRQn                 =  166,             /*!< WatchDog1 Interrupt */
    GPIOA_IRQn                =  167,             /*!< GPIOA global Interrupt */
    GPIOB_IRQn                =  168,             /*!< GPIOB global Interrupt */
    GPIOC_IRQn                =  169,             /*!< GPIOC global Interrupt */
    GPIOD_IRQn                =  170,             /*!< GPIOD global Interrupt */
    IIC0_IRQn                 =  171,             /*!< IIC0 global Interrupt */
    IIC1_IRQn                 =  172,             /*!< IIC1 global Interrupt */
    IIC2_IRQn                 =  173,             /*!< IIC2 global Interrupt */
    SPI0_IRQn                 =  175,             /*!< SPI0 global Interrupt */
    SPI1_IRQn                 =  176,             /*!< SPI1 global Interrupt */
    SSP0_IRQn                 =  177,             /*!< SSP0 global Interrupt */
    SSP1_IRQn                 =  178,             /*!< SSP1 global Interrupt */
    CANA0_IRQn                =  179,             /*!< global Interrupt */
    CANA1_IRQn                =  180,             /*!< global Interrupt */
    CANA2_IRQn                =  181,             /*!< global Interrupt */
    CANA3_IRQn                =  182,             /*!< global Interrupt */
    CANB0_IRQn                =  183,             /*!< global Interrupt */
    CANB1_IRQn                =  184,             /*!< global Interrupt */
    CANB2_IRQn                =  185,             /*!< global Interrupt */
    CANB3_IRQn                =  186,             /*!< global Interrupt */
    UART0_IRQn                =  187,             /*!< global Interrupt */
    UART1_IRQn                =  188,             /*!< global Interrupt */
    UART2_IRQn                =  189,             /*!< global Interrupt */
    UART3_IRQn                =  190,             /*!< global Interrupt */
    UART4_IRQn                =  191,             /*!< global Interrupt */
    UART5_IRQn                =  192,             /*!< global Interrupt */
    UART6_IRQn                =  193,             /*!< global Interrupt */
    UART7_IRQn                =  194,             /*!< global Interrupt */
    SCI0_IRQn                 =  195,             /*!< global Interrupt */
    SCI1_IRQn                 =  196,             /*!< global Interrupt */
    ADC0_IRQn                 =  197,             /*!< global Interrupt */
    ADC1_IRQn                 =  198,             /*!< global Interrupt */
    DAC0_IRQn                 =  199,             /*!< global Interrupt */
    RTC_IRQn                  =  200,             /*!< global Interrupt */
    RCCS_GPHY_LED_IRQn        =  213,             /*!< global Interrupt */
    RCCS_GMACX_WOL_IRQn       =  214,             /*!< global Interrupt */
    RCCS_ECCERR_RD_IRQn       =  215,             /*!< global Interrupt */
    RCCS_ECCERR_RMW_IRQn      =  216,             /*!< global Interrupt */
    RCCS_CRCERR_AHB_IRQn      =  217,             /*!< global Interrupt */
    RCCS_CRCERR_AXI_IRQn      =  218,             /*!< global Interrupt */
    TEE_OVERLAP_IRQn          =  219,             /*!< global Interrupt */
    TEE_ILLEGAL_IRQn          =  220,             /*!< global Interrupt */
    AXIC_X0_IRQn              =  221,             /*!< global Interrupt */
    AXIC_X1_IRQn              =  222,             /*!< global Interrupt */
    AHBC0_IRQn                =  223,             /*!< global Interrupt */
    H2XL_IRQn                 =  224,             /*!< global Interrupt */
    H2XH_IRQn                 =  225,             /*!< global Interrupt */
    REE_DECERR_IRQn           =  226,             /*!< global Interrupt */
    CFG_DECERR_IRQn           =  227,             /*!< global Interrupt */
    LPC_DECERR_IRQn           =  228,             /*!< global Interrupt */
    RCCS_PCIE_TRACK_IRQn      =  229,             /*!< global Interrupt */
    RCCS_USB3_LTSSM_IRQn      =  230,             /*!< global Interrupt */
    IPC0_IRQn                 =  267,             /*!< global Interrupt */
    IPC1_IRQn                 =  268,             /*!< global Interrupt */
    IPC2_IRQn                 =  269,             /*!< global Interrupt */
    IPC3_IRQn                 =  270,             /*!< global Interrupt */
    IPC4_IRQn                 =  271,             /*!< global Interrupt */
    IPC5_IRQn                 =  272,             /*!< global Interrupt */
    IPC6_IRQn                 =  273,             /*!< global Interrupt */
    IPC7_IRQn                 =  274,             /*!< global Interrupt */
    SOC_INT_MAX ,                               /* Max SoC interrupt Number */
} IRQn_Type;

/* =========================================================================================================================== */
/* ================                                  Exception Code Definition                                ================ */
/* =========================================================================================================================== */

typedef enum EXCn {
/* =======================================  Nuclei N/NX Specific Exception Code  ======================================== */
    InsUnalign_EXCn          =   0,              /*!<  Instruction address misaligned */
    InsAccFault_EXCn         =   1,              /*!<  Instruction access fault */
    IlleIns_EXCn             =   2,              /*!<  Illegal instruction */
    Break_EXCn               =   3,              /*!<  Beakpoint */
    LdAddrUnalign_EXCn       =   4,              /*!<  Load address misaligned */
    LdFault_EXCn             =   5,              /*!<  Load access fault */
    StAddrUnalign_EXCn       =   6,              /*!<  Store or AMO address misaligned */
    StAccessFault_EXCn       =   7,              /*!<  Store or AMO access fault */
    UmodeEcall_EXCn          =   8,              /*!<  Environment call from User mode */
    MmodeEcall_EXCn          =  11,              /*!<  Environment call from Machine mode */
    NMI_EXCn                 = 0xfff,            /*!<  NMI interrupt*/
} EXCn_Type;

/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Nuclei N/NX Processor and Core Peripherals  =========================== */
#define __NUCLEI_NX_REV           0x0100                /*!< Core Revision rXpY, version X.Y */
#define __ECLIC_PRESENT           1                     /*!< ECLIC is present */
#define __ECLIC_BASEADDR          0x14000000UL          /*!< ECLIC baseaddr */
#define __ECLIC_INTCTLBITS        3                     /*!< The number of hardware bits actually implemented in the clicintctl registers. */
#define __ECLIC_INTNUM            256                   /*!< The total interrupt number of ECLIC Unit */
#define __SYSTIMER_PRESENT        1                     /*!< System Timer is present */
#define __SYSTIMER_BASEADDR       0x15000000UL          /*!< SysTimer baseaddr */
#define __FPU_PRESENT             2                     /*!< Double floating point unit present */
#define __DSP_PRESENT             0                     /*!< DSP is not present */
#define __PMP_PRESENT             1                     /*!< PMP is present */
#define __PMP_ENTRY_NUM           16                    /*!< The number of PMP entries */
#define __ICACHE_PRESENT          1                     /*!< I-Cache is present */
#define __DCACHE_PRESENT          1                     /*!< D-Cache is present only for Main CPU */
#define __MCORE_DCACHE_PRESENT    1                     /*!< D-Cache is present for Main CPU */
#define __CCORE_DCACHE_PRESENT    0                     /*!< D-Cache is NOT present for Main CPU */
#define __Vendor_SysTickConfig    0                     /*!< Set to 1 if different SysTick Config is used */ //TODO

/** @} */ /* End of group Configuration_of_NMSIS */
#include <nmsis_core.h>
#include "system_t690.h"                    /*!< T690 System */
#if !defined  (USE_STDPERIPH_DRIVER)
/**
 * @brief Comment the line below if you will not use the peripherals drivers.
   In this case, these drivers will not be included and the application code will
   be based on direct access to peripherals registers
   */
   #define USE_STDPERIPH_DRIVER
#endif /* USE_STDPERIPH_DRIVER */



/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */
/* Macros for memory access operations */
#define _REG8P(p, i)                        ((volatile uint8_t *) ((uintptr_t)((p) + (i))))
#define _REG16P(p, i)                       ((volatile uint16_t *) ((uintptr_t)((p) + (i))))
#define _REG32P(p, i)                       ((volatile uint32_t *) ((uintptr_t)((p) + (i))))
#define _REG64P(p, i)                       ((volatile uint64_t *) ((uintptr_t)((p) + (i))))
#define _REG8(p, i)                         (*(_REG8P(p, i)))
#define _REG16(p, i)                        (*(_REG16P(p, i)))
#define _REG32(p, i)                        (*(_REG32P(p, i)))
#define _REG64(p, i)                        (*(_REG64P(p, i)))
#define REG8(addr)                          _REG8((addr), 0)
#define REG16(addr)                         _REG16((addr), 0)
#define REG32(addr)                         _REG32((addr), 0)
#define REG64(addr)                         _REG64((addr), 0)

/* Macros for address type convert and access operations */
#define ADDR16(addr)                        ((uint16_t)(uintptr_t)(addr))
#define ADDR32(addr)                        ((uint32_t)(uintptr_t)(addr))
#define ADDR64(addr)                        ((uint64_t)(uintptr_t)(addr))
#define ADDR8P(addr)                        ((uint8_t *)(uintptr_t)(addr))
#define ADDR16P(addr)                       ((uint16_t *)(uintptr_t)(addr))
#define ADDR32P(addr)                       ((uint32_t *)(uintptr_t)(addr))
#define ADDR64P(addr)                       ((uint64_t *)(uintptr_t)(addr))

/* Macros for Bit Operations */
#if __riscv_xlen == 32
#define BITMASK_MAX                         0xFFFFFFFFUL
#define BITOFS_MAX                          31
#else
#define BITMASK_MAX                         0xFFFFFFFFFFFFFFFFULL
#define BITOFS_MAX                          63
#endif

// BIT/BITS only support bit mask for __riscv_xlen
// For RISC-V 32 bit, it support mask 32 bit wide
// For RISC-V 64 bit, it support mask 64 bit wide
#define BIT(ofs)                            (0x1UL << (ofs))
#define BITS(start, end)                    ((BITMASK_MAX) << (start) & (BITMASK_MAX) >> (BITOFS_MAX - (end)))
#define GET_BIT(regval, bitofs)             (((regval) >> (bitofs)) & 0x1)
#define SET_BIT(regval, bitofs)             ((regval) |= BIT(bitofs))
#define CLR_BIT(regval, bitofs)             ((regval) &= (~BIT(bitofs)))
#define FLIP_BIT(regval, bitofs)            ((regval) ^= BIT(bitofs))
#define WRITE_BIT(regval, bitofs, val)      CLR_BIT(regval, bitofs); ((regval) |= ((val) << bitofs) & BIT(bitofs))
#define CHECK_BIT(regval, bitofs)           (!!((regval) & (0x1UL<<(bitofs))))
#define GET_BITS(regval, start, end)        (((regval) & BITS((start), (end))) >> (start))
#define SET_BITS(regval, start, end)        ((regval) |= BITS((start), (end)))
#define CLR_BITS(regval, start, end)        ((regval) &= (~BITS((start), (end))))
#define FLIP_BITS(regval, start, end)       ((regval) ^= BITS((start), (end)))
#define WRITE_BITS(regval, start, end, val) CLR_BITS(regval, start, end); ((regval) |= ((val) << start) & BITS((start), (end)))
#define CHECK_BITS_ALL(regval, start, end)  (!((~(regval)) & BITS((start), (end))))
#define CHECK_BITS_ANY(regval, start, end)  ((regval) & BITS((start), (end)))

#define BITMASK_SET(regval, mask)           ((regval) |= (mask))
#define BITMASK_CLR(regval, mask)           ((regval) &= (~(mask)))
#define BITMASK_FLIP(regval, mask)          ((regval) ^= (mask))
#define BITMASK_CHECK_ALL(regval, mask)     (!((~(regval)) & (mask)))
#define BITMASK_CHECK_ANY(regval, mask)     ((regval) & (mask))

/* enum definitions */
typedef enum {
    RESET = 0, 
    SET = !RESET
} FlagStatus, ITStatus;

typedef enum {
    DISABLE = 0, 
    ENABLE = !DISABLE
} FunctionalState;

typedef enum {
    ERROR = 0, 
    SUCCESS = !ERROR
} ErrorStatus;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

/* TODO: add here your device specific peripheral access structure typedefs
         following is an example for UART */
/* =========================================================================================================================== */
/* ================                                  ADC                                                      ================ */
/* =========================================================================================================================== */
/** 
  * @brief Analog to Digital Converter  
  */

typedef struct
{
    __IO uint32_t SR;     /*!< ADC status register,                         Address offset: 0x00 */
    __IO uint32_t CR;     /*!< ADC control register,                        Address offset: 0x04 */      
    __IO uint32_t SMP;    /*!< ADC sample time register,                    Address offset: 0x08 */
    __IO uint32_t AWD;    /*!< ADC analog watchdog register,                Address offset: 0x0C */
    __IO uint32_t SQR1;   /*!< ADC regular sequence register 1,             Address offset: 0x10 */
    __IO uint32_t SQR2;   /*!< ADC regular sequence register 2,             Address offset: 0x14 */
    __IO uint32_t JSQR;   /*!< ADC injected sequence register,              Address offset: 0x18 */
    __IO uint32_t DR;     /*!< ADC regular data register,                   Address offset: 0x1C */
    __IO uint32_t JDR;    /*!< ADC injected data register,                  Address offset: 0x20 */
    __IO uint32_t CALIB;  /*!< ADC calibration register,                    Address offset: 0x24 */      
    __IO uint32_t OFR1;   /*!< ADC regular and injected data offset register 1, Address offset: 0x28 */
    __IO uint32_t OFR2;   /*!< ADC regular and injected data offset register 2, Address offset: 0x2C */
    __IO uint32_t OFR3;   /*!< ADC regular and injected data offset register 3, Address offset: 0x30 */
    __IO uint32_t OFR4;   /*!< ADC regular and injected data offset register 4, Address offset: 0x34 */
    __IO uint32_t OFR5;   /*!< ADC regular and injected data offset register 5, Address offset: 0x38 */
    __IO uint32_t OFR6;   /*!< ADC regular and injected data offset register 6, Address offset: 0x3C */
    __IO uint32_t OFR7;   /*!< ADC regular and injected data offset register 7, Address offset: 0x40 */
    __IO uint32_t OFR8;   /*!< ADC regular and injected data offset register 8, Address offset: 0x44 */
    __IO uint32_t OFR9;   /*!< ADC regular and injected data offset register 9, Address offset: 0x48 */
    __IO uint32_t OFR10;  /*!< ADC regular and injected data offset register 10, Address offset: 0x4C */
} ADC_TypeDef;

typedef struct
{
    __IO uint32_t TDC;    /*!< ADC Common TDC register,                     Address offset: ADC1 base address + 0x100 */
} ADC_TDC_TypeDef;

/* =========================================================================================================================== */
/* ================                                  CAN                                                       ================ */
/* =========================================================================================================================== */
/** 
  * @brief Controller Area Network  (CAN)
  */
typedef struct
{
  __IO uint32_t SRR;
  __IO uint32_t MSR;
  __IO uint32_t APBRP;
  __IO uint32_t APBT;
  __IO uint32_t ECR;
  __IO uint32_t ESR;
  __I  uint32_t SR;
  __I  uint32_t ISR;
  __IO uint32_t IER;
  __O  uint32_t ICR;
  __IO uint32_t TR;
  uint32_t RESERVED0[23];
  __IO uint32_t DPBRP;
  __IO uint32_t DPBT;
  __IO uint32_t TBRR;
  uint32_t RESERVED1;
  __IO uint32_t TBCR;
  uint32_t RESERVED2[17];    //todo
  __IO uint32_t AFC;
  uint32_t RESERVED3;
  __IO uint32_t RFSR;
  __IO uint32_t RFWM;
  uint32_t RESERVED4[4];     //todo
  __IO uint32_t TBBASE[144];
  uint32_t RESERVED5[432];
  __IO uint32_t AFBASE[64];
  uint32_t RESERVED6[1408];
  __I uint32_t RBBASE[18];
} CANA_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t BS;
  __IO uint32_t TFD0;
  __IO uint32_t TEIH0;
  __IO uint32_t TFD1;
  __IO uint32_t TEIH1;
  __IO uint32_t TFD2;
  __IO uint32_t TEIH2;
  __IO uint32_t AFEIL[6];
  __IO uint32_t AFDB00;
  __IO uint32_t AFC0;
  __IO uint32_t FMEIL0;
  __IO uint32_t FMEIL1;
  __IO uint32_t FMDB00;
  __IO uint32_t FMC;
  __I uint32_t RFD0;
  __I uint32_t REIH0;
  __I uint32_t RFD1;
  __I uint32_t REIH1;
  __IO uint32_t NBTC0;
  __IO uint32_t NBTC4;
  __IO uint32_t DBTC0;
  __I uint32_t EC;
  __I uint32_t ET;
  uint32_t RESERVED0;
  __IO uint32_t IR;
  __IO uint32_t TB0[16];
  __IO uint32_t TB1[16];
  __IO uint32_t TB2[16];
  __I uint32_t RB0[16];
  __I uint32_t RB1[16];
} CANB_TypeDef;

/* =========================================================================================================================== */
/* ================                                  DAC                                                      ================ */
/* =========================================================================================================================== */
/** 
  * @brief Digital to Analog Converter
  */

typedef struct
{
    __IO uint32_t CR;       /*!< DAC control register,                                    Address offset: 0x00 */
    __IO uint32_t SWTRIGR;  /*!< DAC software trigger register,                           Address offset: 0x04 */
    __IO uint32_t DHR1;     /*!< DAC channel1 data holding register,                      Address offset: 0x08 */
    __IO uint32_t DHR2;     /*!< DAC channel2 data holding register,                      Address offset: 0x0C */
    __IO uint32_t DHRD;     /*!< Dual DAC data holding register,                          Address offset: 0x10 */
    __IO uint32_t DOR1;     /*!< DAC channel1 data output register,                       Address offset: 0x14 */
    __IO uint32_t DOR2;     /*!< DAC channel2 data output register,                       Address offset: 0x18 */
    uint32_t RESERVED1;     /*!< Reserved, 0x1C  */
    __IO uint32_t RATE;     /*!< DAC clock divison rate register,                         Address offset: 0x20 */
    uint32_t RESERVED2[3];  /*!< Reserved, 0x24 - 0x2C  */
    __IO uint32_t SR;       /*!< DAC status register,                                     Address offset: 0x30 */
    __IO uint32_t IT;		/*!< DAC interrupt register,	 							                  Address offset: 0x34 */
} DAC_TypeDef;

/* =========================================================================================================================== */
/* ================                                  DMA                                                      ================ */
/* =========================================================================================================================== */
typedef struct
{
    __IO uint32_t CTR;      /*!< DMA stream x control register      */
    __IO uint32_t CFR;      /*!< DMA stream x configuration register      */
    __IO uint32_t SAR;      /*!< DMA stream x memory source address register   */
    __IO uint32_t DAR;      /*!< DMA stream x memory destion address register   */
    __IO uint32_t LLPR;     /*!< DMA stream x link list pointer register   */
    __IO uint32_t NDTR;     /*!< DMA stream x number of data register     */
    __IO uint32_t SSDR;     /*!< DMA stream x source/destination stride register    */
    uint32_t RESERVED[57];  /*!< 0x11C ~ 1FC */
    __IO uint32_t AER;      /*!< DMA stream x source address and destination address expand register    */
    __IO uint32_t LLPER;    /*!< DMA stream x link list pointer and user-defined signal expand register    */

} DMA_Stream_TypeDef;

typedef struct
{
    __IO uint32_t DMA_INT;                  /*!< DMA interrupt of each DMA channel register,                Address offset: 0x00 */
    __IO uint32_t DMA_INT_TCS;              /*!< DMA terminal count interrupt register,                     Address offset: 0x04 */
    __IO uint32_t DMA_INT_TCS_CLR;          /*!< DMA terminal count interrupt flag clear register,          Address offset: 0x08 */
    __IO uint32_t DMA_INT_EAS;              /*!< DMA error/abort interrupt status register,                 Address offset: 0x0C */
    __IO uint32_t DMA_INT_EAS_CLR;          /*!< DMA error/abort flag clear interrupt status register,      Address offset: 0x10 */
    __IO uint32_t DMA_TCS;                  /*!< DMA terminal count status register,regardless mask bit     Address offset: 0x14 */
    __IO uint32_t DMA_EAS;                  /*!< DMA error/abort status register, regardless mask bit       Address offset: 0x18 */
    __IO uint32_t DMA_CH_EN;                /*!< DMA channel enable  register,                              Address offset: 0x1C */
    __IO uint32_t DMA_CH_SYNC;              /*!< DMA synchronization of peripheral interface register,      Address offset: 0x20 */
    uint32_t RESERVED0;                     /*!< DMA local descriptor memorys register,(Not used)           Address offset: 0x24 */
    __IO uint32_t DMA_WDT;                  /*!< DMA watchdog timer  register,                              Address offset: 0x28 */
    __IO uint32_t DMA_GE;                   /*!< DMA global events register,                                Address offset: 0x2C */
    __IO uint32_t DMA_APB_SLAVE_ERR;        /*!< DMA APB slave error Enable  register,                      Address offset: 0x30 */
    __IO uint32_t DMA_REVISION;             /*!< DMA revision number register,                              Address offset: 0x34 */
    __IO uint32_t DMA_FEATURE;              /*!< DMA hardware feature register,                             Address offset: 0x38 */
    uint32_t RESERVED1[4];                  /*!< DMA reserved                                               Address offset: 0x3C ~ 0x48 */
    __IO uint32_t DMA_ENDIAN;               /*!< DMA endian conversion register,                            Address offset: 0x4C */
    __IO uint32_t DMA_WRITE_ONLY;           /*!< DMA write-only mode constant value register,               Address offset: 0x50 */
} DMA_TypeDef;


/* =========================================================================================================================== */
/* ================                                  DDR                                                      ================ */
/* =========================================================================================================================== */

/**
  * @brief Double Data Rate SDRAM (DDR)
  */
typedef struct {
    __IO uint32_t MCCR;              /*!< Memory controller configuration, Address offset: 0x0 */ 
    __IO uint32_t MCSR;              /*!< Memory controller state control, Address offset: 0x4 */ 
    __IO uint32_t MRSVR0;            /*!< Mode register set values for the Mode Register(MR) and Extended Mode Register(EMR), Address offset: 0x8 */ 
    __IO uint32_t MRSVR1;            /*!< Mode register set values for EMR2 and EMR3, Address offset: 0xC */ 
    __IO uint32_t EXRANKR;           /*!< External rank0/rand1 register, Address offset: 0x10 */ 
    __IO uint32_t TMPR0;             /*!< Timing parameter 0, Address offset: 0x14 */ 
    __IO uint32_t TMPR1;             /*!< Timing parameter 1, Address offset: 0x18 */ 
    __IO uint32_t TMPR2;             /*!< Timing parameter 2, Address offset: 0x1C */ 
    __IO uint32_t PHYCR0;            /*!< Data block control, Address offset: 0x20 */ 
    __IO uint32_t PHYRDTR;           /*!< DLL delay tuning of the DDR PHY read path, Address offset: 0x24 */ 
    __IO uint32_t COMPBLKCR;         /*!< COMPBLK control, Address offset: 0x28 */ 
    __IO uint32_t APDCR;             /*!< Automatic power-down/self-refresh control, Address offset: 0x2C */ 
    __IO uint32_t CHARBRA;           /*!< Channel arbitration setup register A, Address offset: 0x30 */ 
    __IO uint32_t CHGNTRA;           /*!< Channel arbiter grant count register A, Address offset: 0x34 */ 
    __IO uint32_t CHGNTRB;           /*!< Channel arbiter grant count register B, Address offset: 0x38 */ 
    __IO uint32_t PHYWRTMR;          /*!< DDRx PHY write/read data access timing control, Address offset: 0x3C */ 
    __IO uint32_t FLUSHCR;           /*!< Command flush control, Address offset: 0x40 */ 
    __IO uint32_t FLUSHSR;           /*!< Command flush status, Address offset: 0x44 */ 
    __IO uint32_t SPLITCR;           /*!< AHB split control, Address offset: 0x48 */ 
    __IO uint32_t UPDCR;             /*!< DDRx PHY and DDR3 updata control, Address offset: 0x4C */ 
    __I  uint32_t REVR;              /*!< Revisiong register, Address offset: 0x50 */ 
    __I  uint32_t FEATR1;            /*!< Feature register, Address offset: 0x54 */ 
    __I  uint32_t FEATR2;            /*!< Feature register 2, Address offset: 0x58 */ 
    __IO uint32_t UDEFR;             /*!< User-defined register, Address offset: 0x5C */ 
    __IO uint32_t WLEVELCR;          /*!< Write-leveling control register, Address offset: 0x60 */ 
    __IO uint32_t WLEVELBHR;         /*!< Byte 7 ~ byte 4 of the write-leveling control register, Address offset: 0x64 */ 
    __IO uint32_t WLEVELBLR;         /*!< Byte 3 ~ byte 0 of the write-leveling control register, Address offset: 0x68 */ 
    __IO uint32_t PHYMISCR1;         /*!< DDR3 MISC register, Address offset: 0x6C */ 
    __IO uint32_t RLEVELCR;          /*!< Read-leveling control register, Address offset: 0x70 */ 
    __IO uint32_t MSDLYCR;           /*!< msdly byte control register, Address offset: 0x74 */ 
    __IO uint32_t WRDLLCR;           /*!< wdllsel control register, Address offset: 0x78 */ 
    __IO uint32_t TRAFMR;            /*!< Traffic monitor clock cycle register, Address offset: 0x7C */ 
    __I  uint32_t CMDCNTR0;          /*!< Command count for channel 0, Address offset: 0x80 */ 
    __I  uint32_t CMDCNTR1;          /*!< Command count for channel 1, Address offset: 0x84 */ 
    __I  uint32_t CMDCNTR2;          /*!< Command count for channel 2, Address offset: 0x88 */ 
    __I  uint32_t CMDCNTR3;          /*!< Command count for channel 3, Address offset: 0x8C */ 
    __I  uint32_t CMDCNTR4;          /*!< Command count for channel 4, Address offset: 0x90 */ 
    __I  uint32_t CMDCNTR5;          /*!< Command count for channel 5, Address offset: 0x94 */ 
    __I  uint32_t CMDCNTR6;          /*!< Command count for channel 6, Address offset: 0x98 */ 
    __I  uint32_t CMDCNTR7;          /*!< Command count for channel 7, Address offset: 0x9C */ 
    __IO uint32_t AHBRPRER1;         /*!< AHB INCR read prefetch length 1, Address offset: 0xA0 */ 
    __IO uint32_t AHBRPRER2;         /*!< AHB INCR read prefetch length 2, Address offset: 0xA4 */ 
    __IO uint32_t INITWCR1;          /*!< Initialization waiting cycle count 1, Address offset: 0xA8 */ 
    __IO uint32_t INITWCR2;          /*!< Initialization waiting cycle count 2, Address offset: 0xAC */ 
    __IO uint32_t QOSCR;             /*!< QoS control register, Address offset: 0xB0 */ 
    __IO uint32_t QOSCNTRA;          /*!< QoS command count register A, Address offset: 0xB4 */ 
    __IO uint32_t QOSCNTRB;          /*!< QoS command count register B, Address offset: 0xB8 */ 
    __IO uint32_t QOSCNTRC;          /*!< QoS command count register C, Address offset: 0xBC */ 
    __IO uint32_t QOSCNTRD;          /*!< QoS command count register D, Address offset: 0xC0 */ 
    __IO uint32_t CHARBRB;           /*!< Channel arbitration setup register B, Address offset: 0xC4 */ 
    __IO uint32_t CHGNTRC;           /*!< Channel arbiter grant count register C, Address offset: 0xC8 */ 
    __IO uint32_t CHGNTRD;           /*!< Channel arbiter grant count register D, Address offset: 0xCC */
    uint32_t RESERVED0[12];          /*!< Reserved, 0xD0-0xFC */
    __IO uint32_t LP2MRA;            /*!< LPDDR2 Mode Register MR1/MR2/MR3, Address offset: 0x100 */ 
    __IO uint32_t LP2MRB;            /*!< LPDDR2 Mode Registe MR9/MR10, Address offset: 0x104 */
    __IO uint32_t LP2MRC;            /*!< LPDDR2 Mode Register MR16/MR17, Address offset: 0x108 */
    __IO uint32_t LP2MRD;            /*!< LPDDR2 Mode Register MR41/MR42/MR48, Address offset: 0x10C */ 
    __IO uint32_t LP2MRE;            /*!< LPDDR2 Mode Register MR63, Address offset: 0x110 */
    __IO uint32_t LP2MRCR;           /*!< LPDDR2 MRW and MRR Commands, Address offset: 0x114 */
    __I  uint32_t LP2MRVR;           /*!< LPDDR2 MRR Read Value, Address offset: 0x118 */
    __IO uint32_t LP2ADLR;           /*!< LPDDR2 Added Latency, Address offset: 0x11C */
    __IO uint32_t LP2WCR1;           /*!< LPDDR2 1us waiting cycle, Address offset: 0x120 */
    __IO uint32_t LP2WCR2;           /*!< LPDDR2 10us waiting cycle, Address offset: 0x124 */
    uint32_t RESERVED1;              /*!< Reserved, 0x128 */
    __IO uint32_t REARBDISR;         /*!< Re-arbitration disable count register, Address offset: 0x12C */
    __IO uint32_t PHYRDTFR;          /*!< DLL delay tuning of the DDR PHY read path (Falling), Address offset: 0x130 */
    __IO uint32_t PHYMISCR2;         /*!< DDR PHY MISC2 register, Address offset: 0x134 */
    __IO uint32_t EFIFOCR;           /*!< EFIFO control register, Address offset: 0x138 */
    uint32_t RESERVED2[28];          /*!< Reserved, 0x13C-0x1A8 */
    __IO uint32_t B8PHYCR;           /*!< Byte 8 PHY control register, Address offset: 0x1AC */
    uint32_t RESERVED3[12];          /*!< Reserved, 0x1B0-0x1DC */
    __IO uint32_t ECCCTRLR;          /*!< ECC control register, Address offset: 0x1E0 */
    __IO uint32_t ECCINTCR;          /*!< ECC interrupt control register, Address offset: 0x1E4 */
    __I  uint32_t ECCCHR;            /*!< ECC error channel register, Address offset: 0x1E8 */
    __I  uint32_t ECCEAR;            /*!< ECC error address, Address offset: 0x1EC */
    __I  uint32_t ECCEBPLR;          /*!< ECC error bit position low bytes, Address offset: 0x1F0 */
    __I  uint32_t ECCEBPHR;          /*!< ECC error bit position high bytes, Address offset: 0x1F4 */
    __I  uint32_t ECCERR1CNT;        /*!< ECC one-bit error counts register, Address offset: 0x1F8 */
    __I  uint32_t ECCERR2CNT;        /*!< ECC two-bit error counts register, Address offset: 0x1FC */                                                    
} DDRC_TypeDef;

typedef struct
{
    __IO uint32_t CFG0;              /*!< DDR PHY configuration 0 register, Address offset: 0x0 */
    __IO uint32_t CFG1;              /*!< DDR PHY configuration 1 register, Address offset: 0x4 */           
    __IO uint32_t CFG2;              /*!< DDR PHY configuration 2 register, Address offset: 0x8 */          
    __IO uint32_t CFG3;              /*!< DDR PHY configuration 3 register, Address offset: 0xC */         
} DDRC_Config_TypeDef;


/* =========================================================================================================================== */
/* ================                                  FMC                                                      ================ */
/* =========================================================================================================================== */

/**
  * @brief Flexible Memory Controller (FMC)
  */

typedef struct
{
    __IO uint32_t AR;                /*!< FMC Address register, Address offset: 0x00 */
    __IO uint32_t CMD1;              /*!< FMC CMD1 register, Address offset: 0x04 */
    __IO uint32_t DLR;               /*!< FMC Data Length register, Address offset: 0x08 */
    __IO uint32_t CMD3;              /*!< FMC CMD3 register, Address offset: 0x0C */
    __IO uint32_t CR;                /*!< FMC Device Configuration register, Address offset: 0x04 */
    __IO uint32_t ATCR;              /*!< FMC Device ACTR Configuration register, Address offset: 0x14 */
    __IO uint32_t SR;                /*!< FMC  Status register, Address offset: 0x18 */
    __IO uint32_t ICR;               /*!< FMC Interrupt register, Address offset: 0x1C */
    __IO uint32_t ISR;               /*!< FMC Interrupt Status register, Address offset: 0x20 */
    __IO uint32_t SPISR;             /*!< FMC Flash Status register, Address offset: 0x20 */
    __IO uint32_t SPIFSR;            /*!< FMC Flash Size register, Address offset: 0x20 */
    __IO uint32_t XIPCMD;            /*!< FMC XIP Configuration register, Address offset: 0x20 */
    __IO uint32_t XIPPFO;            /*!< FMC XIP PFO register, Address offset: 0x20 */
    __IO uint32_t XIPWCMD;           /*!< FMC XIP WCMD register, Address offset: 0x38 */
    uint32_t RESERVED0[6];           /*!< Reserved, 0x3C-0x50 */
    __IO uint32_t FEATURE;           /*!< FMC Feature register, Address offset: 0x54 */
    uint32_t RESERVED1[42];          /*!< Reserved, 0x58-0xFC */
    __IO uint32_t DR;                /*!< FMC Data register, Address offset: 0x100 */
} FMC_TypeDef;

typedef struct
{
    __IO uint32_t IC;                /*!< FMC0 IO control register, Address offset: 0x0 */
} FMC0_IOControl_TypeDef;           

typedef struct 
{
    __IO uint32_t DC;                /*!< FMC1 DLL control register, Address offset: 0x0 */
} FMC1_DllControl_TypeDef;          

/* =========================================================================================================================== */
/* ================                                  GMAC                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief GMAC
  */

typedef struct
{
    __IO uint32_t MACFLTL; /* 0x1B8 */
    __IO uint32_t MACFLTH; /* 0x1BC */
} GMAC_MacFilterRegister_TypeDef;

typedef struct
{
    __IO uint32_t QCR;           /* 0x400 */
    __IO uint32_t QISR;          /* 0x404 */
    __IO uint32_t QIER;          /* 0x408 */
    __IO uint32_t QTXITC;        /* 0x40C */
    __IO uint32_t QRXITC;        /* 0x410 */
    __IO uint32_t RXDCR;         /* 0x414 */
    __IO uint32_t RXRPTRL;       /* 0x418 */
    __IO uint32_t RXRPTRH;       /* 0x41C */
    __IO uint32_t RXRHDR;        /* 0x420 */
    __IO uint32_t RXRTAIL;       /* 0x424 */
    __IO uint32_t RESERVED0[6];  /* 0x428 ~ 0x43C */
    __IO uint32_t TXDCR;         /* 0x440 */
    __IO uint32_t TXRPTRL;       /* 0x444 */
    __IO uint32_t TXRPTRH;       /* 0x448 */
    __IO uint32_t TXRHDR;        /* 0x44C */
    __IO uint32_t TXRTAIL;       /* 0x450 */
    __IO uint32_t RESERVED1[6];  /* 0x454 ~ 0X468 */
    __IO uint32_t TQBUFCR;       /* 0x46C */
    __IO uint32_t RQBUFCR;       /* 0x470 */
    __IO uint32_t RQBUFSZ;       /* 0x474 */
    __IO uint32_t RESERVED2[34]; /* 0x478 ~ 0x4FC */
} GMAC_QueueRegister_TypeDef;

typedef struct
{
    __IO uint32_t GMACCR;        /* 0x000 */
    __IO uint32_t FCR;           /* 0x004 */
    __IO uint32_t BPR;           /* 0x008 */
    __IO uint32_t RESERVED0;     /* 0x00C */
    __IO uint32_t DMAFIFOS;      /* 0x010 */
    __IO uint32_t RESERVED1;     /* 0x014 */
    __IO uint32_t WOLCR;         /* 0x018 */
    __IO uint32_t WOLSR;         /* 0x01C */
    __IO uint32_t WFCRC;         /* 0x020 */
    __IO uint32_t WFBM[4];       /* 0x024 ~ 0x0x030 */
    __IO uint32_t PTPRXUNDA;     /* 0x034 */
    __IO uint32_t PTPTXUNDA;     /* 0x038 */
    __IO uint32_t PTPTXPSEC;     /* 0x03C */
    __IO uint32_t PTPTXPNSEC;    /* 0x040 */
    __IO uint32_t PTPRXPSEC;     /* 0x044 */
    __IO uint32_t PTPRXPNSEC;    /* 0x048 */
    __IO uint32_t PTPTXPPSEC;    /* 0x04C */
    __IO uint32_t PTPTXPPNSEC;   /* 0x050 */
    __IO uint32_t PTPRXPPSEC;    /* 0x054 */
    __IO uint32_t PTPRXPPNSEC;   /* 0x058 */
    __IO uint32_t PTPTMRNN;      /* 0x05C */
    __IO uint32_t PTPTMRN;       /* 0x060 */
    __IO uint32_t PTPTMRS;       /* 0x064 */
    __IO uint32_t PTPPER0;       /* 0x068 */
    __IO uint32_t PTPPER1;       /* 0x06C */
    __IO uint32_t PTPOFFSET;     /* 0x070 */
    __IO uint32_t PTPADJ;        /* 0x074 */
    __IO uint32_t AXICTRL;       /* 0x078 */
    __IO uint32_t PHYIF;         /* 0x07C */
    __IO uint32_t SRCCR;         /* 0x080 */
    __IO uint32_t ECT;           /* 0x084 */
    __IO uint32_t REVR;          /* 0x088 */
    __IO uint32_t FEAR;          /* 0x08C */
    __IO uint32_t BISTR;         /* 0x090 */
    __IO uint32_t TMCR;          /* 0x094 */
    __IO uint32_t BMTCR;         /* 0x098 */
    __IO uint32_t PHYCR;         /* 0x09C */
    __IO uint32_t PHYDATA;       /* 0x0A0 */
    __IO uint32_t RESERVED2[32]; /* 0xA4~0x120 */
    __IO uint32_t RFRAMECNTL;    /* 0x124 */
    __IO uint32_t RFRAMECNTH;    /* 0x128 */
    __IO uint32_t RESERVED3[28]; /* 0x12C~0x198 */
    __IO uint32_t SISR;          /* 0x19C */
    __IO uint32_t SIER;          /* 0x1A0 */
    __IO uint32_t RESERVED4;     /* 0x1A4 */
    __IO uint32_t MACLADR;       /* 0x1A8 */
    __IO uint32_t MACMADR;       /* 0x1AC */
    __IO uint32_t MAHT0;         /* 0x1B0 */
    __IO uint32_t MAHT1;         /* 0x1B4 */
    GMAC_MacFilterRegister_TypeDef sMacFilterRegister[8];
    __IO uint32_t RESERVED5[42]; /* 0x1F8 ~ 0x29C */
    __IO uint32_t RSSC;          /* 0x2A0 */
    __IO uint32_t RSSRK[10];     /* 0x2A4 ~ 0x2C8*/
    __IO uint32_t RESERVED6[18]; /* 0x2CC ~ 0x310 */
    __IO uint32_t TQWBCR;        /* 0x314 */
    __IO uint32_t RQWBCR;        /* 0x318 */
    __IO uint32_t RESERVED7[57]; /* 0x31C ~ 0x3FC*/
    GMAC_QueueRegister_TypeDef sQueueRegister[8];
    __IO uint32_t RESERVED8[16]; /* 0xC00 ~ 0XC3C */
} GMAC_TypeDef;

typedef struct
{
    __IO uint32_t SYSSCU; /* */
} GMAC_SYSCFG_TypeDef;

/* =========================================================================================================================== */
/* ================                                  GPIO                                                     ================ */
/* =========================================================================================================================== */

/**
  * @brief General Purpose I/O (GPIO)
  */
typedef struct
{
  __IO uint32_t GPIOA_AF[4];         /*!< GPIO A alternate function registers, Address offset: 0x1120 - 0x112C */
  __IO uint32_t GPIOB_AF[4];         /*!< GPIO B alternate function registers, Address offset: 0x1130 - 0x113C */
  __IO uint32_t GPIOC_AF[4];         /*!< GPIO C alternate function registers, Address offset: 0x1140 - 0x114C */
  __IO uint32_t GPIOA_PU;            /*!< GPIO A port pull-up register, Address offset: 0x1150 */
  __IO uint32_t GPIOA_PD;            /*!< GPIO A port pull-down register, Address offset: 0x1154 */
  __IO uint32_t GPIOB_PU;            /*!< GPIO B port pull-up register, Address offset: 0x1158 */
  __IO uint32_t GPIOB_PD;            /*!< GPIO B port pull-down register, Address offset: 0x115C */
  __IO uint32_t GPIOC_PU;            /*!< GPIO C port pull-up register, Address offset: 0x1160 */
  __IO uint32_t GPIOC_PD;            /*!< GPIO C port pull-down register, Address offset: 0x1164 */
  __IO uint32_t GPIOA_DRV[2];        /*!< GPIO A port driver strength registers, Address offset: 0x1168 - 0x116C */
  __IO uint32_t GPIOB_DRV[2];        /*!< GPIO B port driver strength registers, Address offset: 0x1170 - 0x1174 */
  __IO uint32_t GPIOC_DRV[2];        /*!< GPIO C port driver strength registers, Address offset: 0x1178 - 0x117C */  
  __IO uint32_t GPIOA_SMT;           /*!< GPIO A port schmitt trigger register, Address offset: 0x1180 */
  __IO uint32_t GPIOB_SMT;           /*!< GPIO B port schmitt trigger register, Address offset: 0x1184 */
  __IO uint32_t GPIOC_SMT;           /*!< GPIO C port schmitt trigger register, Address offset: 0x1188 */
  __IO uint32_t GPIOC_LS3V;          /*!< GPIO C port LS3V register, Address offset: 0x118C */  //TODO:LS3V?
} GPIO_Attribute_TypeDef;

typedef struct
{
  __IO uint32_t OUT;                 /*!< GPIO output register, Address offset: 0x0 */  
  __I  uint32_t IN;                  /*!< GPIO input register, Address offset: 0x4 */
  __IO uint32_t DIR;                 /*!< GPIO direction register, Address offset: 0x8 */
  uint32_t RESERVED0;                /*!< Reserved, 0xC */
  __IO uint32_t SET;                 /*!< GPIO bits set register, Address offset: 0x10 */ 
  __IO uint32_t CLR;                 /*!< GPIO bits clear register, Address offset: 0x14 */ 
  uint32_t RESERVED1[2];             /*!< Reserved, 0x18 - 0x1C */
  __IO uint32_t IER;                 /*!< GPIO interrupt enable register, Address offset: 0x20 */
  __I  uint32_t IRS;                 /*!< GPIO interrupt raw state register, Address offset: 0x24 */
  __I  uint32_t IMS;                 /*!< GPIO interrupt masked state register, Address offset: 0x28 */
  __IO uint32_t IM;                  /*!< GPIO interrupt mask register, Address offset: 0x2C */          
  __IO uint32_t ICLR;                /*!< GPIO interrupt clear register, Address offset: 0x30 */
  __IO uint32_t TMR;                 /*!< GPIO interrupt trigger mode register, Address offset: 0x34 */
  __IO uint32_t TER;                 /*!< GPIO interrupt trigger edge mode register, Address offset: 0x38 */ //TODO
  __IO uint32_t TRFR;                /*!< GPIO interrupt trigger edge select register, Address offset: 0x3C */  //TODO
  __IO uint32_t DBCR;                /*!< GPIO debounce register, Address offset: 0x40 */
  __IO uint32_t DBCCNT;              /*!< GPIO debounce count register, Address offset: 0x44 */
} GPIO_TypeDef;

/* =========================================================================================================================== */
/* ================                                  I2C                                                      ================ */
/* =========================================================================================================================== */
/**
  * @brief Inter-integrated Circuit Interface (I2C)  
  */
typedef struct
{
    __IO uint32_t CR;
    __IO uint32_t SR;
    __IO uint32_t CDR;
    __IO uint32_t DR;
    __IO uint32_t AR;
    __IO uint32_t TGSR;
    __IO uint32_t BMR;
    __IO uint32_t BSTMR;
    uint32_t      RESERVED0[4];
    __IO uint32_t REVISION;
} I2C_TypeDef;

/* =========================================================================================================================== */
/* ================                                  LTDC                                                     ================ */
/* =========================================================================================================================== */
/**
 * @brief LCD-TFT Display Controller
 */
typedef struct
{
    __IO uint32_t FUNCTION_EN;
    __IO uint32_t PANEL_PIXEL;
    __IO uint32_t IMR;      /*!< LCD interrupt mask register */
    __IO uint32_t ICR;      /*!< LCD interrupt clear register */
    __IO uint32_t ISR;      /*!< LCD interrupt status register */
    __IO uint32_t FB_PARAM; /*!< LCD frame buffer register */
    __IO uint32_t IM0_BASE;
    uint32_t      RESERVED0[2];
    __IO uint32_t IM1_BASE;
    uint32_t      RESERVED1[2];
    __IO uint32_t IM2_BASE;
    uint32_t      RESERVED2[2];
    __IO uint32_t IM3_BASE;
    uint32_t      RESERVED3[2];
    __IO uint32_t PATTERN_BAR_COLOR;  /*!< LCD pattern generator */
    __IO uint32_t FIFO_THRESHOLD;
    __IO uint32_t BANDWIDTH_CTRL;
    uint32_t      RESERVED4[1];
    __IO uint32_t IP_VERSION;
    __IO uint32_t VBI_BASE;
    __IO uint32_t FIFO4_THRESHOLD;
    uint32_t      RESERVED5[3];
    __IO uint32_t FEATUR0;
    __IO uint32_t FEATUR1;
    uint32_t      RESERVED6[34];
    __IO uint32_t HORTIMING;
    __IO uint32_t VERTIMING0;
    __IO uint32_t VERTIMING1;
    __IO uint32_t POLARITY;         /* 0x10C */
    uint32_t      RESERVED7[124];
    __IO uint32_t PIP_BLEND_PARAM;  /* 0x300 */
    __IO uint32_t PIP_SUB1_POSITION_PARAM;
    __IO uint32_t PIP_SUB1_DIMENSION_PARAM;
    __IO uint32_t PIP_SUB2_POSITION_PARAM;
    __IO uint32_t PIP_SUB2_DIMENSION_PARAM;
    __IO uint32_t PIP_IMAGE_PRIORITY;
    __IO uint32_t PIOP_IMAGE_FORMAT1;
    __IO uint32_t PIOP_IMAGE_FORMAT2;
    __IO uint32_t PIP_COLOR_KEY1;
    __IO uint32_t PIP_COLOR_KEY2;
    __IO uint32_t PIP_COLOR_KEY3;
    __IO uint32_t PIP_SUB3_POSITION_PARAM;
    __IO uint32_t PIP_SUB3_DIMENSION_PARAM;/* 0x330 */
    uint32_t      RESERVED8[179];
    __IO uint32_t GARDLUT[64];
    __IO uint32_t GAGNLUT[64];
    __IO uint32_t GABULUT[64];
    uint32_t      RESERVED9[512];
    __IO uint32_t HOR_RESOLUTION_IN;/* 0x1100 */
    __IO uint32_t VER_RESOLUTION_IN;
    __IO uint32_t HOR_RESOLUTION_OUT;
    __IO uint32_t VER_RESOLUTION_OUT;
    __IO uint32_t SCALER_CONTROL;
    __IO uint32_t HOR_HIGH_THRESHOLD;
    __IO uint32_t HOR_LOW_THRESHOLD;
    __IO uint32_t VER_HIGH_THRESHOLD;
    __IO uint32_t VER_LOW_THRESHOLD;
    __IO uint32_t SCALER_RESOLUTION_PARAM;
} LTDC_TypeDef;

/* =========================================================================================================================== */
/* ================                                   MAC                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief MAC
  */

typedef struct
{
    __IO uint32_t ISR;          /* 0x00 */
    __IO uint32_t IER;          /* 0x04 */
    __IO uint32_t MACMADR;      /* 0x08 */
    __IO uint32_t MACLADR;      /* 0x0C */
    __IO uint32_t MAHT0;        /* 0x10 */
    __IO uint32_t MAHT1;        /* 0x14 */
    __IO uint32_t NPTXPD;       /* 0x18 */
    __IO uint32_t RXPD;         /* 0x1C */
    __IO uint32_t NPTXRBADR;    /* 0x20 */
    __IO uint32_t RXRBADR;      /* 0x24 */
    __IO uint32_t HPTXPD;       /* 0x28 */
    __IO uint32_t HPTXRBADR;    /* 0x2C */
    __IO uint32_t TXITC;        /* 0x30 */
    __IO uint32_t RXITC;        /* 0x34 */
    __IO uint32_t APTC;         /* 0x38 */
    __IO uint32_t DBLAC;        /* 0x3C */
    __IO uint32_t DMAFIFOS;     /* 0x40 */
    __IO uint32_t RESERVED0;    /* 0x44 */
    __IO uint32_t TPAFCR;       /* 0x48 */
    __IO uint32_t RBSR;         /* 0x4C */
    __IO uint32_t MACCR;        /* 0x50 */
    __IO uint32_t MACSR;        /* 0x54 */
    __IO uint32_t TM;           /* 0x58 */
    __IO uint32_t RESERVED1;    /* 0x5C */
    __IO uint32_t PHYCR;        /* 0x60 */
    __IO uint32_t PHYDATA;      /* 0x64 */
    __IO uint32_t FCR;          /* 0x68 */
    __IO uint32_t BPR;          /* 0x6C */
    __IO uint32_t WOLCR;        /* 0x70 */
    __IO uint32_t WOLSR;        /* 0x74 */
    __IO uint32_t WFCRC;        /* 0x78 */
    __IO uint32_t RESERVED2;    /* 0x7C */
    __IO uint32_t WFBM1;        /* 0x80 */
    __IO uint32_t WFBM2;        /* 0x84 */
    __IO uint32_t WFBM3;        /* 0x88 */
    __IO uint32_t WFBM4;        /* 0x8C */
    __IO uint32_t NPTXRPTR;     /* 0x90 */
    __IO uint32_t HPTXRPTR;     /* 0x94 */
    __IO uint32_t RXRPTR;       /* 0x98 */
    __IO uint32_t RESERVED3;    /* 0x9C */
    __IO uint32_t TPKTCNT;      /* 0xA0 */
    __IO uint32_t TXMSCOLCNT;   /* 0xA4 */
    __IO uint32_t TXEFCNT;      /* 0xA8 */
    __IO uint32_t TXLUCNT;      /* 0xAC */
    __IO uint32_t RPKTCNT;      /* 0xB0 */
    __IO uint32_t BROPKTCNT;    /* 0xB4 */
    __IO uint32_t MULPKTCNT;    /* 0xB8 */
    __IO uint32_t RPFAEPCNT;    /* 0xBC */
    __IO uint32_t RUNTCNT;      /* 0xC0 */
    __IO uint32_t CRCERFTLCNT;  /* 0xC4 */
    __IO uint32_t RCOLLOSRCNT;  /* 0xC8 */
    __IO uint32_t BISTR;        /* 0xCC */
    __IO uint32_t BMRCR;        /* 0xD0 */
    __IO uint32_t RESERVED4[4]; /* 0xD4 ~ 0xE3 */
    __IO uint32_t ACIR;         /* AXI additional Control Information 0xE4 */
    __IO uint32_t GISR;         /* GMAC Interface Selection 0xE8 */
    __IO uint32_t RESERVED5;    /* 0xEC */
    __IO uint32_t ECT;          /* EEE Control Register 0xF0 */
    __IO uint32_t REVR;         /* 0xF4 */
    __IO uint32_t FEAR;         /* 0xF8 */
} MAC_TypeDef;

/* =========================================================================================================================== */
/* ================                                  MINTC                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief Massage and Interrupt Controller (MINTC)  //TODO
  */
typedef struct
{
    __IO uint32_t IMCR[8];           /*!< Interrupt mux control register, Address offset: 0x0 - 0x1C */
    uint32_t RESERVED0[16];          /*!< Reserved, 0x20 - 0x5C */
    __IO uint32_t IPCR[8];           /*!< IPC register, Address offset: 0x60 - 0x7C */
} MINTC_TypeDef;

/* =========================================================================================================================== */
/* ================                                  RCCS                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief Reset and Clock Control of System (RCCS)  
  */
typedef struct
{
    __IO uint32_t CFGR;              /*!< RCCS PLLHP configuration register, Address offset: 0x5C */
    __IO uint32_t DIVR;              /*!< RCCS PLLHP divider register, Address offset: 0x60 */
    __IO uint32_t FRACR;             /*!< RCCS PLLHP fractional register, Address offset: 0x64 */
} RCCS_PLLHP_TypeDef;

typedef struct
{
    __IO uint32_t MCR;               /*!< RCCS misc control register, Address offset: 0x00 */
    __IO uint32_t CCNT;              /*!< RCCS clk counter register, Address offset: 0x04 */      
    __IO uint32_t WRR0;              /*!< RCCS watchdog record register 0, Address offset: 0x08 */
    __IO uint32_t WRR1;              /*!< RCCS watchdog record register 1, Address offset: 0x0C */
    uint32_t      RESERVED0[2];      /*!< Reserved, 0x10 - 0x14 */
    __IO uint32_t MCORERAR;          /*!< RCCS main processor reset address register, Address offset: 0x18 */
    __IO uint32_t CCORERAR;          /*!< RCCS co-processor reset address register, Address offset: 0x1C */
    uint32_t      RESERVED1[12];     /*!< Reserved, 0x20 - 0x4C */
    __IO uint32_t PLLSYSCFGR;        /*!< RCCS PLLSYS configuration register, Address offset: 0x50 */
    __IO uint32_t PLLMACCFGR;        /*!< RCCS PLLMAC configuration register, Address offset: 0x54 */      
    __IO uint32_t PLLDDRCFGR;        /*!< RCCS PLLDDR configuration register, Address offset: 0x58 */
    RCCS_PLLHP_TypeDef PLLHP[2];     /*!< RCCS PLLHP, Address offset: 0x5C - 0x70 */
    uint32_t      RESERVED2[3];      /*!< Reserved, 0x74-0x7C */
    __IO uint32_t CLKENR0;           /*!< RCCS clock enable register 0, Address offset: 0x80 */
    __IO uint32_t CLKENR1;           /*!< RCCS clock enable register 1, Address offset: 0x84 */
    __IO uint32_t CLKENR2;           /*!< RCCS clock enable register 2, Address offset: 0x88 */
    __IO uint32_t AXIDIVR;           /*!< RCCS AXI clock divider register, Address offset: 0x8C */
    __IO uint32_t AHBDIVR;           /*!< RCCS AHB clock divider register, Address offset: 0x90 */
    __IO uint32_t APBPDIVR;          /*!< RCCS APB peripheral bus clock divider register, Address offset: 0x94 */
    __IO uint32_t CPUDIVR;           /*!< RCCS CPU clock divider register, Address offset: 0x98 */
    __IO uint32_t HSMDIVR;           /*!< RCCS HSM clock divider register, Address offset: 0x9C */
    __IO uint32_t LPCDIVR;           /*!< RCCS LPC clock divider register, Address offset: 0xA0 */
    __IO uint32_t FMC0DIVR;          /*!< RCCS FMC0 clock divider register, Address offset: 0xA4 */
    __IO uint32_t FMC1DIVR;          /*!< RCCS FMC1 clock divider register, Address offset: 0xA8 */
    __IO uint32_t UART1DIVR;         /*!< RCCS UART1 clock divider register, Address offset: 0xAC */
    __IO uint32_t UART2DIVR;         /*!< RCCS UART2 clock divider register, Address offset: 0xB0 */
    __IO uint32_t UART3DIVR;         /*!< RCCS UART3 clock divider register, Address offset: 0xB4 */
    __IO uint32_t UART4DIVR;         /*!< RCCS UART4 clock divider register, Address offset: 0xB8 */
    __IO uint32_t UART5DIVR;         /*!< RCCS UART5 clock divider register, Address offset: 0xBC */
    __IO uint32_t UART6DIVR;         /*!< RCCS UART6 clock divider register, Address offset: 0xC0 */
    __IO uint32_t UART7DIVR;         /*!< RCCS UART7 clock divider register, Address offset: 0xC4 */
    __IO uint32_t SCI0DIVR;          /*!< RCCS SCI0 clock divider register, Address offset: 0xC8 */
    __IO uint32_t SCI1DIVR;          /*!< RCCS SCI1 clock divider register, Address offset: 0xCC */
    __IO uint32_t SPI0DIVR;          /*!< RCCS SPI0 clock divider register, Address offset: 0xD0 */
    __IO uint32_t SPI1DIVR;          /*!< RCCS SPI1 clock divider register, Address offset: 0xD4 */
    __IO uint32_t SSP0DIVR;          /*!< RCCS SSP0 clock divider register, Address offset: 0xD8 */
    __IO uint32_t SSP1DIVR;          /*!< RCCS SSP1 clock divider register, Address offset: 0xDC */
    __IO uint32_t CANA1DIVR;         /*!< RCCS CANA1 clock divider register, Address offset: 0xE0 */
    __IO uint32_t CANA2DIVR;         /*!< RCCS CANA2 clock divider register, Address offset: 0xE4 */
    __IO uint32_t CANA3DIVR;         /*!< RCCS CANA3 clock divider register, Address offset: 0xE8 */
    __IO uint32_t CANB0DIVR;         /*!< RCCS CANB0 clock divider register, Address offset: 0xEC */
    __IO uint32_t CANB1DIVR;         /*!< RCCS CANB1 clock divider register, Address offset: 0xF0 */
    __IO uint32_t CANB2DIVR;         /*!< RCCS CANB2 clock divider register, Address offset: 0xF4 */
    __IO uint32_t CANB3DIVR;         /*!< RCCS CANB3 clock divider register, Address offset: 0xF8 */
    __IO uint32_t USB3C60MDIVR;      /*!< RCCS USB3.0 clock divider register 0, for 60MHz clock, Address offset: 0xFC */
    __IO uint32_t USB3LPDIVR;        /*!< RCCS USB3.0 clock divider register 1, for LP clock, Address offset: 0x100 */ 
    __IO uint32_t GMAC0C312P5MDIVR;  /*!< RCCS GMAC0 clock divider register 0, for 312.5MHz clock, Address offset: 0x104 */
    __IO uint32_t GMAC1C312P5MDIVR;  /*!< RCCS GMAC1 clock divider register 0, for 312.5MHz clock, Address offset: 0x108 */
    __IO uint32_t GMAC0C125MDIVR;    /*!< RCCS GMAC0 clock divider register 1, for 125MHz clock, Address offset: 0x10C */
    __IO uint32_t GMAC1C125MDIVR;    /*!< RCCS GMAC1 clock divider register 1, for 125MHz clock, Address offset: 0x110 */
    __IO uint32_t MAC0C25MDIVR;      /*!< RCCS MAC0 clock divider register 0, for 25MHz clock, Address offset: 0x114 */
    __IO uint32_t MAC1C15MDIVR;      /*!< RCCS MAC1 clock divider register 0, for 25MHz clock, Address offset: 0x118 */
    __IO uint32_t MAC0C2P5MDIVR;     /*!< RCCS MAC0 clock divider register 1, for 2.5MHz clock, Address offset: 0x11C */
    __IO uint32_t MAC1C2P5MDIVR;     /*!< RCCS MAC1 clock divider register 1, for 2.5MHz clock, Address offset: 0x120 */
    __IO uint32_t SDHC2DIVR;         /*!< RCCS SDHC2 clock divider register, Address offset: 0x124 */
    __IO uint32_t SDHC1DIVR;         /*!< RCCS SDHC1 clock divider register, Address offset: 0x128 */
    __IO uint32_t SDHC0DIVR;         /*!< RCCS SDHC0 clock divider register, Address offset: 0x12C */
    __IO uint32_t APBCDIVR;          /*!< RCCS APB control bus clock divider register, Address offset: 0x130 */
    __IO uint32_t LTDCLCDIVR;        /*!< RCCS LTDC clock divider register 0, for LC clock, Address offset: 0x134 */
    __IO uint32_t LTDCTVDIVR;        /*!< RCCS LTDC clock divider register 1, for TV clock, Address offset: 0x138 */
    __IO uint32_t LTDCSCDIVR;        /*!< RCCS LTDC clock divider register 1, for LC SCALER clock, Address offset: 0x13C */
    __IO uint32_t USB2C30MDIVR;      /*!< RCCS USB2.0 clock divider register, Address offset: 0x140 */
    uint32_t      RESERVED3;         /*!< Reserved, 0x144 */
    __IO uint32_t GMAC0C25MDIVR;     /*!< RCCS GMAC0 clock divider register 2, for 25MHz clock, Address offset: 0x148 */
    __IO uint32_t GMAC1C25MDIVR;     /*!< RCCS GMAC1 clock divider register 2, for 25MHz clock, Address offset: 0x14c */
    __IO uint32_t PCIEDIVR;          /*!< RCCS PCIE clock divider register, Address offset: 0x150 */
    __IO uint32_t USB3C30MDIVR;      /*!< RCCS USB3.0 clock divider register 2, for 30MHz clock, Address offset: 0x154 */
    __IO uint32_t GMAC0C2P5MDIVR;    /*!< RCCS GMAC0 clock divider register 3, for 2.5MHz clock, Address offset: 0x158 */
    __IO uint32_t GMAC1C2P5MDIVR;    /*!< RCCS GMAC1 clock divider register 3, for 2.5MHz clock, Address offset: 0x15C */
    uint32_t      RESERVED4[4];      /*!< Reserved, 0x160-0x16C */
    __IO uint32_t RSTCR0;            /*!< RCCS reset control register 0, Address offset: 0x170 */
    __IO uint32_t RSTCR1;            /*!< RCCS reset control register 1, Address offset: 0x174 */      
    __IO uint32_t RSTCR2;            /*!< RCCS reset control register 2, Address offset: 0x178 */
} RCCS_TypeDef;

/* =========================================================================================================================== */
/* ================                                  RTC                                                      ================ */
/* =========================================================================================================================== */
/**
  * @brief Real-Time Clock (RTC)
  */
typedef struct
{
    __IO uint32_t SECOND;
    __IO uint32_t MINUTE;
    __IO uint32_t HOUR;
    __IO uint32_t DAY;
    __IO uint32_t ALARM_SECOND;
    __IO uint32_t ALARM_MINUTE;
    __IO uint32_t ALARM_HOUR;
    uint32_t RESERVED0;
    __IO uint32_t CR;
    __IO uint32_t WRITE_SECOND;
    __IO uint32_t WRITE_MINUTE;
    __IO uint32_t WRITE_HOUR;
    __IO uint32_t WRITE_DAY;
    __IO uint32_t ISR;
    uint32_t RESERVED1;
    __IO uint32_t REVISION;
    __IO uint32_t RW_STATUS;
    __IO uint32_t CURRENT;
    __IO uint32_t SLEEP_TIME;
    __IO uint32_t CUR_DATE;
    __IO uint32_t SLEEP_DATE;
} RTC_TypeDef;

/* =========================================================================================================================== */
/* ================                                  SCI                                                      ================ */
/* =========================================================================================================================== */
/** 
  * @brief Smart Card Interface
  */

typedef struct
{
    __IO uint32_t DR;       /*!< SCI data register,                           Address offset: 0x00 */
    __IO uint32_t CR0;      /*!< SCI control register 0,                      Address offset: 0x04 */      
    __IO uint32_t CR1;      /*!< SCI control register 1,                      Address offset: 0x08 */      
    __IO uint32_t CR2;      /*!< SCI control register 2,                      Address offset: 0x0C */      
    __IO uint32_t IER;      /*!< SCI interrupt enable register,               Address offset: 0x10 */      
    __IO uint32_t RETRY;    /*!< SCI retry limit register,                    Address offset: 0x14 */      
    __IO uint32_t TIDE;     /*!< SCI FIFO tide mark register,                 Address offset: 0x18 */      
    __IO uint32_t TXCNT;    /*!< SCI transmit FIFO count/clear register,      Address offset: 0x1C */      
    __IO uint32_t RXCNT;    /*!< SCI receive FIFO count/clear register,       Address offset: 0x20 */      
    __IO uint32_t FR;       /*!< SCI flag register,                           Address offset: 0x24 */      
    __IO uint32_t RXTIME;    /*!< SCI receive read timeout register,           Address offset: 0x28 */      
    __IO uint32_t ISTAT;    /*!< SCI ICC status register,                     Address offset: 0x2C */      
    __IO uint32_t STABLE;   /*!< SCI debounce timer register,                 Address offset: 0x30 */      
    __IO uint32_t ATIME;    /*!< SCI activation event time register,          Address offset: 0x34 */      
    __IO uint32_t DTIME;    /*!< SCI deactivation event time register,        Address offset: 0x38 */      
    __IO uint32_t ATRSTIME; /*!< the time to start of ATR reception register, Address offset: 0x3C */      
    __IO uint32_t ATRDTIME; /*!< maximum duration of ATR character register,  Address offset: 0x40 */      
    __IO uint32_t BLKTIME;  /*!< SCI receive timeout between blocks register, Address offset: 0x44 */      
    __IO uint32_t CHTIME;   /*!< character to character timeout register,     Address offset: 0x48 */      
    __IO uint32_t CLKICC;   /*!< external smart card clcok frequency register,Address offset: 0x4C */      
    __IO uint32_t BAUD;     /*!< SCI baud rate clock register,                Address offset: 0x50 */      
    __IO uint32_t VALUE;    /*!< SCI baud cycles register,                    Address offset: 0x54 */      
    __IO uint32_t CHGUARD;  /*!< character to character extra guard time reg, Address offset: 0x58 */      
    __IO uint32_t BLKGUARD; /*!< SCI block guard time register,               Address offset: 0x5C */      
    __IO uint32_t SYNCCR;   /*!< asynchronous/synchronous multiplexing reg,   Address offset: 0x60 */      
    __IO uint32_t SYNCDATA; /*!< synchronous smart card data register,        Address offset: 0x64 */      
    __IO uint32_t RAWSTAT;  /*!< raw input/output and clock status register,  Address offset: 0x68 */      
    __IO uint32_t IIR;      /*!< SCI interruot identification/clear register, Address offset: 0x6C */      
}SCI_TypeDef;

/* =========================================================================================================================== */
/* ================                                  SDDC                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief Secure Digital memory card Device Controller (SDDC)
  */

// TODO : serial number from 1
typedef struct
{
    __IO uint32_t CR;           /*!< SDDC Control register,                         Address offset: 0x00 */
    __IO uint32_t CMD;          /*!< SDDC received command register,                Address offset: 0x04 */
    __IO uint32_t ARG;          /*!< SDDC received argument register,               Address offset: 0x08 */
    __IO uint32_t BCOUNT;       /*!< SDDC Block count register,                     Address offset: 0x0C */
    __IO uint32_t DMA1AR;       /*!< SDDC DMA1 Address register,                    Address offset: 0x10 */      
    __IO uint32_t DMA1CR;       /*!< SDDC DMA1 Contrl register,                     Address offset: 0x14 */     
    __IO uint32_t DMA2AR;       /*!< SDDC DMA2Address register,                     Address offset: 0x14 */
    __IO uint32_t DMA2CR;       /*!< SDDC DMA2Address register,                     Address offset: 0x1C */     
    __IO uint32_t EWSAR;        /*!< Erase Write Block Start Register               Address offset: 0x20 */
    __IO uint32_t EWEAR;        /*!< Erase Write Block End Register                 Address offset: 0x24 */  
    __IO uint32_t PLR;          /*!<Password Length Register                        Address offset: 0x28 */  
    __IO uint32_t SBCOUNT;      /*!<Secure Block Count Register                     Address offset: 0x2C */ 
    uint32_t RESERVED0[3];
    __IO uint32_t ISR;          /*!<Interrupt Status Register                       Address offset: 0x3C */        
    __IO uint32_t ISCR;         /*!<Interrupt Status Enable Register                Address offset: 0x40 */
    __IO uint32_t ISGCR;        /*!<Interrupt Signal Enable Register                Address offset: 0x44 */
    __IO uint32_t CAR;          /*!<CardAddress Register                            Address offset: 0x48 */     
    __IO uint32_t CDR;          /*!<Card Data Register                              Address offset: 0x4C */     
    __IO uint32_t IORR;         /*!<IOREADY Register                                Address offset: 0x50 */       
    __IO uint32_t FUN1;         /*!<Function1 Control Register                      Address offset: 0x54 */     
    __IO uint32_t FUN2;         /*!<Function2 Control Register                      Address offset: 0x58 */     
    __IO uint32_t CCCR;         /*!<SDIO CCCR Control Register                      Address offset: 0x5C */
    __IO uint32_t FBR0;         /*!<SDIO FBR0 Control Register                      Address offset: 0x60 */
    __IO uint32_t FBR1;         /*!<SDIO FBR1 Control Register                      Address offset: 0x64 */
    __IO uint32_t FBR2;         /*!<SDIO FBR2 Control Register                      Address offset: 0x68 */
    __IO uint32_t FBR3;         /*!<SDIO FBR3 Control Register                      Address offset: 0x6C */
    __IO uint32_t FBR4;         /*!<SDIO FBR4 Control Register                      Address offset: 0x70 */
    __IO uint32_t FBR5;         /*!<SDIO FBR5 Control Register                      Address offset: 0x74 */
    __IO uint32_t FBR6;         /*!<SDIO FBR6 Control Register                      Address offset: 0x78 */
    __IO uint32_t FBR7;         /*!<SDIO FBR7 Control Register                      Address offset: 0x7C */
    __IO uint32_t CSIZE;        /*!<Card Size Register                              Address offset: 0x80 */     
    __IO uint32_t OCR;          /*!<Secure Block Count Register                     Address offset: 0x84 */      
    __IO uint32_t CR2;          /*!<Card OCR Register                               Address offset: 0x88 */         
    uint32_t RESERVED2;
    __IO uint32_t FUN3;         /*!<Function3 Control Register                      Address offset: 0x90 */     
    __IO uint32_t FUN4;         /*!<Function4 Control Register                      Address offset: 0x94 */     
    __IO uint32_t FUN5;         /*!<Function5 Control Register                      Address offset: 0x98 */     
    __IO uint32_t ISR2;         /*!<Interrupt Status2 Register                      Address offset: 0x9C */  
    __IO uint32_t ISCR2;        /*!<Interrupt Status Enable2 Register               Address offset: 0xA0 */  
    __IO uint32_t ISGCR2;       /*!<Interrupt Signal Enable2 Register               Address offset: 0xA4 */  
    __IO uint32_t PSWD4;        /*!<Password Register_127_96                        Address offset: 0xA8 */    
    __IO uint32_t PSWD3;        /*!<Password_95_64 Register                         Address offset: 0xAC */    
    __IO uint32_t PSWD2;        /*!<Password_64_32 Register                         Address offset: 0xB0 */    
    __IO uint32_t PSWD1;        /*!<Password_31_0 Register                          Address offset: 0xB4 */    
    __IO uint32_t ADMAESR;      /*!<ADMA Error Status Register                      Address offset: 0xB8 */
    __IO uint32_t RCA;          /*!< RCA Register                                   Address offset: 0xBC */           
    uint32_t RESERVED3[7];      
    __IO uint32_t BURST;        /*!<AHB Master Burst size register                  Address offset: 0xDC */
    __IO uint32_t ARG2;         /*!<Argument2 Register                              Address offset: 0xE0 */         

} SDDC_TypeDef;

typedef struct 
{
   __IO uint32_t SR;               /*!< SDC slave master mode switch, Address offset: 0x0 */
   __IO uint32_t MCR;              /*!< SDC master ctrl, Address offset: 0x4 */ 
   uint32_t RESERVED0;             /*!< Reserved, 0x8 */
   __IO uint32_t SMID;             /*!< SDDC SMID, Address offset: 0xC */
   __IO uint32_t OCR;              /*!< SDDC SDIO Operation condition register, Address offset: 0xC */
   uint32_t RESERVED1;             /*!< Reserved, 0x10 */
   __IO uint32_t DLL;              /*!< SDC mater dll configuration register, Address offset: 0x14 */
} SDC_Config_TypeDef; 

/* =========================================================================================================================== */
/* ================                                  SDIO                                                     ================ */
/* =========================================================================================================================== */
/** 
  * @brief SD host Interface
  */
typedef struct
{
    __IO uint32_t SDMAADR;      /*!< SDMA System Address register,                Address offset: 0x00 */
    __IO uint16_t BLKSIZE;      /*!< Block Size register,                         Address offset: 0x04 */
    __IO uint16_t BLKCNT;       /*!< Block Count register,                        Address offset: 0x06 */
    __IO uint32_t CMDARG;       /*!< Argument 1 register,                         Address offset: 0x08 */
    __IO uint16_t TXMODE;       /*!< Transfer mode register,                      Address offset: 0x0C */
    __IO uint16_t CMDVAL;       /*!< Command register,                            Address offset: 0x0E */
    __IO uint64_t CMDRSPLO;     /*!< Response register 0 & 1,                     Address offset: 0x10 */
    __IO uint64_t CMDRSPHI;     /*!< Response register 2 & 3,                     Address offset: 0x18 */
    __IO uint32_t BUFFER;       /*!< Buffer Data Port register,                   Address offset: 0x20 */
    __IO uint32_t PRESENTSTA;   /*!< Present state register,                      Address offset: 0x24 */
    __IO uint8_t CTRL1;         /*!< Host Control 1 register,                     Address offset: 0x28 */
    __IO uint8_t PWRCTRL;       /*!< Power Control register,                      Address offset: 0x29 */
    __IO uint8_t BLKGAPCTRL;    /*!< Block Gap Control register,                  Address offset: 0x2A */
    __IO uint8_t WAKEUPCTRL;    /*!< Wakeup Control register,                     Address offset: 0x2B */
    __IO uint16_t CLKCTRL;      /*!< Clock Control register,                      Address offset: 0x2C */
    __IO uint8_t TIMEOUTCTRL;   /*!< Timeout Control register,                    Address offset: 0x2E */
    __IO uint8_t SOFTRST;       /*!< Software Reset register,                     Address offset: 0x2F */
    __IO uint16_t ISR;          /*!< Normal Interrupt Status register,            Address offset: 0x30 */
    __IO uint16_t ERRISR;       /*!< Error Interrupt Status register,             Address offset: 0x32 */
    __IO uint16_t INTREN;       /*!< Normal Interrupt Status Enable register,     Address offset: 0x34 */
    __IO uint16_t ERRINTREN;    /*!< Error Interrupt Status Enable register,      Address offset: 0x36 */
    __IO uint16_t SIGINTREN;    /*!< Normal Interrupt Signal Enable register,     Address offset: 0x38 */
    __IO uint16_t ERRSIGINTREN; /*!< Error Interrupt Signal Enable register,      Address offset: 0x3A */
    __IO uint16_t AUTOCMDERR;   /*!< Auto CMD12 Error Status register,            Address offset: 0x3C */
    __IO uint16_t CTRL2;        /*!< Host Control 2 register,                     Address offset: 0x3E */
    __IO uint64_t CAPABILITY;   /*!< Capabilities 0 & 1 register,                 Address offset: 0x40 */
    __IO uint64_t MAXCURCAP;    /*!< Maximum Current Capabilities register,       Address offset: 0x48 */
    uint32_t RESERVED0;         /*!< Reserved, 0x50 */
    __IO uint32_t ADMAERRISR;   /*!< ADMA Eoor Status register,                   Address offset: 0x54 */
    __IO uint32_t ADMAADDR;     /*!< ADMA System Address register,                Address offset: 0x58 */
    uint32_t RESERVED1;         /*!< Reserved, 0x5C */
    __IO uint16_t PRESETINIT;   /*!< Preset Value for initialization register,    Address offset: 0x60 */
    __IO uint16_t PRESETDS;     /*!< Preset Value for the deault speed register,  Address offset: 0x62 */
    __IO uint16_t PRESETHS;     /*!< Preset Value for the high speed register,    Address offset: 0x64 */
    __IO uint16_t PRESETSDR12;  /*!< Preset Value for SDR12 register,             Address offset: 0x66 */
    __IO uint16_t PRESETSDR25;  /*!< Preset Value for SDR25 register,             Address offset: 0x68 */
    __IO uint16_t PRESETSDR50;  /*!< Preset Value for SDR50 register,             Address offset: 0x6A */
    __IO uint16_t PRESETSDR104; /*!< Preset Value for SDR104 register,            Address offset: 0x6C */
    __IO uint16_t PRESETDDR50;  /*!< Preset Value for DDR50 register,             Address offset: 0x6E */
    uint32_t RESERVED2[34];     /*!< Reserved, 0x70 - 0xF8 */
    uint16_t RESERVED3;         /*!< Reserved, 0xFC */ 
    __IO uint16_t HCVER;        /*!< High Controller Version register,            Address offset: 0xFE */
    __IO uint32_t VENDORREG0;   /*!< Vendor defined Register 0,                   Address offset: 0x100 */
    __IO uint32_t VENDORREG1;   /*!< Vendor defined Register 1,                   Address offset: 0x104 */
    __IO uint32_t VENDORREG2;   /*!< Vendor defined Register 2,                   Address offset: 0x108 */
    __IO uint32_t VENDORREG3;   /*!< Vendor defined Register 3,                   Address offset: 0x10C */
    __IO uint32_t VENDORREG4;   /*!< Vendor defined Register 4,                   Address offset: 0x110 */
    __IO uint32_t VENDORREG5;   /*!< Vendor defined Register 5,                   Address offset: 0x114 */
    __IO uint32_t VENDORREG6;   /*!< Vendor defined Register 6,                   Address offset: 0x118 */
    __IO uint32_t VENDORREG7;   /*!< Vendor defined Register 7,                   Address offset: 0x11C */
    __IO uint32_t VENDORREG8;   /*!< Vendor defined Register 8,                   Address offset: 0x120 */
    __IO uint32_t VENDORREG9;   /*!< Vendor defined Register 9,                   Address offset: 0x124 */
    __IO uint32_t DMAHANDSHK;   /*!< DMA Handshake Enable Register,               Address offset: 0x128 */
    uint32_t RESERVED4[18];     /*!< Reserved, 0x12C - 0x174 */
    __IO uint32_t HWATTRIBUTES; /*!< Hardware Attributes Register,                Address offset: 0x178 */
    __IO uint32_t IPVERSION;    /*!< IP Revision Register,                        Address offset: 0x17C */
    __IO uint32_t CIPHMCTRL;    /*!< Cipher Mode Control Resigter,                Address offset: 0x180 */
    __IO uint32_t CIPHMSTS;     /*!< Cipher Mode Status Resigter,                 Address offset: 0x184 */
    __IO uint32_t CIPHMSIGEN;   /*!< Cipher Mode Status Enable Resigter,          Address offset: 0x188 */
    __IO uint32_t INDATALO;     /*!< Low Word of Input Data Resigter,             Address offset: 0x18C */
    __IO uint32_t INDATAHI;     /*!< High Word of Input Data Resigter,            Address offset: 0x190 */
    __IO uint32_t INKEYLO;      /*!< Low Word of Input Key Resigter,              Address offset: 0x194 */
    __IO uint32_t INKEYHI;      /*!< High Word of Input Key Resigter,             Address offset: 0x198 */
    __IO uint32_t OUTDATALO;    /*!< Low Word of Output Data Resigter,            Address offset: 0x19C */
    __IO uint32_t OUTDATAHI;    /*!< High Word of Output Data Resigter,           Address offset: 0x1A0 */
    __IO uint32_t SECRTABPORT;  /*!< Secret Constant Table Data Port,             Address offset: 0x1A4 */
	uint32_t RESERVED5[2];     	/*!< Reserved, 0x1A8 - 0x1AC */
    __IO uint32_t CQVER;  		/*!< Command Queuing Version,             		  Address offset: 0x200 */
	__IO uint32_t CQCAP;  		/*!< Command Queuing Capabilities,         		  Address offset: 0x204 */
	__IO uint32_t CQCFG;  		/*!< Command Queuing Configurarion,        		  Address offset: 0x208 */
	__IO uint32_t CQCTL;  		/*!< Command Queuing Control,             		  Address offset: 0x20C */
	__IO uint32_t CQIS;  		/*!< Command Queuing Interruot Status,     		  Address offset: 0x210 */
	__IO uint32_t CQISTE;  		/*!< Command Queuing Interrupt Status Enable,	  Address offset: 0x214 */
	__IO uint32_t CQISGE;  		/*!< Command Queuing Interrupt Signal Enable,	  Address offset: 0x218 */
	__IO uint32_t CQIC;  		/*!< Interrupt Coalescing,             		  	  Address offset: 0x21C */
	__IO uint32_t CQTDLBA; 		/*!< Command Queuing Task Descriptor List Base Address,	  				Address offset: 0x220 */
	__IO uint32_t CQTDLBAU;		/*!< Command Queuing Task Descriptor List Base Address Upper 32 Bits,	Address offset: 0x224 */
	__IO uint32_t CQTDBR;  		/*!< Command Queuing Task Doorbell,        		  Address offset: 0x228 */
	__IO uint32_t CQTCN;  		/*!< Task Completion Notification,         		  Address offset: 0x22C */
	__IO uint32_t CQDQS;  		/*!< Device Queue Status,             		  	  Address offset: 0x230 */
	__IO uint32_t CQDPT;  		/*!< Device Pending Status,             		  Address offset: 0x234 */
	__IO uint32_t CQTCLR;  		/*!< Task Clear,             		  			  Address offset: 0x238 */
	uint32_t RESERVED6;     	/*!< Reserved, 0x23C */
	__IO uint32_t CQSSC1;  		/*!< Send Status Configuration 1,           	  Address offset: 0x240 */
	__IO uint32_t CQSSC2;  		/*!< Send Status Configuration 2,           	  Address offset: 0x244 */
	__IO uint32_t CQCRDCT;  	/*!< Command Response for Direct-Command Task,	  Address offset: 0x248 */
	__IO uint32_t CQRMEMT;  	/*!< Response Mode Error Mask,	  				  Address offset: 0x250 */
	__IO uint32_t CQTERRI;  	/*!< Task Error Information,	  				  Address offset: 0x254 */
	__IO uint32_t CQCRI;  		/*!< Command Response Index,	  				  Address offset: 0x258 */
	__IO uint32_t CQCRA;  		/*!< Command Response Argument,	 				  Address offset: 0x25C */
	__IO uint32_t CQARBSEL;  	/*!< Command Queue Ready Task Arbiration Select,  Address offset: 0x260 */
} SDIO_TypeDef;

/* =========================================================================================================================== */
/* ================                                  SPI                                                   ================ */
/* =========================================================================================================================== */
/** 
  * @brief Serial Peripheral Interface(SPI) 
  */

typedef struct {
    __IO uint32_t CR0;
    __IO uint32_t CR1;
    __IO uint32_t CR2;
    __IO uint32_t SR;
    __IO uint32_t ICR;
    __IO uint32_t ISR;
    __IO uint32_t DR;
    __IO uint32_t CR3;
    __IO uint32_t REVISION;
    __IO uint32_t FEATURE;
} SPI_TypeDef;


/* =========================================================================================================================== */
/* ================                                  SSI                                                      ================ */
/* =========================================================================================================================== */
/**
  * @brief Synchronous Serial Interface (SSI)
  */
typedef struct
{
    __IO uint32_t   CTRLR0;
    __IO uint32_t   CTRLR1;
    __IO uint32_t   SSIENR;
    __IO uint32_t   MWCR;
    __IO uint32_t   SER;
    __IO uint32_t   BAUDR;
    __IO uint32_t   TXFTLR;
    __IO uint32_t   RXFTLR;
    __IO uint32_t   TXFLR;
    __IO uint32_t   RXFLR;
    __IO uint32_t   SR;
    __IO uint32_t   IMR;
    __IO uint32_t   ISR;
    __IO uint32_t   RISR;
    __IO uint32_t   TXOICR;
    __IO uint32_t   RXOICR;
    __IO uint32_t   RXUICR;
    __IO uint32_t   MSTICR;
    __IO uint32_t   ICR;
    __IO uint32_t   DMACR;
    __IO uint32_t   DMATDLR;
    __IO uint32_t   DMARDLR;
    __IO uint32_t   IDR;
    __IO uint32_t   VERSION_ID;
    __IO uint32_t   DR_BASE;
    uint32_t RESERVED0[35];
    __IO uint32_t   RX_SAMPLE_DLY;
    __IO uint32_t   SPI_CTRLR0;
    __IO uint32_t   TXD_DRIVER_EDGE;
    uint32_t RESERVED1[1];
} SSI_TypeDef;

typedef struct
{
    __IO uint32_t SSCR;   /*!< SSI ss control register, Address offset: 0x0 */
} SSI_Config_TypeDef;

/* =========================================================================================================================== */
/* ================                                  SYSCFG                                                   ================ */
/* =========================================================================================================================== */
/**
  * @brief System Config (SYSCFG)
  */
typedef struct {
    __IO uint32_t PCR;               /*!< SYSCFG power control register, Address offset: 0x190 */
    uint32_t      RESERVED0[3];      /*!< Reserved, 0x194-0x19C */
    __IO uint32_t ECR;               /*!< SYSCFG SRAM ECC control register, Address offset: 0x1A0 */
    __I  uint32_t ERMWEAR;           /*!< SYSCFG SRAM ECC read modify write error address register, Address offset: 0x1A4 */
    __I  uint32_t ERMWECNT;          /*!< SYSCFG SRAM ECC read modify write error count register, Address offset: 0x1A8 */
    __I  uint32_t ERDEAR;            /*!< SYSCFG SRAM ECC read error address register, Address offset: 0x1AC */
    __I  uint32_t ERDECNT;           /*!< SYSCFG SRAM ECC read error count register, Address offset: 0x1B0 */
    uint32_t      RESERVED1[3];      /*!< Reserved, 0x1BC4-0x1BC */
    __I  uint32_t AXICESR0;          /*!< SYSCFG CRC AXI error status register 0, Address offset: 0x1C0 */
    __I  uint32_t AXICESR1;          /*!< SYSCFG CRC AXI error stauts register 1, Address offset: 0x1C4 */
    __I  uint32_t AXICECNT;          /*!< SYSCFG CRC AXI error count register, Address offset: 0x1C8 */
    uint32_t      RESERVED2;         /*!< Reserved, 0x1CC  */
    __I  uint32_t AHBCESR;           /*!< SYSCFG CRC AHB error status register, Address offset: 0x1D0 */
    __I  uint32_t AHBCECNT;          /*!< SYSCFG CRC AHB error count register, Address offset: 0x1D4 */
} SYSCFG_TypeDef;

/* =========================================================================================================================== */
/* ================                                  TIM                                                      ================ */
/* =========================================================================================================================== */
/** 
  * @brief TIMER
  */

typedef struct
{
	__IO uint32_t SR;          /*!< TIM status register,                 Address offset: 0x00 */
	__IO uint32_t PSC;         /*!< TIM prescaler,                       Address offset: 0x04 */	
	__IO uint32_t CR;          /*!< TIM control register,                Address offset: 0x08 */
	__IO uint32_t ARR;         /*!< TIM auto-reload register,            Address offset: 0x0C */
	__IO uint32_t CCR;         /*!< TIM capture/compare register,        Address offset: 0x10 */
	__IO uint32_t CNT;         /*!< TIM counter register(only read reg), Address offset: 0x14 */
	__IO uint32_t FD;          /*!< TIM frequency detection count reg,   Address offset: 0x18 */
	__IO uint32_t DCD;         /*!< TIM duty cycle detection count reg,  Address offset: 0x1C */
} TIM_TypeDef;


/* =========================================================================================================================== */
/* ================                                  UART                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief Universal Asynchronous Receiver Transmitter (UART)
  */

typedef struct
{
    __IO uint32_t DR_OR_DLL;         /*!< when LCR_DLBA=0, this is Data Register(Read/Write);
                                          when LCR_DLBA=1, this is Divisor Register LSB */

    __IO uint32_t IER_OR_DLM;        /*!< when LCR_DLBA=0, this is Interrupt Enable register;
                                          when LCR_DLBA=1, this is Divisor Register MSB */

    __IO uint32_t IIR_OR_FCR;        /*!< when Read, this is Interrupt Identification register(Read);
                                          when Write, this is FIFO control register(Write) */

    __IO uint32_t LCR;               /*!< Line Control register */
    __IO uint32_t MCR;               /*!< Modem Control Register */
    __IO uint32_t LSR;               /*!< Line status register(Read) */  //TODO uint16?
    __IO uint32_t MSR;               /*!< Modem Status register (Read) */
    __IO uint32_t SPR;               /*!< Scratch pad register */
    __IO uint32_t MDR;               /*!< Mode Definition Register */
    __IO uint32_t ACR;               /*!< Auxiliary Control Register */
} UART_TypeDef; 


/* =========================================================================================================================== */
/* ================                                   HSM                                                     ================ */
/* =========================================================================================================================== */
/**
  * @brief Hardware Security Module (HSM)
  */

typedef struct
{
    __IO uint32_t QC;                /*!< HSM Queue Ctrl register, Address offset: 0x00 */
    __IO uint32_t QIER;              /*!< HSM Queue Interrupt Enable register, Address offset: 0x04 */
    __IO uint32_t QISR;              /*!< HSM Queue Interrupt Status register, Address offset: 0x08 */
    __IO uint32_t QLSR;              /*!< HSM Queue LSR register, Address offset: 0x0C */
    uint32_t RESERVED0;              /*!< Reserved, 0x10 */
    __IO uint32_t DC;                /*!< HSM Descriptor Ctrl register, Address offset: 0x14 */
    uint32_t RESERVED1[2];           /*!< Reserved, 0x18-0x1C */
    __IO uint32_t RINGBL;            /*!< HSM Ring Low Base Address register, Address offset: 0x20 */
    __IO uint32_t RINGBH;            /*!< HSM Ring High Base Address register, Address offset: 0x24 */
    __IO uint32_t RINGHD;            /*!< HSM Ring Header Index register, Address offset: 0x28 */
    __IO uint32_t RINGTL;            /*!< HSM Ring Tail Index register, Address offset: 0x2C */
} HSM_TypeDef;

/*@}*/ /* end of group T690_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__GNUC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */
/* Memory base address */
#define SRAM_BASE                           ((uint32_t)0x00800000UL)
#define RTSRAM_BASE                         ((uint32_t)0x08000000UL)
#define CCORE_TCM_BASE                      ((uint32_t)0x01000000UL) /* TODO */
#define XIP0_BASE                           ((uint32_t)0x20000000UL)
#define XIP1_BASE                           ((uint32_t)0x30000000UL)
#define DDR_BASE                            ((uint32_t)0x80000000UL)

/*!< Peripheral base address */
#define AXIPERIPH_BASE                      ((uint32_t)0x02000000UL)
#define AHBPERIPH_BASE                      ((uint32_t)0x04000000UL)
#define APBRPERIPH_BASE                     ((uint32_t)0x06000000UL)
#define APBLPERIPH_BASE                     ((uint32_t)0x08000000UL)
#define APBCPERIPH_BASE                     ((uint32_t)0x09000000UL)

/*!< AXI peripherals */
// #define HSMSYM_BASE                         (AXIPERIPH_BASE + 0x00100000UL)
// #define HSMMB_BASE                          (AXIPERIPH_BASE + 0x00200000UL)
#define HSMSYM0_BASE                        (AXIPERIPH_BASE + 0x00100000UL)
#define HSMSYM1_BASE                        (AXIPERIPH_BASE + 0x00101000UL)
#define HSMSYM2_BASE                        (AXIPERIPH_BASE + 0x00102000UL)
#define HSMPK0_BASE                         (AXIPERIPH_BASE + 0x00300000UL)
#define HSMPK1_BASE                         (AXIPERIPH_BASE + 0x00301000UL)
#define HSMPK2_BASE                         (AXIPERIPH_BASE + 0x00302000UL)
#define HSMCTRL0_BASE                       (AXIPERIPH_BASE + 0x00200000UL)
#define HSMCTRL1_BASE                       (AXIPERIPH_BASE + 0x00201000UL)
#define HSMCTRL2_BASE                       (AXIPERIPH_BASE + 0x00202000UL)
#define GMAC0_BASE                          (AXIPERIPH_BASE + 0x00400000UL)
#define GMAC1_BASE                          (AXIPERIPH_BASE + 0x00500000UL)
#define PCIE_BASE                           (AXIPERIPH_BASE + 0x00800000UL)
#define USB3_BASE                           (AXIPERIPH_BASE + 0x00900000UL)
#define MINTC_BASE                          (AXIPERIPH_BASE + 0x00A00400UL)

/*!< AHB peripherals */
#define FMC0_BASE                           (AHBPERIPH_BASE + 0x00100000UL)
#define FMC1_BASE                           (AHBPERIPH_BASE + 0x00200000UL)
#define USB2_BASE                           (AHBPERIPH_BASE + 0x00400000UL)
#define SDIO0_BASE                          (AHBPERIPH_BASE + 0x00800000UL)
#define SDIO1_BASE                          (AHBPERIPH_BASE + 0x00900000UL)
#define SDIO2_BASE                          (AHBPERIPH_BASE + 0x00A00000UL)
#define SDDC_BASE                           (AHBPERIPH_BASE + 0x00B00000UL)
#define MAC0_BASE                           (AHBPERIPH_BASE + 0x01000000UL)
#define MAC1_BASE                           (AHBPERIPH_BASE + 0x01100000UL)

/*!< APBR peripherals */
#define RCCS_BASE                           (APBRPERIPH_BASE + 0x00000000UL)
#define SYSCFG_BASE                         (APBRPERIPH_BASE + 0x00000190UL)
#define AT_BASE                             (APBRPERIPH_BASE + 0x00001000UL)  
#define USB2CFG_BASE                        (APBRPERIPH_BASE + 0x00001040UL)
#define USB3CFG_BASE                        (APBRPERIPH_BASE + 0x00001050UL)
#define SDCCFG_BASE                         (APBRPERIPH_BASE + 0x00001068UL)
#define FMC1DC_BASE                         (APBRPERIPH_BASE + 0x00001094UL)
#define DDRCCFG_BASE                        (APBRPERIPH_BASE + 0x000010A0UL)
#define FMC0IC_BASE                         (APBRPERIPH_BASE + 0x000010F0UL)
#define SDHC0IO_BASE                        (APBRPERIPH_BASE + 0x000010F4UL)
#define GMAC1DL_BASE                        (APBRPERIPH_BASE + 0x000010F8UL)
#define SSICFG_BASE                         (APBRPERIPH_BASE + 0x00001100UL)
#define GPHY_BASE                           (APBRPERIPH_BASE + 0x00001110UL)
#define GMAC0PHY_BASE                       (APBRPERIPH_BASE + 0x00001118UL)
#define MACWOL_BASE                         (APBRPERIPH_BASE + 0x0000111CUL)
#define GPIOATTR_BASE                       (APBRPERIPH_BASE + 0x00001120UL)
#define PCIEPHY_BASE                        (APBRPERIPH_BASE + 0x00001200UL)
#define SGMII_BASE                          (APBRPERIPH_BASE + 0x00001270UL)
#define DMA0_BASE                           (APBRPERIPH_BASE + 0x00100000UL)
#define DMA0_Stream0_BASE                   (APBRPERIPH_BASE + 0x00100100UL)
#define DMA0_Stream1_BASE                   (APBRPERIPH_BASE + 0x00100120UL)
#define DMA0_Stream2_BASE                   (APBRPERIPH_BASE + 0x00100140UL)
#define DMA0_Stream3_BASE                   (APBRPERIPH_BASE + 0x00100160UL)
#define DMA0_Stream4_BASE                   (APBRPERIPH_BASE + 0x00100180UL)
#define DMA0_Stream5_BASE                   (APBRPERIPH_BASE + 0x001001A0UL)
#define DMA0_Stream6_BASE                   (APBRPERIPH_BASE + 0x001001C0UL)
#define DMA0_Stream7_BASE                   (APBRPERIPH_BASE + 0x001001E0UL)
#define DMA1_BASE                           (APBRPERIPH_BASE + 0x00200000UL)
#define DMA1_Stream0_BASE                   (APBRPERIPH_BASE + 0x00200100UL)
#define DMA1_Stream1_BASE                   (APBRPERIPH_BASE + 0x00200120UL)
#define DMA1_Stream2_BASE                   (APBRPERIPH_BASE + 0x00200140UL)
#define DMA1_Stream3_BASE                   (APBRPERIPH_BASE + 0x00200160UL)
#define DMA1_Stream4_BASE                   (APBRPERIPH_BASE + 0x00200180UL)
#define DMA1_Stream5_BASE                   (APBRPERIPH_BASE + 0x002001A0UL)
#define DMA1_Stream6_BASE                   (APBRPERIPH_BASE + 0x002001C0UL)
#define DMA1_Stream7_BASE                   (APBRPERIPH_BASE + 0x002001E0UL)
#define WDG0_BASE                           (APBRPERIPH_BASE + 0x00300000UL)
#define WDG1_BASE                           (APBRPERIPH_BASE + 0x00400000UL)
#define TIMO_BASE                           (APBRPERIPH_BASE + 0x00300600UL)
#define TIM1_BASE                           (APBRPERIPH_BASE + 0x00300620UL)
#define TIM2_BASE                           (APBRPERIPH_BASE + 0x00300640UL)
#define TIM3_BASE                           (APBRPERIPH_BASE + 0x00300660UL)
#define TIM4_BASE                           (APBRPERIPH_BASE + 0x00300680UL)
#define TIM5_BASE                           (APBRPERIPH_BASE + 0x003006A0UL)
#define TIM6_BASE                           (APBRPERIPH_BASE + 0x003006C0UL)
#define TIM7_BASE                           (APBRPERIPH_BASE + 0x003006E0UL)
#define TIM8_BASE                           (APBRPERIPH_BASE + 0x00400600UL)
#define TIM9_BASE                           (APBRPERIPH_BASE + 0x00400620UL)
#define TIM10_BASE                          (APBRPERIPH_BASE + 0x00400640UL)
#define TIM11_BASE                          (APBRPERIPH_BASE + 0x00400660UL)
#define TIM12_BASE                          (APBRPERIPH_BASE + 0x00400680UL)
#define TIM13_BASE                          (APBRPERIPH_BASE + 0x004006A0UL)
#define TIM14_BASE                          (APBRPERIPH_BASE + 0x004006C0UL)
#define TIM15_BASE                          (APBRPERIPH_BASE + 0x004006E0UL)
#define GPIOA_BASE                          (APBRPERIPH_BASE + 0x00500000UL)
#define GPIOB_BASE                          (APBRPERIPH_BASE + 0x00520000UL)
#define GPIOC_BASE                          (APBRPERIPH_BASE + 0x00540000UL)
#define USB3PHY_BASE                        (APBRPERIPH_BASE + 0x00600000UL)
#define I2C1_BASE                           (APBRPERIPH_BASE + 0x00700000UL)
#define I2C2_BASE                           (APBRPERIPH_BASE + 0x00800000UL)
#define LTDC_BASE                           (APBRPERIPH_BASE + 0x00900000UL)
#define SSI0_BASE                           (APBRPERIPH_BASE + 0x00A00000UL)
#define SSI1_BASE                           (APBRPERIPH_BASE + 0x00B00000UL)
#define SPI0_BASE                           (APBRPERIPH_BASE + 0x00C00000UL)
#define SPI1_BASE                           (APBRPERIPH_BASE + 0x00D00000UL)
#define CANA1_BASE                          (APBRPERIPH_BASE + 0x00E00000UL)
#define CANA2_BASE                          (APBRPERIPH_BASE + 0x00F00000UL)
#define CANA3_BASE                          (APBRPERIPH_BASE + 0x01000000UL)
#define CANB0_BASE                          (APBRPERIPH_BASE + 0x01100000UL)
#define CANB1_BASE                          (APBRPERIPH_BASE + 0x01200000UL)
#define CANB2_BASE                          (APBRPERIPH_BASE + 0x01300000UL)
#define CANB3_BASE                          (APBRPERIPH_BASE + 0x01400000UL)
#define UART1_BASE                          (APBRPERIPH_BASE + 0x01500000UL)
#define UART2_BASE                          (APBRPERIPH_BASE + 0x01600000UL)
#define UART3_BASE                          (APBRPERIPH_BASE + 0x01700000UL)
#define UART4_BASE                          (APBRPERIPH_BASE + 0x01800000UL)
#define UART5_BASE                          (APBRPERIPH_BASE + 0x01900000UL)
#define UART6_BASE                          (APBRPERIPH_BASE + 0x01A00000UL)
#define UART7_BASE                          (APBRPERIPH_BASE + 0x01B00000UL)
#define SCI0_BASE                           (APBRPERIPH_BASE + 0x01C00000UL)
#define SCI1_BASE                           (APBRPERIPH_BASE + 0x01D00000UL)
#define ADC0_BASE                           (APBRPERIPH_BASE + 0x01E00000UL)
#define ADC1_BASE                           (APBRPERIPH_BASE + 0x01E00060UL)
#define ADCT_BASE                           (APBRPERIPH_BASE + 0x01E00100UL)
#define DAC_BASE                            (APBRPERIPH_BASE + 0x01F00000UL)

/*!< APBL peripherals */
#define RCCL_BASE                           (APBLPERIPH_BASE + 0x00100000UL)
#define LPC_BASE                            (APBLPERIPH_BASE + 0x00200000UL)
#define RTC_BASE                            (APBLPERIPH_BASE + 0x00300000UL)
#define GPIOD_BASE                          (APBLPERIPH_BASE + 0x00400000UL)
#define I2C0_BASE                           (APBLPERIPH_BASE + 0x00500000UL)
#define CANA0_BASE                          (APBLPERIPH_BASE + 0x00600000UL)
#define UART0_BASE                          (APBLPERIPH_BASE + 0x00700000UL)

/*!< APBC peripherals */
#define DDRC_BASE                           (APBCPERIPH_BASE + 0x00400000UL)
#define H2XL_BASE                           (APBCPERIPH_BASE + 0x00A00000UL)
#define H2XH_BASE                           (APBCPERIPH_BASE + 0x00B00000UL)
       

//TODO
#define RTRAM_LPCBASE                       ((uint32_t)0x00000000)
#define LPCSCU_LPCBASE                      ((uint32_t)0x00002000)
#define PMU_LPCBASE                         ((uint32_t)0x00002400)
#define RTC_LPCBASE                         ((uint32_t)0x00002800)
#define GPIOD_LPCBASE                       ((uint32_t)0x00002C00)
#define IIC0_LPCBASE                        ((uint32_t)0x00003000)
#define CAN0_LPCBASE                        ((uint32_t)0x00008000)
#define UART0_LPCBASE                       ((uint32_t)0x00010000)


/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/* TODO: add here your device peripherals pointer definitions
         following is an example for uart0 */
/** @addtogroup Device_Peripheral_declaration
  * @{
  */
#define ADC0                                  ((ADC_TypeDef *) ADC0_BASE)
#define ADC1                                  ((ADC_TypeDef *) ADC1_BASE)
#define ADCT                                  ((ADC_TDC_TypeDef *) ADCT_BASE)
#define CANA0                                 ((CANA_TypeDef *)CANA0_BASE)
#define CANA1                                 ((CANA_TypeDef *)CANA1_BASE)
#define CANA2                                 ((CANA_TypeDef *)CANA2_BASE)
#define CANA3                                 ((CANA_TypeDef *)CANA3_BASE)
#define CANB0                                 ((CANB_TypeDef *)CANB0_BASE)
#define CANB1                                 ((CANB_TypeDef *)CANB1_BASE)
#define CANB2                                 ((CANB_TypeDef *)CANB2_BASE)
#define CANB3                                 ((CANB_TypeDef *)CANB3_BASE)
#define DAC                                   ((DAC_TypeDef *) DAC_BASE)
#define DDRC                                  ((DDRC_TypeDef *) DDRC_BASE)
#define DDRC_CFG                              ((DDRC_Config_TypeDef *) DDRCCFG_BASE)
#define DMA0                                  ((DMA_TypeDef *) DMA0_BASE)
#define DMA0_Stream0                          ((DMA_Stream_TypeDef *) DMA0_Stream0_BASE)
#define DMA0_Stream1                          ((DMA_Stream_TypeDef *) DMA0_Stream1_BASE)
#define DMA0_Stream2                          ((DMA_Stream_TypeDef *) DMA0_Stream2_BASE)
#define DMA0_Stream3                          ((DMA_Stream_TypeDef *) DMA0_Stream3_BASE)
#define DMA0_Stream4                          ((DMA_Stream_TypeDef *) DMA0_Stream4_BASE)
#define DMA0_Stream5                          ((DMA_Stream_TypeDef *) DMA0_Stream5_BASE)
#define DMA0_Stream6                          ((DMA_Stream_TypeDef *) DMA0_Stream6_BASE)
#define DMA0_Stream7                          ((DMA_Stream_TypeDef *) DMA0_Stream7_BASE)
#define DMA1                                  ((DMA_TypeDef *) DMA1_BASE)
#define DMA1_Stream0                          ((DMA_Stream_TypeDef *) DMA1_Stream0_BASE)
#define DMA1_Stream1                          ((DMA_Stream_TypeDef *) DMA1_Stream1_BASE)
#define DMA1_Stream2                          ((DMA_Stream_TypeDef *) DMA1_Stream2_BASE)
#define DMA1_Stream3                          ((DMA_Stream_TypeDef *) DMA1_Stream3_BASE)
#define DMA1_Stream4                          ((DMA_Stream_TypeDef *) DMA1_Stream4_BASE)
#define DMA1_Stream5                          ((DMA_Stream_TypeDef *) DMA1_Stream5_BASE)
#define DMA1_Stream6                          ((DMA_Stream_TypeDef *) DMA1_Stream6_BASE)
#define DMA1_Stream7                          ((DMA_Stream_TypeDef *) DMA1_Stream7_BASE)
#define FMC0                                  ((FMC_TypeDef *) FMC0_BASE)
#define FMC0_IC                               ((FMC0_IOControl_TypeDef *) FMC0IC_BASE) 
#define FMC1                                  ((FMC_TypeDef *) FMC1_BASE)
#define FMC1_DC                               ((FMC1_DllControl_TypeDef *) FMC1DC_BASE)
#define GPIOA                                 ((GPIO_TypeDef *) GPIOA_BASE)
#define GPIOB                                 ((GPIO_TypeDef *) GPIOB_BASE)
#define GPIOC                                 ((GPIO_TypeDef *) GPIOC_BASE)
#define GPIO_ATTRIBUTE                        ((GPIO_Attribute_TypeDef *) GPIOATTR_BASE)
#define HSMSYM0                               ((HSM_TypeDef *) HSMSYM0_BASE)
#define HSMSYM1                               ((HSM_TypeDef *) HSMSYM1_BASE)
#define HSMSYM2                               ((HSM_TypeDef *) HSMSYM2_BASE)
#define HSMPK0                                ((HSM_TypeDef *) HSMPK0_BASE)
#define HSMPK1                                ((HSM_TypeDef *) HSMPK1_BASE)
#define HSMPK2                                ((HSM_TypeDef *) HSMPK2_BASE)
#define HSMCTRL0                              ((HSM_TypeDef *) HSMCTRL0_BASE)
#define HSMCTRL1                              ((HSM_TypeDef *) HSMCTRL1_BASE)
#define HSMCTRL2                              ((HSM_TypeDef *) HSMCTRL2_BASE)
#define I2C0                                  ((I2C_TypeDef *) I2C0_BASE)
#define I2C1                                  ((I2C_TypeDef *) I2C1_BASE)
#define I2C2                                  ((I2C_TypeDef *) I2C2_BASE)
#define IMX                                   ((IMX_TypeDef *) IMX_BASE)
#define LTDC                                  ((LTDC_TypeDef *) LTDC_BASE)
#define MINTC                                 ((MINTC_TypeDef *) MINTC_BASE)
#define RCCS                                  ((RCCS_TypeDef *) RCCS_BASE)
#define SCI0                                  ((SCI_TypeDef *) SCI0_BASE)
#define SCI1                                  ((SCI_TypeDef *) SCI1_BASE)
#define SDDC                                  ((SDDC_TypeDef *) SDDC_BASE)
#define SDIO0                                 ((SDIO_TypeDef *) SDIO0_BASE)
#define SDIO1                                 ((SDIO_TypeDef *) SDIO1_BASE)
#define SDIO2                                 ((SDIO_TypeDef *) SDIO2_BASE)
#define SDCCFG                                ((SDC_Config_TypeDef *) SDCCFG_BASE)
#define SPI0                                  ((SPI_TypeDef *) SPI0_BASE) 
#define SPI1                                  ((SPI_TypeDef *) SPI1_BASE)
#define SSI0                                  ((SSI_TypeDef *) SSI0_BASE)
#define SSI1                                  ((SSI_TypeDef *) SSI1_BASE)
#define SSICFG                                ((SSI_Config_TypeDef *) SSICFG_BASE)
#define SYSCFG                                ((SYSCFG_TypeDef *) SYSCFG_BASE)
#define TIM0                                  ((TIM_TypeDef *) TIMO_BASE)
#define TIM1                                  ((TIM_TypeDef *) TIM1_BASE)
#define TIM2                                  ((TIM_TypeDef *) TIM2_BASE)
#define TIM3                                  ((TIM_TypeDef *) TIM3_BASE)
#define TIM4                                  ((TIM_TypeDef *) TIM4_BASE)
#define TIM5                                  ((TIM_TypeDef *) TIM5_BASE)
#define TIM6                                  ((TIM_TypeDef *) TIM6_BASE)
#define TIM7                                  ((TIM_TypeDef *) TIM7_BASE)
#define TIM8                                  ((TIM_TypeDef *) TIM8_BASE)
#define TIM9                                  ((TIM_TypeDef *) TIM9_BASE)
#define TIM10                                 ((TIM_TypeDef *) TIM10_BASE)
#define TIM11                                 ((TIM_TypeDef *) TIM11_BASE)
#define TIM12                                 ((TIM_TypeDef *) TIM12_BASE)
#define TIM13                                 ((TIM_TypeDef *) TIM13_BASE)
#define TIM14                                 ((TIM_TypeDef *) TIM14_BASE)
#define TIM15                                 ((TIM_TypeDef *) TIM15_BASE)
#define UART0                                 ((UART_TypeDef *) UART0_BASE)
#define UART1                                 ((UART_TypeDef *) UART1_BASE)
#define UART2                                 ((UART_TypeDef *) UART2_BASE)
#define UART3                                 ((UART_TypeDef *) UART3_BASE)
#define UART4                                 ((UART_TypeDef *) UART4_BASE)
#define UART5                                 ((UART_TypeDef *) UART5_BASE)
#define UART6                                 ((UART_TypeDef *) UART6_BASE)
#define UART7                                 ((UART_TypeDef *) UART7_BASE)
#define RTC                                   ((RTC_TypeDef *) RTC_BASE)
/** @} */ /* End of group Device_Peripheral_declaration */

  /** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */
    
/* =========================================================================================================================== */
/* ================                            Peripheral Registers Bits Definition                          ================= */
/* =========================================================================================================================== */

/* =========================================================================================================================== */
/* ================                            Analog to Digital Converter                                   ================= */
/* =========================================================================================================================== */

/* ====================  Bit definition for ADC_SR register  ====================== */
#define  ADC_SR_EOC                          ((uint16_t)0x0001)            /*!<End of conversion                  */
#define  ADC_SR_JEOC                         ((uint16_t)0x0002)            /*!<Injected channel end of conversion */
#define  ADC_SR_AWDLALM                      ((uint16_t)0x0004)            /*!<Analog watchdog low threshold alarm flag  */
#define  ADC_SR_AWDHALM                      ((uint16_t)0x0008)            /*!<Analog watchdog high threshold alarm flag */
#define  ADC_SR_OVR                          ((uint16_t)0x0010)            /*!<Overrun flag                       */
#define  ADC_SR_EMPTY                        ((uint16_t)0x0020)            /*!<Fifo Empty flag                    */
#define  ADC_SR_CNT                          ((uint16_t)0x03C0)            /*!<Fifo data count                    */
#define  ADC_SR_CNT_0                        ((uint16_t)0x0040)            /*!<Bit 0 */
#define  ADC_SR_CNT_1                        ((uint16_t)0x0080)            /*!<Bit 1 */
#define  ADC_SR_CNT_2                        ((uint16_t)0x0100)            /*!<Bit 2 */
#define  ADC_SR_CNT_3                        ((uint16_t)0x0200)            /*!<Bit 3 */
#define  ADC_SR_JOVR                         ((uint16_t)0x0400)            /*!<Injected channel Overrun flag      */
#define  ADC_SR_JEMPTY                       ((uint16_t)0x0800)            /*!<Injected channel Fifo Empty flag   */
#define  ADC_SR_JCNT                         ((uint16_t)0x7000)            /*!<Injected channel Fifo data count   */
#define  ADC_SR_JCNT_0                       ((uint16_t)0x1000)            /*!<Bit 0 */
#define  ADC_SR_JCNT_1                       ((uint16_t)0x2000)            /*!<Bit 1 */
#define  ADC_SR_JCNT_2                       ((uint16_t)0x4000)            /*!<Bit 2 */

/* ====================  Bit definition for ADC_CR1 register  ====================== */
#define  ADC_CR_ADOFF                        ((uint32_t)0x00000001)        /*!<A/D Converter ON / OFF             */
#define  ADC_CR_CONT                         ((uint32_t)0x00000002)        /*!<Continuous Conversion              */
#define  ADC_CR_DMA                          ((uint32_t)0x00000004)        /*!<Direct Memory access mode          */
#define  ADC_CR_ALIGN                        ((uint32_t)0x00000008)        /*!<Data Alignment                     */
#define  ADC_CR_JEXTSEL                      ((uint32_t)0x000000F0)        /*!<JEXTSEL[3:0] bits (External event select for injected group) */
#define  ADC_CR_JEXTSEL_0                    ((uint32_t)0x00000010)        /*!<Bit 0 */
#define  ADC_CR_JEXTSEL_1                    ((uint32_t)0x00000020)        /*!<Bit 1 */
#define  ADC_CR_JEXTSEL_2                    ((uint32_t)0x00000040)        /*!<Bit 2 */
#define  ADC_CR_JEXTSEL_3                    ((uint32_t)0x00000080)        /*!<Bit 3 */
#define  ADC_CR_JEXTEN                       ((uint32_t)0x00000300)        /*!<JEXTEN[1:0] bits (External Trigger Conversion mode for injected channelsp) */
#define  ADC_CR_JEXTEN_0                     ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  ADC_CR_JEXTEN_1                     ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  ADC_CR_JSWSTART                     ((uint32_t)0x00000400)        /*!<Start Conversion of injected channels */
#define  ADC_CR_EXTSEL                       ((uint32_t)0x0000F000)        /*!<EXTSEL[3:0] bits (External Event Select for regular group) */
#define  ADC_CR_EXTSEL_0                     ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_CR_EXTSEL_1                     ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_CR_EXTSEL_2                     ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_CR_EXTSEL_3                     ((uint32_t)0x00008000)        /*!<Bit 3 */
#define  ADC_CR_EXTEN                        ((uint32_t)0x00030000)        /*!<EXTEN[1:0] bits (External Trigger Conversion mode for regular channelsp) */
#define  ADC_CR_EXTEN_0                      ((uint32_t)0x00010000)        /*!<Bit 0 */
#define  ADC_CR_EXTEN_1                      ((uint32_t)0x00020000)        /*!<Bit 1 */
#define  ADC_CR_SWSTART                      ((uint32_t)0x00040000)        /*!<Start Conversion of regular channels */
#define  ADC_CR_EOCIE                        ((uint32_t)0x01000000)        /*!<Interrupt enable for EOC             */
#define  ADC_CR_AWDIE                        ((uint32_t)0x02000000)        /*!<AAnalog Watchdog interrupt enable    */
#define  ADC_CR_JEOCIE                       ((uint32_t)0x04000000)        /*!<Interrupt enable for injected channels */
#define  ADC_CR_OVRIE                        ((uint32_t)0x08000000)        /*!<overrun interrupt enable             */
#define  ADC_CR_SCAN                         ((uint32_t)0x10000000)        /*!<Scan mode                            */
#define  ADC_CR_SWRST                        ((uint32_t)0x20000000)        /*!<Software reset                       */

/* ====================  Bit definition for ADC_SMP register  ====================== */
#define  ADC_SMP_SMP0                        ((uint32_t)0x00000007)        /*!<SMP0[2:0] bits (Channel 0 Sample time selection) */
#define  ADC_SMP_SMP0_0                      ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SMP_SMP0_1                      ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SMP_SMP0_2                      ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SMP_SMP1                        ((uint32_t)0x00000038)        /*!<SMP1[2:0] bits (Channel 1 Sample time selection) */
#define  ADC_SMP_SMP1_0                      ((uint32_t)0x00000008)        /*!<Bit 0 */
#define  ADC_SMP_SMP1_1                      ((uint32_t)0x00000010)        /*!<Bit 1 */
#define  ADC_SMP_SMP1_2                      ((uint32_t)0x00000020)        /*!<Bit 2 */
#define  ADC_SMP_SMP2                        ((uint32_t)0x000001C0)        /*!<SMP2[2:0] bits (Channel 2 Sample time selection) */
#define  ADC_SMP_SMP2_0                      ((uint32_t)0x00000040)        /*!<Bit 0 */
#define  ADC_SMP_SMP2_1                      ((uint32_t)0x00000080)        /*!<Bit 1 */
#define  ADC_SMP_SMP2_2                      ((uint32_t)0x00000100)        /*!<Bit 2 */
#define  ADC_SMP_SMP3                        ((uint32_t)0x00000E00)        /*!<SMP3[2:0] bits (Channel 3 Sample time selection) */
#define  ADC_SMP_SMP3_0                      ((uint32_t)0x00000200)        /*!<Bit 0 */
#define  ADC_SMP_SMP3_1                      ((uint32_t)0x00000400)        /*!<Bit 1 */
#define  ADC_SMP_SMP3_2                      ((uint32_t)0x00000800)        /*!<Bit 2 */
#define  ADC_SMP_SMP4                        ((uint32_t)0x00007000)        /*!<SMP4[2:0] bits (Channel 4 Sample time selection) */
#define  ADC_SMP_SMP4_0                      ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_SMP_SMP4_1                      ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_SMP_SMP4_2                      ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_SMP_SMP5                        ((uint32_t)0x00038000)        /*!<SMP5[2:0] bits (Channel 5 Sample time selection) */
#define  ADC_SMP_SMP5_0                      ((uint32_t)0x00008000)        /*!<Bit 0 */
#define  ADC_SMP_SMP5_1                      ((uint32_t)0x00010000)        /*!<Bit 1 */
#define  ADC_SMP_SMP5_2                      ((uint32_t)0x00020000)        /*!<Bit 2 */
#define  ADC_SMP_SMP6                        ((uint32_t)0x001C0000)        /*!<SMP6[2:0] bits (Channel 6 Sample time selection) */
#define  ADC_SMP_SMP6_0                      ((uint32_t)0x00040000)        /*!<Bit 0 */
#define  ADC_SMP_SMP6_1                      ((uint32_t)0x00080000)        /*!<Bit 1 */
#define  ADC_SMP_SMP6_2                      ((uint32_t)0x00100000)        /*!<Bit 2 */
#define  ADC_SMP_SMP7                        ((uint32_t)0x00E00000)        /*!<SMP7[2:0] bits (Channel 7 Sample time selection) */
#define  ADC_SMP_SMP7_0                      ((uint32_t)0x00200000)        /*!<Bit 0 */
#define  ADC_SMP_SMP7_1                      ((uint32_t)0x00400000)        /*!<Bit 1 */
#define  ADC_SMP_SMP7_2                      ((uint32_t)0x00800000)        /*!<Bit 2 */
#define  ADC_SMP_SMP8                        ((uint32_t)0x07000000)        /*!<SMP8[2:0] bits (Channel 8 Sample time selection) */
#define  ADC_SMP_SMP8_0                      ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_SMP_SMP8_1                      ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_SMP_SMP8_2                      ((uint32_t)0x04000000)        /*!<Bit 2 */
#define  ADC_SMP_SMP9                        ((uint32_t)0x38000000)        /*!<SMP9[2:0] bits (Channel 9 Sample time selection) */
#define  ADC_SMP_SMP9_0                      ((uint32_t)0x08000000)        /*!<Bit 0 */
#define  ADC_SMP_SMP9_1                      ((uint32_t)0x10000000)        /*!<Bit 1 */
#define  ADC_SMP_SMP9_2                      ((uint32_t)0x20000000)        /*!<Bit 2 */

/* ====================  Bit definition for ADC_AWD register  ====================== */
#define  ADC_AWD_AWDLT                       ((uint32_t)0x00000FFF)        /*!<Analog watchdog low threshold */
#define  ADC_AWD_AWDHT                       ((uint32_t)0x00FFF000)        /*!<Analog watchdog high threshold */
#define  ADC_AWD_AWDCH                       ((uint32_t)0x0F000000)        /*!< AWDCH[4:0] bits (Analog watchdog channel select bits) */
#define  ADC_AWD_AWDCH_0                     ((uint32_t)0x01000000)        /*!< Bit 0 */
#define  ADC_AWD_AWDCH_1                     ((uint32_t)0x02000000)        /*!< Bit 1 */
#define  ADC_AWD_AWDCH_2                     ((uint32_t)0x04000000)        /*!< Bit 2 */
#define  ADC_AWD_AWDCH_3                     ((uint32_t)0x08000000)        /*!< Bit 3 */
#define  ADC_AWD_AWDEN                       ((uint32_t)0x10000000)        /*!< Analog watchdog enable on regular channels */
#define  ADC_AWD_JAWDEN                      ((uint32_t)0x20000000)        /*!< Analog watchdog enable on injected channels */
#define  ADC_AWD_AWDGRP                      ((uint32_t)0x40000000)        /*!< Enable the watchdog on a single channel or group channels in scan mode */

/* ====================  Bit definition for ADC_SQR1 register  ====================== */
#define  ADC_SQR1_SQ1                        ((uint32_t)0x0000000F)        /*!<SQ1[3:0] bits (1st conversion in regular sequence) */
#define  ADC_SQR1_SQ1_0                      ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SQR1_SQ1_1                      ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SQR1_SQ1_2                      ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SQR1_SQ1_3                      ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_SQR1_SQ2                        ((uint32_t)0x000000F0)        /*!<SQ2[3:0] bits (2nd conversion in regular sequence) */
#define  ADC_SQR1_SQ2_0                      ((uint32_t)0x00000010)        /*!<Bit 0 */
#define  ADC_SQR1_SQ2_1                      ((uint32_t)0x00000020)        /*!<Bit 1 */
#define  ADC_SQR1_SQ2_2                      ((uint32_t)0x00000040)        /*!<Bit 2 */
#define  ADC_SQR1_SQ2_3                      ((uint32_t)0x00000080)        /*!<Bit 3 */
#define  ADC_SQR1_SQ3                        ((uint32_t)0x00000F00)        /*!<SQ3[3:0] bits (3rd conversion in regular sequence) */
#define  ADC_SQR1_SQ3_0                      ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  ADC_SQR1_SQ3_1                      ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  ADC_SQR1_SQ3_2                      ((uint32_t)0x00000400)        /*!<Bit 2 */
#define  ADC_SQR1_SQ3_3                      ((uint32_t)0x00000800)        /*!<Bit 3 */
#define  ADC_SQR1_SQ4                        ((uint32_t)0x0000F000)        /*!<SQ4[3:0] bits (4th conversion in regular sequence) */
#define  ADC_SQR1_SQ4_0                      ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ4_1                      ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ4_2                      ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ4_3                      ((uint32_t)0x00008000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ5                        ((uint32_t)0x000F000)        /*!<SQ5[3:0] bits (5th conversion in regular sequence) */
#define  ADC_SQR1_SQ5_0                      ((uint32_t)0x00010000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ5_1                      ((uint32_t)0x00020000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ5_2                      ((uint32_t)0x00040000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ5_3                      ((uint32_t)0x00080000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ6                        ((uint32_t)0x00F00000)        /*!<SQ6[3:0] bits (6th conversion in regular sequence) */
#define  ADC_SQR1_SQ6_0                      ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ6_1                      ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ6_2                      ((uint32_t)0x00400000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ6_3                      ((uint32_t)0x00800000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ7                        ((uint32_t)0x0F000000)        /*!<SQ7[3:0] bits (7th conversion in regular sequence) */
#define  ADC_SQR1_SQ7_0                      ((uint32_t)0x01000000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ7_1                      ((uint32_t)0x02000000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ7_2                      ((uint32_t)0x04000000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ7_3                      ((uint32_t)0x08000000)        /*!<Bit 3 */
#define  ADC_SQR1_SQ8                        ((uint32_t)0xF0000000)        /*!<SQ8[3:0] bits (8th conversion in regular sequence) */
#define  ADC_SQR1_SQ8_0                      ((uint32_t)0x10000000)        /*!<Bit 0 */
#define  ADC_SQR1_SQ8_1                      ((uint32_t)0x20000000)        /*!<Bit 1 */
#define  ADC_SQR1_SQ8_2                      ((uint32_t)0x40000000)        /*!<Bit 2 */
#define  ADC_SQR1_SQ8_3                      ((uint32_t)0x80000000)        /*!<Bit 3 */

/* ====================  Bit definition for ADC_SQR2 register  ====================== */
#define  ADC_SQR2_SQ9                        ((uint32_t)0x0000000F)        /*!<SQ9[3:0] bits (9th conversion in regular sequence) */
#define  ADC_SQR2_SQ9_0                      ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_SQR2_SQ9_1                      ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_SQR2_SQ9_2                      ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_SQR2_SQ9_3                      ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_SQR2_SQ10                       ((uint32_t)0x000000F0)        /*!<SQ10[3:0] bits (10th conversion in regular sequence) */
#define  ADC_SQR2_SQ10_0                     ((uint32_t)0x00000010)        /*!<Bit 0 */
#define  ADC_SQR2_SQ10_1                     ((uint32_t)0x00000020)        /*!<Bit 1 */
#define  ADC_SQR2_SQ10_2                     ((uint32_t)0x00000040)        /*!<Bit 2 */
#define  ADC_SQR2_SQ10_3                     ((uint32_t)0x00000080)        /*!<Bit 3 */
#define  ADC_SQR2_L                          ((uint32_t)0x00000F00)        /*!<L[3:0] bits (Regular channel sequence length) */
#define  ADC_SQR2_L_0                        ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  ADC_SQR2_L_1                        ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  ADC_SQR2_L_2                        ((uint32_t)0x00000400)        /*!<Bit 2 */
#define  ADC_SQR2_L_3                        ((uint32_t)0x00000800)        /*!<Bit 3 */

/* ====================  Bit definition for ADC_JSQR register  ====================== */
#define  ADC_JSQR_JSQ1                       ((uint32_t)0x0000000F)        /*!<JSQ1[4:0] bits (1st conversion in injected sequence) */  
#define  ADC_JSQR_JSQ1_0                     ((uint32_t)0x00000001)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ1_1                     ((uint32_t)0x00000002)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ1_2                     ((uint32_t)0x00000004)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ1_3                     ((uint32_t)0x00000008)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ2                       ((uint32_t)0x000000F0)        /*!<JSQ2[4:0] bits (2nd conversion in injected sequence) */
#define  ADC_JSQR_JSQ2_0                     ((uint32_t)0x00000010)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ2_1                     ((uint32_t)0x00000020)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ2_2                     ((uint32_t)0x00000040)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ2_3                     ((uint32_t)0x00000080)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ3                       ((uint32_t)0x00000F00)        /*!<JSQ3[4:0] bits (3rd conversion in injected sequence) */
#define  ADC_JSQR_JSQ3_0                     ((uint32_t)0x00000100)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ3_1                     ((uint32_t)0x00000200)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ3_2                     ((uint32_t)0x00000400)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ3_3                     ((uint32_t)0x00000800)        /*!<Bit 3 */
#define  ADC_JSQR_JSQ4                       ((uint32_t)0x0000F000)        /*!<JSQ4[4:0] bits (4th conversion in injected sequence) */
#define  ADC_JSQR_JSQ4_0                     ((uint32_t)0x00001000)        /*!<Bit 0 */
#define  ADC_JSQR_JSQ4_1                     ((uint32_t)0x00002000)        /*!<Bit 1 */
#define  ADC_JSQR_JSQ4_2                     ((uint32_t)0x00004000)        /*!<Bit 2 */
#define  ADC_JSQR_JSQ4_3                     ((uint32_t)0x00008000)        /*!<Bit 3 */
#define  ADC_JSQR_JL                         ((uint32_t)0x00030000)        /*!<JL[1:0] bits (Injected Sequence length) */
#define  ADC_JSQR_JL_0                       ((uint32_t)0x00010000)        /*!<Bit 0 */
#define  ADC_JSQR_JL_1                       ((uint32_t)0x00020000)        /*!<Bit 1 */

/* ====================  Bit definition for ADC_DR register  ====================== */
#define  ADC_DR_DATA                         ((uint16_t)0xFFFF)            /*!<Regular data */

/* ====================  Bit definition for ADC_JDR register  ====================== */
#define  ADC_JDR_JDATA                       ((uint16_t)0xFFFF)            /*!<Injected data */

/* ====================  Bit definition for ADC_Calibration register  ====================== */
#define  ADC_CALIB_XBVOS                     ((uint16_t)0x01FC)            /*!<XBVOS signals */
#define  ADC_CALIB_FLAG                      ((uint16_t)0x0002)            /*!<Calibration signals */
#define  ADC_CALIB_EN                        ((uint16_t)0x0001)            /*!<Calibration enable */

/* ====================  Bit definition for ADC_OFR1 register  ====================== */
#define  ADC_OFR1_OFFSET1                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 1 */

/* ====================  Bit definition for ADC_OFR2 register  ====================== */
#define  ADC_OFR2_OFFSET2                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 2 */
 
/* ====================  Bit definition for ADC_OFR3 register  ====================== */
#define  ADC_OFR3_OFFSET3                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 3 */

/* ====================  Bit definition for ADC_OFR4 register  ====================== */
#define  ADC_OFR4_OFFSET4                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 4 */

/* ====================  Bit definition for ADC_OFR5 register  ====================== */
#define  ADC_OFR5_OFFSET5                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 5 */

/* ====================  Bit definition for ADC_OFR6 register  ====================== */
#define  ADC_OFR6_OFFSET6                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 6 */
 
/* ====================  Bit definition for ADC_OFR7 register  ====================== */
#define  ADC_OFR7_OFFSET7                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 7 */

/* ====================  Bit definition for ADC_OFR8 register  ====================== */
#define  ADC_OFR8_OFFSET8                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 8 */

/* ====================  Bit definition for ADC_OFR9 register  ====================== */
#define  ADC_OFR9_OFFSET9                    ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 9 */

/* ====================  Bit definition for ADC_OFR10 register  ====================== */
#define  ADC_OFR10_OFFSET10                  ((uint16_t)0x0FFF)            /*!<Data offset for regular and injected channel 10 */

/* ====================  Bit definition for ADC_TDC register  ====================== */
#define  ADC_TDC_RST                         ((uint32_t)0x00000001)         /*!<TDC reset */
#define  ADC_TDC_EN                          ((uint32_t)0x00000002)         /*!<TDC enable */
#define  ADC_TDC_CHOP                        ((uint32_t)0x00000004)         /*!<TDC OP-AMP chip control */
#define  ADC_TDC_CLKEN                       ((uint32_t)0x00000008)         /*!<TDC clk enable */
#define  ADC_TDC_SMPDATA                     ((uint32_t)0x02FF0000)         /*!<TDC sample data */
#define  ADC_TDC_SMPDATA_FLAG                ((uint32_t)0x04000000)         /*!<TDC sample data valid flag */


/* =========================================================================================================================== */
/* ================                            Controller Area Network  A                                    ================= */
/* =========================================================================================================================== */
/* ====================  Bit definition for CANA_SRR register  ====================== */
#define CANA_SRR_SRST                       ((uint32_t)0x00000001) /* Reset Value */
#define CANA_SRR_CEN                        ((uint32_t)0x00000002) /* CAN ENABLE */

/* ====================  Bit definition for CANA_SR register  ====================== */
#define CANA_SR_CONFIG                      ((uint32_t)0x00000001) /* Configuration mode */
#define CANA_SR_SLEEP                       ((uint32_t)0x00000004) /* Sleep mode */

/* ====================  Bit definition for CANA_ESR register  ====================== */
#define CANA_ESR_REC                        ((uint32_t)0x0000FF00) /* Receive Error Count */
#define CANA_ESR_TEC                        ((uint32_t)0x000000FF) /* Transmit Error Count */

/* ====================  Bit definition for CANA_RB-ID register  ====================== */
#define CANA_IDR_ID1                        ((uint32_t)0xFFE00000) /* Standard msg identifier */
#define CANA_IDR_SRR                        ((uint32_t)0x00100000) /* Substitute remote TXreq */
#define CANA_IDR_IDE                        ((uint32_t)0x00080000) /* Identifier extension */
#define CANA_IDR_ID2                        ((uint32_t)0x0007FFFE) /* Extended message ident */
#define CANA_IDR_RTR                        ((uint32_t)0x00000001) /* Remote TX request */

/* ====================  Bit definition for CANA_DLC register  ====================== */
#define CANA_DLCR_DLC                       ((uint32_t)0xF0000000) /* Data length code */
#define CANA_DLCR_EDL                       ((uint32_t)0x08000000) /* EDL Mask in DLC */
#define CANA_DLCR_BRS                       ((uint32_t)0x04000000) /* BRS Mask in DLC */

/* ====================  Bit definition for CANA_RFSR register  ====================== */
#define CANA_RFSR_FL                        ((uint32_t)0x00003F00) /* RX Fill Level */
#define CANA_RFSR_IRI                       ((uint32_t)0x00000080) /* RX Increment Read Index */
#define CANA_RFSR_RI                        ((uint32_t)0x0000001F) /* RX Read Index */

/* ====================  Bit definition for CANA_IER register  ====================== */
#define CANA_IER_EARBLOST                   ((uint32_t)0x00000001) /* Arbitration lost interruption */
#define CANA_IER_ETXOK                      ((uint32_t)0x00000002) /* Transmission successful */
#define CANA_IER_ERXOK                      ((uint32_t)0x00000010) /* New Message Received */
#define CANA_IER_ERFXOFLW        			((uint32_t)0x00000040) /* RX FIFO-0 Overflow */
#define CANA_IER_EERROR                     ((uint32_t)0x00000100) /* Error Interrupt Enable */
#define CANA_IER_EBSOFF                     ((uint32_t)0x00000200) /* Bus-Off Interrupt Enable */
#define CANA_IER_ESLP                       ((uint32_t)0x00000400) /* Sleep Interrupt Enable */
#define CANA_IER_EWKUP                      ((uint32_t)0x00000800) /* Wake-Up Interrupt Enable */
#define CANA_IER_ERXFWMFLL       			((uint32_t)0x00001000) /* RX FIFO-0 Watermark Full Interrupt Enable */
#define CANA_IER_ERXRBF                     ((uint32_t)0x00008000) /* RX Buffer Bull Interrupt Enable */
#define CANA_IER_ERXBOFLW                   ((uint32_t)0x00010000) /* RX Buffer Overflow interrupt Enable */

/* ====================  Bit definition for CANA_ISR register  ====================== */
#define CANA_ISR_ARBLOST                    ((uint32_t)0x00000001) /* Arbitration Lost Interrupt */
#define CANA_ISR_TXOK                       ((uint32_t)0x00000002) /* Transmission Successful Interrupt */
#define CANA_ISR_RXOK                       ((uint32_t)0x00000010) /* New Message Received Interrupt */
#define CANA_ISR_RFXOFLW        			((uint32_t)0x00000040) /* RX FIFO-0 Overflow Interrupt */
#define CANA_ISR_ERROR                      ((uint32_t)0x00000100) /* Error Interrupt */
#define CANA_ISR_BSOFF                      ((uint32_t)0x00000200) /* Bus-Off Interrupt */
#define CANA_ISR_SLP                        ((uint32_t)0x00000400) /* Sleep Interrupt */
#define CANA_ISR_WKUP                       ((uint32_t)0x00000800) /* Wake-Up Interrupt */
#define CANA_ISR_RXFWMFLL        			((uint32_t)0x00001000) /* RX FIFO-0 Watermark Full Interrupt */
#define CANA_ISR_RXRBF                      ((uint32_t)0x00008000) /* RX Buffer Full Interrupt  */
#define CANA_ISR_RXBOFLW                    ((uint32_t)0x00010000) /* RX Buffer Overflow Interrupt  */

/* ====================  Bit definition for CANA_MSR register  ====================== */
#define CANA_MSR_DAR                        ((uint32_t)0x00000010) /* Disable Auto-Retransmission */

/* ====================  Bit definition for CANA_AFMR register  ====================== */
#define CANA_AFMR_AMSRR                     ((uint32_t)0x00100000) /* Substitute Remote Transmission Request Mask */
#define CANA_AFMR_AMIDE                     ((uint32_t)0x00080000) /* Identif ier Extension  Mask */
#define CANA_AFMR_AMRTR                     ((uint32_t)0x00000001) /* Remote Transmission Request  Mask */

/* ====================  Bit definition for CANA_AFIR register  ====================== */
#define CANA_AFIR_AISRR                     ((uint32_t)0x00100000) /* Substitute Remote Transmission Request */
#define CANA_AFIR_AIIDE                     ((uint32_t)0x00080000) /* Identif ier Extension */
#define CANA_AFIR_AIRTR                     ((uint32_t)0x00000001) /* Remote Transmission Request */

/* =========================================================================================================================== */
/* ================                            Controller Area Network  B                                    ================= */
/* =========================================================================================================================== */
/* ====================  Bit definition for CANB_CR register  ====================== */
#define CANB_CR_RR                          ((uint32_t)0x40000000)    /* Soft Reset the CAN core */
#define CANB_CR_OMR                         ((uint32_t)0x07000000)    /* Operation Mode Request */
#define CANB_CR_RT                          ((uint32_t)0x18000000)    /* Retransmission Times */
#define CANB_CR_WIE                         ((uint32_t)0x00008000)    /* Wake-up Interrupt Enable */
#define CANB_CR_OIE                         ((uint32_t)0x00004000)    /* Overrun Interrupt Enable */
#define CANB_CR_EIE                         ((uint32_t)0x00002000)    /* Error Interrupt Enable */
#define CANB_CR_TIE                         ((uint32_t)0x00001000)    /* Transmit Interrupt Enable */
#define CANB_CR_RIE                         ((uint32_t)0x00000800)    /* Receive Interrupt Enable */
#define CANB_CR_RRB0                        ((uint32_t)0x00000080)    /* Release Receive Buffer 0 */
#define CANB_CR_RRB1                        ((uint32_t)0x00000040)    /* Release Receive Buffer 1 */
#define CANB_CR_BTR0                        ((uint32_t)0x00000020)    /* Transmit Buffer 0 Request */
#define CANB_CR_BTR1                        ((uint32_t)0x00000010)    /* Transmit Buffer 1 Request */
#define CANB_CR_BTR2                        ((uint32_t)0x00000008)    /* Transmit Buffer 2 Request */
#define CANB_CR_BTRn                        ((uint32_t)0x00000038)    /* Transmit Buffer 0, 1, 2 Request */
#define CANB_CR_SLEEP                       ((uint32_t)0x02000000)    /* Sleep Mode */

/* ====================  Bit definition for CANB_BS register  ====================== */
#define CANB_BS_BRS0                        ((uint16_t)0x1800)        /* Receive Buffer (FIFO) 0 Status */
#define CANB_BS_BRS1                        ((uint16_t)0x0600)        /* Receive Buffer (FIFO) 1 Status */
#define CANB_BS_BO                          ((uint16_t)0x0080)        /* Bus-off */
#define CANB_BS_EW                          ((uint16_t)0x0040)        /* Error Warning */
#define CANB_BS_TS                          ((uint16_t)0x0020)        /* Transmit Status */
#define CANB_BS_RS                          ((uint16_t)0x0010)        /* Receive Status */
#define CANB_BS_DO                          ((uint16_t)0x000C)        /* Data Overrun Field */
#define CANB_BS_BTA0                        ((uint32_t)0x08000000)    /* Buffer0 Transmission Abort */
#define CANB_BS_BTA1                        ((uint32_t)0x04000000)    /* Buffer1 Transmission Abort */
#define CANB_BS_BTA2                        ((uint32_t)0x02000000)    /* Buffer2 Transmission Abort */

/* ====================  Bit definition for CANB_TFDn register  ====================== */
#define CANB_TFDn_RTR                       ((uint16_t)0x8000)        /* (Tx Buffer) Remote Transmission Request */
#define CANB_TFDn_EIR                       ((uint16_t)0x4000)        /* (Tx Buffer) Extended Identifier Enable */
#define CANB_TFDn_EDL                       ((uint16_t)0x0080)        /* (Tx Buffer) Extended Data Length (FD Enable) */
#define CANB_TFDn_BRS                       ((uint16_t)0x0040)        /* (Tx Buffer) Baud Rate Switch */

/* ====================  Bit definition for CANB_AFC0 register  ====================== */
#define CANB_AFC0_RBAFG0E                   ((uint8_t)0x80)           /* Receive Buffer Acceptance Filter Group 0 Enable */
#define CANB_AFC0_RBAFG1E                   ((uint8_t)0x40)           /* Receive Buffer Acceptance Filter Group 1 Enable */
#define CANB_AFC0_RB0DFB0E                  ((uint8_t)0x20)           /* Receive Buffer0 Data Filter Byte 0 Enable */
#define CANB_AFC0_RB0DFB1E                  ((uint8_t)0x10)           /* Receive Buffer0 Data Filter Byte 1 Enable */
#define CANB_AFC0_RB1DFB0E                  ((uint8_t)0x08)           /* Receive Buffer1 Data Filter Byte 0 Enable */
#define CANB_AFC0_RB1DFB1E                  ((uint8_t)0x04)           /* Receive Buffer1 Data Filter Byte 1 Enable */

/* ====================  Bit definition for CANB_FMC register  ====================== */
#define CANB_FMC_FMA                        ((uint8_t)0x80)           /* Filter Mask All */
#define CANB_FMC_RBAFM0E                    ((uint8_t)0x40)           /* Receive Buffer Acceptance Filter Mask Group 0 Enable */
#define CANB_FMC_RBAFM1E                    ((uint8_t)0x20)           /* Receive Buffer Acceptance Filter Mask Group 1 Enable */
#define CANB_FMC_RB0DFMB0E                  ((uint8_t)0x10)           /* Receive Buffer0 Data Filter Mask Byte 0 Enable */
#define CANB_FMC_RB0DFMB1E                  ((uint8_t)0x08)           /* Receive Buffer0 Data Filter Mask Byte 1 Enable */
#define CANB_FMC_RB1DFMB0E                  ((uint8_t)0x04)           /* Receive Buffer1 Data Filter Mask Byte 0 Enable */
#define CANB_FMC_RB1DFMB1E                  ((uint8_t)0x02)           /* Receive Buffer1 Data Filter Mask Byte 1 Enable */

/* ====================  Bit definition for CANB_RFDn register  ====================== */
#define CANB_RFDn_RTR                       ((uint16_t)0x8000)        /* (Rx Buffer) Remote Transmission Request */
#define CANB_RFDn_EIE                       ((uint16_t)0x4000)        /* (Rx Buffer) Extended Identifier Enable */
#define CANB_RFDn_EDL                       ((uint16_t)0x0080)        /* (Rx Buffer) Extended Data Length (FD Enable) */
#define CANB_RFDn_BRS                       ((uint16_t)0x0040)        /* (Rx Buffer) Baud Rate Switch */
#define CANB_RFDn_ESI                       ((uint16_t)0x0020)        /* (Rx Buffer) Error State Indicator */

/* ====================  Bit definition for CANB_REIHn register  ====================== */
#define CANB_REIHn_DL                       ((uint16_t)0x0F00)        /* (Rx Buffer) Data Lentgh Code */

/* ====================  Bit definition for CANB_EC register  ====================== */
#define CANB_EC_TEC                         ((uint16_t)0xFF00)        /* Transmitter Error Counter (TEC) */
#define CANB_EC_REC                         ((uint16_t)0x00FF)        /* Receiver Error Counter (REC) */

/* ====================  Bit definition for CANB_ET register  ====================== */
#define CANB_ET_BE                          ((uint8_t)0x80)           /* Bit Error */
#define CANB_ET_SE                          ((uint8_t)0x40)           /* Stuff Error */
#define CANB_ET_CE                          ((uint8_t)0x20)           /* CRC Error */
#define CANB_ET_FE                          ((uint8_t)0x10)           /* Form Error */
#define CANB_ET_AE                          ((uint8_t)0x08)           /* ACK Error */
#define CANB_ET_OE                          ((uint8_t)0x04)           /* Overrun Error */

/* ====================  Bit definition for CANB_IR register  ====================== */
#define CANB_IRR_WIR                        ((uint8_t)0x80)           /* Wake-up Interrupt Request */
#define CANB_IRR_OIR                        ((uint8_t)0x40)           /* Overrun Interrupt Request */
#define CANB_IRR_EIR                        ((uint8_t)0x20)           /* Error Interrupt Request */
#define CANB_IRR_TBI0                       ((uint8_t)0x10)           /* Transmit Buffer Interrupt 0 */
#define CANB_IRR_TBI1                       ((uint8_t)0x08)           /* Transmit Buffer Interrupt 1 */
#define CANB_IRR_TBI2                       ((uint8_t)0x04)           /* Transmit Buffer Interrupt 2 */
#define CANB_IRR_TBIn                       ((uint8_t)0x1C)           /* TBIn (n=0,1,2) field */
#define CANB_IRR_RBI0                       ((uint8_t)0x02)           /* Receive Buffer Interrupt 0 */
#define CANB_IRR_RBI1                       ((uint8_t)0x01)           /* Receive Buffer Interrupt 1 */
#define CANB_IRR_RBIn                       ((uint8_t)0x03)           /* RBIn (n=0,1) field */

/* =========================================================================================================================== */
/* ================                            Double Data Rate SDRAM                                        ================= */
/* =========================================================================================================================== */
/* ====================  Bit definition for DAC_CR register  ====================== */
#define  DAC_CR_EN1                          ((uint32_t)0x00000001)        /*!<DAC channel1 enable */
#define  DAC_CR_TEN1                         ((uint32_t)0x00000002)        /*!<DAC channel1 Trigger enable */

#define  DAC_CR_TSEL1                        ((uint32_t)0x0000001C)        /*!<TSEL1[2:0] (DAC channel1 Trigger selection) */
#define  DAC_CR_TSEL1_0                      ((uint32_t)0x00000004)        /*!<Bit 0 */
#define  DAC_CR_TSEL1_1                      ((uint32_t)0x00000008)        /*!<Bit 1 */
#define  DAC_CR_TSEL1_2                      ((uint32_t)0x00000010)        /*!<Bit 2 */

#define  DAC_CR_WAVE1                        ((uint32_t)0x00000020)        /*!<WAVE1 (DAC channel1 triangle wave generation enable) */

#define  DAC_CR_AMP1                         ((uint32_t)0x000003C0)        /*!<MAMP1[3:0] (DAC channel1 Amplitude selector) */
#define  DAC_CR_AMP1_0                       ((uint32_t)0x00000040)        /*!<Bit 0 */
#define  DAC_CR_AMP1_1                       ((uint32_t)0x00000080)        /*!<Bit 1 */
#define  DAC_CR_AMP1_2                       ((uint32_t)0x00000100)        /*!<Bit 2 */
#define  DAC_CR_AMP1_3                       ((uint32_t)0x00000200)        /*!<Bit 3 */

#define  DAC_CR_DALIGN1                      ((uint32_t)0x00000400)        /*!<DAC channel1 data align */
#define  DAC_CR_DMODE1                       ((uint32_t)0x00000800)        /*!<DAC channel1 data mode */

#define  DAC_CR_DMAEN1                       ((uint32_t)0x00001000)        /*!<DAC channel1 DMA enable */

#define  DAC_CR_EN2                          ((uint32_t)0x00010000)        /*!<DAC channel2 enable */
#define  DAC_CR_TEN2                         ((uint32_t)0x00020000)        /*!<DAC channel2 Trigger enable */

#define  DAC_CR_TSEL2                        ((uint32_t)0x001C0000)        /*!<TSEL2[2:0] (DAC channel2 Trigger selection) */
#define  DAC_CR_TSEL2_0                      ((uint32_t)0x00040000)        /*!<Bit 0 */
#define  DAC_CR_TSEL2_1                      ((uint32_t)0x00080000)        /*!<Bit 1 */
#define  DAC_CR_TSEL2_2                      ((uint32_t)0x00100000)        /*!<Bit 2 */

#define  DAC_CR_WAVE2                        ((uint32_t)0x00200000)        /*!<WAVE2 (DAC channel2 triangle wave generation enable) */

#define  DAC_CR_MAMP2                        ((uint32_t)0x03C00000)        /*!<MAMP2[3:0] (DAC channel2 Amplitude selector) */
#define  DAC_CR_MAMP2_0                      ((uint32_t)0x00400000)        /*!<Bit 0 */
#define  DAC_CR_MAMP2_1                      ((uint32_t)0x00800000)        /*!<Bit 1 */
#define  DAC_CR_MAMP2_2                      ((uint32_t)0x01000000)        /*!<Bit 2 */
#define  DAC_CR_MAMP2_3                      ((uint32_t)0x02000000)        /*!<Bit 3 */

#define  DAC_CR_DALIGN2                      ((uint32_t)0x04000000)        /*!<DAC channel2 data align */
#define  DAC_CR_DMODE2                       ((uint32_t)0x08000000)        /*!<DAC channel2 data mode */

#define  DAC_CR_DMAEN2                       ((uint32_t)0x10000000)        /*!<DAC channel2 DMA enabled */

#define  DAC_CR_SYNTEN                       ((uint32_t)0x20000000)        /*!<DAC channel1 and channel2 synchronous trigger enabled */

/* ====================  Bit definition for DAC_SWTRIGR register  ====================== */
#define  DAC_SWTRIGR_SWTRIG1                 ((uint8_t)0x01)               /*!<DAC channel1 software trigger */
#define  DAC_SWTRIGR_SWTRIG2                 ((uint8_t)0x02)               /*!<DAC channel2 software trigger */

/* ====================  Bit definition for DAC_DHR1 register  ====================== */
#define  DAC_DHR1_DACC1DHR                   ((uint16_t)0xFFFF)            /*!<DAC channel1 data hold register */

/* ====================  Bit definition for DAC_DHR2 register  ====================== */
#define  DAC_DHR2_DACC2DHR                   ((uint16_t)0x0FFF)            /*!<DAC channel2 data hold register */

/* ====================  Bit definition for DAC_DHRD register  ====================== */
#define  DAC_DHRD_DACC1DHR                   ((uint32_t)0x0000FFFF)        /*!<DAC channel1 DHRD data hold register */
#define  DAC_DHRD_DACC2DHR                   ((uint32_t)0xFFFF0000)        /*!<DAC channel2 DHRD data hold register */

/* ====================  Bit definition for DAC_DOR1 register  ====================== */
#define  DAC_DOR1_DACC1DOR                   ((uint16_t)0x0FFF)            /*!<DAC channel1 data output */

/* ====================  Bit definition for DAC_DOR2 register  ====================== */
#define  DAC_DOR2_DACC2DOR                   ((uint16_t)0x0FFF)            /*!<DAC channel2 data output */

/* ====================  Bit definition for DAC_RATE register  ====================== */
#define  DAC_RATE_DIVISION                   ((uint16_t)0x03FF)            /*!<DAC clock division rate */

/* ====================  Bit definition for DAC_SR register  ====================== */
#define  DAC_SR_DMAUDR1                      ((uint32_t)0x00000001)        /*!<DAC channel1 DMA underrun flag */
#define  DAC_SR_DMAUDR2                      ((uint32_t)0x00000002)        /*!<DAC channel2 DMA underrun flag */

/* ====================  Bit definition for DAC_IE register  ====================== */
#define  DAC_IE_DMAUDR1                      ((uint32_t)0x00000001)        /*!<DAC channel1 DMA underrun interrupt enable */
#define  DAC_IE_DMAUDR2                      ((uint32_t)0x00000002)        /*!<DAC channel2 DMA underrun interrupt enable */


/* =========================================================================================================================== */
/* ================                            Double Data Rate SDRAM                                        ================= */
/* =========================================================================================================================== */
/* ====================  Bit definition for MCCR register  ====================== */
#define DDR_MCCR_GDS                      ((uint32_t)0x00000007)        /*!< Generate DQS sampling window */
#define DDR_MCCR_DC                       ((uint32_t)0x00000008)        /*!< Data coherence check disable */
#define DDR_MCCR_AMTSEL                   ((uint32_t)0x00000030)        /*!< DDR memory address mapping table select */
#define DDR_MCCR_MW                       ((uint32_t)0x00000300)        /*!< Memory Width */
#define DDR_MCCR_ARCI                     ((uint32_t)0x00001C00)        /*!< Auto-refresh commands in the initial SDRAM sequency */
#define DDR_MCCR_PRCCNT                   ((uint32_t)0x0000E000)        /*!< Post-refresh command counts threshold */
#define DDR_MCCR_DM                       ((uint32_t)0x00030000)        /*!< DDR Mode */
#define DDR_MCCR_BYONE                    ((uint32_t)0x00040000)        /*!< MClk versus DRAM clock frequency ratio */
#define DDR_MCCR_LPM                      ((uint32_t)0x00080000)        /*!< LPDDR mode */
#define DDR_MCCR_CMDR                     ((uint32_t)0x00100000)        /*!< DDR command reorder */
#define DDR_MCCR_CCL                      ((uint32_t)0x00600000)        /*!< Continuous command limitation in the scheduler */
#define DDR_MCCR_WC                       ((uint32_t)0x07800000)        /*!< Wait cycles max value for command popped out to the scheduler */
#define DDR_MCCR_AER                      ((uint32_t)0x08000000)        /*!< APB error response disable */
#define DDR_MCCR_MR                       ((uint32_t)0x10000000)        /*!< manual refresh enable */

/* ====================  Bit definition for MCSR register  ====================== */
#define DDR_MCSR_INIT                     ((uint32_t)0x00000001)        /*!< Initial command */
#define DDR_MCSR_MRS                      ((uint32_t)0x00000002)        /*!< Initial command */
#define DDR_MCSR_SRF                      ((uint32_t)0x00000004)        /*!< Self-refresh command */
#define DDR_MCSR_SRFE                     ((uint32_t)0x00000008)        /*!< Exit self-refresh command */
#define DDR_MCSR_RM                       ((uint32_t)0x00000030)        /*!< Register mode */
#define DDR_MCSR_ZQCS                     ((uint32_t)0x00000040)        /*!< ZQCS Operation */
#define DDR_MCSR_ZQCL                     ((uint32_t)0x00000080)        /*!< ZQCL Operation */
#define DDR_MCSR_INITCMPL                 ((uint32_t)0x00000100)        /*!< Initial OK */
#define DDR_MCSR_INITSTS                  ((uint32_t)0x00000200)        /*!< Initial state */
#define DDR_MCSR_SRFSTS                   ((uint32_t)0x00000400)        /*!< Self-refresh state */
#define DDR_MCSR_APDSTS                   ((uint32_t)0x00000800)        /*!< Automatic power-down state */
#define DDR_MCSR_ZQCSSTS                  ((uint32_t)0x00001000)        /*!< ZQCS state */
#define DDR_MCSR_ZQCLSTS                  ((uint32_t)0x00002000)        /*!< ZQCL state */
#define DDR_MCSR_MCCQE                    ((uint32_t)0x00004000)        /*!< Memory controller command queue empty */
#define DDR_MCSR_ACQE                     ((uint32_t)0x00008000)        /*!< AHB/AXI command queue empty */
#define DDR_MCSR_RLFAIL                   ((uint32_t)0x00010000)        /*!< Read-leveling fail or hardware disable */
#define DDR_MCSR_WLFAIL                   ((uint32_t)0x00020000)        /*!< Write-leveling fail or hardware disable */
#define DDR_MCSR_DADC                     ((uint32_t)0x00040000)        /*!< DDR access disable complete */
#define DDR_MCSR_WS                       ((uint32_t)0x01000000)        /*!< Warm Start */
#define DDR_MCSR_DAD                      ((uint32_t)0x02000000)        /*!< DDR access disable */
#define DDR_MCSR_MRRS                     ((uint32_t)0x00000000)        /*!< MR rank select */

/* ====================  Bit definition for MRSVR0 register  ====================== */
#define DDR_MRSVR0_MR                     ((uint32_t)0x00003FFF)        /*!< Mode register (MR0 in the DDR3 mode) */
#define DDR_MRSVR0_EMR                    ((uint32_t)0x3FFF0000)        /*!< Extended mode register (MR1 in the DDR3 mode) */

/* ====================  Bit definition for MRSVR1 register  ====================== */
#define DDR_MRSVR1_EMR2                   ((uint32_t)0x00003FFF)        /*!< Extended mode register 2 (MR2 in the DDR3 mode) */
#define DDR_MRSVR1_EMR3                   ((uint32_t)0x3FFF0000)        /*!< Extended mode register 3 (MR3 in the DDR3 mode) */

/* ====================  Bit definition for EXRANKR register  ====================== */
#define DDR_EXRANKR_R0S                   ((uint32_t)0x00000007)        /*!< Rank0 size */
#define DDR_EXRANKR_R0T                   ((uint32_t)0x00000070)        /*!< Rank0 type */
#define DDR_EXRANKR_R1S                   ((uint32_t)0x00000700)        /*!< Rank1 size */
#define DDR_EXRANKR_R1T                   ((uint32_t)0x00007000)        /*!< Rank1 type */
#define DDR_EXRANKR_R1EN                  ((uint32_t)0x00010000)        /*!< Rank1 enable */
#define DDR_EXRANKR_R0B                   ((uint32_t)0xFF000000)        /*!< Rank0 base address */

/* ====================  Bit definition for TMPR0 register  ====================== */
#define DDR_TMPR0_TRAS                    ((uint32_t)0x0000001F)        /*!< Active to Precharge period */
#define DDR_TMPR0_TRC                     ((uint32_t)0x00003F00)        /*!< Active to Active command period for the same bank */
#define DDR_TMPR0_TFAW                    ((uint32_t)0x001F0000)        /*!< 4 bank activate windows */
#define DDR_TMPR0_TRFC                    ((uint32_t)0xFF000000)        /*!< Refresh-to-Active/Refresh command period */

/* ====================  Bit definition for TMPR1 register  ====================== */
#define DDR_TMPR1_TRCD                    ((uint32_t)0x0000000F)        /*!< The minimum delay between the active and read/write commands */
#define DDR_TMPR1_TRRD                    ((uint32_t)0x000000F0)        /*!< Active-to-Active command period for different banks */
#define DDR_TMPR1_TRP                     ((uint32_t)0x00000F00)        /*!< Precharge period */
#define DDR_TMPR1_TMRD                    ((uint32_t)0x0000F000)        /*!< Cycle time of the load mode register command */
#define DDR_TMPR1_TMOD                    ((uint32_t)0x000F0000)        /*!< The mode register sets the command update delay */
#define DDR_TMPR1_TWR                     ((uint32_t)0x00F00000)        /*!< Write recovery time */
#define DDR_TMPR1_TRTP                    ((uint32_t)0x07000000)        /*!< Internal read-to-precharge delay */
#define DDR_TMPR1_TWTR                    ((uint32_t)0x70000000)        /*!< Internal write-to-read delay */

/* ====================  Bit definition for TMPR2 register  ====================== */
#define DDR_TMPR2_TREFI                   ((uint32_t)0x000000FF)        /*!< Average periodic refresh interval */
#define DDR_TMPR2_TXSR                    ((uint32_t)0x0000FF00)        /*!< Exit from the self-refresh mode to a command period */
#define DDR_TMPR2_TRTOW                   ((uint32_t)0x03000000)        /*!< Additional delay cycles from the read command to the write command */
#define DDR_TMPR2_TRTOR                   ((uint32_t)0x0C000000)        /*!< Additional delay cycles from the read command to the read command */
#define DDR_TMPR2_TWTOW                   ((uint32_t)0x30000000)        /*!< Additional delay cycles from the write command to the write command */
#define DDR_TMPR2_TWTOR                   ((uint32_t)0xC0000000)        /*!< Additional delay cycles from the write command to the read command for accessing different ranks */

/* ====================  Bit definition for PHYCR0 register  ====================== */
#define DDR_PHYCR0_ODTMDDQ                ((uint32_t)0x00000007)        /*!< ODT value of DQ */
#define DDR_PHYCR0_PRSRFX                 ((uint32_t)0x00000008)        /*!< Enable automatically reset D-PHY after exiting the self-refresh mode */
#define DDR_PHYCR0_ODTMDDQS               ((uint32_t)0x00000070)        /*!< ODT value of DQS */
#define DDR_PHYCR0_AICPDN                 ((uint32_t)0x00000080)        /*!< Automatic control of the I/O Input buffer at power-down state */
#define DDR_PHYCR0_ODTOEN                 ((uint32_t)0x00000100)        /*!< Enable input drivers of ODT */
#define DDR_PHYCR0_CMDADDROEN             ((uint32_t)0x00000200)        /*!< The input controls of the DDR PHY ADDR, BA, RAS, CAS, WE, and CS drivers */
#define DDR_PHYCR0_CLKOEN                 ((uint32_t)0x00000400)        /*!< The input controls DDR PHY CK and CKB */
#define DDR_PHYCR0_DQIE                   ((uint32_t)0x00000800)        /*!< DQ and DQS receivers enable */
#define DDR_PHYCR0_CPS                    ((uint32_t)0x00001000)        /*!< DDR PHY input clock for the DDR SDRAM phase */
#define DDR_PHYCR0_CUP                    ((uint32_t)0x00002000)        /*!< DDR PHY DLL update enable control */
#define DDR_PHYCR0_SB                     ((uint32_t)0x00004000)        /*!< VREF selection */
#define DDR_PHYCR0_AIDPDN                 ((uint32_t)0x00008000)        /*!< Automatic control of the I/O input buffer at the power-down state */
#define DDR_PHYCR0_CFLDO                  ((uint32_t)0x00010000)        /*!< Command block DLL lock state. */
#define DDR_PHYCR0_PHYODD                 ((uint32_t)0x00020000)        /*!< RE_ODD and WR_ODD signal usages for DDRx PHY */
#define DDR_PHYCR0_B0FLDO                 ((uint32_t)0x01000000)        /*!< Byte 0 DLL lock flag indicates that DLL is at the lock state */
#define DDR_PHYCR0_B1FLDO                 ((uint32_t)0x02000000)        /*!< Byte 1 DLL lock flag indicates that DLL is at the lock state */
#define DDR_PHYCR0_B2FLDO                 ((uint32_t)0x04000000)        /*!< Byte 2 DLL lock flag indicates that DLL is at the lock state */
#define DDR_PHYCR0_B3FLDO                 ((uint32_t)0x08000000)        /*!< Byte 3 DLL lock flag indicates that DLL is at the lock state */

/* ====================  Bit definition for PHYRDTR register  ====================== */
#define DDR_PHYRDTR_B0DLSELRD             ((uint32_t)0x0000000F)        /*!< Byte 0 delay value control to add a delay into the read DQS or read DQ */
#define DDR_PHYRDTR_B1DLSELRD             ((uint32_t)0x000000F0)        /*!< Byte 1 delay value control to add a delay into the read DQS or read DQ */
#define DDR_PHYRDTR_B2DLSELRD             ((uint32_t)0x00000F00)        /*!< Byte 2 delay value control to add a delay into the read DQS or read DQ */
#define DDR_PHYRDTR_B3DLSELRD             ((uint32_t)0x0000F000)        /*!< Byte 3 delay value control to add a delay into the read DQS or read DQ */

/* ====================  Bit definition for COMPBLKCR register  ====================== */
#define DDR_COMPBLKCR_COMPSEL             ((uint32_t)0x00000001)        /*!< Compensation method selection */
#define DDR_COMPBLKCR_DIP                 ((uint32_t)0x0000007E)        /*!< Preset value for the COMPBLK pull-up PMOS impedance */
#define DDR_COMPBLKCR_DIN                 ((uint32_t)0x00001F80)        /*!< Preset value for the COMPBLK pull-down NMOS impedance */
#define DDR_COMPBLKCR_DOP                 ((uint32_t)0x0007E000)        /*!< Value of the COMPBLK pull-up PMOS impedance setting from the input */
#define DDR_COMPBLKCR_DON                 ((uint32_t)0x01F80000)        /*!< Value of the COMPBLK pull-down NMOS impedance setting from the input */

/* ====================  Bit definition for APDCR register  ====================== */
#define DDR_APDCR_APDNT                   ((uint32_t)0x00000FFF)        /*!< Automatic power-down timer */
#define DDR_APDCR_APDN                    ((uint32_t)0x00001000)        /*!< Automatic power-down mode control */
#define DDR_APDCR_ASRFT                   ((uint32_t)0x0FFF0000)        /*!< Automatic self-refresh timer */
#define DDR_APDCR_ASRF                    ((uint32_t)0x10000000)        /*!< Automatic self-refresh mode control */
 
/* ====================  Bit definition for CHARBRA register  ====================== */
#define DDR_CHARBRA_CHP                   ((uint32_t)0x000000FF)        /*!< Channel high-priority */
#define DDR_CHARBRA_BOA                   ((uint32_t)0x0000FF00)        /*!< Burst oriented arbitration enable */
#define DDR_CHARBRA_GGCL                  ((uint32_t)0x1F000000)        /*!< Group grant count low */
#define DDR_CHARBRA_IRW                   ((uint32_t)0x40000000)        /*!< Independent R/W control */
#define DDR_CHARBRA_RWG                   ((uint32_t)0x80000000)        /*!< Enable the Read-Write group arbitration */

/* ====================  Bit definition for CHGNTRA register  ====================== */
#define DDR_CHGNTRA_ARBCNT0               ((uint32_t)0x000000FF)        /*!< The maximum allowed commands will be issued once channel 0 is granted. */
#define DDR_CHGNTRA_ARBCNT1               ((uint32_t)0x0000FF00)        /*!< The maximum allowed commands will be issued once channel 1 is granted. */
#define DDR_CHGNTRA_ARBCNT2               ((uint32_t)0x00FF0000)        /*!< The maximum allowed commands will be issued once channel 2 is granted. */
#define DDR_CHGNTRA_ARBCNT3               ((uint32_t)0xFF000000)        /*!< The maximum allowed commands will be issued once channel 3 is granted. */

/* ====================  Bit definition for PHYWRTMR register  ====================== */
#define DDR_PHYWRTMR_WRLAT                ((uint32_t)0x0000000F)        /*!< The number of MClk clock cycles between when a write command is sent 
                                                                             on the DFI control interface and when the dfi_wrdata_en signal is asserted. */
#define DDR_PHYWRTMR_WRD                  ((uint32_t)0x00000030)        /*!< The number of MClk clock cycles between when the dfi_wrdata_en signal is 
                                                                             asserted and when the associated write data are driven on the dfi_wrdata signal. */
#define DDR_PHYWRTMR_TRDEN                ((uint32_t)0x000F0000)        /*!< The cycles must be asserted after the assertion of a read command on the PHY 
                                                                             control interface and remains valid for the duration of contiguous read data 
                                                                             expected on the dfi_rddata bus. */
#define DDR_PHYWRTMR_RDLAT                ((uint32_t)0x00F00000)        /*!< The MClk cycles that dfi_rddata expected to receive after rdcmd is asserted. */

/* ====================  Bit definition for FLUSHCR register  ====================== */
#define DDR_FLUSHCR_CFEN                  ((uint32_t)0x000000FF)        /*!< Enable of command flushing. */
#define DDR_FLUSHCR_FIEN                  ((uint32_t)0x0000FF00)        /*!< Interrupt enable for the command flushing. */
#define DDR_FLUSHCR_DIEN                  ((uint32_t)0x00010000)        /*!< Interrupt enable for the debug function. */

/* ====================  Bit definition for FLUSHSR register  ====================== */
#define DDR_FLUSHSR_FD                    ((uint32_t)0x000000FF)        /*!< Status of the command flushing. */
#define DDR_FLUSHSR_DH                    ((uint32_t)0x00000100)        /*!< Status of the debug function. */

/* ====================  Bit definition for SPLITCR register  ====================== */
#define DDR_SPLITCR_CH2SDEN               ((uint32_t)0x00000004)        /*!< Disable SPLIT response of channel 2. */
#define DDR_SPLITCR_CH3SDEN               ((uint32_t)0x00000008)        /*!< Disable SPLIT response of channel 3. */
#define DDR_SPLITCR_CH2HPROT              ((uint32_t)0x00003000)        /*!< Channel 2 bufferable select. */
#define DDR_SPLITCR_CH3HPROT              ((uint32_t)0x0000C000)        /*!< Channel 3 bufferable select. */
 
/* ====================  Bit definition for UPDCR register  ======================== */
#define DDR_UPDCR_TDLLUP                  ((uint32_t)0x000000FF)        /*!< Digital DLL update delay control code timing interval. */
#define DDR_UPDCR_TWLUP                   ((uint32_t)0x0000FF00)        /*!< Write-leveling calibration timing interval. */
#define DDR_UPDCR_ZQCUP                   ((uint32_t)0x00030000)        /*!< ZQCS or ZQCL enable after exiting from the self-refresh state. */

/* ====================  Bit definition for REVR register  ====================== */
#define DDR_REVR_REL                      ((uint32_t)0x000000FF)        /*!< The release number of the current revision. */
#define DDR_REVR_MIN                      ((uint32_t)0x0000FF00)        /*!< The minor version number of the DDRx memory controller. */
#define DDR_REVR_MAJ                      ((uint32_t)0x00000000)        /*!< The major version number of the DDRx memory controller. */

/* ====================  Bit definition for FEATR1 register  ====================== */
#define DDR_FEATR1_CHNCNT                 ((uint32_t)0x00000007)        /*!< The channel counts */
#define DDR_FEATR1_AMECN                  ((uint32_t)0x00000038)        /*!< The atomic monitor entries counts */
#define DDR_FEATR1_MAXMW                  ((uint32_t)0x000000C0)        /*!< The maximum memory width of controller */
#define DDR_FEATR1_CH0TYP                 ((uint32_t)0x00000100)        /*!< The channel 0 interface type */
#define DDR_FEATR1_CH1TYP                 ((uint32_t)0x00000200)        /*!< The channel 1 interface type */
#define DDR_FEATR1_CH2TYP                 ((uint32_t)0x00000300)        /*!< The channel 2 interface type */
#define DDR_FEATR1_CH3TYP                 ((uint32_t)0x00000400)        /*!< The channel 3 interface type */
#define DDR_FEATR1_CH0DW                  ((uint32_t)0x00010000)        /*!< The channel 0 data width */
#define DDR_FEATR1_CH1DW                  ((uint32_t)0x00020000)        /*!< The channel 1 data width */
#define DDR_FEATR1_CH2DW                  ((uint32_t)0x00040000)        /*!< The channel 2 data width */
#define DDR_FEATR1_CH3DW                  ((uint32_t)0x00080000)        /*!< The channel 3 data width */
#define DDR_FEATR1_BN                     ((uint32_t)0x01000000)        /*!< The bank number per rank */
#define DDR_FEATR1_BS                     ((uint32_t)0x02000000)        /*!< The bank swizzle configuration */

/* ====================  Bit definition for FEATR2 register  ====================== */
#define DDR_FEATR2_CH0CM                  ((uint32_t)0x00000003)        /*!< The channel 0 clock mode. */
#define DDR_FEATR2_CH0STYP                ((uint32_t)0x00000004)        /*!< The channel 0 split type. */
#define DDR_FEATR2_CH0BCTYP               ((uint32_t)0x00000008)        /*!< The channel 0 bus connect type. */
#define DDR_FEATR2_CH1CM                  ((uint32_t)0x00000030)        /*!< The channel 1 clock mode. */       
#define DDR_FEATR2_CH1STYP                ((uint32_t)0x00000040)        /*!< The channel 1 split type. */       
#define DDR_FEATR2_CH1BCTYP               ((uint32_t)0x00000080)        /*!< The channel 1 bus connect type. */ 
#define DDR_FEATR2_CH2CM                  ((uint32_t)0x00000300)        /*!< The channel 2 clock mode. */       
#define DDR_FEATR2_CH2STYP                ((uint32_t)0x00000400)        /*!< The channel 2 split type. */       
#define DDR_FEATR2_CH2BCTYP               ((uint32_t)0x00000800)        /*!< The channel 2 bus connect type. */ 
#define DDR_FEATR2_CH3CM                  ((uint32_t)0x00003000)        /*!< The channel 3 clock mode. */       
#define DDR_FEATR2_CH3STYP                ((uint32_t)0x00004000)        /*!< The channel 3 split type. */       
#define DDR_FEATR2_CH3BCTYP               ((uint32_t)0x00008000)        /*!< The channel 3 bus connect type. */ 

/* ====================  Bit definition for UDEFR register  ====================== */
#define DDR_UDEFR_UDR                     ((uint32_t)0xFFFFFFFF)        /*!< User-defined register for specific usage. */

/* ====================  Bit definition for WLEVELCR register  ====================== */
#define DDR_WLEVELCR_TWLO                 ((uint32_t)0x000000FF)        /*!< Write-leveling DQS enable to latch the DQ data delay time. */
#define DDR_WLEVELCR_BYTE0DEN             ((uint32_t)0x00010000)        /*!< Byte 0 write-leveling hardware disable. */
#define DDR_WLEVELCR_BYTE1DEN             ((uint32_t)0x00020000)        /*!< Byte 1 write-leveling hardware disable. */
#define DDR_WLEVELCR_BYTE2DEN             ((uint32_t)0x00040000)        /*!< Byte 2 write-leveling hardware disable. */
#define DDR_WLEVELCR_BYTE3DEN             ((uint32_t)0x00080000)        /*!< Byte 3 write-leveling hardware disable. */
#define DDR_WLEVELCR_BYTE0PASS            ((uint32_t)0x01000000)        /*!< Byte 0 write-leveling status. */
#define DDR_WLEVELCR_BYTE1PASS            ((uint32_t)0x02000000)        /*!< Byte 1 write-leveling status. */
#define DDR_WLEVELCR_BYTE2PASS            ((uint32_t)0x04000000)        /*!< Byte 2 write-leveling status. */
#define DDR_WLEVELCR_BYTE3PASS            ((uint32_t)0x08000000)        /*!< Byte 3 write-leveling status. */

/* ====================  Bit definition for WLEVELBLR register  ====================== */
#define DDR_WLEVELBLR_BYTE0PDL            ((uint32_t)0x0000007F)        /*!< Byte 0 programable DLL delay */
#define DDR_WLEVELBLR_BYTE1PDL            ((uint32_t)0x00007F00)        /*!< Byte 1 programable DLL delay */
#define DDR_WLEVELBLR_BYTE2PDL            ((uint32_t)0x007F0000)        /*!< Byte 2 programable DLL delay */
#define DDR_WLEVELBLR_BYTE3PDL            ((uint32_t)0x7F000000)        /*!< Byte 3 programable DLL delay */
 
/* ====================  Bit definition for PHYMISCR1 register  ====================== */
#define DDR_PHYMISCR1_BYTE0DQSRD          ((uint32_t)0x00000001)        /*!< Byte 0 read added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE0DQSWR          ((uint32_t)0x00000002)        /*!< Byte 0 write added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE1DQSRD          ((uint32_t)0x00000010)        /*!< Byte 1 read added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE1DQSWR          ((uint32_t)0x00000020)        /*!< Byte 1 write added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE2DQSRD          ((uint32_t)0x00000100)        /*!< Byte 2 read added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE2DQSWR          ((uint32_t)0x00000200)        /*!< Byte 2 write added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE3DQSRD          ((uint32_t)0x00001000)        /*!< Byte 3 read added delay in DQ or DQS configuration */
#define DDR_PHYMISCR1_BYTE3DQSWR          ((uint32_t)0x00002000)        /*!< Byte 3 write added delay in DQ or DQS configuration */

/* ====================  Bit definition for RLEVELCR register  ====================== */
#define DDR_RLEVELCR_BYTE0DEN             ((uint32_t)0x00000001)        /*!< Byte 0 read-leveling hardware disable */
#define DDR_RLEVELCR_BYTE1DEN             ((uint32_t)0x00000002)        /*!< Byte 1 read-leveling hardware disable */
#define DDR_RLEVELCR_BYTE2DEN             ((uint32_t)0x00000004)        /*!< Byte 2 read-leveling hardware disable */
#define DDR_RLEVELCR_BYTE3DEN             ((uint32_t)0x00000008)        /*!< Byte 3 read-leveling hardware disable */
#define DDR_RLEVELCR_TRAINPERIOD          ((uint32_t)0x0000FF00)        /*!< Periodic read-leveling training timing interval */
#define DDR_RLEVELCR_PERIOTRAINEN         ((uint32_t)0x00010000)        /*!< Periodic read leveling enable (Only for LPDDR2 mode) */
#define DDR_RLEVELCR_BYTE0PASS            ((uint32_t)0x01000000)        /*!< Byte 0 read-leveling status */
#define DDR_RLEVELCR_BYTE1PASS            ((uint32_t)0x02000000)        /*!< Byte 1 read-leveling status */
#define DDR_RLEVELCR_BYTE2PASS            ((uint32_t)0x04000000)        /*!< Byte 2 read-leveling status */
#define DDR_RLEVELCR_BYTE3PASS            ((uint32_t)0x08000000)        /*!< Byte 3 read-leveling status */

/* ====================  Bit definition for MSDLYCR register  ====================== */
#define DDR_MSDLYCR_BYTE0MSDLY           ((uint32_t)0x0000000F)         /*!< Byte 0 programmable read DQS filtering window */
#define DDR_MSDLYCR_BYTE1MSDLY           ((uint32_t)0x000000F0)         /*!< Byte 1 programmable read DQS filtering window */
#define DDR_MSDLYCR_BYTE2MSDLY           ((uint32_t)0x00000F00)         /*!< Byte 2 programmable read DQS filtering window */
#define DDR_MSDLYCR_BYTE3MSDLY           ((uint32_t)0x0000F000)         /*!< Byte 3 programmable read DQS filtering window */
 
/* ====================  Bit definition for WRDLLCR register  ====================== */
#define DDR_WRDLLCR_BYTE0DLSEL           ((uint32_t)0x0000000F)         /*!< Byte 0 delay control, to add a delay in DQS or DQ */
#define DDR_WRDLLCR_BYTE1DLSEL           ((uint32_t)0x000000F0)         /*!< Byte 1 delay control, to add a delay in DQS or DQ */
#define DDR_WRDLLCR_BYTE2DLSEL           ((uint32_t)0x00000F00)         /*!< Byte 2 delay control, to add a delay in DQS or DQ */
#define DDR_WRDLLCR_BYTE3DLSEL           ((uint32_t)0x0000F000)         /*!< Byte 3 delay control, to add a delay in DQS or DQ */

/* ====================  Bit definition for TRAFMR register  ====================== */
#define DDR_TRAFMR_CYCLE                 ((uint32_t)0xFFFFFFFF)         /*!< Traffic monitor clock cycle */
 
/* ====================  Bit definition for CMDCNTR0 register  ====================== */
#define DDR_CMDCNTR0_CNT                  ((uint32_t)0xFFFFFFFF)         /*!< The records of issued commands from channel 0 */

/* ====================  Bit definition for CMDCNTR1 register  ====================== */
#define DDR_CMDCNTR1_CNT                  ((uint32_t)0xFFFFFFFF)         /*!< The records of issued commands from channel 1 */

/* ====================  Bit definition for CMDCNTR2 register  ====================== */
#define DDR_CMDCNTR2_CNT                  ((uint32_t)0xFFFFFFFF)         /*!< The records of issued commands from channel 2 */

/* ====================  Bit definition for CMDCNTR3 register  ====================== */
#define DDR_CMDCNTR3_CNT                  ((uint32_t)0xFFFFFFFF)         /*!< The records of issued commands from channel 3 */

/* ====================  Bit definition for AHBRPRER1 register  ====================== */
#define DDR_AHBRPRER1_CH0_PREF_VALUE              ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH0_LIMITED_PREF            ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH1_PREF_VALUE              ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH1_LIMITED_PREF             ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH2_PREF_VALUE               ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH2_LIMITED_PREF             ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH3_PREF_VALUE               ((uint32_t)0x00000000) /*!<    */
#define DDR_AHBRPRER1_CH3_LIMITED_PREF             ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for INITWCR1 register  ====================== */
#define DDR_INITWCR1                               ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for INITWCR2 register  ====================== */
#define DDR_INITWCR2                               ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for QOSCR register  ====================== */
#define DDR_QOSCR_QOS_EN                           ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCR_PERIOD_MODE                      ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCR_INDEP_RW_EN                      ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for QOSCNTRA register  ====================== */
#define DDR_QOSCNTRA_CH0_CMD_CNT                  ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRA_CH1_CMD_CNT                  ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRA_CH2_CMD_CNT                   ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRA_CH3_CMD_CNT                   ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for QOSCNTRC register  ====================== */
#define DDR_QOSCNTRC_CH0_CMD_CNT_W                ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRC_CH1_CMD_CNT_W                ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRC_CH2_CMD_CNT_W                 ((uint32_t)0x00000000) /*!<    */
#define DDR_QOSCNTRC_CH3_CMD_CNT_W                 ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for CHARBRB register  ====================== */
#define DDR_CHARBRB_CH_HI_PRIOR_W                 ((uint32_t)0x00000000) /*!<    */
#define DDR_CHARBRB_BST_ORI_ARB_W                 ((uint32_t)0x00000000) /*!<    */
#define DDR_CHARBRB_GRP_GRANT_CNT_H                ((uint32_t)0x00000000) /*!<    */
#define DDR_CHARBRB_GRP_GRANT_CNT_W                ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for CHGNTRC register  ====================== */
#define DDR_CHGNTRC_ARB_CNT0_W                    ((uint32_t)0x00000000) /*!<    */
#define DDR_CHGNTRC_ARB_CNT1_W                    ((uint32_t)0x00000000) /*!<    */
#define DDR_CHGNTRC_ARB_CNT2_W                     ((uint32_t)0x00000000) /*!<    */
#define DDR_CHGNTRC_ARB_CNT3_W                     ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for LP2MRA register  ====================== */
#define DDR_LP2MRA_MR1                            ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRA_MR2                            ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRA_MR3                             ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for LP2MRB register  ====================== */
#define DDR_LP2MRB_MR9                             ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRB_MR10                            ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for LP2MRC register  ====================== */
#define DDR_LP2MRC_MR16                           ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRC_MR17                           ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for LP2MRD register  ====================== */
#define DDR_LP2MRD_MR41                           ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRD_MR42                           ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRD_MR48                            ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for LP2MRE register  ====================== */
#define DDR_LP2MRE_MR63                            ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for LP2MRCR register  ====================== */
#define DDR_LP2MRCR_MR_CMD                        ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRCR_MR_SEL                        ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRCR_RANK_SEL                       ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRCR_MRR_BYTE_SEL                   ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for LP2MRVR register  ====================== */
#define DDR_LP2MRVR_MRR_VALUE                     ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2MRVR_MRR_VALID                      ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for LP2ADLR register  ====================== */
#define DDR_LP2ADLR_WL_NORMAL                      ((uint32_t)0x00000000) /*!<    */
#define DDR_LP2ADLR_RL_NORMAL                      ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for LP2WCR1 register  ====================== */
#define DDR_LP2WCR1                                ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for LP2WCR2 register  ====================== */
#define DDR_LP2WCR2                                ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for REARBDISR register  ====================== */
#define DDR_REARBDISR_CH0_ARBDISCNT               ((uint32_t)0x00000000) /*!<    */
#define DDR_REARBDISR_CH1_ARBDISCNT               ((uint32_t)0x00000000) /*!<    */
#define DDR_REARBDISR_CH2_ARBDISCNT               ((uint32_t)0x00000000) /*!<    */
#define DDR_REARBDISR_CH3_ARBDISCNT                ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for PHYRDTFR register  ====================== */
#define DDR_PHYRDTFR_BYTE0_DLSEL_RD_FALL          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYRDTFR_BYTE1_DLSEL_RD_FALL          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYRDTFR_BYTE2_DLSEL_RD_FALL          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYRDTFR_BYTE3_DLSEL_RD_FALL           ((uint32_t)0x00000000) /*!<    */
 
/* ====================  Bit definition for PHYMISCR2 register  ====================== */
#define DDR_PHYMISCR2_RONMD_CMD                   ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_RONMD_CK                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_RONMD_DQ                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_RONMD_DQS                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_EYE_RDLVL                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_RDLVL_GATE                   ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_CMD_DLSEL                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_ODT_MODE_WR                  ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYMISCR2_ODT_MODE_RD                  ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for EFIFOCR register  ====================== */
#define DDR_EFIFOCR_CMD_SYNC_POS                   ((uint32_t)0x00000000) /*!<    */
#define DDR_EFIFOCR_READ_SYNC_POS                  ((uint32_t)0x00000000) /*!<    */
#define DDR_EFIFOCR_AUTO_RST_SRF                   ((uint32_t)0x00000000) /*!<    */
#define DDR_EFIFOCR_EFIFO_RST                      ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for B8PHYCR register  ====================== */
#define DDR_B8PHYCR_MSDLY                         ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_RL_HW_DISABLE                 ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_WL_HW_DISABLE                 ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_DQS_SEL                       ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_DQS_SEL_WR                    ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_PDLSET                        ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_WL_PASS                        ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_DLSEL_RD                       ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_DLSEL_RD_FALL                  ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_BLSEL_WR                       ((uint32_t)0x00000000) /*!<    */
#define DDR_B8PHYCR_RL_PASS                        ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCCTRLR register  ====================== */
#define DDR_ECCCTRLR_ECC_ENABLE                   ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_FORCE_ERR                    ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_RMW_RDATA_ECC_DISABLE        ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_CH0_RMW_LOCKED               ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_CH1_RMW_LOCKED               ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_CH2_RMW_LOCKED                ((uint32_t)0x00000000) /*!<    */
#define DDR_ECCCTRLR_CH3_RMW_LOCKED                ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCINTCR register  ====================== */
#define DDR_ECCINTCR                               ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCCHR register  ====================== */
#define DDR_ECCCHR                                 ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCEAR register  ====================== */
#define DDR_ECCEAR                                 ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCEBPLR register  ====================== */
#define DDR_ECCEBPLR                               ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCEBPHR register  ====================== */
#define DDR_ECCEBPHR                               ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCERR1CNTR register  ====================== */
#define DDR_ECCERR1CNTR                            ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for ECCERR2CNTR register  ====================== */
#define DDR_ECCERR2CNTR                            ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for PHYCFG0 register  ====================== */
#define DDR_PHYCFG0_HW_SRF_REQ                     ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CH0_HIP                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CH1_HIP                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CH2_HIP                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CH3_HIP                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CKTREE_DELAY                             ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CKTREE_SKEW                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_DUTYSEL                            ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_SIO                                ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_DLLPDN                             ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_DLLFRANGE                         ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_CONUPDATE                          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_LEAKAGE0                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_LEAKAGE1                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_LEAKAGE2                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_LEAKAGE3                        ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG0_LEAKAGE4                        ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for PHYCFG1 register  ====================== */
#define DDR_PHYCFG1_BYONE                            ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_DDR3                             ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_MDDR                              ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_CLK_EN                            ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_VREF_SEL                         ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_IO15V                             ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_DSRONB                           ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_LPDDR2                                  ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG1_SELFBIAS                          ((uint32_t)0x00000000) /*!<    */

/* ====================  Bit definition for PHYCFG2 register  ====================== */
#define DDR_PHYCFG3_CKTREE_DELAY4                     ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CKTREE_SKEW4                      ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CLK_EN0                          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CLK_EN1                          ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CLK_EN2                           ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CLK_EN3                           ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_CLK_EN4                           ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_PLLPDN                            ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG3_PLLRESETN                         ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_DELAY0                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_SKEW0                     ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_DELAY1                    ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_SKEW1                      ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_DELAY2                     ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_SKEW2                      ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_DELAY3                      ((uint32_t)0x00000000) /*!<    */
#define DDR_PHYCFG2_CKTREE_SKEW3                       ((uint32_t)0x00000000) /*!<    */

/* =========================================================================================================================== */
/* ================                            Flexible Memory Controller                                    ================= */
/* =========================================================================================================================== */
/* ====================  Bits definition for DMA_SxCNDTR register  ====================== */
#define DMA_SxCTR_EN                           ((uint32_t)0x00010000)

/* =========================================================================================================================== */
/* ================                           Flex Memory Cotroller                                          ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for SMC_AR register =================== */
#define  FMC_AR_ADDRESS                 ((uint32_t)0xFFFFFFFF)            /*!< ADDRESS[31:0]: Address */

/* ====================== Bit definition for FMC_CCR register =================== */
#define FMC_CCR_CONTI_READ_EN           ((uint32_t)0x10000000)            /*!< Continuous Mode Enable */
#define FMC_CCR_INSTR_LEN               ((uint32_t)0x03000000)            /*!< Instruction Length */
#define FMC_CCR_INSTR_LEN_1             ((uint32_t)0x01000000)            /*!< Instruction Length: 1 Byte */
#define FMC_CCR_INSTR_LEN_2             ((uint32_t)0x02000000)            /*!< Instruction Length: 2 Byte */
#define FMC_DCY                         ((uint32_t)0x00FF0000)            /*!< Dummy[2:0]: Address Size */
#define FMC_CCR_ADSIZE                  ((uint32_t)0x00000007)            /*!< ADSIZE[2:0]: Address Size */
#define FMC_CCR_ADSIZE_1                ((uint32_t)0x00000001)            /*!< Bit 0 */
#define FMC_CCR_ADSIZE_2                ((uint32_t)0x00000002)            /*!< Bit 1 */
#define FMC_CCR_ADSIZE_3                ((uint32_t)0x00000003)            /*!< Bit 2 */
#define FMC_CCR_ADSIZE_4                ((uint32_t)0x00000004)            /*!< Bit 2 */

/* ====================== Bit definition for FMC_DLR register =================== */
#define   FMC_DLR                       ((uint32_t)0xFFFFFFFF)               /*!< DL[31:0]: Data Length */
/* ====================== Bit definition for FMC_CCR2 register =================== */
#define FMC_CCR2_INSTRUCTION            ((uint32_t)0xFF000000)            /*!< INSTRUCTION[7:0]: Instruction */
#define FMC_CCR2_CRM_INSTRUCTION        ((uint32_t)0xFF000000)            /*!< Continuous Read Mode Instruction[7:0]: Instruction */

#define FMC_CCR2_IO_MODE_EN             ((uint32_t)0x00000400)            /*!< IO Mode Enable */
#define FMC_CCR2_CS                     ((uint32_t)0x00000300)            /*!< Chip Select[1:0]: CS */
#define FMC_CCR2_OP_MODE                ((uint32_t)0x000000E0)            /*!< SPI Operate Mode Mode[3:0]: Mode */
#define FMC_CCR2_OP_MODE_111            ((uint32_t)0x00000000)            /*!< Mode: 1-1-1 */
#define FMC_CCR2_OP_MODE_114            ((uint32_t)0x00000040)            /*!< Mode: 1-1-4 */
#define FMC_CCR2_OP_MODE_144            ((uint32_t)0x00000060)            /*!< Mode: 1-4-4 */
#define FMC_CCR2_OP_MODE_444            ((uint32_t)0x00000080)            /*!< Mode: 4-4-4 */
#define FMC_CCR2_OP_MODE_118            ((uint32_t)0x000000A0)            /*!< Mode: 1-1-8 */
#define FMC_CCR2_OP_MODE_188            ((uint32_t)0x000000C0)            /*!< Mode: 1-8-8 */
#define FMC_CCR2_OP_MODE_888            ((uint32_t)0x000000E0)            /*!< Mode: 8-8-8 */
#define FMC_CCR2_DDRM_EN                ((uint32_t)0x00000010)            /*!< DTR Enable */
#define FMC_CCR2_READ_STATUS_BY_SW      ((uint32_t)0x00000008)            /*!< Read Status By SW */
#define FMC_CCR2_READ_STATUS_EN         ((uint32_t)0x00000004)            /*!< Read Status Enable */
#define FMC_CCR2_WRITE_EN               ((uint32_t)0x00000002)            /*!< Write Enable */

/* ====================== Bit definition for FMC_CR register =================== */
#define FMC_CR_PORT_SELECT              ((uint32_t)0x00100000)            /*!< Port selection */
#define FMC_CR_BUSY_BIT_STS             ((uint32_t)0x000E0000)            /*!< BUSY_BIT_STS[2:0]: BusyBitStatus*/
#define FMC_CR_DTR_MODE_SELECT          ((uint32_t)0x00000200)            /*!< Psram DTR mode OB/OC interface select */
#define FMC_CR_ABORT                    ((uint32_t)0x00000100)            /*!< Abort request */
#define FMC_CR_XPORT_STS                ((uint32_t)0x00000080)            /*!< XIP port idle status */
#define FMC_CR_DQSM_EN                  ((uint32_t)0x00000040)            /*!< DQS/DM enable */
#define FMC_CR_CLK_EDGE                 ((uint32_t)0x00000020)            /*!< Clock edge latch */
#define FMC_CR_DEV_TYPE                 ((uint32_t)0x0000000C)            /*!< DEV_TYPE[1:0]: Device type */

/* ====================== Bit definition for FMC_ATCR register =================== */
#define FMC_ATCR_DLL_POWER_DOWN         ((uint32_t)0x00000800)            /*!< DLL power down */
#define FMC_ATCR_DLL_SELECT             ((uint32_t)0x00000700)            /*!< DLL_SELECT[2:0]: DLL Select */
#define FMC_ATCR_CS_DELAY               ((uint32_t)0x0000000F)            /*!< CS_DELAY[3:0]: CS delay */

/* ====================== Bit definition for FMC_SR register =================== */
#define FMC_SR_TXFIFO_RDY               ((uint32_t)0x00000001)            /*!< Transfer Tx FIFO Ready     */
#define FMC_SR_RXFIFO_RDY               ((uint32_t)0x00000002)            /*!< Transfer Rx FIFO Ready     */

/* ====================== Bit definition for FMC_ICR register =================== */
#define FMC_ICR_RX_FIFO_TRIGGER         ((uint32_t)0x00003000)            /*!< RX_FIFO_TRIGGER [1:0]: RxFIFO threshold*/
#define FMC_ICR_TX_FIFO_TRIGGER         ((uint32_t)0x00000300)            /*!< TX_FIFO_TRIGGER [1:0]: TxFIFO threshold*/
#define FMC_ICR_XIP_WERR_INTR_EN        ((uint32_t)0x00000004)            /*!< XIP write data error interrupt enable */
#define FMC_ICR_CMD_CMPLT_INTR_EN       ((uint32_t)0x00000002)            /*!< Command complete interrupt enable */
#define FMC_ICR_DMAEN                   ((uint32_t)0x00000001)            /*!< DMA handshake enable */

/* ====================== Bit definition for FMC_ISR register =================== */
#define FMC_ISR_XIPW_EF                 ((uint32_t)0x00000002)             /*!< XIP Write Transfer Error Flag     */
#define FMC_ISR_TCF                     ((uint32_t)0x00000001)             /*!< Transfer Complete Flag  */

/* ====================== Bit definition for FMC_SPISR register =================== */
#define FMC_SPISR                       ((uint32_t)0x000000FF)             /*!< Status of norflash  */

/* ====================== Bit definition for FMC_SIZE register =================== */
#define FMC_SIZE                        ((uint32_t)0xFFFFFFFF)             /*!< flash/psram size */

/* ====================== Bit definition for FMC_XIPCMD register =================== */
#define FMC_XIP_RDTR                 ((uint32_t)0x80000000)             /*!< XIP read data DTR mode */
#define FMC_XIP_CS                   ((uint32_t)0x60000000)             /*!< XIPCMD_CS[1:0] */
#define FMC_XIP_IO_MODE_EN           ((uint32_t)0x10000000)             /*!< XIP IO mode enable */
#define FMC_XIP_IO_MODE_INSTRUCTION  ((uint32_t)0x0FF00000)             /*!< IO_MODE_INSTRUCTION[7:0]: XIP IO mode code */
#define FMC_XIP_RD_INSTRUCTION       ((uint32_t)0x000FF000)             /*!< RD_INSTRUCTION[7:0]: XIP read data Instruction code */
#define FMC_XIP_ADDR_LEN_4BYTE       ((uint32_t)0x00000800)             /*!< SPI address length for XIP port */
#define FMC_XIP_RD_MODE              ((uint32_t)0x00000700)             /*!< XIPCMD_RD_MODE[2:0]: XIP SPI read data operate mode */
#define FMC_XIP_DUMMY_CYCLE          ((uint32_t)0x000000FF)             /*!< XIPCMD_DUMMY_CYCLE[7:0]: Second dummy state cycle for XIP port */

/* ====================== Bit definition for FMC_XIPPFO register =================== */
#define FMC_XIPPFO_RSTS_DUMMY           ((uint32_t)0x0FF00000)             /*!< XIPPFO_RSTS_DUMMY[7:0]: XIP channel read status dummy cycle */
#define FMC_XIPPFO_WEN_INSTRUCTION      ((uint32_t)0x000FF000)             /*!< XIPPFO_WEN_INSTRUCTION[7:0]: XIP channel write enable instruction code */
#define FMC_XIPPFO_RSTS_INSTRUCTION     ((uint32_t)0x00000FF0)            /*!< XIPPFO_RSTS_INTRUCTION[7:0]: XIP channel read status instruction code */
#define FMC_XIPPFO_WE                   ((uint32_t)0x00000008)             /*!< XIP channel write data allow */
#define FMC_XIPPFO_BYPASS_CACHE         ((uint32_t)0x00000001)             /*!< Bypass cache function */

/* ====================== Bit definition for FMC_XIPWCMD register =================== */
#define FMC_XIPWCMD_DTR_EN              ((uint32_t)0x00080000)             /*!< XIP write data DTR mode */
#define FMC_XIPWCMD_WD_MODE             ((uint32_t)0x00070000)             /*!< XIPWCMD_WD_MODE[2:0] XIP SPI write data operate mode */
#define FMC_XIPWCMD_WD_DUMMY            ((uint32_t)0x0000FF00)             /*!< XIPWCMD_WD_DUMMY[7:0] XIP channel write data dummy cycle */
#define FMC_XIPWCMD_WD_INSTRUCTION      ((uint32_t)0x000000FF)             /*!< XIPWCMD_WD_INSTRUCTION[7:0] XIP channel write data instruction code */

/* ====================== Bit definition for FMC_FEATURE register =================== */
#define FMC_FEATURE_RXFIFO_DEPTH        ((uint32_t)0x0003FE00)             /*!< FEATURE_RXFIFO_DEPTH[8:0]: RXFIFO depth */
#define FMC_FEATURE_TXFIFO_DEPTH        ((uint32_t)0x000001FF)             /*!< FEATURE_TXFIFO_DEPTH[8:0]: TXFIFO depth */

/* ====================== Bit definition for FMC_DR register =================== */
#define FMC_DR_DATA                     ((uint32_t)0xFFFFFFFF)              /*!< DATA[31:0]: Data */

/* ====================== Bit definition for PSRAM init register =================== */
#define FMC_PSRAM_INIT_ATCR             ((uint32_t)0x00000034)             /* !< ATCR value for PSRAM initial */
#define FMC_PSRAM_INIT_ICR              ((uint32_t)0x00000000)             /* !< ICR value for PSRAM initial */
#define FMC_PSRAM_INIT_SPIFSR           ((uint32_t)0x02000000)             /* !< Memory size register value for PSRAM initial */
#define FMC_PSRAM_INIT_XIPCMD           ((uint32_t)0x800A0F0F)
#define FMC_PSRAM_INIT_XIPPFO           ((uint32_t)0x00000009)
#define FMC_PSRAM_INIT_XIPWCMD          ((uint32_t)0x000F0F20)
#define FMC_PSRAM_INIT_CR0              ((uint32_t)0x000002D4)

#define FMC_PSRAM_INIT0_CMD0            ((uint32_t)0x00040000)
#define FMC_PSRAM_INIT0_CMD1            ((uint32_t)0x01000004)
#define FMC_PSRAM_INIT0_CMD2            ((uint32_t)0x00000002)
#define FMC_PSRAM_INIT0_CMD3            ((uint32_t)0x400000FA)
#define FMC_PSRAM_INIT0_DATA0           ((uint8_t)0xF0)
#define FMC_PSRAM_INIT0_DATA1           ((uint8_t)0x5A)

#define FMC_PSRAM_INIT_RCMD0            ((uint32_t)0x00040000)
#define FMC_PSRAM_INIT_RCMD1            ((uint32_t)0x01100004)
#define FMC_PSRAM_INIT_RCMD2            ((uint32_t)0x00000002)
#define FMC_PSRAM_INIT_RCMD3            ((uint32_t)0xC00000F8)

#define FMC_PSRAM_INIT_CR1              ((uint32_t)0x001002D4)

/* ====================== Bit definition for norflash init register =================== */
#define FMC_NOR_INIT_ATCR               ((uint32_t)0x0000103F)            /* !< ATCR value for PSRAM initial */
#define FMC_NOR_INIT_ICR                ((uint32_t)0x00000000)            /* !< ICR value for PSRAM initial */
#define FMC_NOR_INIT_SPIFSR             ((uint32_t)0x02000000)            /* !< Memory size register value for PSRAM initial */
#define FMC_NOR_INIT_XIPCMD             ((uint32_t)0x100EB406)
#define FMC_NOR_INIT_XIPPFO             ((uint32_t)0x00006050)
#define FMC_NOR_INIT_XIPWCMD            ((uint32_t)0x00000000)
#define FMC_NOR_INIT_CR0                ((uint32_t)0x00000090)

/* =========================================================================================================================== */
/* ================                                           GMAC                                           ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for CTRL register ====================== */

#define GMAC_CTRL_SW_RST           ((uint32_t)0x80000000) // (1 << 31)
#define GMAC_CTRL_CTAG_RM          ((uint32_t)0x10000000) // (1 << 28)
#define GMAC_CTRL_STAG_RM          ((uint32_t)0x08000000) // (1 << 27)
#define GMAC_CTRL_FULLDUP          ((uint32_t)0x04000000) // (1 << 26)
#define GMAC_CTRL_SPEED            ((uint32_t)0x03000000)
#define GMAC_CTRL_IFG              ((uint32_t)0x00800000) // (1 << 23)
#define GMAC_CTRL_IFG_CNT          ((uint32_t)0x00700000) // (0x7 << 20)
#define GMAC_CTRL_LOOPBACK         ((uint32_t)0x00080000) // (1 << 19)
#define GMAC_CTRL_PTP_EN           ((uint32_t)0x00040000) // (1 << 18)
#define GMAC_CTRL_TX_PAD           ((uint32_t)0x00020000) // (1 << 17)
#define GMAC_CTRL_APPEND_CRC       ((uint32_t)0x00008000) // (1 << 15)
#define GMAC_CTRL_JUMBO_LONG       ((uint32_t)0x00002000) // (1 << 13)
#define GMAC_CTRL_RX_RUNT          ((uint32_t)0x00001000) // (1 << 12)
#define GMAC_CTRL_RX_ALL_BCST_EN   ((uint32_t)0x00000800) // (1 << 11)
#define GMAC_CTRL_RX_ALL_MCST_EN   ((uint32_t)0x00000400) // (1 << 10)
#define GMAC_CTRL_RX_HASH_MCAST_EN ((uint32_t)0x00000200) // (1 << 9)
#define GMAC_CTRL_L4_FLT_EN        ((uint32_t)0x00000080) // (1 << 7)
#define GMAC_CTRL_L3_FLT_EN        ((uint32_t)0x00000040) // (1 << 6)
#define GMAC_CTRL_VLAN_FLT_EN      ((uint32_t)0x00000020) // (1 << 5)
#define GMAC_CTRL_L2_FLT_EN        ((uint32_t)0x00000010) // (1 << 4)
#define GMAC_CTRL_RXMAC_EN         ((uint32_t)0x00000008) // (1 << 3)
#define GMAC_CTRL_TXMAC_EN         ((uint32_t)0x00000004) // (1 << 2)
#define GMAC_CTRL_RXDMA_EN         ((uint32_t)0x00000002) // (1 << 1)
#define GMAC_CTRL_TXDMA_EN         ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for FDPX register ====================== */
#define GMAC_FDPX_PAUSE_TIME     ((uint32_t)0xffff0000)
#define GMAC_FDPX_LOW_THR        ((uint32_t)0x0000FE00) // (15~9)
#define GMAC_FDPX_HIGH_THR       ((uint32_t)0x000001FC) // (8~2)
#define GMAC_FDPX_TX_PAUSE_FRAME ((uint32_t)0x00000002) // (1 << 1)
#define GMAC_FDPX_EN             ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for HDPX register ====================== */
#define GMAC_HDPX_LOW_THR     ((uint32_t)0x00007F00) // (8)
#define GMAC_HDPX_JAM_LEN     ((uint32_t)0x000000f0)
#define GMAC_HDPX_PATTERN_ALL ((uint32_t)0x00000002) // (1 << 1)
#define GMAC_HDPX_EN          ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for DMAFIFOS register ====================== */
#define GMAC_DMA_FIFO_STS_TX_FIFO_EMPTY ((uint32_t)0x08000000) // (1 << 27)
#define GMAC_DMA_FIFO_STS_RX_FIFO_EMPTY ((uint32_t)0x04000000) // (1 << 26)

/* ====================== Bit definition for WOLCR register ====================== */
#define GMAC_WOLCR_SW_PDNPHY ((uint32_t)0x00040000) // (1 << 18)

/* ====================== Bit definition for PTPTMR1 register ====================== */
// #define GMAC_PTP_TMR1(x) ((x & 0x3fffffff) << 0)

/* ====================== Bit definition for PTPADJ register ====================== */
#define GMAC_PTP_ADJ_ADD ((uint32_t)0x80000000) // (1 << 31)


/* ====================== Bit definition for PHYIF register ====================== */
#define GMAC_PHY_IF_GMII  ((uint32_t)0x00000000)
#define GMAC_PHY_IF_RGMII ((uint32_t)0x00000002)

/* ====================== Bit definition for PHYCR register ====================== */
#define GMAC_MDIO_SOF     ((uint32_t)0x00000001)
#define GMAC_MDIO_EXT_SOF ((uint32_t)0x00000000)
#define GMAC_MDIO_OP_RD   ((uint32_t)0x00000002)
#define GMAC_MDIO_OP_WR   ((uint32_t)0x00000001)
#define GMAC_PHYCR_PHYWR  ((uint32_t)0x08000000) // (1 << 27)
#define GMAC_PHYCR_PHYRD  ((uint32_t)0x04000000) // (1 << 26)
#define GMAC_PHYCR_REGAD  ((uint32_t)0x03e00000) // ((x & 0x1f) << 21)
#define GMAC_PHYCR_PHYAD  ((uint32_t)0x001f0000) // ((x & 0x1f) << 16)
#define GMAC_PHYCR_OP     ((uint32_t)0x00300000) // ((x & 0x3) << 14)
#define GMAC_PHYCR_SOF    ((uint32_t)0x000c0000) // ((x & 0x3) << 12)
#define GMAC_PHYCR_CYCTHR ((uint32_t)0x000000ff) // ((x & 0xff) << 0)

/* ====================== Bit definition for PHYDATA register ====================== */
#define GMAC_PHYDATA_RDATA ((uint32_t)0xffff0000)
#define GMAC_PHYDATA_WDATA ((uint32_t)0x0000ffff)

/* ====================== Bit definition for MFCR register ====================== */
#define GMAC_L2_REDR_EN ((uint32_t)0x00400000) // (1 << 22)
#define GMAC_L2_FLT_INV ((uint32_t)0x00020000) // (1 << 17)
#define GMAC_L2_FLT_DA  ((uint32_t)0x00010000) // (1 << 16)

/* ====================== Bit definition for RSSCR register ====================== */
#define GMAC_RSS_EN ((uint32_t)0x00000001)

/* ====================== Bit definition for TQWBCR register ====================== */
#define GMAC_TQ_WB_THR     ((uint32_t)0x000f0000) // ((x & 0xf) << 16)
#define GMAC_TQ_WB_TIMEOUT ((uint32_t)0x0000ffff) // ((x & 0xffff) << 0)

/* ====================== Bit definition for RQWBCR register ====================== */
#define GMAC_RQ_WB_THR     ((uint32_t)0x000f0000) // ((x & 0xf) << 16)
#define GMAC_RQ_WB_TIMEOUT ((uint32_t)0x0000ffff) // ((x & 0xffff) << 0)

/* ====================== Bit definition for QCR register ====================== */
#define GMAC_QPAIR_CTRL_RX_EN ((uint32_t)0x00000010) // (1 << 4)
#define GMAC_QPAIR_CTRL_TX_EN ((uint32_t)0x00000008) // (1 << 3)

/* ====================== Bit definition for TXITC register ====================== */
#define GMAC_INT_UNIT_1         ((uint32_t)0x00000000)
#define GMAC_INT_UNIT_4         ((uint32_t)0x00000001)
#define GMAC_INT_UNIT_16        ((uint32_t)0x00000002)
#define GMAC_INT_UNIT_64        ((uint32_t)0x00000003)
#define GMAC_TXINT_CYC_BIG_UNIT ((uint32_t)0x00010000) // (1 << 16)
#define GMAC_TXINT_CYC_CNT      ((uint32_t)0x0000ff00) // ((x & 0xff) << 8)
#define GMAC_TXINT_THR          ((uint32_t)0x00000070) // ((x & 0x7) << 4)
#define GMAC_TXINT_UNIT         ((uint32_t)0x00000003) // ((x & 0x3) << 0)

/* ====================== Bit definition for RXITC register ====================== */
#define GMAC_RXINT_RST          ((uint32_t)0x0ff00000) // ((x & 0xff) << 20)
#define GMAC_RXINT_CYC_BIG_UNIT ((uint32_t)0x00010000) // (1 << 16)
#define GMAC_RXINT_CYC_CNT      ((uint32_t)0x0000ff00) // ((x & 0xff) << 8)
#define GMAC_RXINT_THR          ((uint32_t)0x00000070) // ((x & 0x7) << 4)
#define GMAC_RXINT_UNIT         ((uint32_t)0x00000003) // ((x & 0x3) << 0)

/* ====================== Bit definition for RDSR register ====================== */
#define GMAC_RX_DESC_SZ  ((uint32_t)0x003c0000) // ((x & 0xf) << 12)
#define GMAC_RX_DESC_CNT ((uint32_t)0x00000fff) // ((x & 0xfff) << 0)

/* ====================== Bit definition for RXR_BADR_L register ====================== */
#define GMAC_RX_RING_BASE_L ((uint32_t)0xffffffff) // (((uint64_t)(x)) & 0xffffffff)

/* ====================== Bit definition for RXR_BADR_H register ====================== */
#define GMAC_RX_RING_BASE_H ((uint32_t)0x0000ffff) // ((uint32_t)((uint64_t)(x) >> 32) & 0xffff)

/* ====================== Bit definition for TDSR register ====================== */
#define GMAC_TX_DESC_SZ  ((uint32_t)0x003c0000) // ((x & 0xf) << 12)
#define GMAC_TX_DESC_CNT ((uint32_t)0x00000fff) // ((x & 0xfff) << 0)

/* ====================== Bit definition for TXR_BADR_L register ====================== */
#define GMAC_TX_RING_BASE_L ((uint32_t)0xffffffff) // (((uint64_t)(x)) & 0xffffffff)

/* ====================== Bit definition for TXR_BADR_H register ====================== */
#define GMAC_TX_RING_BASE_H ((uint32_t)0x0000ffff) // ((uint32_t)((uint64_t)(x) >> 32) & 0xffff)

/* ====================== Bit definition for EEECTRL register ====================== */
#define GMAC_EEE_CTRL_TX_LPI ((uint32_t)0x00010000) // (1 << 16)
#define GMAC_EEE_CTRL_WU_CNT ((uint32_t)(0x0000ffff))

/* ====================== Bit definition for TQBCR register ====================== */
#define GMAC_TQ_BUF_CTRL_TIMEOUT ((uint32_t)0xffff0000) // ((x & 0xffff) << 16)
#define GMAC_TQ_BUF_CTRL_DES_THR ((uint32_t)0x0000f000) // ((x & 0xf) << 12)
#define GMAC_TQ_BUF_CTRL_BUF_THR ((uint32_t)0x00000f00) // ((x & 0xf) << 8)
#define GMAC_TQ_BUF_CTRL_BUF_SZ  ((uint32_t)0x000000ff) // ((x & 0xff) << 0)

/* ====================== Bit definition for RQBCR register ====================== */
#define GMAC_RQ_BUF_CTRL_TIMEOUT ((uint32_t)0xffff0000) // ((x & 0xffff) << 16)
#define GMAC_RQ_BUF_CTRL_DES_THR ((uint32_t)0x0000f000) // ((x & 0xf) << 12)
#define GMAC_RQ_BUF_CTRL_BUF_THR ((uint32_t)0x00000f00) // ((x & 0xf) << 8)
#define GMAC_RQ_BUF_CTRL_BUF_SZ  ((uint32_t)0x000000ff) // ((x & 0xff) << 0)

/* TXDES3 */
#define GMAC_TXDES3_TXBUF_BADRH ((uint32_t)0x0000ffff) // ((uint32_t)(((uint64_t)(x)) >> 32) & 0xffff)

/* TXDES4 */
#define GMAC_TXDES4_TXBUF_BADRL ((uint32_t)0xffffffff) // (((uint64_t)(x)) & 0xffffffff)

/* RXDES2 */
#define GMAC_RXDES2_RXBUF_BADRH ((uint32_t)0x0000ffff)

/* RXDES3 */
#define GMAC_RXDES3_RXBUF_BADRL ((uint32_t)0xffffffff)

/* =========================================================================================================================== */
/* ================                            General Purpose I/O                                           ================= */
/* =========================================================================================================================== */
/* ============================== Bit definition for GPIO_OUT register =================================== */
/*!< GPIO Output value */
#define GPIO_OUT                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO output value */

/* ============================== Bit definition for GPIO_IN register =================================== */
/*!< GPIO Input Value */
#define GPIO_IN                           ((uint32_t)0xFFFFFFFF)        /*!< GPIO input value */

/* ============================== Bit definition for GPIO_DIR register =================================== */
/*!< GPIO Direction set */
#define GPIO_DIR                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Direction set */

/* ============================== Bit definition for GPIO_SET register =================================== */
/*!< GPIO Data Set */
#define GPIO_SET                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Data Set */

/* ============================== Bit definition for GPIO_CLR register =================================== */
/*!< GPIO Data Clear */
#define GPIO_CLR                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Data clear */

/* ============================== Bit definition for GPIO_IER register =================================== */
/*!< GPIO Interrput enable */
#define GPIO_IER                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Interrput enable */

/* ============================== Bit definition for GPIO_IRS register =================================== */
/*!< GPIO Interrput raw state */
#define GPIO_IRS                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Interrput raw state */

/* ============================== Bit definition for GPIO_IMS register =================================== */
/*!< GPIO Interrput masked state */
#define GPIO_IMS                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Interrput masked state */

/* ============================== Bit definition for GPIO_IM register =================================== */
/*!< GPIO Interrput masked */
#define GPIO_IM                           ((uint32_t)0xFFFFFFFF)        /*!< GPIO Interrput masked */

/* ============================== Bit definition for GPIO_ICLR register =================================== */
/*!< GPIO Interrput clear */
#define GPIO_ICLR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIO Interrput clear */

/* ============================== Bit definition for GPIO_TMR register =================================== */
/*!< GPIO Trigger mode configuration */
#define GPIO_TMR                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Trigger mode configuration */

/* ============================== Bit definition for GPIO_TER register =================================== */
/*!< GPIO Trigger edge configuration */
#define GPIO_TER                          ((uint32_t)0xFFFFFFFF)        /*!< GPIO Trigger edge configuration */

/* ============================== Bit definition for GPIO_TRFR register =================================== */
/*!< GPIO Trigger rise or fail configuration */
#define GPIO_TRFR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIO Trigger rise or fail configuration */

/* ============================== Bit definition for GPIO_DBCR register =================================== */
/*!< GPIO Debounce configuration */
#define GPIO_DBCR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIO Debounce configuration */

/* ============================== Bit definition for GPIO_DBCCNT register =================================== */
/*!< GPIO Debounce Count */
#define GPIO_DBCCNT                       ((uint32_t)0xFFFFFFFF)        /*!< GPIO Debounce Count*/


/* ============================== Bit definition for GPIOA_AF0 register =================================== */
/*!< GPIOA Alternate Function group0 Configuration  */
#define GPIOA_AF0R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group0 Configuration */

#define GPIOA_AF0R_0                      ((uint32_t)0x00000007)
#define GPIOA_AF0R_1                      ((uint32_t)0x00000038)
#define GPIOA_AF0R_2                      ((uint32_t)0x000001C0)
#define GPIOA_AF0R_3                      ((uint32_t)0x00000E00)
#define GPIOA_AF0R_4                      ((uint32_t)0x00007000)
#define GPIOA_AF0R_5                      ((uint32_t)0x00038000)
#define GPIOA_AF0R_6                      ((uint32_t)0x001C0000)
#define GPIOA_AF0R_7                      ((uint32_t)0x00E00000)
#define GPIOA_AF0R_8                      ((uint32_t)0x07000000)
#define GPIOA_AF0R_9                      ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOA_AF1 register =================================== */
/*!< GPIOA Alternate Function group1 Configuration  */
#define GPIOA_AF1R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group1 Configuration */

#define GPIOA_AF1R_10                     ((uint32_t)0x00000007)
#define GPIOA_AF1R_11                     ((uint32_t)0x00000038)
#define GPIOA_AF1R_12                     ((uint32_t)0x000001C0)
#define GPIOA_AF1R_13                     ((uint32_t)0x00000E00)
#define GPIOA_AF1R_14                     ((uint32_t)0x00007000)
#define GPIOA_AF1R_15                     ((uint32_t)0x00038000)
#define GPIOA_AF1R_16                     ((uint32_t)0x001C0000)
#define GPIOA_AF1R_17                     ((uint32_t)0x00E00000)
#define GPIOA_AF1R_18                     ((uint32_t)0x07000000)
#define GPIOA_AF1R_19                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOA_AF2 register =================================== */
/*!< GPIOA Alternate Function group2 Configuration  */
#define GPIOA_AF2R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group2 Configuration */

#define GPIOA_AF2R_20                     ((uint32_t)0x00000007)
#define GPIOA_AF2R_21                     ((uint32_t)0x00000038)
#define GPIOA_AF2R_22                     ((uint32_t)0x000001C0)
#define GPIOA_AF2R_23                     ((uint32_t)0x00000E00)
#define GPIOA_AF2R_24                     ((uint32_t)0x00007000)
#define GPIOA_AF2R_25                     ((uint32_t)0x00038000)
#define GPIOA_AF2R_26                     ((uint32_t)0x001C0000)
#define GPIOA_AF2R_27                     ((uint32_t)0x00E00000)
#define GPIOA_AF2R_28                     ((uint32_t)0x07000000)
#define GPIOA_AF2R_29                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOA_AF3 register =================================== */
/*!< GPIOA Alternate Function group3 Configuration  */
#define GPIOA_AF3R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group2 Configuration */

#define GPIOA_AF3R_30                     ((uint32_t)0x00000007)
#define GPIOA_AF3R_31                     ((uint32_t)0x00000038)


/* ============================== Bit definition for GPIOB_AF0 register =================================== */
/*!< GPIOB Alternate Function group0 Configuration  */
#define GPIOB_AF0R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Alternate Function group0 Configuration */

#define GPIOB_AF0R_0                      ((uint32_t)0x00000007)
#define GPIOB_AF0R_1                      ((uint32_t)0x00000038)
#define GPIOB_AF0R_2                      ((uint32_t)0x000001C0)
#define GPIOB_AF0R_3                      ((uint32_t)0x00000E00)
#define GPIOB_AF0R_4                      ((uint32_t)0x00007000)
#define GPIOB_AF0R_5                      ((uint32_t)0x00038000)
#define GPIOB_AF0R_6                      ((uint32_t)0x001C0000)
#define GPIOB_AF0R_7                      ((uint32_t)0x00E00000)
#define GPIOB_AF0R_8                      ((uint32_t)0x07000000)
#define GPIOB_AF0R_9                      ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOB_AF1 register =================================== */
/*!< GPIOB Alternate Function group1 Configuration  */
#define GPIOB_AF1R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group1 Configuration */

#define GPIOB_AF1R_10                     ((uint32_t)0x00000007)
#define GPIOB_AF1R_11                     ((uint32_t)0x00000038)
#define GPIOB_AF1R_12                     ((uint32_t)0x000001C0)
#define GPIOB_AF1R_13                     ((uint32_t)0x00000E00)
#define GPIOB_AF1R_14                     ((uint32_t)0x00007000)
#define GPIOB_AF1R_15                     ((uint32_t)0x00038000)
#define GPIOB_AF1R_16                     ((uint32_t)0x001C0000)
#define GPIOB_AF1R_17                     ((uint32_t)0x00E00000)
#define GPIOB_AF1R_18                     ((uint32_t)0x07000000)
#define GPIOB_AF1R_19                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOB_AF2 register =================================== */
/*!< GPIOB Alternate Function group2 Configuration  */
#define GPIOB_AF2R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Alternate Function group2 Configuration */

#define GPIOB_AF2R_20                     ((uint32_t)0x00000007)
#define GPIOB_AF2R_21                     ((uint32_t)0x00000038)
#define GPIOB_AF2R_22                     ((uint32_t)0x000001C0)
#define GPIOB_AF2R_23                     ((uint32_t)0x00000E00)
#define GPIOB_AF2R_24                     ((uint32_t)0x00007000)
#define GPIOB_AF2R_25                     ((uint32_t)0x00038000)
#define GPIOB_AF2R_26                     ((uint32_t)0x001C0000)
#define GPIOB_AF2R_27                     ((uint32_t)0x00E00000)
#define GPIOB_AF2R_28                     ((uint32_t)0x07000000)
#define GPIOB_AF2R_29                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOB_AF3 register =================================== */
/*!< GPIOB Alternate Function group3 Configuration  */
#define GPIOB_AF3R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Alternate Function group2 Configuration */

#define GPIOB_AF3R_30                     ((uint32_t)0x00000007)
#define GPIOB_AF3R_31                     ((uint32_t)0x00000038)


/* ============================== Bit definition for GPIOC_AF0 register =================================== */
/*!< GPIOC Alternate Function group0 Configuration  */
#define GPIOC_AF0R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Alternate Function group0 Configuration */

#define GPIOC_AF0R_0                      ((uint32_t)0x00000007)
#define GPIOC_AF0R_1                      ((uint32_t)0x00000038)
#define GPIOC_AF0R_2                      ((uint32_t)0x000001C0)
#define GPIOC_AF0R_3                      ((uint32_t)0x00000E00)
#define GPIOC_AF0R_4                      ((uint32_t)0x00007000)
#define GPIOC_AF0R_5                      ((uint32_t)0x00038000)
#define GPIOC_AF0R_6                      ((uint32_t)0x001C0000)
#define GPIOC_AF0R_7                      ((uint32_t)0x00E00000)
#define GPIOC_AF0R_8                      ((uint32_t)0x07000000)
#define GPIOC_AF0R_9                      ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOC_AF1 register =================================== */
/*!< GPIOC Alternate Function group1 Configuration  */
#define GPIOC_AF1R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Alternate Function group1 Configuration */

#define GPIOC_AF1R_10                     ((uint32_t)0x00000007)
#define GPIOC_AF1R_11                     ((uint32_t)0x00000038)
#define GPIOC_AF1R_12                     ((uint32_t)0x000001C0)
#define GPIOC_AF1R_13                     ((uint32_t)0x00000E00)
#define GPIOC_AF1R_14                     ((uint32_t)0x00007000)
#define GPIOC_AF1R_15                     ((uint32_t)0x00038000)
#define GPIOC_AF1R_16                     ((uint32_t)0x001C0000)
#define GPIOC_AF1R_17                     ((uint32_t)0x00E00000)
#define GPIOC_AF1R_18                     ((uint32_t)0x07000000)
#define GPIOC_AF1R_19                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOC_AF2 register =================================== */
/*!< GPIOC Alternate Function group2 Configuration  */
#define GPIOC_AF2R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Alternate Function group2 Configuration */

#define GPIOC_AF2R_20                     ((uint32_t)0x00000007)
#define GPIOC_AF2R_21                     ((uint32_t)0x00000038)
#define GPIOC_AF2R_22                     ((uint32_t)0x000001C0)
#define GPIOC_AF2R_23                     ((uint32_t)0x00000E00)
#define GPIOC_AF2R_24                     ((uint32_t)0x00007000)
#define GPIOC_AF2R_25                     ((uint32_t)0x00038000)
#define GPIOC_AF2R_26                     ((uint32_t)0x001C0000)
#define GPIOC_AF2R_27                     ((uint32_t)0x00E00000)
#define GPIOC_AF2R_28                     ((uint32_t)0x07000000)
#define GPIOC_AF2R_29                     ((uint32_t)0x38000000)

/* ============================== Bit definition for GPIOC_AF3 register =================================== */
/*!< GPIOC Alternate Function group3 Configuration  */
#define GPIOC_AF3R                        ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Alternate Function group2 Configuration */
#define GPIOC_AF3R_30                     ((uint32_t)0x00000007)
#define GPIOC_AF3R_31                     ((uint32_t)0x00000038)

/* ============================== Bit definition for GPIOA_PU register =================================== */
/*!< GPIOA Pull Up Configuration  */
#define GPIOA_PUR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Pull Up Configuration */

/* ============================== Bit definition for GPIOA_PD register =================================== */
/*!< GPIOA Pull Down Configuration  */
#define GPIOA_PDR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Pull Down Configuration */

/* ============================== Bit definition for GPIOB_PU register =================================== */
/*!< GPIOB Pull Up Configuration  */
#define GPIOB_PUR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Pull Up Configuration */

/* ============================== Bit definition for GPIOB_PD register =================================== */
/*!< GPIOB Pull Down Configuration  */
#define GPIOB_PDR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Pull Down Configuration */

/* ============================== Bit definition for GPIOC_PU register =================================== */
/*!< GPIOC Pull Up Configuration  */
#define GPIOC_PUR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Pull Up Configuration */

/* ============================== Bit definition for GPIOC_PD register =================================== */
/*!< GPIOC Pull Down Configuration  */
#define GPIOC_PDR                         ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Pull Down Configuration */

/* ============================== Bit definition for GPIOA_DRV0 register =================================== */
/*!< GPIOA driver strength sel0 Configuration  */
#define GPIOA_DRV0R                       ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Driver Strength sel0 Configuration */

/* ============================== Bit definition for GPIOA_DRV1 register =================================== */
/*!< GPIOA driver strength sel1 Configuration  */
#define GPIOA_DRVR1R                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOA Driver Strength sel1 Configuration */

/* ============================== Bit definition for GPIOB_DRV0 register =================================== */
/*!< GPIOB driver strength sel0 Configuration  */
#define GPIOB_DRV0R                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Driver Strength sel0 Configuration */

/* ============================== Bit definition for GPIOB_DRV1 register =================================== */
/*!< GPIOB driver strength sel1 Configuration  */
#define GPIOB_DRV1R                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOB Driver Strength sel1 Configuration */

/* ============================== Bit definition for GPIOC_DRV0 register =================================== */
/*!< GPIOC driver strength sel0 Configuration  */
#define GPIOC_DRV0R                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Driver Strength sel0 Configuration */

/* ============================== Bit definition for GPIOC_DRV1 register =================================== */
/*!< GPIOC driver strength sel1 Configuration  */
#define GPIOC_DRV1R                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOC Driver Strength sel1 Configuration */

/* ============================== Bit definition for GPIOA_SMT register =================================== */
/*!< GPIOA SMT Configuration  */
#define GPIOA_SMTR                       ((uint32_t)0xFFFFFFFF)         /*!< GPIOA SMT Configuration */

/* ============================== Bit definition for GPIOB_SMT register =================================== */
/*!< GPIOB SMT Configuration  */
#define GPIOB_SMTR                       ((uint32_t)0xFFFFFFFF)         /*!< GPIOB SMT Configuration */

/* ============================== Bit definition for GPIOC_SMT register =================================== */
/*!< GPIOC SMT Configuration  */
#define GPIOC_SMTR                       ((uint32_t)0xFFFFFFFF)         /*!< GPIOC SMT Configuration */

/* ============================== Bit definition for GPIOC_LS3V register =================================== */
/*!< GPIOC LS3V Configuration  */
#define GPIOC_LS3VR                      ((uint32_t)0xFFFFFFFF)        /*!< GPIOC LS3V Configuration */


/* =========================================================================================================================== */
/* ================                          Hardware Security Module (HSM)                                  ================= */
/* =========================================================================================================================== */
/* ============================== Bit definition for HSM_QC register =================================== */
#define HSM_QC_QE                          ((uint32_t)0x00000001)        /*!< Queue enable */

/* ============================== Bit definition for HSM_QIER register =================================== */
#define HSM_QIER_QD                        ((uint32_t)0x00000001)        /*!< Queue done Interrupt Enable */

/* ============================== Bit definition for HSM_QISR register =================================== */
#define HSM_QISR_QD                        ((uint32_t)0x00000001)        /*!< Queue done Interrupt */

/* ============================== Bit definition for HSM_QLSR register =================================== */
#define HSM_QLSR_BUSY                      ((uint32_t)0x00000002)        /*!< Kernel Busy */


/* =========================================================================================================================== */
/* ================                            Inter-integrated Circuit Interface                            ================= */
/* =========================================================================================================================== */
/* ============================== Bit definition for CR register =================================== */
#define I2C_CR_FLOW_CTRL_EN                 ((uint32_t)0x03000000) /* For burst mode */
#define I2C_CR_SBI_EN                       ((uint32_t)0x00200000)
#define I2C_CR_HSI_EN                       ((uint32_t)0x00100000)
#define I2C_CR_HS_MODE                      ((uint32_t)0x00080000)
#define I2C_CR_ARB_OFF                      ((uint32_t)0x00040000)
#define I2C_CR_STARTI_EN                    ((uint32_t)0x00004000)
#define I2C_CR_ALI_EN                       ((uint32_t)0x00002000)
#define I2C_CR_SAMI_EN                      ((uint32_t)0x00001000)
#define I2C_CR_STOPI_EN                     ((uint32_t)0x00000800)
#define I2C_CR_NACKI_EN                     ((uint32_t)0x00000400)
#define I2C_CR_TDI_EN                       ((uint32_t)0x00000200)
#define I2C_CR_BSTTHODI_EN                  ((uint32_t)0x00000100)
#define I2C_CR_TB_EN                        ((uint32_t)0x00000080)
#define I2C_CR_NACK                         ((uint32_t)0x00000040)
#define I2C_CR_STOP                         ((uint32_t)0x00000020)
#define I2C_CR_START                        ((uint32_t)0x00000010)
#define I2C_CR_GC_EN                        ((uint32_t)0x00000008)
#define I2C_CR_MST_EN                       ((uint32_t)0x00000004)
#define I2C_CR_I2C_EN                       ((uint32_t)0x00000002)
#define I2C_CR_I2C_RST                      ((uint32_t)0x00000001)

/* ============================== Bit definition for SR register =================================== */
#define I2C_SR_SBS                          ((uint32_t)0x00800000)
#define I2C_SR_HSS                          ((uint32_t)0x00400000)
#define I2C_SR_START                        ((uint32_t)0x00000800)
#define I2C_SR_AL                           ((uint32_t)0x00000400)
#define I2C_SR_GC                           ((uint32_t)0x00000200)
#define I2C_SR_SAM                          ((uint32_t)0x00000100)
#define I2C_SR_STOP                         ((uint32_t)0x00000080)
#define I2C_SR_NACK                         ((uint32_t)0x00000040)
#define I2C_SR_TD                           ((uint32_t)0x00000020)
#define I2C_SR_BSTTHOD                      ((uint32_t)0x00000010)
#define I2C_SR_BB                           ((uint32_t)0x00000008)
#define I2C_SR_BUSY                         ((uint32_t)0x00000004)
#define I2C_SR_RESERVED                     ((uint32_t)0x00000002)
#define I2C_SR_RW                           ((uint32_t)0x00000001)

/* ============================== Bit definition for CDR register =================================== */
#define I2C_CDR_DUTY                        ((uint32_t)0xF0000000)
#define I2C_CDR_COUNTH                      ((uint32_t)0x0FF00000)
#define I2C_CDR_COUNT                       ((uint32_t)0x000FFFFF)

/* ============================== Bit definition for AR register =================================== */
#define I2C_AR_ADDR10EN                     ((uint32_t)0x00001000)

/* ============================== Bit definition for TGSR register =================================== */
#define I2C_TGSR_TSR                        ((uint32_t)0x000003FF)
#define I2C_TGSR_GSR                        ((uint32_t)0x00003C00)


/* =========================================================================================================================== */
/* ================                           LCD-TFT Display Controller                                     ================= */
/* =========================================================================================================================== */
/* ============================== Bit definition for FUNCTION_EN register =================================== */
#define LTDC_FUNCTION_EN_ADDRSYNC            ((uint32_t)0x00010000)
#define LTDC_FUNCTION_EN_PAT_GEN             ((uint32_t)0x00004000)
#define LTDC_FUNCTION_EN_PIP                 ((uint32_t)0x00000C00)
#define LTDC_FUNCTION_EN_BLEND               ((uint32_t)0x00000300)
#define LTDC_FUNCTION_EN_POP                 ((uint32_t)0x00000080)
#define LTDC_FUNCTION_EN_DITHER              ((uint32_t)0x00000040)
#define LTDC_FUNCTION_EN_SCALER              ((uint32_t)0x00000020)
#define LTDC_FUNCTION_EN_LCDON               ((uint32_t)0x00000002)
#define LTDC_FUNCTION_EN_LCDEN               ((uint32_t)0x00000001)

/* ============================== Bit definition for PANEL_PIXEL register =================================== */
#define LTDC_PANEL_PIXEL_PRST                ((uint32_t)0x00080000)
#define LTDC_PANEL_PIXEL_LRST                ((uint32_t)0x00040000)
#define LTDC_PANEL_PIXEL_MRST                ((uint32_t)0x00020000)
#define LTDC_PANEL_PIXEL_ADDR_UPDATE         ((uint32_t)0x00010000)
#define LTDC_PANEL_PIXEL_UPDATE              ((uint32_t)0x0000C000)
#define LTDC_PANEL_PIXEL_DITH_TYPE           ((uint32_t)0x00003000)
#define LTDC_PANEL_PIXEL_PANEL_TYPE          ((uint32_t)0x00000800)
#define LTDC_PANEL_PIXEL_VCOMP               ((uint32_t)0x00000600)
#define LTDC_PANEL_PIXEL_RGBTYPE             ((uint32_t)0x00000180)
#define LTDC_PANEL_PIXEL_ENDIAN              ((uint32_t)0x00000060)
#define LTDC_PANEL_PIXEL_BGRSW               ((uint32_t)0x00000010)
#define LTDC_PANEL_PIXEL_PWROFF              ((uint32_t)0x00000008)
#define LTDC_PANEL_PIXEL_BPPFIFO             ((uint32_t)0x00000007)

/* ============================== Bit definition for IMR register =================================== */
#define LTDC_IMR_BUS_ERR                     ((uint32_t)0x00000008)
#define LTDC_IMR_VSTATUS                     ((uint32_t)0x00000004)
#define LTDC_IMR_NEXT_BASE                   ((uint32_t)0x00000002)
#define LTDC_IMR_FIFO_UNDERRUN               ((uint32_t)0x00000001)

/* ============================== Bit definition for ICR register =================================== */
#define LTDC_ICR_BUS_ERR                     ((uint32_t)0x00000008)
#define LTDC_ICR_VSTATUS                     ((uint32_t)0x00000004)
#define LTDC_ICR_NEXT_BASE                   ((uint32_t)0x00000002)
#define LTDC_ICR_FIFO_UNDERRUN               ((uint32_t)0x00000001)

/* ============================== Bit definition for ISR register =================================== */
#define LTDC_ISR_BUS_ERR                     ((uint32_t)0x00000008)
#define LTDC_ISR_VSTATUS                     ((uint32_t)0x00000004)
#define LTDC_ISR_NEXT_BASE                   ((uint32_t)0x00000002)
#define LTDC_ISR_FIFO_UNDERRUN               ((uint32_t)0x00000001)

/* ============================== Bit definition for PATTERN_BAR_COLOR register =================================== */
#define LTDC_PATTERN_BAR_COLOR_IMG3          ((uint32_t)0x000000C0)
#define LTDC_PATTERN_BAR_COLOR_IMG2          ((uint32_t)0x00000030)
#define LTDC_PATTERN_BAR_COLOR_IMG1          ((uint32_t)0x0000000C)
#define LTDC_PATTERN_BAR_COLOR_IMG0          ((uint32_t)0x00000003)

/* ============================== Bit definition for FIFO_THRESHOLD register =================================== */
#define LTDC_FIFO_THRESHOLD_BUF3             ((uint32_t)0xFF000000)
#define LTDC_FIFO_THRESHOLD_BUF2             ((uint32_t)0x00FF0000)
#define LTDC_FIFO_THRESHOLD_BUF1             ((uint32_t)0x0000FF00)
#define LTDC_FIFO_THRESHOLD_BUF0             ((uint32_t)0x000000FF)

/* ============================== Bit definition for BANDWIDTH_CR register =================================== */
#define LTDC_BANDWIDTH_CTRL_LOCK             ((uint32_t)0x00000200)
#define LTDC_BANDWIDTH_CTRL_RATIO            ((uint32_t)0x00000100)
#define LTDC_BANDWIDTH_CTRL_IMG3             ((uint32_t)0x000000C0)
#define LTDC_BANDWIDTH_CTRL_IMG2             ((uint32_t)0x00000030)
#define LTDC_BANDWIDTH_CTRL_IMG1             ((uint32_t)0x0000000C)
#define LTDC_BANDWIDTH_CTRL_IMG0             ((uint32_t)0x00000003)

/* ============================== Bit definition for HORTIMING register =================================== */
#define LTDC_HORTIMING_HBP                   ((uint32_t)0xFF000000)
#define LTDC_HORTIMING_HFP                   ((uint32_t)0x00FF0000)
#define LTDC_HORTIMING_HW                    ((uint32_t)0x0000FF00)
#define LTDC_HORTIMING_PL                    ((uint32_t)0x000000FF)

/* ============================== Bit definition for VERTIMING0 register =================================== */
#define LTDC_VERTIMING0_VFP                  ((uint32_t)0xFF000000)
#define LTDC_VERTIMING0_VW                   ((uint32_t)0x003F0000)
#define LTDC_VERTIMING0_LF                   ((uint32_t)0x00000FFF)

/* ============================== Bit definition for VERTIMING1 register =================================== */
#define LTDC_VERTIMING1_VBP                  ((uint32_t)0x000000FF)

/* ============================== Bit definition for POLARITY register =================================== */
#define LTDC_POLARITY_DIV                    ((uint32_t)0x00007F00)
#define LTDC_POLARITY_IPWR                   ((uint32_t)0x00000010)
#define LTDC_POLARITY_IDE                    ((uint32_t)0x00000008)
#define LTDC_POLARITY_ICK                    ((uint32_t)0x00000004)
#define LTDC_POLARITY_IHS                    ((uint32_t)0x00000002)
#define LTDC_POLARITY_IVS                    ((uint32_t)0x00000001)

/* ============================== Bit definition for SCALER_CONTROL register =================================== */
#define LTDC_SCALER_CONTROL_FIR_SEL          ((uint32_t)0x000001C0)
#define LTDC_SCALER_CONTROL_HOR              ((uint32_t)0x00000018)
#define LTDC_SCALER_CONTROL_VER              ((uint32_t)0x00000006)
#define LTDC_SCALER_CONTROL_BYPASS2          ((uint32_t)0x00000001)

/* ============================== Bit definition for PIP_BLEND_PARAM register =================================== */
#define LTDC_PIP_BLEND_PARAM_DOWN            ((uint32_t)0x00FF0000)
#define LTDC_PIP_BLEND_PARAM_HIGH            ((uint32_t)0x0000FF00)
#define LTDC_PIP_BLEND_PARAM_LOW             ((uint32_t)0x000000FF)

/* ============================== Bit definition for PIP_SUB1_POSITION_PARAM register =================================== */
#define LTDC_PIP_SUB1_POSITION_PARAM_UPDATE  ((uint32_t)0x10000000)
#define LTDC_PIP_SUB1_POSITION_PARAM_HPOS    ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB1_POSITION_PARAM_VPOS    ((uint32_t)0x000007FF)

/* ============================== Bit definition for PIP_SUB1_DIMENSION_PARAM register =================================== */
#define LTDC_PIP_SUB1_DIMENSION_PARAM_HDIM   ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB1_DIMENSION_PARAM_VDIM   ((uint32_t)0x000007FF)

/* ============================== Bit definition for PIP_SUB2_POSITION_PARAM register =================================== */
#define LTDC_PIP_SUB2_POSITION_PARAM_HPOS    ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB2_POSITION_PARAM_VPOS    ((uint32_t)0x000007FF)

/* ============================== Bit definition for PIP_SUB2_DIMENSION_PARAM register =================================== */
#define LTDC_PIP_SUB2_DIMENSION_PARAM_HDIM   ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB2_DIMENSION_PARAM_VDIM   ((uint32_t)0x000007FF)

/* ============================== Bit definition for PIP_IMAGE_PRIORITY register =================================== */
#define LTDC_PIP_IMAGE_PRIORITY_IMG3         ((uint32_t)0x000000C0)
#define LTDC_PIP_IMAGE_PRIORITY_IMG2         ((uint32_t)0x00000030)
#define LTDC_PIP_IMAGE_PRIORITY_IMG1         ((uint32_t)0x0000000C)
#define LTDC_PIP_IMAGE_PRIORITY_IMG0         ((uint32_t)0x00000003)

/* ============================== Bit definition for PIP_COLOR_KEY1 register =================================== */
#define LTDC_PIP_COLOR_KEY1_EN               ((uint32_t)0x01000000)
#define LTDC_PIP_COLOR_KEY1_VALUE            ((uint32_t)0x00FFFFFF)

/* ============================== Bit definition for PIP_COLOR_KEY2 register =================================== */
#define LTDC_PIP_COLOR_KEY2_EN               ((uint32_t)0x01000000)
#define LTDC_PIP_COLOR_KEY2_VALUE            ((uint32_t)0x00FFFFFF)

/* ============================== Bit definition for PIP_COLOR_KEY3 register =================================== */
#define LTDC_PIP_COLOR_KEY3_EN               ((uint32_t)0x01000000)
#define LTDC_PIP_COLOR_KEY3_VALUE            ((uint32_t)0x00FFFFFF)

/* ============================== Bit definition for PIP_SUB3_POSITION_PARAM register =================================== */
#define LTDC_PIP_SUB3_POSITION_PARAM_HPOS    ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB3_POSITION_PARAM_VPOS    ((uint32_t)0x000007FF)

/* ============================== Bit definition for PIP_SUB3_DIMENSION_PARAM register =================================== */
#define LTDC_PIP_SUB3_DIMENSION_PARAM_HDIM   ((uint32_t)0x07FF0000)
#define LTDC_PIP_SUB3_DIMENSION_PARAM_VDIM   ((uint32_t)0x000007FF)

/* =========================================================================================================================== */
/* ================                                            MAC                                           ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for MADR register ====================== */
#define MAC_MADR ((uint32_t)0x0000ffff)

/* ====================== Bit definition for LADR register ====================== */
#define MAC_LADR ((uint32_t)0xffffffff)

/* ====================== Bit definition for TXITC register ====================== */
#define MAC_TXITC_TIME_SEL ((uint32_t)0x00010000) // (1 << 16)
#define MAC_TXITC_CYL      ((uint32_t)0x0000ff00) // (((x)&0xff) << 8)
#define MAC_TXITC_THR      ((uint32_t)0x00000070) // (((x)&0x7) << 4)
#define MAC_TXITC_THR_UNIT ((uint32_t)0x00000003) // (((x)&0x3) << 0)

/* ====================== Bit definition for RXITC register ====================== */
#define MAC_RXITC_RST      ((uint32_t)0x0ff00000) // (((x)&0xff) << 20)
#define MAC_RXITC_TIME_SEL ((uint32_t)0x00010000) // ((uint32_t)0x00010000) // (1 << 16)
#define MAC_RXITC_CYL      ((uint32_t)0x0000ff00) // (((x)&0xff) << 8)
#define MAC_RXITC_THR      ((uint32_t)0x00000070) // (((x)&0x7) << 4)
#define MAC_RXITC_THR_UNIT ((uint32_t)0x00000003) // (((x)&0x3) << 0)

/* ====================== Bit definition for APTC register ====================== */
#define MAC_APTC_TX_TIME ((uint32_t)0x00001000) // (1 << 12)
#define MAC_APTC_TX_CNT  ((uint32_t)0x00000f00) // ((x & 0xf) << 8)
#define MAC_APTC_RX_TIME ((uint32_t)0x00000010) // (1 << 4)
#define MAC_APTC_RX_CNT  ((uint32_t)0x0000000f) // ((x & 0xf) << 0)

/* ====================== Bit definition for DBLAC register ====================== */
#define MAC_DBLAC_IFG_INC     ((uint32_t)0x00800000) // (1 << 23)
#define MAC_DBLAC_IFG_CNT     ((uint32_t)0x00700000) // ((x & 0x7) << 20)
#define MAC_DBLAC_TXBST_SIZE  ((uint32_t)0x00000c00) // ((x & 0x3) << 10)
#define MAC_DBLAC_RXBST_SIZE  ((uint32_t)0x00000300) // ((x & 0x3) << 8)
#define MAC_DBLAC_RX_THR_EN   ((uint32_t)0x00000040) // ((uint32_t)0x00000040) //(1 << 6)
#define MAC_DBLAC_RXFIFO_HTHR ((uint32_t)0x00000038) // ((x & 0x7) << 3)
#define MAC_DBLAC_RXFIFO_LTHR ((uint32_t)0x00000007) // ((x & 0x7) << 0)

/* ====================== Bit definition for DMAFIFOS register ====================== */

#define MAC_DMAFIFOS_TXFIFO_EMPTY ((uint32_t)0x08000000) // (1 << 27)
#define MAC_DMAFIFOS_RXFIFO_EMPTY ((uint32_t)0x04000000) // (1 << 26)


/* ====================== Bit definition for TPAFCR register ====================== */
#define MAC_TPAFCR_TFIFO_SIZE ((uint32_t)0x38000000) // ((x & 0x7) << 27)
#define MAC_TPAFCR_RFIFO_SIZE ((uint32_t)0x07000000) // ((x & 0x7) << 24)
#define MAC_TPAFCR_HPKT_THR   ((uint32_t)0x000000f0) // ((x & 0xf) << 4)
#define MAC_TPAFCR_NPKT_THR   ((uint32_t)0x0000000f) // ((x & 0xf) << 0)

/* ====================== Bit definition for RBSR register ====================== */
#define MAC_RBSR_RXBUF_SIZE ((uint32_t)0x00003fff)

/* ====================== Bit definition for MACCR register ====================== */
#define MAC_MACCR_SW_RST         ((uint32_t)0x80000000) // ((uint32_t)1 << 31)
#define MAC_MACCR_FULLDUP        ((uint32_t)0x04000000) // (1 << 26)
#define MAC_MACCR_SPEED          ((uint32_t)0x03000000)
#define MAC_MACCR_HPTXR_EN       ((uint32_t)0x00400000) // (1 << 22)
#define MAC_MACCR_LOOP_EN        ((uint32_t)0x00200000) // (1 << 21)
#define MAC_MACCR_PTP_EN         ((uint32_t)0x00100000) // (1 << 20)
#define MAC_MACCR_REMOVE_VLAN    ((uint32_t)0x00040000) // (1 << 18)
#define MAC_MACCR_CRC_APD        ((uint32_t)0x00020000) // (1 << 17)
#define MAC_MACCR_DROP_CRC_ERR   ((uint32_t)0x00010000) // (1 << 16)
#define MAC_MACCR_ENRX_IN_HALFTX ((uint32_t)0x00004000) // (1 << 14)
#define MAC_MACCR_JUMBO_LF       ((uint32_t)0x00002000) // (1 << 13)
#define MAC_MACCR_RX_RUNT        ((uint32_t)0x00001000) // (1 << 12)
#define MAC_MACCR_RX_BROADPKT_EN ((uint32_t)0x00000800) // (1 << 11)
#define MAC_MACCR_RX_MULTIPKT_EN ((uint32_t)0x00000400) // (1 << 10)
#define MAC_MACCR_RX_HT_EN       ((uint32_t)0x00000200) // (1 << 9)
#define MAC_MACCR_RX_ALLADR      ((uint32_t)0x00000100) // (1 << 8)
#define MAC_MACCR_RXMAC_EN       ((uint32_t)0x00000008) // (1 << 3)
#define MAC_MACCR_TXMAC_EN       ((uint32_t)0x00000004) // (1 << 2)
#define MAC_MACCR_RXDMA_EN       ((uint32_t)0x00000002) // (1 << 1)
#define MAC_MACCR_TXDMA_EN       ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for TM register ====================== */
#define MAC_TM_PTIMER_TEST ((uint32_t)0x00100000) // (1 << 20)
#define MAC_TM_ITIMER_TEST ((uint32_t)0x00080000) // (1 << 19)
#define MAC_TM_TEST_COL    ((uint32_t)0x00008000) // (1 << 15)
#define MAC_TM_TEST_BKOFF  ((uint32_t)0x00007FE0) // (((x)&0x3ff) << 5)
#define MAC_TM_TEST_EXSTHR ((uint32_t)0x0000001f) // (((x)&0x1f) << 0)

/* ====================== Bit definition for PHYCR register ====================== */
#define MAC_MDIO_SOF     1
#define MAC_MDIO_EXT_SOF 0
#define MAC_MDIO_OP_RD   2
#define MAC_MDIO_OP_WR   1
#define MAC_PHYCR_PHYWR  ((uint32_t)0x08000000) // (1 << 27)
#define MAC_PHYCR_PHYRD  ((uint32_t)0x04000000) // (1 << 26)
#define MAC_PHYCR_REGAD  ((uint32_t)0x03e00000) // (((x)&0x1f) << 21)
#define MAC_PHYCR_PHYAD  ((uint32_t)0x001f0000) // (((x)&0x1f) << 16)
#define MAC_PHYCR_OP     ((uint32_t)0x0000c000) // (((x)&0x3) << 14)
#define MAC_PHYCR_SOF    ((uint32_t)0x00003000) //  (((x)&0x3) << 12)
#define MAC_PHYCR_CYCTHR ((uint32_t)0x000000ff)

/* ====================== Bit definition for PHYDATA register ====================== */
#define MAC_PHYDATA_MIIRDATA ((uint32_t)0xffff0000) // (((x)&0xffff0000) >> 16)
#define MAC_PHYDATA_MIIWDATA ((uint32_t)0x0000ffff)

/* ====================== Bit definition for FCR register ====================== */
#define MAC_FCR_PAUSE_TIME ((uint32_t)0xffff0000) // (((x)&0xffff) << 16)
#define MAC_FCR_FC_H_L     ((uint32_t)0x0000fe00) // (((x)&0x7f) << 9)
#define MAC_FCR_HTHR       ((uint32_t)0x00000100) //  (1 << 8)
#define MAC_FCR_RX_PAUSE   ((uint32_t)0x00000010) // (1 << 4)
#define MAC_FCR_TXPAUSED   ((uint32_t)0x00000008) //  (1 << 3)
#define MAC_FCR_FCTHR_EN   ((uint32_t)0x00000004) //   (1 << 2)
#define MAC_FCR_TX_PAUSE   ((uint32_t)0x00000002) //  (1 << 1)
#define MAC_FCR_FC_EN      ((uint32_t)0x00000001) //  (1 << 0)

/* ====================== Bit definition for BPR register ====================== */
#define MAC_BPR_BK_LOW     ((uint32_t)0x00007f00) // ((x & 0x7f) << 8)
#define MAC_BPR_BKJAM_LEN  ((uint32_t)0x000000f0) // ((x & 0xf) << 4)
#define MAC_BPR_BKADR_MODE ((uint32_t)0x00000002) //  (1 << 1)
#define MAC_BPR_BKEN       ((uint32_t)0x00000001) //  (1 << 0)

/* ====================== Bit definition for WOLCR register ====================== */
#define MAC_WOLCR_WOL_TYPE   ((uint32_t)0x03000000) // ((x & 0x3) << 24)
#define MAC_WOLCR_SW_PDNPHY  ((uint32_t)0x00040000) // (1 << 18)
#define MAC_WOLCR_WAKEUP_SEL ((uint32_t)0x00030000) // ((x & 0x3) << 16)
//#define MAC_WOLCR_WAKEUP4  ((uint32_t)0x00000040) // 	(1 << 6)
//#define MAC_WOLCR_WAKEUP3  ((uint32_t)0x00000020) // 	(1 << 5)
//#define MAC_WOLCR_WAKEUP2  ((uint32_t)0x00000010) // 	(1 << 4)
//#define MAC_WOLCR_WAKEUP1  ((uint32_t)0x00000008) // 	(1 << 3)
//#define MAC_WOLCR_MAGICPKT ((uint32_t)0x00000004) // 	(1 << 2)
//#define MAC_WOLCR_LINKCHG1 ((uint32_t)0x00000002) // 	(1 << 1)
//#define MAC_WOLCR_LINKCHG0 ((uint32_t)0x00000001) // 	(1 << 0)

/* ====================== Bit definition for WOLSR register ====================== */
#define MAC_WOLSR_WAKEUP4  ((uint32_t)0x00000040) // (1 << 6)
#define MAC_WOLSR_WAKEUP3  ((uint32_t)0x00000020) // (1 << 5)
#define MAC_WOLSR_WAKEUP2  ((uint32_t)0x00000010) // (1 << 4)
#define MAC_WOLSR_WAKEUP1  ((uint32_t)0x00000008) // (1 << 3)
#define MAC_WOLSR_MAGICPKT ((uint32_t)0x00000004) // (1 << 2)
#define MAC_WOLSR_LINKCHG1 ((uint32_t)0x00000002) // (1 << 1)
#define MAC_WOLSR_LINKCHG0 ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for BMRCR register ====================== */
#define MAC_BMRCR_TIME_STEP    ((uint32_t)0x01000000) // (1 << 24)
#define MAC_BMRCR_TIME_THR_NUM ((uint32_t)0x00ff0000) //(((x)&0xff) << 16)
#define MAC_BMRCR_PKT_THR_VAL  ((uint32_t)0x0000001f) // ((x)&0x1f)

/* ====================== Bit definition for ERCR register ====================== */
#define MAC_ERCR_RONLY_ERR_EN ((uint32_t)0x00000002) // (1 << 1)
#define MAC_ERCR_DEC_ERR_EN   ((uint32_t)0x00000001) // (1 << 0)

/* ====================== Bit definition for ACIR register ====================== */
#define MAC_ACIR_BRESP_WAIT ((uint32_t)0xf0000000) // (((x) >> 28) & 0xf)
#define MAC_ACIR_WDATA_WAIT ((uint32_t)0x0f000000) // (((x) >> 24) & 0xf)
#define MAC_ACIR_RDATA_WAIT ((uint32_t)0x00f00000) // (((x) >> 20) & 0xf)
#define MAC_ACIR_AXI_ACI_EN ((uint32_t)0x00010000) // ((uint32_t)0x00010000) // (1 << 16)
#define MAC_ACIR_AWCACHE    ((uint32_t)0x0000f000) // (((x)&0xf) << 12)
#define MAC_ACIR_AWPROT     ((uint32_t)0x00000700) // (((x)&0x7) << 8)
#define MAC_ACIR_ARCACHE    ((uint32_t)0x000000f0) // (((x)&0xf) << 4)
#define MAC_ACIR_ARPROT     ((uint32_t)0x00000007) // (((x)&0x7) << 0)

/* ====================== Bit definition for GISR register ====================== */
#define MAC_IF_MII_GMII     ((uint32_t)0x00000000)
#define MAC_IF_RMII         ((uint32_t)0x00000001)
#define MAC_GISR_GMACIF_SEL ((uint32_t)0x00000003)

/* ====================== Bit definition for REVR register ====================== */
#define MAC_REV_B1 ((uint32_t)0x00ff0000) // (((x) >> 16) & 0xff)
#define MAC_REV_B2 ((uint32_t)0x0000ff00) // (((x) >> 8) & 0xff)
#define MAC_REV_B3 ((uint32_t)0x000000ff) // ((x)&0xff)

/* ====================== Bit definition for FEAR register ====================== */
#define MAC_FEAR_RGMII_IF     ((uint32_t)0x08000000)
#define MAC_FEAR_RMII_IF      ((uint32_t)0x04000000)
#define MAC_FEAR_GMII_IF      ((uint32_t)0x02000000)
#define MAC_FEAR_MII_IF       ((uint32_t)0x01000000)
#define MAC_FEAR_PTP          ((uint32_t)0x00040000)
#define MAC_FEAR_IP_COE       ((uint32_t)0x00020000)
#define MAC_FEAR_HOST_IF      ((uint32_t)0x00010000)
#define MAC_FEAR_AXI_ID_WIDTH ((uint32_t)0x0007f000) // (((x) >> 8) & 0x1f)
#define MAC_FEAR_TFIFO_RSIZE  ((uint32_t)0x00000070) // (((x) >> 4) & 0x07)
#define MAC_FEAR_RFIFO_RSIZE  ((uint32_t)0x00000007) // ((x)&0x07)

/* ====================== Bit definition for TXDES0 descriptor ====================== */
#define MAC_TXDES0_TXDMA_OWN ((uint32_t)0x80000000) // (1 << 31)
#define MAC_TXDES0_FTS       ((uint32_t)0x20000000) // (1 << 29)
#define MAC_TXDES0_LTS       ((uint32_t)0x10000000) // (1 << 28)
#define MAC_TXDES0_CRC_ERR   ((uint32_t)0x00080000) // (1 << 19)
#define MAC_TXDES0_EDOTR     ((uint32_t)0x00008000) // (1 << 15)
#define MAC_TXDES0_BUF_SIZE  ((uint32_t)0x00003fff) // (((x)&0x3fff) << 0)
#define FRAME_RUNT           ((uint32_t)0x00000004) // (1 << 2)
#define FRAME_WHOLE          (MAC_TXDES0_FTS | MAC_TXDES0_LTS)
#define FRAME_FIRST_PART     MAC_TXDES0_FTS
#define FRAME_MIDDLE_PART    0
#define FRAME_LAST_PART      MAC_TXDES0_LTS

/* ====================== Bit definition for TXDES1 descriptor ====================== */
#define MAC_TXDES1_TXIC      ((uint32_t)0x80000000) // (1 << 31)
#define MAC_TXDES1_TX2FIC    ((uint32_t)0x40000000) // (1 << 30)
#define MAC_TXDES1_LLC_PKT   ((uint32_t)0x00400000) // (1 << 22)
#define MAC_TXDES1_OTHER_PKT ((uint32_t)0x00200000) // (2 << 20)
#define MAC_TXDES1_IPV6_PKT  ((uint32_t)0x00100000) // (1 << 20)
#define MAC_TXDES1_IPCS_EN   ((uint32_t)0x00080000) // (1 << 19)
#define MAC_TXDES1_UDPCS_EN  ((uint32_t)0x00040000) // (1 << 18)
#define MAC_TXDES1_TCPCS_EN  ((uint32_t)0x00020000) // (1 << 17)
#define MAC_TXDES1_INS_VLAN  ((uint32_t)0x00010000) // (1 << 16)
#define MAC_TXDES1_VLAN_TAGC ((uint32_t)0x0000ffff) // (((x)&0xffff) << 0)
#define MAC_TXDES1_DEFAULT   (MAC_TXDES1_TXIC)

/* ====================== Bit definition for RXDES0 descriptor ====================== */
#define MAC_RXDES0_RXPKT_RDY    ((uint32_t)0x80000000) // (1 << 31)
#define MAC_RXDES0_FRS          ((uint32_t)0x20000000) // (1 << 29) /* First Receive Segment descriptor */
#define MAC_RXDES0_LRS          ((uint32_t)0x10000000) // (1 << 28) /* Last Receive Segment descriptor */
#define MAC_RXDES0_PAUSE_FRAME  ((uint32_t)0x02000000) // (1 << 25)
#define MAC_RXDES0_PAUSE_OPCODE ((uint32_t)0x01000000) // (1 << 24)
#define MAC_RXDES0_FIFO_FULL    ((uint32_t)0x00800000) // (1 << 23)
#define MAC_RXDES0_RX_ODD_NB    ((uint32_t)0x00400000) // (1 << 22)
#define MAC_RXDES0_RUNT         ((uint32_t)0x00200000) // (1 << 21)
#define MAC_RXDES0_FTL          ((uint32_t)0x00100000) // (1 << 20)
#define MAC_RXDES0_CRC_ERR      ((uint32_t)0x00080000) // (1 << 19)
#define MAC_RXDES0_RX_ERR       ((uint32_t)0x00040000) // (1 << 18)
#define MAC_RXDES0_BROADCAST    ((uint32_t)0x00020000) // (1 << 17)
#define MAC_RXDES0_MULTICAST    ((uint32_t)0x00010000) // (1 << 16)
#define MAC_RXDES0_EDORR        ((uint32_t)0x00008000) // (1 << 15)
#define MAC_RXDES0_VDBC         ((uint32_t)0x00003fff) // (((x)&0x3fff) << 0)

/* ====================== Bit definition for RXDES1 descriptor ====================== */
#define MAC_RXDES1_IPCS_FAIL  ((uint32_t)0x08000000) // (1 << 27)
#define MAC_RXDES1_UDPCS_FAIL ((uint32_t)0x04000000) // (1 << 26)
#define MAC_RXDES1_TCPCS_FAIL ((uint32_t)0x02000000) // (1 << 25)
#define MAC_RXDES1_VLAN_AVA   ((uint32_t)0x01000000) // (1 << 24)
#define MAC_RXDES1_DF         ((uint32_t)0x00800000) // (1 << 23)
#define MAC_RXDES1_LLC_PKT    ((uint32_t)0x00400000) // (1 << 22)
#define MAC_RXDES1_PROTL_TYPE ((uint32_t)0x00300000) // (((x) >> 20) & 0x3)
#define MAC_RXDES1_IP6_TYPE   ((uint32_t)0x00080000) // (((x) >> 19) & 0x1)
#define MAC_RXDES1_VLAN_PRIO  ((uint32_t)0x0000e000) // (((x)&7) << 13)
#define MAC_RXDES1_VLAN_CFI   ((uint32_t)0x00001000) // (((x)&1) << 12)
#define MAC_RXDES1_VLAN_VID   ((uint32_t)0x00000fff) // ((x)&0x0fff)

/* =========================================================================================================================== */
/* ================                           Message and Interrupt Controller                               ================= */
/* =========================================================================================================================== */

/* ============================== Bit definition for IMCR register =================================== */
#define MINTC_IMCR                        ((uint32_t)0xFFFFFFFF)        /*!< Interrupt mux control */

/* ============================== Bit definition for IPCR register =================================== */
#define MINTC_IPCR_M2C                    ((uint32_t)0x00000001)        /*!< IPC MCore to CCore interrupt control bit */
#define MINTC_IPCR_C2M                    ((uint32_t)0x00000002)        /*!< IPC CCore to MCore interrupt control bit */

/* =========================================================================================================================== */
/* ================                            Reset and Clock Control of Systerm                            ================= */
/* =========================================================================================================================== */

/* ============================== Bit definition for RCCS_MCR register =================================== */
/*!< SW configuration */
#define RCCS_MCR_SW                       ((uint32_t)0x00000001)        /*!< SW bits (System clock Switch) */

#define RCCS_MCR_SW_OSC                   ((uint32_t)0x00000000)        /*!< OSC selected as system clock */
#define RCCS_MCR_SW_PLL                   ((uint32_t)0x00000001)        /*!< PLL selected as system clock */

/*!< CPUDIVEN configuration */
#define RCCS_MCR_CPUSW                    ((uint32_t)0x00000002)        /*!< CPU clock divider enable */

/*!< CCPUSW configuration */
#define RCCS_MCR_CCOREPSW                 ((uint32_t)0x00000004)        /*!< Co-CPU clock Switch */

#define RCCS_MCR_CCORESW_CPUCLK           ((uint32_t)0x00000000)        /*!< CPU clock selected as Co-CPU clock */
#define RCCS_MCR_CCORESW_AXICLK           ((uint32_t)0x00000001)        /*!< AXI clock selected as Co-CPU clock */

/*!< CPT State */
#define RCCS_MCR_CPT                      ((uint32_t)0x000000C0)        /*!< Chip Package Type */

#define RCCS_MCR_CPT_BGA484               ((uint32_t)0x00000000)        /*!< BGA484 as Chip Package Type */
#define RCCS_MCR_CPT_BGA256               ((uint32_t)0x00000040)        /*!< BGA256 as Chip Package Type */
#define RCCS_MCR_CPT_QFN88                ((uint32_t)0x00000080)        /*!< QFN88 as Chip Package Type */        

/*!< SSP0SW configuration */
#define RCCS_MCR_SSP0SW                   ((uint32_t)0x00000100)        /*!< SSP0 clock Switch */

#define RCCS_MCR_SSP0SW_PLL               ((uint32_t)0x00000000)        /*!< System PLL as SSP0 clock */
#define RCCS_MCR_SSP0SW_OSC               ((uint32_t)0x00000100)        /*!< OSC as SSP0 clock */

/*!< SSP1SW configuration */
#define RCCS_MCR_SSP1SW                   ((uint32_t)0x00000200)        /*!< SSP1 clock Switch */

#define RCCS_MCR_SSP1SW_PLL               ((uint32_t)0x00000000)        /*!< System PLL as SSP1 clock */
#define RCCS_MCR_SSP1SW_OSC               ((uint32_t)0x00000200)        /*!< OSC as SSP1 clock */

/*!< MCORE Sleep State */
#define RCCS_MCR_MCORESS                   ((uint32_t)0x00000400)        /*!< Main CPU Sleep State */

#define RCCS_MCR_MCORESS_NO                ((uint32_t)0x00000000)        /*!< Main CPU not in Sleep State */
#define RCCS_MCR_MCORESS_IN                ((uint32_t)0x00000400)        /*!< Main CPU in Sleep State */

/*!< CCPU Sleep State */
#define RCCS_MCR_CCPUSS                   ((uint32_t)0x00000800)        /*!< CO-CPU Sleep State */

#define RCCS_MCR_CCPUSS_NO                ((uint32_t)0x00000000)        /*!< CO-CPU not in Sleep State */
#define RCCS_MCR_CCPUSS_IN                ((uint32_t)0x00000800)        /*!< CO-CPU in Sleep State */

/*!< HSM Sleep State */
#define RCCS_MCR_HSMSS                    ((uint32_t)0x00001000)        /*!< HSM Sleep State */

#define RCCS_MCR_HSMSS_NO                 ((uint32_t)0x00000000)        /*!< HSM not in Sleep State */
#define RCCS_MCR_HSMSS_IN                 ((uint32_t)0x00001000)        /*!< HSM in Sleep State */

/* Bit definition for RCCS_CCNT register */
/*!< CCNT configuration */
#define RCCS_CCNT_EN                      ((uint32_t)0x00000001)        /*!< RCCS clk counter enable */

/*!< CCNT Value */
#define RCCS_CCNT_VAL                     ((uint32_t)0xFFFFFFFF)        /*!< RCCS clk counter value */

/* Bit definition for RCCS_WRR0 register */
/*!< WRR0 Value */
#define RCCS_WRR0_VAL                     ((uint32_t)0xFFFFFFFF)        /*!< Watchdog record register 0 value */

/* Bit definition for RCCS_WRR1 register */
/*!< WRR1 Value */
#define RCCS_WRR1_VAL                     ((uint32_t)0xFFFFFFFF)        /*!< Watchdog record register 1 value */

/* Bit definition for RCCS_MCORERAR register */
/*!< MCORERAR configuration */
#define RCCS_MCORERAR_VAL                  ((uint32_t)0xFFFFFFFF)        /*!< Main CPU reset address configuration */

/* Bit definition for RCCS_CCPURAR register */
/*!< CCPURAR configuration */
#define RCCS_CCPURAR_VAL                  ((uint32_t)0xFFFFFFFF)        /*!< Co-CPU reset address configuration */


/* Bit definition for RCCS_PLLSYSCFGR register */
/*!< PLLSYSCFGR PLL NS configuration */
#define RCCS_PLLSYSCFGR_PLLNS             ((uint32_t)0x0000003F)        /*!< Systerm PLL NS configuration */

/*!< PLLSYSCFGR PLL ENABLE configuration */
#define RCCS_PLLSYSCFGR_PLLEN             ((uint32_t)0x00000040)        /*!< Systerm PLL NS configuration */

/* Bit definition for RCCS_PLLMACCFGR register */
/*!< PLLMACCFGR PLL NS configuration */
#define RCCS_PLLMACCFGR_PLLNS             ((uint32_t)0x0000003F)        /*!< MAC PLL NS configuration */

/*!< PLLMACCFGR PLL ENABLE configuration */
#define RCCS_PLLMACCFGR_PLLEN             ((uint32_t)0x00000040)        /*!< MAC PLL NS configuration */

/* Bit definition for RCCS_PLLDDRCFGR register */
/*!< PLLDDRCFGR PLL NS configuration */
#define RCCS_PLLDDRCFGR_PLLNS             ((uint32_t)0x0000003F)        /*!< DDR PLL NS configuration */

/*!< PLLDDRCFGR PLL ENABLE configuration */
#define RCCS_PLLDDRCFGR_PLLEN             ((uint32_t)0x00000040)        /*!< DDR PLL NS configuration */

/* Bit definition for RCCS_PLLHPCFGR register */
/*!< PLLHPCFGR Bypass configuration */
#define RCCS_PLLHPCFGR_BYPASS             ((uint32_t)0x00000001)        /*!< FREF is bypassed to FOUT1 and FOUT2 */  //TODO

/*!< PLLHPCFGR DSMPD configuration */
#define RCCS_PLLHPCFGR_DSMPD              ((uint32_t)0x00000002)        /*!< Delta-Sigma Modulator Power Down */  //TODO

/*!< PLLHPCFGR FBDIV configuration */
#define RCCS_PLLHPCFGR_FBDIV              ((uint32_t)0x00003FFC)        /*!<PLL Feedback divide value */  //TODO

/*!< PLLHPCFGR FOUT1PD configuration */
#define RCCS_PLLHPCFGR_FOUT1PD            ((uint32_t)0x00004000)        /*!< FOUT1PD */  //TODO

/*!< PLLHPCFGR FOUT2PD configuration */
#define RCCS_PLLHPCFGR_FOUT2PD            ((uint32_t)0x00008000)        /*!< FOUT2PD */  //TODO

/*!< PLLHPCFGR FOUTVCOPD configuration */
#define RCCS_PLLHPCFGR_FOUTVCOPD          ((uint32_t)0x00010000)        /*!< FOUTVCOPD */  //TODO

/*!< PLLHPCFGR LOCK configuration */
#define RCCS_PLLHPCFGR_LOCK               ((uint32_t)0x00020000)        /*!< LOCK Indicates no cycle slips between the feedback clock and FPFD for 256 consectutive cycles */  //TODO

/*!< PLLHPCFGR PD configuration */
#define RCCS_PLLHPCFGR_PD                 ((uint32_t)0x00040000)        /*!< Power down for PLL */  //TODO

/* Bit definition for RCCS_PLLHPDIVR register */
/*!< PLLHPDIVR FOUT1PDIV1 configuration */ 
#define RCCS_PLLHPDIVR_FOUT1PDIV1         ((uint32_t)0x0000000F)        /*!< FOUT1 post divide 1 setting */  //TODO

/*!< PLLHPDIVR FOUT2PDIV1 configuration */ 
#define RCCS_PLLHPDIVR_FOUT2PDIV1         ((uint32_t)0x000000F0)        /*!< FOUT2 post divide 1 setting */  //TODO

/*!< PLLHPDIVR FOUT1PDIV2 configuration */ 
#define RCCS_PLLHPDIVR_FOUT1PDIV2         ((uint32_t)0x00000700)        /*!< FOUT1 post divide 2 setting */  //TODO

/*!< PLLHPDIVR FOUT2PDIV2 configuration */ 
#define RCCS_PLLHPDIVR_FOUT2PDIV2         ((uint32_t)0x00003800)        /*!< FOUT2 post divide 2 setting */  //TODO

/*!< PLLHPDIVR RDIV configuration */
#define RCCS_PLLHPDIVR_RDIV               ((uint32_t)0x000FC000)        /*!< Reference divide value */  //TODO

/* ================= Bit definition for RCCS_PLLHPFRACR register =================== */
/*!< PLLHPFRACR FRAC configuration */
#define RCCS_PLLHPFRACR_FRAC              ((uint32_t)0x00FFFFFF)        /*!< Reference divide value */  //TODO


/* ================= Bit definition for RCCS_CLKENR0 register  ===================== */
#define RCCS_CLKEN0_MCOREEN               ((uint32_t)0x00000002)                 
#define RCCS_CLKEN0_CCOREEN               ((uint32_t)0x00000004)
#define RCCS_CLKEN0_PCIEEN                ((uint32_t)0x00000008) 
#define RCCS_CLKEN0_GMAC0EN               ((uint32_t)0x00000010)
#define RCCS_CLKEN0_GMAC1EN               ((uint32_t)0x00000020)
#define RCCS_CLKEN0_MINTCEM               ((uint32_t)0x00000040)
#define RCCS_CLKEN0_USB3EN                ((uint32_t)0x00000080) 
#define RCCS_CLKEN0_FMC0EN                ((uint32_t)0x00000100)
#define RCCS_CLKEN0_FMC1EN                ((uint32_t)0x00000200)
#define RCCS_CLKEN0_DDRCEN                ((uint32_t)0x00000400)
#define RCCS_CLKEN0_X2PCFGEN              ((uint32_t)0x00000800)
#define RCCS_CLKEN0_X2PLPCEN              ((uint32_t)0x00001000)
#define RCCS_CLKEN0_H2XLEN                ((uint32_t)0x00002000)
#define RCCS_CLKEN0_H2XHEN                ((uint32_t)0x00004000) 
#define RCCS_CLKEN0_X2HEN                 ((uint32_t)0x00008000)
#define RCCS_CLKEN0_DMA0EN                ((uint32_t)0x00002000)
#define RCCS_CLKEN0_DMA1EN                ((uint32_t)0x00004000)
#define RCCS_CLKEN0_WDTIMER0EN            ((uint32_t)0x00008000)
#define RCCS_CLKEN0_WDTIMER1EN            ((uint32_t)0x00010000)
#define RCCS_CLKEN0_IIC2EN                ((uint32_t)0x00400000)
#define RCCS_CLKEN0_IIC1EN                ((uint32_t)0x00800000)
#define RCCS_CLKEN0_GPIOEN                ((uint32_t)0x01000000)
#define RCCS_CLKEN0_AXI1EN                ((uint32_t)0x04000000)
#define RCCS_CLKEN0_AHB0EN                ((uint32_t)0x10000000)

/* ================= Bit definition for RCCS_CLKENR1 register  ====================== */
#define RCCS_CLKEN1_UART1EN               ((uint32_t)0x00000001)
#define RCCS_CLKEN1_UART2EN               ((uint32_t)0x00000002)
#define RCCS_CLKEN1_UART3EN               ((uint32_t)0x00000004)
#define RCCS_CLKEN1_UART4EN               ((uint32_t)0x00000008)
#define RCCS_CLKEN1_UART5EN               ((uint32_t)0x00000010)
#define RCCS_CLKEN1_UART6EN               ((uint32_t)0x00000020)
#define RCCS_CLKEN1_UART7EN               ((uint32_t)0x00000040)
#define RCCS_CLKEN1_SCI0EN                ((uint32_t)0x00000080) 
#define RCCS_CLKEN1_SCI1EN                ((uint32_t)0x00000100) 
#define RCCS_CLKEN1_SPI0EN                ((uint32_t)0x00000200) 
#define RCCS_CLKEN1_SPI1EN                ((uint32_t)0x00000400) 
#define RCCS_CLKEN1_DACEN                 ((uint32_t)0x00000800)
#define RCCS_CLKEN1_SSP0EN                ((uint32_t)0x00001000) 
#define RCCS_CLKEN1_SSP1EN                ((uint32_t)0x00002000) 
#define RCCS_CLKEN1_CANA1EN               ((uint32_t)0x00004000) 
#define RCCS_CLKEN1_CANA2EN               ((uint32_t)0x00008000) 
#define RCCS_CLKEN1_CANA3EN               ((uint32_t)0x00010000) 
#define RCCS_CLKEN1_CANB4EN               ((uint32_t)0x00020000) 
#define RCCS_CLKEN1_CANB5EN               ((uint32_t)0x00040000) 
#define RCCS_CLKEN1_CANB6EN               ((uint32_t)0x00080000) 
#define RCCS_CLKEN1_CANB7EN               ((uint32_t)0x00100000) 
#define RCCS_CLKEN1_USB2EN                ((uint32_t)0x00200000) 
#define RCCS_CLKEN1_LTDCEN                 ((uint32_t)0x00400000)
#define RCCS_CLKEN1_SDHC1EN               ((uint32_t)0x00800000) 
#define RCCS_CLKEN1_SDHC2EN               ((uint32_t)0x01000000)
#define RCCS_CLKEN1_SDHC0EN               ((uint32_t)0x02000000)
#define RCCS_CLKEN1_MAC0EN                ((uint32_t)0x04000000)
#define RCCS_CLKEN1_MAC1EN                ((uint32_t)0x08000000)
#define RCCS_CLKEN1_TEEEN                 ((uint32_t)0x10000000)

/* =================  Bit definition for RCCS_CLKEN2 register  ====================== */
#define RCCS_CLKEN2_HSMEN                 ((uint32_t)0x00000001)
#define RCCS_CLKEN2_LPCEN                 ((uint32_t)0x00000002)
#define RCCS_CLKEN2_SRAMAXIEN             ((uint32_t)0x00000004)
#define RCCS_CLKEN2_ROMEN                 ((uint32_t)0x00000008)
#define RCCS_CLKEN2_AXICEN                ((uint32_t)0x00000010)

/* =================  Bit definition for RCCS_ModuleDIV register  =================== */
#define RCCS_AXIDIVR_AXIDIV              ((uint32_t)0x000000FF)  
#define RCCS_AHBDIVR_AHBDIV              ((uint32_t)0x000000FF)  
#define RCCS_APBPDIVR_APBDIV             ((uint32_t)0x000000FF)  
#define RCCS_CPUDIVR_CPUDIV              ((uint32_t)0x000000FF)  
#define RCCS_HSMDIVR_HSMDIV              ((uint32_t)0x000000FF)  
#define RCCS_LPCDIVR_LPCDIV              ((uint32_t)0x000000FF)  
#define RCCS_FMC0DIVR_FMCODIV            ((uint32_t)0x000000FF)  
#define RCCS_FMC1DIVR_FMC1DIV            ((uint32_t)0x000000FF)  
#define RCCS_UART1DIVR_UART1DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART2DIVR_UART2DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART3DIVR_UART3DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART4DIVR_UART4DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART5DIVR_UART5DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART6DIVR_UART6DIV          ((uint32_t)0x000000FF)  
#define RCCS_UART7DIVR_UART7DIV          ((uint32_t)0x000000FF)  
#define RCCS_SCI0DIVR_SCI0DIV            ((uint32_t)0x000000FF)  
#define RCCS_SCI1DIVR_SCI1DIV            ((uint32_t)0x000000FF)  
#define RCCS_SPI0DIVR_SPI0DIV            ((uint32_t)0x000000FF)  
#define RCCS_SPI1DIVR_SPI1DIV            ((uint32_t)0x000000FF)  
#define RCCS_SSP0DIVR_SSP0DIV            ((uint32_t)0x000000FF)  
#define RCCS_SSP1DIVR_SSP1DIV            ((uint32_t)0x000000FF)  
#define RCCS_CANA1DIVR_CAN1DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANA2DIVR_CAN2DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANA3DIVR_CAN3DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANB0DIVR_CAN4DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANB1DIVR_CAN5DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANB2DIVR_CAN6DIV           ((uint32_t)0x000000FF)  
#define RCCS_CANB3DIVR_CAN7DIV           ((uint32_t)0x000000FF)  
#define RCCS_USB3DIVR0_USB3DIV0          ((uint32_t)0x000000FF)  
#define RCCS_USB3DIVR1_USB3DIV0          ((uint32_t)0x000000FF)  
#define RCCS_GMAC0DIVR0_GMAC0DIV0        ((uint32_t)0x000000FF)  
#define RCCS_GMAC1DIVR0_GMAC1DIV0        ((uint32_t)0x000000FF)  
#define RCCS_GMAC0DIVR1_GMAC0DIV1        ((uint32_t)0x000000FF)  
#define RCCS_GMAC1DIVR1_GMAC1DIV1        ((uint32_t)0x000000FF)  
#define RCCS_MAC0DIVR0_MAC0DIV0          ((uint32_t)0x000000FF)  
#define RCCS_MAC1DIVR0_MAC1DIV0          ((uint32_t)0x000000FF)  
#define RCCS_MAC0DIVR1_MAC0DIV1          ((uint32_t)0x000000FF)  
#define RCCS_MAC1DIVR1_MAC1DIV1          ((uint32_t)0x000000FF)  
#define RCCS_SDHC2DIVR_SDHC2DIV          ((uint32_t)0x000000FF)  
#define RCCS_SDHC1DIVR_SDHC1DIV          ((uint32_t)0x000000FF)  
#define RCCS_SDHC0DIVR_SDHC0DIV          ((uint32_t)0x000000FF)  
#define RCCS_APBCDIVR_APBCDIV            ((uint32_t)0x000000FF)  
#define RCCS_LTDCDIVR0_LTDCDIV0            ((uint32_t)0x000000FF)  
#define RCCS_LTDCDIVR1_LTDCDIV1            ((uint32_t)0x000000FF)  
#define RCCS_USB2DIVR_USB2DIV            ((uint32_t)0x000000FF)  
#define RCCS_GMAC0DIVR2_GMAC0DIV2        ((uint32_t)0x000000FF)  
#define RCCS_GMAC1DIVR2_GMAC1DIV2        ((uint32_t)0x000000FF)  
#define RCCS_PCIEDIVR_PCIEDIV            ((uint32_t)0x000000FF)  
#define RCCS_USB3DIVR2_USB3DIV2          ((uint32_t)0x000000FF)  
#define RCCS_GMAC0DIV3_GAMC0DIV3         ((uint32_t)0x000000FF)  
#define RCCS_GMAC1DIV3_GMAC1DIV3         ((uint32_t)0x000000FF)

/* ====================  Bit definition for RCCS_RSTCR0 register ==================== */
#define RCCS_RSTCR0_MCORERST             ((uint32_t)0x00000002)                 
#define RCCS_RSTCR0_CCORERST             ((uint32_t)0x00000004)
#define RCCS_RSTCR0_PCIERST              ((uint32_t)0x00000008) 
#define RCCS_RSTCR0_GMAC0RST             ((uint32_t)0x00000010)
#define RCCS_RSTCR0_GMAC1RST             ((uint32_t)0x00000020)
#define RCCS_RSTCR0_MINTCRST             ((uint32_t)0x00000040)
#define RCCS_RSTCR0_USB3RST              ((uint32_t)0x00000080) 
#define RCCS_RSTCR0_FMC0RST              ((uint32_t)0x00000100)
#define RCCS_RSTCR0_FMC1RST              ((uint32_t)0x00000200)
#define RCCS_RSTCR0_DDRCRST              ((uint32_t)0x00000400)
#define RCCS_RSTCR0_X2PCFGRST            ((uint32_t)0x00000800)
#define RCCS_RSTCR0_X2PLPCRST            ((uint32_t)0x00001000)
#define RCCS_RSTCR0_H2XLRST              ((uint32_t)0x00002000)
#define RCCS_RSTCR0_H2XHRST              ((uint32_t)0x00004000) 
#define RCCS_RSTCR0_X2HRST               ((uint32_t)0x00008000)
#define RCCS_RSTCR0_DMA0RST              ((uint32_t)0x00002000)
#define RCCS_RSTCR0_DMA1RST              ((uint32_t)0x00004000)
#define RCCS_RSTCR0_WDTIMER0RST          ((uint32_t)0x00008000)
#define RCCS_RSTCR0_WDTIMER1RST          ((uint32_t)0x00010000)
#define RCCS_RSTCR0_IIC2RST              ((uint32_t)0x00400000)
#define RCCS_RSTCR0_IIC1RST              ((uint32_t)0x00800000)
#define RCCS_RSTCR0_GPIORST              ((uint32_t)0x01000000)
#define RCCS_RSTCR0_AXI1RST              ((uint32_t)0x04000000)
#define RCCS_RSTCR0_AHB0RST              ((uint32_t)0x10000000)
#define RCCS_RSTCR0_USB3PHYRST           ((uint32_t)0x20000000)

/* ====================  Bit definition for RCCS_RSTCR1 register  =================== */
#define RCCS_RSTCR1_UART1RST             ((uint32_t)0x00000001)
#define RCCS_RSTCR1_UART2RST             ((uint32_t)0x00000002)
#define RCCS_RSTCR1_UART3RST             ((uint32_t)0x00000004)
#define RCCS_RSTCR1_UART4RST             ((uint32_t)0x00000008)
#define RCCS_RSTCR1_UART5RST             ((uint32_t)0x00000010)
#define RCCS_RSTCR1_UART6RST             ((uint32_t)0x00000020)
#define RCCS_RSTCR1_UART7RST             ((uint32_t)0x00000040)
#define RCCS_RSTCR1_SCI0RST              ((uint32_t)0x00000080) 
#define RCCS_RSTCR1_SCI1RST              ((uint32_t)0x00000100) 
#define RCCS_RSTCR1_SPI0RST              ((uint32_t)0x00000200) 
#define RCCS_RSTCR1_SPI1RST              ((uint32_t)0x00000400) 
#define RCCS_RSTCR1_DACRST               ((uint32_t)0x00000800)
#define RCCS_RSTCR1_SSP0RST              ((uint32_t)0x00001000) 
#define RCCS_RSTCR1_SSP1RST              ((uint32_t)0x00002000) 
#define RCCS_RSTCR1_CANA1RST             ((uint32_t)0x00004000) 
#define RCCS_RSTCR1_CANA2RST             ((uint32_t)0x00008000) 
#define RCCS_RSTCR1_CANA3RST             ((uint32_t)0x00010000) 
#define RCCS_RSTCR1_CANB0RST             ((uint32_t)0x00020000) 
#define RCCS_RSTCR1_CANB1RST             ((uint32_t)0x00040000) 
#define RCCS_RSTCR1_CANB2RST             ((uint32_t)0x00080000) 
#define RCCS_RSTCR1_CANB3RST             ((uint32_t)0x00100000) 
#define RCCS_RSTCR1_USB2RST              ((uint32_t)0x00200000) 
#define RCCS_RSTCR1_LTDCRST               ((uint32_t)0x00400000)
#define RCCS_RSTCR1_SDHC1RST             ((uint32_t)0x00800000) 
#define RCCS_RSTCR1_SDHC2RST             ((uint32_t)0x01000000)
#define RCCS_RSTCR1_SDHC0TST             ((uint32_t)0x02000000)
#define RCCS_RSTCR1_MAC0EN               ((uint32_t)0x04000000)
#define RCCS_RSTCR1_MAC1EN               ((uint32_t)0x08000000)
#define RCCS_RSTCR1_TEEEN                ((uint32_t)0x10000000)
#define RCCS_RSTCR1_USB2PHYRST           ((uint32_t)0x20000000)

/* ====================== Bit definition for RCCS_RSTCR22 register =================== */
#define RCCS_RSTCR2_HSMRST               ((uint32_t)0x00000001)
#define RCCS_RSTCR2_LPCRST               ((uint32_t)0x00000002)
#define RCCS_RSTCR2_SRAMAXIRST           ((uint32_t)0x00000004)
#define RCCS_RSTCR2_ROMRST               ((uint32_t)0x00000008)
#define RCCS_RSTCR2_AXICRST              ((uint32_t)0x00000010)

/* =========================================================================================================================== */
/* ================                        Real-Time Clock                                                   ================= */
/* =========================================================================================================================== */

/* ====================== Bit definition for DAY register  ====================== */
#define RTC_DAY_WEEK                    ((uint32_t)0x00000007)
#define RTC_DAY_DAY                     ((uint32_t)0x00001F00)
#define RTC_DAY_MONTH                   ((uint32_t)0x000F0000)
#define RTC_DAY_YEAR                    ((uint32_t)0x7F000000)

/* ====================== Bit definition for CR register  ====================== */
#define RTC_CR_CRR                      ((uint32_t)0x00000080) /* counter register refresh per second */
#define RTC_CR_CL                       ((uint32_t)0x00000040) /* counter load */
#define RTC_CR_AI                       ((uint32_t)0x00000020) /* alarm interrupt */
#define RTC_CR_AID                      ((uint32_t)0x00000010) /* alarm interrupt per day */
#define RTC_CR_AIH                      ((uint32_t)0x00000008) /* alarm interrupt per hour */
#define RTC_CR_AIM                      ((uint32_t)0x00000004) /* alarm interrupt per minute */
#define RTC_CR_AIS                      ((uint32_t)0x00000002) /* alarm interrupt per second */
#define RTC_CR_EN                       ((uint32_t)0x00000001)

/* ====================== Bit definition for WRITE DAY register  ====================== */
#define RTC_WRTC_DAY_YEAR               ((uint32_t)0x007F0000)
#define RTC_WRTC_DAY_MONTH              ((uint32_t)0x00000F00)
#define RTC_WRTC_DAY_DAY                ((uint32_t)0x0000001F)

/* ====================== Bit definition for DAY register  ====================== */
#define RTC_ISR_YEAR                    ((uint32_t)0x00000080)
#define RTC_ISR_MONTH                   ((uint32_t)0x00000040)
#define RTC_ISR_LOAD                    ((uint32_t)0x00000020)
#define RTC_ISR_ALARM                   ((uint32_t)0x00000010)
#define RTC_ISR_DAY                     ((uint32_t)0x00000008)
#define RTC_ISR_HOUR                    ((uint32_t)0x00000004)
#define RTC_ISR_MINUTE                  ((uint32_t)0x00000002)
#define RTC_ISR_SECOND                  ((uint32_t)0x00000001)

/* ====================== Bit definition for RW STATUS register  ====================== */
#define RTC_RW_STATUS_WWEEK_ST          ((uint32_t)0x00000200)
#define RTC_RW_STATUS_REF_ST            ((uint32_t)0x00000100) /* Restore or refresh status */
#define RTC_RW_STATUS_WDAY_ST           ((uint32_t)0x00000080) /* WRtcDay transfer status */
#define RTC_RW_STATUS_WHOUR_ST          ((uint32_t)0x00000040) /* WRtcHour transfer status */
#define RTC_RW_STATUS_WMINUTE_ST        ((uint32_t)0x00000020) /* WRtcMinute transfer status */
#define RTC_RW_STATUS_WSECOND_ST        ((uint32_t)0x00000010) /* WRtcSecond transfer status */
#define RTC_RW_STATUS_CR_ST             ((uint32_t)0x00000008) /* RtcCR transfer status */
#define RTC_RW_STATUS_AHOUR_ST          ((uint32_t)0x00000004) /* AlarmHour transfer status */
#define RTC_RW_STATUS_AMINUTE_ST        ((uint32_t)0x00000002) /* AlarmMinute transfer status */
#define RTC_RW_STATUS_ASECOND_ST        ((uint32_t)0x00000001) /* AlarmSecond transfer status */

/* ====================== Bit definition for CURRENT TIME register  ====================== */
#define RTC_CURRENT_HOUR                ((uint32_t)0x001F0000)
#define RTC_CURRENT_MINUTE              ((uint32_t)0x00003F00)
#define RTC_CURRENT_SECOND              ((uint32_t)0x0000003F)

/* ====================== Bit definition for SLEEP TIME register  ====================== */
#define RTC_SLEEP_TIME_HOUR             ((uint32_t)0x001F0000)
#define RTC_SLEEP_TIME_MINUTE           ((uint32_t)0x00003F00)
#define RTC_SLEEP_TIME_SECOND           ((uint32_t)0x0000003F)

/* ====================== Bit definition for CURRENT DATE register  ====================== */
#define RTC_CURRENT_DATE_YEAR           ((uint32_t)0x7F000000)
#define RTC_CURRENT_DATE_MONTH          ((uint32_t)0x000F0000)
#define RTC_CURRENT_DATE_DAY            ((uint32_t)0x00001F00)
#define RTC_CURRENT_DATE_WEEK           ((uint32_t)0x00000007)

/* ====================== Bit definition for SLEEP DATE register  ====================== */
#define RTC_SLEEP_DATE_YEAR             ((uint32_t)0x7F000000)
#define RTC_SLEEP_DATE_MONTH            ((uint32_t)0x000F0000)
#define RTC_SLEEP_DATE_DAY              ((uint32_t)0x00001F00)
#define RTC_SLEEP_DATE_WEEK             ((uint32_t)0x00000007)

/* =========================================================================================================================== */
/* ================               Smart Card Interfac                                                        ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for SCI_DATA register  ====================== */
#define  SCI_DATA_PARITY                     ((uint16_t)0x0100)            /*!<Parity Error                     */
#define  SCI_DATA_DATA                       ((uint16_t)0x00FF)            /*!<Eight data bits                  */

/* ====================== Bit definition for SCI_CR0 register  ====================== */
#define  SCI_CR0_RXNAK                       ((uint8_t)0x20)               /*!<character receipt handshaking    */
#define  SCI_CR0_RXPARITY                    ((uint8_t)0x10)               /*!<Receive Parity setting           */
#define  SCI_CR0_TXNAK                       ((uint8_t)0x08)               /*!<Character transmission handshaking */
#define  SCI_CR0_TXPARITY                    ((uint8_t)0x04)               /*!<Transmit Parity setting          */
#define  SCI_CR0_ORDER                       ((uint8_t)0x02)               /*!<Ordering of the data bits        */
#define  SCI_CR0_SENSE                       ((uint8_t)0x01)               /*!<Inverts sense of in/out line for data and Parity bits */

/* ====================== Bit definition for SCI_CR1 register  ====================== */
#define  SCI_CR1_EXDBNCE                     ((uint8_t)0x20)               /*!<External debounce                */
#define  SCI_CR1_BGTEN                       ((uint8_t)0x10)               /*!<Block guard timer enable         */
#define  SCI_CR1_CLKZ1                       ((uint8_t)0x08)               /*!<SCICLK output configuration      */
#define  SCI_CR1_MODE                        ((uint8_t)0x04)               /*!<Interface direction of communication control */
#define  SCI_CR1_BLKEN                       ((uint8_t)0x02)               /*!<Block timeout enable             */
#define  SCI_CR1_ATRDEN                      ((uint8_t)0x01)               /*!<ATR duration timeout enable      */

/* ====================== Bit definition for SCI_CR2 register  ====================== */
#define  SCI_CR2_WRESET                      ((uint8_t)0x04)               /*!<Warm reset                       */
#define  SCI_CR2_FINISH                      ((uint8_t)0x02)               /*!<Deactivates the card             */
#define  SCI_CR2_STARTUP                     ((uint8_t)0x01)               /*!<Starts the activates of the card */

/* ====================== Bit definition for SCI_IER register  ====================== */
#define  SCI_IER_TXTIDE                      ((uint16_t)0x0800)            /*!<Transmit FIFO tide mark          */
#define  SCI_IER_RXTIDE                      ((uint16_t)0x0400)            /*!<Receive FIFO tide mark           */
#define  SCI_IER_RTOUT                       ((uint16_t)0x0200)            /*!<Receive FIFO read timeout        */
#define  SCI_IER_CHTOUT                      ((uint16_t)0x0100)            /*!<Between character timeout        */
#define  SCI_IER_BLKTOUT                     ((uint16_t)0x0080)            /*!<Between block timeout            */
#define  SCI_IER_ATRDTOUT                    ((uint16_t)0x0040)            /*!<ATR reception duration timeout   */
#define  SCI_IER_ATRSTOUT                    ((uint16_t)0x0020)            /*!<ATR reception start timeout      */
#define  SCI_IER_XERR                        ((uint16_t)0x0010)            /*!<Character transmission error     */
#define  SCI_IER_CARDDN                      ((uint16_t)0x0008)            /*!<Smart Card powered down          */
#define  SCI_IER_CARDUP                      ((uint16_t)0x0004)            /*!<Smart Card powered up            */
#define  SCI_IER_CARDOUT                     ((uint16_t)0x0002)            /*!<Smart Card removed               */
#define  SCI_IER_CARDIN                      ((uint16_t)0x0001)            /*!<Smart Card inserted              */

/* ====================== Bit definition for SCI_RETRY register  ====================== */
#define  SCI_RETRY_RX                        ((uint8_t)0x38)               /*!<Maximum number of retries to receive */
#define  SCI_RETRY_RX_0                      ((uint8_t)0x08)               /*!<Bit 0 */
#define  SCI_RETRY_RX_1                      ((uint8_t)0x10)               /*!<Bit 1 */
#define  SCI_RETRY_RX_2                      ((uint8_t)0x20)               /*!<Bit 2 */
#define  SCI_RETRY_TX                        ((uint8_t)0x07)               /*!<Maximum number of times to be retransmitted */
#define  SCI_RETRY_TX_0                      ((uint8_t)0x01)               /*!<Bit 0 */
#define  SCI_RETRY_TX_1                      ((uint8_t)0x02)               /*!<Bit 1 */
#define  SCI_RETRY_TX_2                      ((uint8_t)0x04)               /*!<Bit 2 */

/* ====================== Bit definition for SCI_TIDE register  ====================== */
#define  SCI_TIDE_RX                         ((uint8_t)0xF0)               /*!<Trigger point for SCIRXTIDEINTR  */
#define  SCI_TIDE_RX_0                       ((uint8_t)0x10)               /*!<Bit 0 */
#define  SCI_TIDE_RX_1                       ((uint8_t)0x20)               /*!<Bit 1 */
#define  SCI_TIDE_RX_2                       ((uint8_t)0x40)               /*!<Bit 2 */
#define  SCI_TIDE_RX_3                       ((uint8_t)0x80)               /*!<Bit 3 */
#define  SCI_TIDE_TX                         ((uint8_t)0x0F)               /*!<Trigger point for SCITXTIDEINTR   */
#define  SCI_TIDE_TX_0                       ((uint8_t)0x01)               /*!<Bit 0 */
#define  SCI_TIDE_TX_1                       ((uint8_t)0x02)               /*!<Bit 1 */
#define  SCI_TIDE_TX_2                       ((uint8_t)0x04)               /*!<Bit 2 */
#define  SCI_TIDE_TX_3                       ((uint8_t)0x08)               /*!<Bit 3 */

/* ====================== Bit definition for SCI_TXCNT register  ====================== */
#define  SCI_TXCNT                           ((uint8_t)0x1F)               /*!<Transmit FIFO count              */
#define  SCI_TXCNT_0                         ((uint8_t)0x01)               /*!<Bit 0 */
#define  SCI_TXCNT_1                         ((uint8_t)0x02)               /*!<Bit 1 */
#define  SCI_TXCNT_2                         ((uint8_t)0x04)               /*!<Bit 2 */
#define  SCI_TXCNT_3                         ((uint8_t)0x08)               /*!<Bit 3 */
#define  SCI_TXCNT_4                         ((uint8_t)0x10)               /*!<Bit 4 */

/* ====================== Bit definition for SCI_RXCNT register  ====================== */
#define  SCI_RXCNT                           ((uint8_t)0x1F)               /*!<Receive FIFO count               */
#define  SCI_RXCNT_0                         ((uint8_t)0x01)               /*!<Bit 0 */
#define  SCI_RXCNT_1                         ((uint8_t)0x02)               /*!<Bit 1 */
#define  SCI_RXCNT_2                         ((uint8_t)0x04)               /*!<Bit 2 */
#define  SCI_RXCNT_3                         ((uint8_t)0x08)               /*!<Bit 3 */
#define  SCI_RXCNT_4                         ((uint8_t)0x10)               /*!<Bit 4 */

/* ====================== Bit definition for SCI_FR register  ====================== */
#define  SCI_FR_RXFE                         ((uint8_t)0x08)               /*!<RXFIFO empty status              */
#define  SCI_FR_RXFF                         ((uint8_t)0x04)               /*!<RXFIFO full status               */
#define  SCI_FR_TXFE                         ((uint8_t)0x02)               /*!<TXFIFO empty status              */
#define  SCI_FR_TXFF                         ((uint8_t)0x01)               /*!<TXFIFO full status               */

/* ====================== Bit definition for SCI_ISTAT register  ====================== */
#define  SCI_ISTAT_CARDPRESENT               ((uint16_t)0x0200)            /*!<Smart card present               */
#define  SCI_ISTAT_SCIDATAEN                 ((uint16_t)0x0100)            /*!<Tristate control for external off-chip buffer for data */
#define  SCI_ISTAT_SCIDATAOUTEN              ((uint16_t)0x0080)            /*!<Tristate output buffer control for data */
#define  SCI_ISTAT_SCICLKOUT                 ((uint16_t)0x0040)            /*!<Smart card clock output          */
#define  SCI_ISTAT_SCICLKEN                  ((uint16_t)0x0020)            /*!<Tristate control for external off-chip buffer for clock */
#define  SCI_ISTAT_SCICLKOUTEN               ((uint16_t)0x0010)            /*!<Tristate output buffer control for clock */
#define  SCI_ISTAT_DATAEN                    ((uint16_t)0x0008)            /*!<Enable smart card data           */
#define  SCI_ISTAT_CLKEN                     ((uint16_t)0x0004)            /*!<Enable smart card clock          */
#define  SCI_ISTAT_CRESET                    ((uint16_t)0x0002)            /*!<Controls smart card reset signal */
#define  SCI_ISTAT_POWER                     ((uint16_t)0x0001)            /*!<Controls smart card VCC          */

/* ====================== Bit definition for SCI_SYNCCR register  ====================== */
#define  SCI_SYNCCR_SELCLK                   ((uint8_t)0x02)                /*!<Selects the source of the smart card clock */
#define  SCI_SYNCCR_SELDATA                  ((uint8_t)0x01)                /*!<Selects the signal used to drive the in/out lline */

/* ====================== Bit definition for SCI_SYNCDATA register  ====================== */
#define  SCI_SYNCDATA_WCLKEN                 ((uint8_t)0x08)                /*!<Control the SCICLKEN line       */
#define  SCI_SYNCDATA_WDATAEN                ((uint8_t)0x04)                /*!<Control the SCIDATAEN line      */
#define  SCI_SYNCDATA_WCLK                   ((uint8_t)0x02)                /*!<drive the smart card clock      */
#define  SCI_SYNCDATA_WDATA                  ((uint8_t)0x01)                /*!<drive the in/out line           */

/* ====================== Bit definition for SCI_RAWSTAT register  ====================== */
#define  SCI_RAWSTAT_RCLK                    ((uint8_t)0x02)                /*!<Raw value of the clock          */
#define  SCI_RAWSTAT_RLDATA                  ((uint8_t)0x01)                /*!<Raw value of the in/out lline   */

/* ====================== Bit definition for SCI_IIR register  ====================== */
#define  SCI_IIR_TXTIDE                      ((uint16_t)0x0800)            /*!<Transmit FIFO tide mark          */
#define  SCI_IIR_RXTIDE                      ((uint16_t)0x0400)            /*!<Receive FIFO tide mark           */
#define  SCI_IIR_RTOUT                       ((uint16_t)0x0200)            /*!<Receive FIFO read timeout        */
#define  SCI_IIR_CHTOUT                      ((uint16_t)0x0100)            /*!<Between character timeout        */
#define  SCI_IIR_BLKTOUT                     ((uint16_t)0x0080)            /*!<Between block timeout            */
#define  SCI_IIR_ATRDTOUT                    ((uint16_t)0x0040)            /*!<ATR reception duration timeout   */
#define  SCI_IIR_ATRSTOUT                    ((uint16_t)0x0020)            /*!<ATR reception start timeout      */
#define  SCI_IIR_XERR                        ((uint16_t)0x0010)            /*!<Character transmission error     */
#define  SCI_IIR_CARDDN                      ((uint16_t)0x0008)            /*!<Smart Card powered down          */
#define  SCI_IIR_CARDUP                      ((uint16_t)0x0004)            /*!<Smart Card powered up            */
#define  SCI_IIR_CARDOUT                     ((uint16_t)0x0002)            /*!<Smart Card removed               */
#define  SCI_IIR_CARDIN                      ((uint16_t)0x0001)            /*!<Smart Card inserted              */


/* =========================================================================================================================== */
/* ================              Secure Digital memory card Device Controller                                ================= */
/* =========================================================================================================================== */

/* ====================== Bit definition for DMA1CR register  ====================== */
#define  SDDC_DMA1CR_DMA_EN             ((uint32_t)0x00000001)        

/* =========================================================================================================================== */
/* ================              SD host Interface                                                           ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for SDIO Transfer Mode register  ====================== */
#define  SDIO_TXMODE_BLKMULTI                ((uint16_t)0x0020)            /*!<Single/Multi-block selection     */
#define  SDIO_TXMODE_DIR_SEL                 ((uint16_t)0x0010)            /*!<Data transfer direction selection*/
#define  SDIO_TXMODE_AUTOCMD_EN              ((uint16_t)0x000C)            /*!<Auto CMD enable                  */
#define  SDIO_TXMODE_AUTOCMD_EN_0            ((uint16_t)0x0004)            /*!<Bit 0 */
#define  SDIO_TXMODE_AUTOCMD_EN_1            ((uint16_t)0x0008)            /*!<Bit 1 */
#define  SDIO_TXMODE_BLKCNT_EN               ((uint16_t)0x0002)            /*!<Block count enable               */
#define  SDIO_TXMODE_DMA_EN                  ((uint16_t)0x0001)            /*!<DMA enable                       */

/* ====================== Bit definition for SDIO Present state register  ====================== */
#define  SDIO_PRESENTSTA_CMD_LINE_LEVEL      ((uint32_t)0x01000000)        /*!<Command Line Signal Level        */
#define  SDIO_PRESENTSTA_DAT_LINE_LEVEL      ((uint32_t)0x00F00000)        /*!<DATA[3:0] Line Signal Level      */
#define  SDIO_PRESENTSTA_DAT_LINE_LEVEL_0    ((uint32_t)0x00100000)        /*!<Bit 0 */
#define  SDIO_PRESENTSTA_DAT_LINE_LEVEL_1    ((uint32_t)0x00200000)        /*!<Bit 1 */
#define  SDIO_PRESENTSTA_DAT_LINE_LEVEL_2    ((uint32_t)0x00400000)        /*!<Bit 2 */
#define  SDIO_PRESENTSTA_DAT_LINE_LEVEL_3    ((uint32_t)0x00800000)        /*!<Bit 3 */
#define  SDIO_PRESENTSTA_WR_PROTECT_LEVEL    ((uint32_t)0x00080000)        /*!<Write Protect Pin Level          */
#define  SDIO_PRESENTSTA_CARD_DETECT_LEVEL   ((uint32_t)0x00040000)        /*!<Card Detect Pin Level            */
#define  SDIO_PRESENTSTA_CARD_STABLE         ((uint32_t)0x00020000)        /*!<Card State Stable                */
#define  SDIO_PRESENTSTA_CARD_INSERT         ((uint32_t)0x00010000)        /*!<Card State Stable                */
#define  SDIO_PRESENTSTA_BUFF_READ           ((uint32_t)0x00000800)        /*!<Buffer Read Enable               */
#define  SDIO_PRESENTSTA_BUFF_WRITE          ((uint32_t)0x00000400)        /*!<Buffer Write Enable              */
#define  SDIO_PRESENTSTA_READ_TRAN_ACT       ((uint32_t)0x00000200)        /*!<Read Transfer Active             */
#define  SDIO_PRESENTSTA_WRITE_TRAN_ACT      ((uint32_t)0x00000100)        /*!<Write Transfer Active            */
#define  SDIO_PRESENTSTA_DAT_LINE_ACT        ((uint32_t)0x00000004)        /*!<Data Line Active                 */
#define  SDIO_PRESENTSTA_DAT_INHIBIT         ((uint32_t)0x00000002)        /*!<Command Inhibit(DAT)             */
#define  SDIO_PRESENTSTA_CMD_INHIBIT         ((uint32_t)0x00000001)        /*!<Command Inhibit(CMD)             */

/* ====================== Bit definition for SDIO Host Control 1 register  ====================== */
#define  SDIO_CTRL1_CARD_DETECT_SIGNAL       ((uint8_t)0x80)               /*!<Card Detect Signal Selection     */
#define  SDIO_CTRL1_CARD_DETECT_TEST         ((uint8_t)0x40)               /*!<Card Detect Test Level           */
#define  SDIO_CTRL1_BUS_WIDTH_8BIT           ((uint8_t)0x20)               /*!<Extended Data Transfer Width     */
#define  SDIO_CTRL1_USE_SDMA                 ((uint8_t)0x18)               /*!<Extended Data Transfer Width     */
#define  SDIO_CTRL1_USE_SDMA_0               ((uint8_t)0x08)               /*!<Bit 0 */
#define  SDIO_CTRL1_USE_SDMA_1               ((uint8_t)0x10)               /*!<Bit 1 */
#define  SDIO_CTRL1_HI_SPEED                 ((uint8_t)0x04)               /*!<High Speed Enable                */
#define  SDIO_CTRL1_BUS_WIDTH_4BIT           ((uint8_t)0x02)               /*!<Data Width                       */
#define  SDIO_CTRL1_LED_ON                   ((uint8_t)0x01)               /*!<Led Control                      */

/* ====================== Bit definition for SDIO Power Control register  ====================== */
#define  SDIO_PWRCTRL_POWER                  ((uint8_t)0x0E)               /*!<SD Bus Voltage Select           */
#define  SDIO_PWRCTRL_POWER_0                ((uint8_t)0x02)               /*!<Bit 0 */
#define  SDIO_PWRCTRL_POWER_1                ((uint8_t)0x04)               /*!<Bit 1 */
#define  SDIO_PWRCTRL_POWER_2                ((uint8_t)0x08)               /*!<Bit 2 */
#define  SDIO_PWRCTRL_POWER_ON               ((uint8_t)0x01)               /*!<SD Bus Power                    */

/* ====================== Bit definition for SDIO Block Gap Control register  ====================== */
#define  SDIO_BLKGAPCTRL_INT_AT_BLOCK_GAP    ((uint8_t)0x08)               /*!<Interrupt at Block Gap          */
#define  SDIO_BLKGAPCTRL_READ_WAIT_CTL       ((uint8_t)0x04)               /*!<Read Wait Control               */
#define  SDIO_BLKGAPCTRL_CONTINUE_REQ        ((uint8_t)0x02)               /*!<Continue Request                */
#define  SDIO_BLKGAPCTRL_STOP_AT_BLOCK_GAP   ((uint8_t)0x01)               /*!<Stop at Block Gap               */

/* ====================== Bit definition for SDIO Clock Control register  ====================== */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO        ((uint16_t)0xFF00)            /*!<SD Clock Frequency Value[7:0]   */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_0      ((uint16_t)0x0100)            /*!<Bit 0 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_1      ((uint16_t)0x0200)            /*!<Bit 1 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_2      ((uint16_t)0x0400)            /*!<Bit 2 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_3      ((uint16_t)0x0800)            /*!<Bit 3 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_4      ((uint16_t)0x1000)            /*!<Bit 4 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_5      ((uint16_t)0x2000)            /*!<Bit 5 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_6      ((uint16_t)0x4000)            /*!<Bit 6 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_LO_7      ((uint16_t)0x8000)            /*!<Bit 7 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_HI        ((uint16_t)0x00C0)            /*!<SD Clock Frequency Value[9:8]   */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_HI_0      ((uint16_t)0x0040)            /*!<Bit 0 */
#define  SDIO_CLKCTRL_SDCLK_DIVIDE_HI_1      ((uint16_t)0x0080)            /*!<Bit 1 */
#define  SDIO_CLKCTRL_SDCLK_GEN_SEL          ((uint16_t)0x0020)            /*!<This bit is always set to zero  */
#define  SDIO_CLKCTRL_SDCLK_EN               ((uint16_t)0x0004)            /*!<SD Clock Enable                 */
#define  SDIO_CLKCTRL_INTERNAL_CLK_STABLE    ((uint16_t)0x0002)            /*!<Internal Clock Stable           */
#define  SDIO_CLKCTRL_INTERNAL_CLK_EN        ((uint16_t)0x0001)            /*!<Internal Clock Enable           */

/* ====================== Bit definition for SDIO Software Reset register  ====================== */
#define  SDIO_SOFTRST_DAT                    ((uint8_t)0x04)               /*!<Software Reset for Data Line    */
#define  SDIO_SOFTRST_CMD                    ((uint8_t)0x02)               /*!<Software Reset for Command Line */
#define  SDIO_SOFTRST_ALL                    ((uint8_t)0x01)               /*!<Software Reset for All          */

/* ====================== Bit definition for SDIO Normal Interrupt Status register  ====================== */
#define  SDIO_ISR_ERR                        ((uint16_t)0x8000)            /*!<Error Interrupt                 */
#define  SDIO_ISR_CMD_QUEUING                ((uint16_t)0x4000)            /*!<Command Queuing Interrupt       */
#define  SDIO_ISR_RE_TUNING                  ((uint16_t)0x1000)            /*!<Re-Tuning Event                 */
#define  SDIO_ISR_INT_C                      ((uint16_t)0x0800)            /*!<INT_C                           */
#define  SDIO_ISR_INT_B                      ((uint16_t)0x0400)            /*!<INT_B                           */
#define  SDIO_ISR_INT_A                      ((uint16_t)0x0200)            /*!<INT_A                           */
#define  SDIO_ISR_CARD_INTR                  ((uint16_t)0x0100)            /*!<Card Interrupt                  */
#define  SDIO_ISR_CARD_REMOVE                ((uint16_t)0x0080)            /*!<Card Remove                     */
#define  SDIO_ISR_CARD_INSERT                ((uint16_t)0x0040)            /*!<Card Insert                     */
#define  SDIO_ISR_BUFF_READ_READY            ((uint16_t)0x0020)            /*!<Buffer Read Ready               */
#define  SDIO_ISR_BUFF_WRITE_READY           ((uint16_t)0x0010)            /*!<Buffer Write Ready              */
#define  SDIO_ISR_DMA                        ((uint16_t)0x0008)            /*!<DMA Interrupt                   */
#define  SDIO_ISR_BLKGAP                     ((uint16_t)0x0004)            /*!<Block Gap Event                 */
#define  SDIO_ISR_DATA_COMPLETE              ((uint16_t)0x0002)            /*!<Transfer Complete               */
#define  SDIO_ISR_CMD_COMPLETE               ((uint16_t)0x0001)            /*!<Command Complete                */

/* ====================== Bit definition for SDIO Error Interrupt Status register  ====================== */
#define  SDIO_ERRISR_TUNING                  ((uint16_t)0x0400)            /*!<Tuning Error                    */
#define  SDIO_ERRISR_ADMA                    ((uint16_t)0x0200)            /*!<ADMA Error                      */
#define  SDIO_ERRISR_AUTO_CMD                ((uint16_t)0x0100)            /*!<Auto CMD 12 Error               */
#define  SDIO_ERRISR_CURR_LIMIT              ((uint16_t)0x0080)            /*!<Current Limit Error             */
#define  SDIO_ERRISR_DATA_ENDBIT             ((uint16_t)0x0040)            /*!<Data End Bit Error              */
#define  SDIO_ERRISR_DATA_CRC                ((uint16_t)0x0020)            /*!<Data CRC Error                  */
#define  SDIO_ERRISR_DATA_TIMEOUT            ((uint16_t)0x0010)            /*!<Data Timeout Error              */
#define  SDIO_ERRISR_CMD_INDEX               ((uint16_t)0x0008)            /*!<Command Index Error             */
#define  SDIO_ERRISR_CMD_ENDBIT              ((uint16_t)0x0004)            /*!<Command End Bit Error           */
#define  SDIO_ERRISR_CMD_CRC                 ((uint16_t)0x0002)            /*!<Command CRC Error               */
#define  SDIO_ERRISR_CMD_TIMEOUT             ((uint16_t)0x0001)            /*!<Command Timeout Error           */

/* ====================== Bit definition for SDIO Host Control 2 register  ====================== */
#define  SDIO_CTRL2_PRESET_VAL_EN            ((uint16_t)0x8000)            /*!<Preset Value Enable             */
#define  SDIO_CTRL2_ASYNC_INT_EN             ((uint16_t)0x4000)            /*!<Asynchronous Interrupt Enable   */
#define  SDIO_CTRL2_SMPL_CLCK_SELECT         ((uint16_t)0x0080)            /*!<Sampling Clock Enable           */
#define  SDIO_CTRL2_EXECUTE_TUNING           ((uint16_t)0x0040)            /*!<Execute Tuning                  */
#define  SDIO_CTRL2_DRV_STR_SELECT           ((uint16_t)0x0030)            /*!<Driver Strength Select          */
#define  SDIO_CTRL2_DRV_STR_SELECT_0         ((uint16_t)0x0010)            /*!<Bit 0 */
#define  SDIO_CTRL2_DRV_STR_SELECT_1         ((uint16_t)0x0020)            /*!<Bit 1 */
#define  SDIO_CTRL2_1V8_SIGNAL               ((uint16_t)0x0008)            /*!<1.8V Signaling Enable           */
#define  SDIO_CTRL2_UHS_MODE_MASK            ((uint16_t)0x0007)            /*!<UHS Mode Select                 */
#define  SDIO_CTRL2_UHS_MODE_MASK_0          ((uint16_t)0x0001)            /*!<Bit 0 */
#define  SDIO_CTRL2_UHS_MODE_MASK_1          ((uint16_t)0x0002)            /*!<Bit 1 */
#define  SDIO_CTRL2_UHS_MODE_MASK_2          ((uint16_t)0x0004)            /*!<Bit 2 */

/* ====================== Bit definition for Capabilities 0/1 register  ====================== */
#define  SDIO_CAPABILITY_CLK_MULTI           ((uint64_t)0x00FF000000000000) /*!<Clock Multiplier               */
#define  SDIO_CAPABILITY_RE_TUNING           ((uint64_t)0x0000C00000000000) /*!<Re_Tuning Mode                 */
#define  SDIO_CAPABILITY_SDR50_TUNING        ((uint64_t)0x0000400000000000) /*!<Use Tuning for SDR50           */
#define  SDIO_CAPABILITY_TIMER_RE_TUNING     ((uint64_t)0x00000F0000000000) /*!<Timer Count for Re_Tuning      */
#define  SDIO_CAPABILITY_DRV_D_SUPPORT       ((uint64_t)0x0000004000000000) /*!<Driver Type D Support          */
#define  SDIO_CAPABILITY_DRV_C_SUPPORT       ((uint64_t)0x0000002000000000) /*!<Driver Type C Support          */
#define  SDIO_CAPABILITY_DRV_A_SUPPORT       ((uint64_t)0x0000001000000000) /*!<Driver Type A Support          */
#define  SDIO_CAPABILITY_DDR50_SUPPORT       ((uint64_t)0x0000000400000000) /*!<DDR50 Support                  */
#define  SDIO_CAPABILITY_SDR104_SUPPORT      ((uint64_t)0x0000000200000000) /*!<SDR104 Support                 */
#define  SDIO_CAPABILITY_SDR50_SUPPORT       ((uint64_t)0x0000000100000000) /*!<SDR50 Support                  */
#define  SDIO_CAPABILITY_SLOT_TYPE           ((uint64_t)0x00000000C0000000) /*!<Slot Type                      */
#define  SDIO_CAPABILITY_ASYNC_INT_SUPPORT   ((uint64_t)0x0000000020000000) /*!<Asynchronous Interrupt Support */
#define  SDIO_CAPABILITY_BUS64_SUPPORT       ((uint64_t)0x0000000010000000) /*!<64-bit System Bus Support      */
#define  SDIO_CAPABILITY_VOL_1V8_SUPPORT     ((uint64_t)0x0000000004000000) /*!<Voltage Supports 1.8V          */
#define  SDIO_CAPABILITY_VOL_3V0_SUPPORT     ((uint64_t)0x0000000002000000) /*!<Voltage Supports 3.0V          */
#define  SDIO_CAPABILITY_VOL_3V3_SUPPORT     ((uint64_t)0x0000000001000000) /*!<Voltage Supports 3.3V          */
#define  SDIO_CAPABILITY_SUSPEND_SUPPORT     ((uint64_t)0x0000000000800000) /*!<Suspend/Resume Support         */
#define  SDIO_CAPABILITY_SDMA_SUPPORT        ((uint64_t)0x0000000000400000) /*!<SDMA Supports                  */
#define  SDIO_CAPABILITY_HIGH_SPEED_SUPPORT  ((uint64_t)0x0000000000200000) /*!<High Speed Support             */
#define  SDIO_CAPABILITY_ADMA1_SUPPORT       ((uint64_t)0x0000000000100000) /*!<ADMA1 Support                  */
#define  SDIO_CAPABILITY_ADMA2_SUPPORT       ((uint64_t)0x0000000000080000) /*!<ADMA2 Support                  */
#define  SDIO_CAPABILITY_BUS_8BIT_SUPPORT    ((uint64_t)0x0000000000040000) /*!<8-bit Support for Embedded Device */
#define  SDIO_CAPABILITY_MAX_BLK_LENGTH      ((uint64_t)0x0000000000030000) /*!<Maximum Block Length           */
#define  SDIO_CAPABILITY_BASE_CLK_FREQ       ((uint64_t)0x000000000000FF00) /*!<Base Clock Frequency For SD Clock */
#define  SDIO_CAPABILITY_TIMEOUT_CLK_UNIT    ((uint64_t)0x0000000000000080) /*!<Timeout Clock Unit             */
#define  SDIO_CAPABILITY_TIMEOUT_CLK_FREQ    ((uint64_t)0x000000000000003F) /*!<Timeout Clock Frequency        */


/* =========================================================================================================================== */
/* ================              Serial Peripheral Interface                                         ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for SPI_I2S_CR0 register  ====================== */
#define SPI_I2S_CR0_LCDDCX   				((uint32_t)0x200000) 			/* LCD D/CX value */
#define SPI_I2S_CR0_LCDDCXS  				((uint32_t)0x100000) 			/* LCD D/CX Select */
#define SPI_I2S_CR0_SPICONTX 				((uint32_t)0x80000)  			/* SPI Continuous Transfer control */
#define SPI_I2S_CR0_FLASHTX  				((uint32_t)0x40000)  			/* FLASH Transmit control */
#define SPI_I2S_CR0_FSFSBK   				((uint32_t)0x20000)  			/* fs_in feedback select */
#define SPI_I2S_CR0_SCLKFDBK 				((uint32_t)0x10000)  			/* sclk_in feedback select */
#define SPI_I2S_CR0_SPIFSPO  				((uint16_t)0x8000)   			/* Frame/Sync. polarity for the SPI mode */
#define SPI_I2S_CR0_FFMT     				((uint16_t)0x7000)   			/* FFMT[14:12] bits Frame format*/
#define SPI_I2S_CR0_FFMT_SSP 				((uint16_t)0x0000)   			/* Frame format ssp */
#define SPI_I2S_CR0_FFMT_SPI 				((uint16_t)0x1000)   			/* Frame format spi */
#define SPI_I2S_CR0_FFMT_MWR 				((uint16_t)0x2000)   			/* Frame format microwire */
#define SPI_I2S_CR0_FFMT_I2S 				((uint16_t)0x3000)   			/* Frame format i2s */
#define SPI_I2S_CR0_FLASH    				((uint16_t)0x800)    			/* This bit indicates that the current application is SPI Flash */
#define SPI_I2S_CR0_FSDIST   				((uint16_t)0x100)    			/* Frame/Sync. and data distance */
#define SPI_I2S_CR0_LBM      				((uint8_t)0x80)      			/* Loopback mode */
#define SPI_I2S_CR0_LSB      				((uint8_t)0x40)      			/* Bit sequence indicator */
#define SPI_I2S_CR0_FSJSTFY  				((uint8_t)0x10)      			/* Data justify */

/* ====================== Bit definition for SPI_I2S_CR1 register  ====================== */
#define SPI_I2S_CR1_PDL     				((uint32_t)0xFF000000) 			/* PDL[31:24] Padding data length */
#define SPI_I2S_CR1_SDL     				((uint32_t)0x7F0000)   			/* SDL[22:16] Serial data length */
#define SPI_I2S_CR1_SCLKDIV 				((uint32_t)0xFFFF)     			/* SCLKDIV[15:0] SCLK divider */

/* ====================== Bit definition for SPI_I2S_CR2 register  ====================== */
#define SPI_I2S_CR2_FSOS   					((uint16_t)0xC00) 				/* FSOS[11:10] Frame/Sync. Output Select */
#define SPI_I2S_CR2_FS     					((uint16_t)0x200) 				/* Frame Sync. output */
#define SPI_I2S_CR2_TXEN   					((uint16_t)0x100) 				/* Transmit Function Enable */
#define SPI_I2S_CR2_RXEN   					((uint8_t)0x80)   				/* Receive Function Enable */
#define SPI_I2S_CR2_SSPRST 					((uint8_t)0x40)   				/* SSP Reset */
#define SPI_I2S_CR2_TXFCLR 					((uint8_t)0x8)    				/* Transmit FIFO Clear */
#define SPI_I2S_CR2_RXFCLR 					((uint8_t)0x4)    				/* Receive FIFO Clear */
#define SPI_I2S_CR2_TXDOE  					((uint8_t)0x2)    				/* Transmit Data Output Enable */
#define SPI_I2S_CR2_SSPEN  					((uint8_t)0x1)    				/* SSP Enable */

/* ====================== Bit definition for SPI_I2S_SR register  ====================== */
#define SPI_I2S_SR_TFVE 					((uint32_t)0x3F000) 			/* TFVE[17:12] Transmit FIFO Valid Entry */
#define SPI_I2S_SR_RFVE 					((uint16_t)0x3F0)   			/* RFVE[9:4] Receive FIFO Valid Entry */
#define SPI_I2S_SR_BUSY 					((uint8_t)0x4)      			/* Busy Indicator */
#define SPI_I2S_SR_TFNF 					((uint8_t)0x2)      			/* Transmit FIFO Not Full */
#define SPI_I2S_SR_RFF  					((uint8_t)0x1)      			/* Receive FIFO Full */

/* ====================== Bit definition for SPI_I2S_ICR register  ====================== */
#define SPI_I2S_ICR_TXCIEN      			((uint32_t)0x40000) 			/* Transmit Data Complete Interrupt Enable */
#define SPI_I2S_ICR_RFTHOD_UINT 			((uint32_t)0x20000) 			/* Receive FIFO Threshold Unit */
#define SPI_I2S_ICR_TFTHOD      			((uint32_t)0x1F000) 			/* TFTHOD[16:12] Transmit FIFO Threshold */
#define SPI_I2S_ICR_RFTHOD      			((uint32_t)0xF80)   			/* RFTHOD[11:7] Receive FIFO Threshold */
#define SPI_I2S_ICR_TFDMAEN     			((uint8_t)0x20)     			/* Transmit DMA Request Enable */
#define SPI_I2S_ICR_RFDMAEN     			((uint8_t)0x10)     			/* Receive DMA Request Enable */
#define SPI_I2S_ICR_TFTHIEN     			((uint8_t)0x8)      			/* Transmit FIFO Threshold Interrupt Enable */
#define SPI_I2S_ICR_RFTHIEN     			((uint8_t)0x4)      			/* Receive FIFO Threshold Interrupt Enable */
#define SPI_I2S_ICR_TFURIEN     			((uint8_t)0x2)      			/* Transmit FIFO Underrun Interrupt Enable */
#define SPI_I2S_ICR_RFORIEN     			((uint8_t)0x1)      			/* Receive FIFO Overrun Interrupt Enable */

/* ====================== Bit definition for SPI_I2S_ISR register  ====================== */
#define SPI_I2S_ISR_TXCI  					((uint8_t)0x20) 				/* Transmit Data Complete Interrupt */
#define SPI_I2S_ISR_TFTHI 					((uint8_t)0x8)  				/* Transmit FIFO Threshold Interrupt */
#define SPI_I2S_ISR_RFTHI 					((uint8_t)0x4)  				/* Receive FIFO Threshold Interrupt */
#define SPI_I2S_ISR_TFURI 					((uint8_t)0x2)  				/* Transmit FIFO Underrun Interrupt */
#define SPI_I2S_ISR_RFORI 					((uint8_t)0x1)  				/* Receive FIFO Overrun Interrupt */

/* ====================== Bit definition for SPI_I2S_CR3 register  ====================== */
#define SPI_I2S_CR3_DPDL   					((uint32_t)0xFF0000) 			/* DPDL[23:16] Different Padding Data Length */
#define SPI_I2S_CR3_DPDLEN 					((uint16_t)0x1000)   			/* Different Padding Data Length Enable */
#define SPI_I2S_CR3_CPL    					((uint16_t)0x3FF)    			/* PCL[9:0] Padding Cycle Length(SPI only) */



/* =========================================================================================================================== */
/* ================              Synchronous Serial Interface                                                ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for DMA1CR register  ====================== */
#define SSI_CTRLR0_SSTE                 ((uint32_t)0x01000000)  /* Slave Select Toggle Enable */
#define SSI_CTRLR0_SPI_FRF              ((uint32_t)0x00600000)  /* SSI Frame Format */
#define SSI_CTRLR0_DFS32                ((uint32_t)0x001F0000)  /* Data Frame Size */
#define SSI_CTRLR0_CFS                  ((uint32_t)0x0000F000)  /* Control Frame Size */
#define SSI_CTRLR0_SLV_OE               ((uint32_t)0x00000400)  /* Slave Output Enable */
#define SSI_CTRLR0_TMOD                 ((uint32_t)0x00000300)  /* Transfer Mode */
#define SSI_CTRLR0_SCPOL                ((uint32_t)0x00000080)  /* Serial Clock Polarity */
#define SSI_CTRLR0_SCPH                 ((uint32_t)0x00000040)  /* Serial Clock Phase */
#define SSI_CTRLR0_FRF                  ((uint32_t)0x00000030)  /* Frame Format */

/* ====================== Bit definition for CTRLR1 register  ====================== */
#define SSI_CTRLR1_NDF                  ((uint32_t)0x0000FFFF)  /* Number of Data Frames */

/* ====================== Bit definition for SSIENR register  ====================== */
#define SSI_SSIENR_SSI_EN               ((uint32_t)0x00000001)  /* SSI Enable */

/* ====================== Bit definition for MWCR register  ====================== */
#define SSI_MWCR_MHS                    ((uint32_t)0x00000004)  /* HANDSHAKE. */
#define SSI_MWCR_MDD                    ((uint32_t)0x00000002)  /* data direction. */
#define SSI_MWCR_MWMOD                  ((uint32_t)0x00000001)  /* sequential or no sequential. */

/* ====================== Bit definition for SER register  ====================== */
#define SSI_SER_SER                     ((uint32_t)0x00000001)  /* Slave Select Enable */

/* ====================== Bit definition for BAUD register  ====================== */
#define SSI_BAUDR_SCLDIV                ((uint32_t)0x0000FFFF)  /* SSI Clock Divider */

/* ====================== Bit definition for TXFTLR register  ====================== */
#define SSI_TXFTLR_TFT                  ((uint32_t)0x0000003F)  /* Transmit FIFO Threshold */

/* ====================== Bit definition for RXFTLR register  ====================== */
#define SSI_RXFTLR_RFT                  ((uint32_t)0x0000003F)  /* Receive FIFO Threshold */

/* ====================== Bit definition for TXFLR register  ====================== */
#define SSI_TXFLR_TXTFL                 ((uint32_t)0x00000040)  /* Transmit FIFO Level */

/* ====================== Bit definition for RXFLR register  ====================== */
#define SSI_RXFLR_RXTFL                 ((uint32_t)0x00000040)  /* Receive FIFO Level */

/* ====================== Bit definition for SR register  ====================== */
#define SSI_SR_DCOL                     ((uint32_t)0x00000040)  /* Data Collision Error */
#define SSI_SR_TXE                      ((uint32_t)0x00000020)  /* Transmission Error */
#define SSI_SR_RXFF                     ((uint32_t)0x00000010)  /* Receive FIFO Full */
#define SSI_SR_RFNE                     ((uint32_t)0x00000008)  /* Receive FIFO Not Empty */
#define SSI_SR_TFE                      ((uint32_t)0x00000004)  /* Transmit FIFO Empty */
#define SSI_SR_TFNF                     ((uint32_t)0x00000002)  /* Transmit FIFO Not Full */
#define SSI_SR_BUSY                     ((uint32_t)0x00000001)  /* SSI Busy Flag. */

/* ====================== Bit definition for IMR register  ====================== */
#define SSI_IMR_MSTIM                   ((uint32_t)0x00000020)  /* Multi-Master Contention Interrupt Mask */
#define SSI_IMR_RXFIM                   ((uint32_t)0x00000010)  /* Receive FIFO Full Interrupt Mask */
#define SSI_IMR_RXOIM                   ((uint32_t)0x00000008)  /* Receive FIFO Overflow Interrupt Mask */
#define SSI_IMR_RXUIM                   ((uint32_t)0x00000004)  /* Receive FIFO Underflow Interrupt Mask */
#define SSI_IMR_TXOIM                   ((uint32_t)0x00000002)  /* Transmit FIFO Overflow Interrupt Mask */
#define SSI_IMR_TXEIM                   ((uint32_t)0x00000001)  /* Transmit FIFO Empty Interrupt Mask */

/* ====================== Bit definition for ISR register  ====================== */
#define SSI_ISR_MSTIS                   ((uint32_t)0x00000020)  /* Multi-Master Contention Interrupt Status. */
#define SSI_ISR_RXFIS                   ((uint32_t)0x00000010)  /* Receive FIFO Full Interrupt Status. */
#define SSI_ISR_RXOIS                   ((uint32_t)0x00000008)  /* Receive FIFO Overflow Interrupt Status. */
#define SSI_ISR_RXUIS                   ((uint32_t)0x00000004)  /* Receive FIFO Underflow Interrupt Status. */
#define SSI_ISR_TXOIS                   ((uint32_t)0x00000002)  /* Transmit FIFO Overflow Interrupt Status. */
#define SSI_ISR_TXEIS                   ((uint32_t)0x00000001)  /* Transmit FIFO Empty Interrupt Status. */

/* ====================== Bit definition for RISR register  ====================== */
#define SSI_RISR_MSTIR                  ((uint32_t)0x00000020)  /* Multi-Master Contention Raw Interrupt Status. */
#define SSI_RISR_RXFIR                  ((uint32_t)0x00000010)  /* Receive FIFO Full Raw Interrupt Status. */
#define SSI_RISR_RXOIR                  ((uint32_t)0x00000008)  /* Receive FIFO Overflow Raw Interrupt Status. */
#define SSI_RISR_RXUIR                  ((uint32_t)0x00000004)  /* Receive FIFO Underflow Raw Interrupt Status. */
#define SSI_RISR_TXOIR                  ((uint32_t)0x00000002)  /* Transmit FIFO Overflow Raw Interrupt Status. */
#define SSI_RISR_TXEIR                  ((uint32_t)0x00000001)  /* Transmit FIFO Empty Raw Interrupt Status. */

/* ====================== Bit definition for TXOICR register  ====================== */
#define SSI_TXOICR_TXOICR               ((uint32_t)0x00000001)  /* Clear Transmit FIFO Overflow Interrupt */

/* ====================== Bit definition for RXOICR register  ====================== */
#define SSI_RXOICR_RXOICR               ((uint32_t)0x00000001)  /* Clear Receive FIFO Overflow Interrupt */

/* ====================== Bit definition for RXUICR register  ====================== */
#define SSI_RXUICR_RXUICR               ((uint32_t)0x00000001)  /* Clear Receive FIFO Underflow Interrupt */

/* ====================== Bit definition for MSTICR register  ====================== */
#define SSI_MSTICR_MSTICR               ((uint32_t)0x00000001)  /* Clear Multi-Master Contention Interrupt */

/* ====================== Bit definition for ICR register  ====================== */
#define SSI_ICR_ICR_OFFSET              ((uint32_t)0x00000001)  /* Clear Interrupts */

/* ====================== Bit definition for DMACR register  ====================== */
#define SSI_DMACR_TDMAE                 ((uint32_t)0x00000002) /* Transmit DMA Enable */
#define SSI_DMACR_RDMAE                 ((uint32_t)0x00000001) /* Receive DMA Enable */

/* ====================== Bit definition for DMATDLR register  ====================== */
#define SSI_DMATDLR_DMATDL              ((uint32_t)0x0000003F)  /* Transmit Data Level */

/* ====================== Bit definition for DMARDLR register  ====================== */
#define SSI_DMARDLR_DMARDL              ((uint32_t)0x0000003F)  /* Receive Data Level */

/* ====================== Bit definition for IDR register  ====================== */
#define SSI_IDR_IDCODE                  ((uint32_t)0xFFFFFFFF)  /* Identification code */

/* ====================== Bit definition for VERSION register  ====================== */
#define SSI_SSI_VERSION_ID              ((uint32_t)0xFFFFFFFF)  /* version ID */

/* ====================== Bit definition for RX_SAMPLE_DLY register  ====================== */
#define SSI_RX_SAMPLE_DLY_RSD           ((uint32_t)0x000000FF)  /* Rxd Sample Delay */

/* ====================== Bit definition for SSI_CTRLR0 register  ====================== */
#define SSI_SPI_CTRLR0_SSI_RXDS_EN      ((uint32_t)0x00040000)  /* Read data strobe enable bit */
#define SSI_SPI_CTRLR0_INST_DDR_EN      ((uint32_t)0x00020000)  /* Instruction DDR Enable bit */
#define SSI_SPI_CTRLR0_SSI_DDR_EN       ((uint32_t)0x00010000)  /* SSI DDR Enable bit */
#define SSI_SPI_CTRLR0_WAIT_CYCLES      ((uint32_t)0x0000F100)  /* Wait cycles */
#define SSI_SPI_CTRLR0_INST_L           ((uint32_t)0x00000300)  /* Instruction Length */
#define SSI_SPI_CTRLR0_ADDR_L           ((uint32_t)0x0000003C)  /* Address Length */
#define SSI_SPI_CTRLR0_TRANS_TYPE       ((uint32_t)0x00000003)  /* Address and instruction transfer format */

/* ====================== Bit definition for DRIVE_EDGE register  ====================== */
#define SSI_TXD_DRIVER_EDGE_TDE_OFFSET  ((uint32_t)0x000000FF)  /* TXD Drive edge */




/* =========================================================================================================================== */
/* ================                           Systerm Config                                                 ================= */
/* =========================================================================================================================== */

/* ====================== Bit definition for SYSCFG_PCR register  ====================== */
/*!< PCR PSW configuration */
#define SYSCFG_PCR_PSW                     ((uint32_t)0x000000FF)        /*!< power switch */  //TODO

#define SYSCFG_PCR_PSW_HSM                 ((uint32_t)0x00000001)        /*!< HSM power switch */  //TODO
#define SYSCFG_PCR_PSW_SRAM                ((uint32_t)0x00000002)        /*!< SRAM power switch */  //TODO
#define SYSCFG_PCR_PSW_GMAC0               ((uint32_t)0x00000004)        /*!< GMAC0 power switch */  //TODO
#define SYSCFG_PCR_PSW_GMAC1               ((uint32_t)0x00000008)        /*!< GMAC1 power switch */  //TODO
#define SYSCFG_PCR_PSW_CCORE               ((uint32_t)0x00000010)        /*!< CCORE power switch */  //TODO
#define SYSCFG_PCR_PSW_DDR                 ((uint32_t)0x00000012)        /*!< DDR power switch */  //TODO
#define SYSCFG_PCR_PSW_USB3                ((uint32_t)0x00000014)        /*!< USB3 power switch */  //TODO
#define SYSCFG_PCR_PSW_PCIE                ((uint32_t)0x00000018)        /*!< PCIE power switch */  //TODO

/*!< PCR ICC configuration */
#define SYSCFG_PCR_ICC                     ((uint32_t)0x0000FF00)        /*!< isolation cell control */  //TODO

#define SYSCFG_PCR_ICC_HSM                 ((uint32_t)0x00000100)        /*!< HSM isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_SRAM                ((uint32_t)0x00000200)        /*!< SRAM isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_GMAC0               ((uint32_t)0x00000400)        /*!< GMAC0 isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_GMAC1               ((uint32_t)0x00000800)        /*!< GMAC1 isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_CCORE               ((uint32_t)0x00001000)        /*!< CCORE isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_DDR                 ((uint32_t)0x00001200)        /*!< DDR isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_USB3                ((uint32_t)0x00001400)        /*!< USB3 isolation cell control */  //TODO
#define SYSCFG_PCR_ICC_PCIE                ((uint32_t)0x00001800)        /*!< PCIE isolation cell control */  //TODO

/* ====================  Bit definition for SYSCFG_ECR register  ====================== */
/*!< ECR EN configuration */
#define SYSCFG_ECR_EN                      ((uint32_t)0x00000001)        /*!< axi2sram ECC control bit */  //TODO

/* ====================  Bit definition for SYSCFG_ERMWEAR register  ================== */
/*!< ERMWEAR value */
#define SYSCFG_ERMWEAR_ADDR                ((uint32_t)0x0000FFFF)        /*!< ECC RMW error address */  //TODO

/* ====================  Bit definition for SYSCFG_ERMWECNT register  ================= */
/*!< ERMWECNT value */
#define SYSCFG_ERMWECNT_CNT                ((uint32_t)0x00000007)        /*!< ECC RMW error count */  //TODO

/* ====================  Bit definition for SYSCFG_ERDEAR register  =================== */
/*!< ERDEAR value */
#define SYSCFG_ERDEAR_ADDR                 ((uint32_t)0x00000007)        /*!< ECC read error address */  //TODO

/* ====================  Bit definition for SYSCFG_ERDECNT register =================== */
/*!< ERDECNT value */
#define SYSCFG_ERDECNT_CNT                 ((uint32_t)0x00000007)        /*!< ECC read error count */  //TODO


/* ====================  Bit definition for SYSCFG_AXICESR0 register  ====================== */
/*!< AXI CRC ERR Status */
#define SYSCFG_AXICESR0_PCIEDS0            ((uint32_t)0x00000001)        /*!< CRC Error Status of PCIE Data Slave0 */
#define SYSCFG_AXICESR0_DDRDS1             ((uint32_t)0x00000002)        /*!< CRC Error Status of DDR Data Slave1 */
#define SYSCFG_AXICESR0_FMC1XIPDS          ((uint32_t)0x00000004)        /*!< CRC Error Status of FMC1 XIP Data Slave */
#define SYSCFG_AXICESR0_FMC0XIPDS          ((uint32_t)0x00000008)        /*!< CRC Error Status of FMC0 XIP Data Slave */
#define SYSCFG_AXICESR0_X2PCFGDS           ((uint32_t)0x00000010)        /*!< CRC Error Status of CFG X2P bridge Data Slave */
#define SYSCFG_AXICESR0_X2PLPCDS           ((uint32_t)0x00000020)        /*!< CRC Error Status of LPC X2P bridge Data Slave */
#define SYSCFG_AXICESR0_X2PREEDS           ((uint32_t)0x00000040)        /*!< CRC Error Status of REE X2P bridge Data Slave */
#define SYSCFG_AXICESR0_X2HDS              ((uint32_t)0x00000080)        /*!< CRC Error Status of X2H bridge Data Slave*/
#define SYSCFG_AXICESR0_PCIEATRS           ((uint32_t)0x00000100)        /*!< CRC Error Status of PCIE AT Register Slave */
#define SYSCFG_AXICESR0_MCOREATRS           ((uint32_t)0x00000200)        /*!< CRC Error Status of Main CPU AT Register Slave */
#define SYSCFG_AXICESR0_MINTCRS            ((uint32_t)0x00000400)        /*!< CRC Error Status of MINTC Register Slave */
#define SYSCFG_AXICESR0_USB3RS             ((uint32_t)0x00000800)        /*!< CRC Error Status of USB3 Register Slave */
#define SYSCFG_AXICESR0_PCIERS             ((uint32_t)0x00001000)        /*!< CRC Error Status of PCIE Register Slave */
#define SYSCFG_AXICESR0_GMAC1RS            ((uint32_t)0x00002000)        /*!< CRC Error Status of GMAC1 Register Slave */
#define SYSCFG_AXICESR0_GMAC0RS            ((uint32_t)0x00004000)        /*!< CRC Error Status of GMAC0 Register Slave */
#define SYSCFG_AXICESR0_HSMMBDS            ((uint32_t)0x00008000)        /*!< CRC Error Status of HSM MB Data Slave */
#define SYSCFG_AXICESR0_HSMSYMDS           ((uint32_t)0x00010000)        /*!< CRC Error Status of HSM SYM Data slave */
#define SYSCFG_AXICESR0_CCPUDS             ((uint32_t)0x00020000)        /*!< CRC Error Status of Co-CPU Data slave */
#define SYSCFG_AXICESR0_SRAM               ((uint32_t)0x00040000)        /*!< CRC Error Status of SRAM */
#define SYSCFG_AXICESR0_ROM                ((uint32_t)0x00080000)        /*!< CRC Error Status of ROM */
#define SYSCFG_AXICESR0_PCIEDS1            ((uint32_t)0x00100000)        /*!< CRC Error Status of PCIE Data Slave1 */
#define SYSCFG_AXICESR0_DDRDS2             ((uint32_t)0x00200000)        /*!< CRC Error Status of DDR Data Slave2 */
#define SYSCFG_AXICESR0_X2XDS              ((uint32_t)0x00400000)        /*!< CRC Error Status of X2X Data Slave */
#define SYSCFG_AXICESR0_X2XM               ((uint32_t)0x00800000)        /*!< CRC Error Status of X2X Master */
#define SYSCFG_AXICESR0_PCIEM              ((uint32_t)0x01000000)        /*!< CRC Error Status of PCIE Master */
#define SYSCFG_AXICESR0_DMA1M              ((uint32_t)0x02000000)        /*!< CRC Error Status of DMA1 Master */
#define SYSCFG_AXICESR0_DMA0M              ((uint32_t)0x04000000)        /*!< CRC Error Status of DMA0 Master */
#define SYSCFG_AXICESR0_H2XHM              ((uint32_t)0x08000000)        /*!< CRC Error Status of H2XH bridge Master */
#define SYSCFG_AXICESR0_H2XLM              ((uint32_t)0x10000000)        /*!< CRC Error Status of H2XL bridge Master */
#define SYSCFG_AXICESR0_H2XHSMM            ((uint32_t)0x20000000)        /*!< CRC Error Status of HSM H2X bridge Master */
#define SYSCFG_AXICESR0_HSMSYMM            ((uint32_t)0x40000000)        /*!< CRC Error Status of HSM SYM Master */
#define SYSCFG_AXICESR0_MINTCM             ((uint32_t)0x80000000)        /*!< CRC Error Status of MINTC Master */

/* ====================  Bit definition for SYSCFG_AXICESR0 register  ====================== */
/*!< AXI CRC ERR Status */
#define SYSCFG_AXICESR1_CCPUM              ((uint32_t)0x00000001)        /*!< CRC Error Status of Co-CPU Master */
#define SYSCFG_AXICESR1_MCOREM              ((uint32_t)0x00000002)        /*!< CRC Error Status of Main CPU Master */
#define SYSCFG_AXICESR1_USB3M              ((uint32_t)0x00000008)        /*!< CRC Error Status of USB3 Master */
#define SYSCFG_AXICESR1_GMAC1M             ((uint32_t)0x00000010)        /*!< CRC Error Status of GMAC1 Master */
#define SYSCFG_AXICESR1_GMAC0M             ((uint32_t)0x00000020)        /*!< CRC Error Status of GMAC0 Master */


/* ====================  Bit definition for SYSCFG_AXICECNT register  ====================== */
/*!< CRC ERR Count Value */
#define SYSCFG_AXICECNT_CNT                ((uint32_t)0x00000007)        /*!< AXI CRC Error Count */ //TODO

/* ====================  Bit definition for SYSCFG_AHBCESR register  ====================== */
/*!< AXI CRC ERR Status */
#define SYSCFG_AHBCESR_DDRDS3             ((uint32_t)0x00000001)         /*!< CRC Error Status of DDR Data Slave3 */
#define SYSCFG_AHBCESR_H2XHDS             ((uint32_t)0x00000002)         /*!< CRC Error Status of H2XH bridge Data Slave */
#define SYSCFG_AHBCESR_SDHC1RS            ((uint32_t)0x00000008)         /*!< CRC Error Status of SDHC1 Register Slave */
#define SYSCFG_AHBCESR_SDHC0RS            ((uint32_t)0x00000010)         /*!< CRC Error Status of SDHC0 Register Slave */
#define SYSCFG_AHBCESR_MAC1RS             ((uint32_t)0x00000020)         /*!< CRC Error Status of MAC1 Register Slave */
#define SYSCFG_AHBCESR_MAC0RS             ((uint32_t)0x00000040)         /*!< CRC Error Status of MAC0 Register Slave */
#define SYSCFG_AHBCESR_SDDCRS             ((uint32_t)0x00000080)         /*!< CRC Error Status of SDDC Register Slave */
#define SYSCFG_AHBCESR_SDHC2RS            ((uint32_t)0x00000100)         /*!< CRC Error Status of SDHC2 Register Slave */
#define SYSCFG_AHBCESR_USB2RS             ((uint32_t)0x00000200)         /*!< CRC Error Status of USB2 Register Slave */
#define SYSCFG_AHBCESR_FMS1CMDDS          ((uint32_t)0x00000400)         /*!< CRC Error Status of FMS1 CMD Data Slave */
#define SYSCFG_AHBCESR_FMS0CMDDS          ((uint32_t)0x00001000)         /*!< CRC Error Status of FMS0 CMD Data Slave */
#define SYSCFG_AHBCESR_AHBCRS             ((uint32_t)0x00002000)         /*!< CRC Error Status of AHBC Register Slave */
#define SYSCFG_AHBCESR_H2XLDS             ((uint32_t)0x00001000)         /*!< CRC Error Status of H2XL bridge Data Slave */
#define SYSCFG_AHBCESR_LTDCM              ((uint32_t)0x00002000)         /*!< CRC Error Status of LTDC Master */
#define SYSCFG_AHBCESR_MAC1M              ((uint32_t)0x00004000)         /*!< CRC Error Status of MAC1 Master */
#define SYSCFG_AHBCESR_MAC0M              ((uint32_t)0x00008000)         /*!< CRC Error Status of MAC0 Master */
#define SYSCFG_AHBCESR_SDHC2M             ((uint32_t)0x00010000)         /*!< CRC Error Status of SDHC2 Master */
#define SYSCFG_AHBCESR_SDHC1M             ((uint32_t)0x00020000)         /*!< CRC Error Status of SDHC1 Master */
#define SYSCFG_AHBCESR_SDHC0M             ((uint32_t)0x00040000)         /*!< CRC Error Status of SDHC0 Master */
#define SYSCFG_AHBCESR_USB2M              ((uint32_t)0x00080000)         /*!< CRC Error Status of USB2 Master */
#define SYSCFG_AHBCESR_X2HM               ((uint32_t)0x00080000)         /*!< CRC Error Status of X2H Master */

/* ====================  Bit definition for SYSCFG_AHBCECNT register  ====================== */
/*!< CRC ERR Count Value */
#define SYSCFG_AHBCECNT_CNT               ((uint32_t)0x00000007)         /*!< AHB CRC Error Count */ //TODO


/* =========================================================================================================================== */
/* ================                   TIM                                                                    ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for TIM_CR register  ====================== */
#define  TIM_CR_MODE                         ((uint32_t)0x00000003)         /*!<Counter MODE                   */
#define  TIM_CR_MODE_0                       ((uint32_t)0x00000001)         /*!<Bit 0 */
#define  TIM_CR_MODE_1                       ((uint32_t)0x00000002)         /*!<Bit 1 */
#define  TIM_CR_CEN                          ((uint32_t)0x00000004)         /*!<Counter enable                 */
#define  TIM_CR_UG                           ((uint32_t)0x00000008)         /*!<manual update generation       */
#define  TIM_CR_CCNE                         ((uint32_t)0x00000010)         /*!<Timer output inverter on/off   */
#define  TIM_CR_OPM                          ((uint32_t)0x00000020)         /*!<One pulse mode                 */


/* =========================================================================================================================== */
/* ================                   Universal Asynchronous Receiver Transmitter                            ================= */
/* =========================================================================================================================== */
/* ====================== Bit definition for IER register  ====================== */
#define UART_IER_CTSEN                      ((uint32_t)0x00000020)  /* CTS flow control enable */
#define UART_IER_RTSEN                      ((uint32_t)0x00000010)  /* RTS flow control enable */
#define UART_IER_MODEM                      ((uint32_t)0x00000008)  /* modem status interrupt enable */
#define UART_IER_RECEIVE_LINE               ((uint32_t)0x00000004)  /* receive line status interrupt enable */
#define UART_IER_THR_EMPTY                  ((uint32_t)0x00000002)  /* transmitter holding register empty interrupt enable */
#define UART_IER_RECEIVE_AVALIABLE          ((uint32_t)0x00000001)  /* receive data available interrupt enable */

/* ====================== Bit definition for IIR register  ====================== */
#define UART_IIR_FIFO_MODE_EN               ((uint32_t)0x000000C0)
#define UART_IIR_TXFIFO_FULL                ((uint32_t)0x00000010)
#define UART_IIR_FIFO_MODE_ONLY             ((uint32_t)0x00000008)

/* ====================== Bit definition for FCR register  ====================== */
#define UART_FCR_RXFIFO_TRGL                ((uint32_t)0x000000C0)
#define UART_FCR_TXFIFO_TRGL                ((uint32_t)0x00000030)
#define UART_FCR_DMA_MODE                   ((uint32_t)0x00000008)
#define UART_FCR_TXFIFO_RST                 ((uint32_t)0x00000004)
#define UART_FCR_RXFIFO_RST                 ((uint32_t)0x00000002)
#define UART_FCR_FIFO_EN                    ((uint32_t)0x00000001)

/* ====================== Bit definition for LCR register  ====================== */
#define UART_LCR_DLBA                       ((uint32_t)0x00000080)
#define UART_LCR_SET_BREAK                  ((uint32_t)0x00000040)
#define UART_LCR_STICK_PARITY               ((uint32_t)0x00000020)
#define UART_LCR_EVEN_PARITY                ((uint32_t)0x00000010)
#define UART_LCR_PARITY_EN                  ((uint32_t)0x00000008)
#define UART_LCR_STOP_BIT                   ((uint32_t)0x00000004)
#define UART_LCR_WL1                        ((uint32_t)0x00000002)
#define UART_LCR_WL0                        ((uint32_t)0x00000001)

/* ====================== Bit definition for MCR register  ====================== */
#define UART_MCR_OUT3                       ((uint32_t)0x00000040)
#define UART_MCR_DMA_MODE2                  ((uint32_t)0x00000020)
#define UART_MCR_LOOP                       ((uint32_t)0x00000010)
#define UART_MCR_OUT2                       ((uint32_t)0x00000008)
#define UART_MCR_OUT1                       ((uint32_t)0x00000004)
#define UART_MCR_RTS                        ((uint32_t)0x00000002)
#define UART_MCR_DTR                        ((uint32_t)0x00000001)

/* ====================== Bit definition for MCR register  ====================== */
#define UART_LSR_FIFO_DATA_ERR              ((uint32_t)0x00000080) /* FIFO Data Error */
#define UART_LSR_TRANS_EMPTY                ((uint32_t)0x00000040) /* Transmitter Empty */
#define UART_LSR_THR_EMPTY                  ((uint32_t)0x00000020) /* THR Empty */
#define UART_LSR_BREAK_INTR                 ((uint32_t)0x00000010) /* Break Interrupt */
#define UART_LSR_FRAMING_ERR                ((uint32_t)0x00000008) /* Framing Error */
#define UART_LSR_PARITY_ERR                 ((uint32_t)0x00000004) /* Parity Error */
#define UART_LSR_OVERRUN_ERR                ((uint32_t)0x00000002) /* Overrun Error */
#define UART_LSR_DATA_READY                 ((uint32_t)0x00000001) /* Data Ready */

/* ====================== Bit definition for MSR register  ====================== */
#define UART_MSR_DCD                        ((uint32_t)0x00000080)
#define UART_MSR_RI                         ((uint32_t)0x00000040)
#define UART_MSR_DSR                        ((uint32_t)0x00000020)
#define UART_MSR_CTS                        ((uint32_t)0x00000010)
#define UART_MSR_DELTA_DCD                  ((uint32_t)0x00000008)
#define UART_MSR_TRAL_EDGE_R1               ((uint32_t)0x00000004)
#define UART_MSR_DELTA_DSR                  ((uint32_t)0x00000002)
#define UART_MSR_DELTA_CTS                  ((uint32_t)0x00000001)

/* ====================== Bit definition for MDR register  ====================== */
#define UART_MDR_IR_INV_TX                  ((uint32_t)0x00000040)
#define UART_MDR_FIR_INV_RX                 ((uint32_t)0x00000020)
#define UART_MDR_DMA_EN                     ((uint32_t)0x00000010)
#define UART_MDR_FMEND_MD                   ((uint32_t)0x00000008)
#define UART_MDR_SIP_BYCPU                  ((uint32_t)0x00000004)
#define UART_MDR_MODE_SEL                   ((uint32_t)0x00000003)

/* ====================== Bit definition for ACR register  ====================== */
#define UART_ACR_SIR_PW                     ((uint32_t)0x00000080)
#define UART_ACR_STFF_TRGL                  ((uint32_t)0x00000060)
#define UART_ACR_SEND_SIP                   ((uint32_t)0x00000010)
#define UART_ACR_FORCE_ABORT                ((uint32_t)0x00000008)
#define UART_ACR_SET_EOT                    ((uint32_t)0x00000004)
#define UART_ACR_RX_EN                      ((uint32_t)0x00000002)
#define UART_ACR_TX_EN                      ((uint32_t)0x00000001)

/** @} */ /* End of group Peripheral_Registers_Bits_Definition */

/** @} */ /* End of group T690 */

/** @} */ /* End of group TIH */

#ifdef USE_STDPERIPH_DRIVER
  #include "t690_conf.h"
#endif /* USE_STDPERIPH_DRIVER */

#ifdef __cplusplus
}
#endif

#endif  /* __T690_H__ */
