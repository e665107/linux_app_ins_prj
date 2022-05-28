#ifndef _HSM_INS_PROCESS_H
#define _HSM_INS_PROCESS_H

/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "qepn.h"


enum QHsmTstSignals {
    GO_UP = Q_USER_SIG,
    GO_DOWN,
    FLOOR_REACHED,
    MOV_SUB0,
    MOV_SUB1,
    TICK,
    DO_NOTHING
};



void hsm_ins_process_task_create(uint8_t priority_1);
void HAL_MutexUnlock(void *mutex);

void HAL_MutexLock(void *mutex);

void HAL_MutexDestroy(void *mutex);

void *HAL_MutexCreate(void);

#endif /* _HSM_INS_PROCESS_H */
