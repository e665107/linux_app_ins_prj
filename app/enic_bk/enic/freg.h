#ifndef __FREG_H
#define __FREG_H

#include "stdint.h"

/* fake registers of each PF */
typedef enum
{
    FREG_CMD_ADD_L,
    FREG_CMD_ADD_H,
    FREG_CMD_TRIGGER,

    FREG_EVENT_ADDR_L,
    FREG_EVENT_ADDR_H,
    FREG_EVENT_READY,

    FREG_QUEUE_ISR0,
    FREG_QUEUE_ISR1,
    FREG_QUEUE_ISR2,
    FREG_QUEUE_ISR3,

    FREG_QUEUE_IE0,
    FREG_QUEUE_IE1,
    FREG_QUEUE_IE2,
    FREG_QUEUE_IE3,

    FREG_RDBAL0,
    FREG_RDBAL1,
    FREG_RDBAL2,
    FREG_RDBAL3,
    FREG_RDBAH0,
    FREG_RDBAH1,
    FREG_RDBAH2,
    FREG_RDBAH3,

    FREG_RDH0,  /* queue0 header */
    FREG_RDH1,  /* queue1 header */
    FREG_RDH2,  /* queue2 header */
    FREG_RDH3,  /* queue3 header */

    FREG_RDT0,  /* queue0 tail */
    FREG_RDT1,  /* queue0 tail */
    FREG_RDT2,  /* queue0 tail */
    FREG_RDT3,  /* queue0 tail */

    FREG_RBL0,
    FREG_RBL1,
    FREG_RBL2,
    FREG_RBL3,

    FREG_TDBAL0,
    FREG_TDBAL1,
    FREG_TDBAL2,
    FREG_TDBAL3,
    FREG_TDBAH0,
    FREG_TDBAH1,
    FREG_TDBAH2,
    FREG_TDBAH3,

    FREG_TDH0,
    FREG_TDH1,
    FREG_TDH2,
    FREG_TDH3,

    FREG_TDT0,
    FREG_TDT1,
    FREG_TDT2,
    FREG_TDT3,

    FREG_IPSEC_RX_CHKSUM,

    FREG_QCTRL0,
    FREG_QCTRL1,
    FREG_QCTRL2,
    FREG_QCTRL3,

    /* MAX */
    FREG_NUM,
} FREG_TYPETypeDef;

typedef struct
{
    uint32_t pf;
    uint32_t freg;
    uint32_t ramAddr;
    void (*write_resp)(uint32_t pf, uint32_t freg);
} FREG_ATMappingTypeDef;

void FREG_CMDTriggerHandler(uint32_t pf, uint32_t freg);
void FREG_QISRUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_QIEUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_QCTRLUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_TDTUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_RDTUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_TDBAHUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_RDBAHUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_RBLUpdateHandler(uint32_t pf, uint32_t freg);
void FREG_IPsecRxChecksumHandler(uint32_t pf, uint32_t freg);
#endif
