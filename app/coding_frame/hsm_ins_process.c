#ifdef HSM_INS_PROCESS
/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"
#include "qpn_port.h"

/* app */
#include "hsm_ins_process.h"

/* bsp */
#include "bsp_ll_uart.h"

/* func */
/* #include "hsm_f.h" */
#define HSM_INS_PROCESS_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

typedef struct QHsmTstTag {
    QHsm super;                                        /* extend class QHsm */
    /* extended state variables... */
} QHsmTst;



QHsmTst HSM_QHsmTst;/* the sole instance of the QHsmTst HSM */
QHsmTst HSM_QHsmTst_two;/* the sole instance of the QHsmTst HSM */
static void hsm_ins_process_task(void *parameter);
static void dispatch(QSignal sig);
static QSignal sig_detect(uint8_t time_cnt);
void QHsmTst_ctor(void);
QState QHsmTst_MOVING(QHsmTst *me);
QState QHsmTst_WAITING(QHsmTst *me);
QState QHsmTst_SUPER(QHsmTst *me);
QState QHsmTst_initial(QHsmTst *me);
QState QHsmTst_mov_sub_0(QHsmTst *me);
QState QHsmTst_mov_sub_1(QHsmTst *me);

void *lock;

static void hsm_ins_process_two_task(void *parameter);
static void dispatch_two(QSignal sig);
static QSignal sig_detect_two(uint8_t time_cnt);
void QHsmTst_ctor_two(void);
QState QHsmTst_MOVING_two(QHsmTst *me);
QState QHsmTst_WAITING_two(QHsmTst *me);
QState QHsmTst_SUPER_two(QHsmTst *me);
QState QHsmTst_initial_two(QHsmTst *me);
QState QHsmTst_mov_sub_0_two(QHsmTst *me);
QState QHsmTst_mov_sub_1_two(QHsmTst *me);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

void hsm_ins_process_task_create(uint8_t priority_1)
{
    xTaskCreate(hsm_ins_process_task, "hsm_ins_process_process", HSM_INS_PROCESS_TASK_STACK_SIZE, NULL, priority_1, NULL);

    xTaskCreate(hsm_ins_process_two_task, "hsm_ins_process_two", HSM_INS_PROCESS_TASK_STACK_SIZE, NULL, priority_1+1, NULL);

}

static void hsm_ins_process_task(void *parameter)
{
    /* static uint8_t state = 0; */
    static uint8_t time_cnt_temp = 0;

    (void) parameter;
    QHsmTst_ctor();/* instantiate the HSM */
    QHsm_init((QHsm *)&HSM_QHsmTst);/* take the initial transitioin */
    lock = HAL_MutexCreate();
    HAL_MutexDestroy(lock);
    for (;;)
    {
        QSignal sig;
        sig = sig_detect(time_cnt_temp);
        dispatch(sig); 
        vTaskDelay(100);
        time_cnt_temp++;
        if(time_cnt_temp == 30)
            time_cnt_temp = 0; 
    }
}

static QSignal sig_detect(uint8_t time_cnt)
{
    static QSignal sig_temp;
    /* sig_temp = GO_UP; */
    /* vTaskDelay(1000); */
    if(time_cnt == 10)
        sig_temp = GO_DOWN;
    else if(time_cnt == 20) {
        /* sig_temp = GO_UP; */
        sig_temp = MOV_SUB0;

    }
    else if(time_cnt == 25)
        sig_temp = MOV_SUB1;

    return sig_temp;
}

static void dispatch(QSignal sig)
{
    Q_SIG((QHsm *)&HSM_QHsmTst) = sig;
    QHsm_dispatch((QHsm *)&HSM_QHsmTst);/* dispatch the event */
}


/**
 * @brief Create a mutex.
 *
 * @retval NULL : Initialize mutex failed.
 * @retval NOT_NULL : The mutex handle.
 * @see None.
 * @note None.
 */
void *HAL_MutexCreate(void)
{
    QueueHandle_t sem;

    sem = xSemaphoreCreateMutex();
    if (0 == sem) {
        return NULL;
    }

    return sem;
}

/**
 * @brief Destroy the specified mutex object, it will release related resource.
 *
 * @param [in] mutex @n The specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexDestroy(void *mutex)
{
    QueueHandle_t sem;
    if (mutex == NULL) {
        return;
    }
    sem = (QueueHandle_t)mutex;
    vSemaphoreDelete(sem);
}

/**
 * @brief Waits until the specified mutex is in the signaled state.
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexLock(void *mutex)
{
    BaseType_t ret;
    QueueHandle_t sem;
    if (mutex == NULL) {
        return;
    }

    sem = (QueueHandle_t)mutex;
    ret = xSemaphoreTake(sem, 0xffffffff);
    while (pdPASS != ret) {
        ret = xSemaphoreTake(sem, 0xffffffff);
    }
}

/**
 * @brief Releases ownership of the specified mutex object..
 *
 * @param [in] mutex @n the specified mutex.
 * @return None.
 * @see None.
 * @note None.
 */
void HAL_MutexUnlock(void *mutex)
{
    QueueHandle_t sem;
    if (mutex == NULL) {
        return;
    }
    sem = (QueueHandle_t)mutex;
    (void)xSemaphoreGive(sem);
}

void QHsmTst_ctor(void)
{
    QHsm_ctor(&HSM_QHsmTst.super, (QStateHandler)&QHsmTst_initial);
}

QState QHsmTst_initial(QHsmTst *me)
{
    /* BSP_display("top-INIT;"); */
    /* srandom (time (0)); */
    //srandom (1);
    return Q_TRAN(&QHsmTst_WAITING);
}

QState QHsmTst_SUPER(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            printf("super-ENTRY\r\n");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            printf("super-EXIT\r\n");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            printf("super-INIT\r\n");
            return Q_TRAN(&QHsmTst_WAITING);
        }
    }
    printf("Super return to top\r\n");
    return Q_SUPER(&QHsm_top);
}

QState QHsmTst_WAITING(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("waiting in\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("waiting out\r\n");
                return Q_HANDLED();
            }

        case GO_DOWN:
            {
                printf("go down\r\n");
                return Q_TRAN(&QHsmTst_MOVING);
            }
        case GO_UP:
            {
                printf("go up\r\n");
                return Q_TRAN(&QHsmTst_MOVING);
            }
    }
    return Q_SUPER(&QHsmTst_SUPER);
}

QState QHsmTst_MOVING(QHsmTst *me)
{
    QState status_;
    switch (Q_SIG(me)) {

        case Q_ENTRY_SIG: {
            printf("moving-ENTR\r\n");
            status_ =  Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            printf("moving-EXIT\r\n");
            status_ =  Q_HANDLED();
        }
        case Q_INIT_SIG: {
            printf("moving-init\r\n");
            status_ = Q_TRAN(&QHsmTst_mov_sub_0);
            break;
        }
        case FLOOR_REACHED: {
            printf("floor-reached\r\n");
            status_ =  Q_TRAN(&QHsmTst_WAITING);
            break;
        }
        default:
            status_ =  Q_SUPER(&QHsmTst_SUPER);
            break;
    }
    return status_;
}

QState QHsmTst_mov_sub_0(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("mov_sub_0 in\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("mov_sub_0 out\r\n");
                return Q_HANDLED();
            }

        case MOV_SUB0:
            {
                printf("mov_sub0\r\n");
                return Q_TRAN(&QHsmTst_mov_sub_1);
            }
    }
    return Q_SUPER(&QHsmTst_MOVING);
}

QState QHsmTst_mov_sub_1(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("mov_sub_1 in\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("mov_sub_1 out\r\n");
                return Q_HANDLED();
            }

        case MOV_SUB1:
            {
                printf("mov_sub1\r\n");
                return Q_TRAN(&QHsmTst_mov_sub_0);;
            }
    }
    return Q_SUPER(&QHsmTst_MOVING);
}

static void hsm_ins_process_two_task(void *parameter)
{
    /* static uint8_t state = 0; */
    static uint8_t time_cnt_temp = 0;

    (void) parameter;
    QHsmTst_ctor_two();/* instantiate the HSM */
    QHsm_init((QHsm *)&HSM_QHsmTst_two);/* take the initial transitioin */
    
    for (;;)
    {
        QSignal sig;
        sig = sig_detect_two(time_cnt_temp);
        dispatch_two(sig); 
        vTaskDelay(100);
        time_cnt_temp++;
        if(time_cnt_temp == 30)
            time_cnt_temp = 0; 
    }
}

static QSignal sig_detect_two(uint8_t time_cnt)
{
    static QSignal sig_temp;
    /* sig_temp = GO_UP; */
    /* vTaskDelay(1000); */
    if(time_cnt == 10)
        sig_temp = GO_DOWN;
    else if(time_cnt == 20) {
        /* sig_temp = GO_UP; */
        sig_temp = MOV_SUB0;

    }
    else if(time_cnt == 25)
        sig_temp = MOV_SUB1;

    return sig_temp;
}

static void dispatch_two(QSignal sig)
{
    Q_SIG((QHsm *)&HSM_QHsmTst_two) = sig;
    QHsm_dispatch((QHsm *)&HSM_QHsmTst_two);/* dispatch the event */
}

void QHsmTst_ctor_two(void)
{
    QHsm_ctor(&HSM_QHsmTst_two.super, (QStateHandler)&QHsmTst_initial_two);
}

QState QHsmTst_initial_two(QHsmTst *me)
{
    /* BSP_display("top-INIT;"); */
    /* srandom (time (0)); */
    //srandom (1);
    return Q_TRAN(&QHsmTst_WAITING_two);
}

QState QHsmTst_SUPER_two(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG: {
            printf("super2-ENTRY\r\n");
            return Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            printf("super2-EXIT\r\n");
            return Q_HANDLED();
        }
        case Q_INIT_SIG: {
            printf("super2-INIT\r\n");
            return Q_TRAN(&QHsmTst_WAITING_two);
        }
    }
    printf("Super2 return to top\r\n");
    return Q_SUPER(&QHsm_top);
}

QState QHsmTst_WAITING_two(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("waiting in 2\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("waiting out 2\r\n");
                return Q_HANDLED();
            }

        case GO_DOWN:
            {
                printf("go down 2\r\n");
                return Q_TRAN(&QHsmTst_MOVING_two);
            }
        case GO_UP:
            {
                printf("go up 2\r\n");
                return Q_TRAN(&QHsmTst_MOVING_two);
            }
    }
    return Q_SUPER(&QHsmTst_SUPER_two);
}

QState QHsmTst_MOVING_two(QHsmTst *me)
{
    QState status_;
    switch (Q_SIG(me)) {

        case Q_ENTRY_SIG: {
            printf("moving-ENTR 2\r\n");
            status_ =  Q_HANDLED();
        }
        case Q_EXIT_SIG: {
            printf("moving-EXIT 2\r\n");
            status_ =  Q_HANDLED();
        }
        case Q_INIT_SIG: {
            printf("moving-init 2\r\n");
            status_ = Q_TRAN(&QHsmTst_mov_sub_0_two);
            break;
        }
        case FLOOR_REACHED: {
            printf("floor-reached 2\r\n");

            status_ =  Q_TRAN(&QHsmTst_WAITING_two);
            break;
        }
        default:
            status_ =  Q_SUPER(&QHsmTst_SUPER_two);
            break;
    }
    return status_;
}

QState QHsmTst_mov_sub_0_two(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("mov_sub_0 in 2\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("mov_sub_0 out 2\r\n");
                return Q_HANDLED();
            }

        case MOV_SUB0:
            {
                printf("mov_sub0 2\r\n");
                return Q_TRAN(&QHsmTst_mov_sub_1_two);
            }
    }
    return Q_SUPER(&QHsmTst_MOVING_two);
}

QState QHsmTst_mov_sub_1_two(QHsmTst *me)
{
    switch (Q_SIG(me)) {
        case Q_ENTRY_SIG:
            {
                printf("mov_sub_1 in 2\r\n");
                return Q_HANDLED();
            }
        case Q_EXIT_SIG:
            {
                printf("mov_sub_1 out 2\r\n");
                return Q_HANDLED();
            }

        case MOV_SUB1:
            {
                printf("mov_sub1 2\r\n");
                return Q_TRAN(&QHsmTst_mov_sub_0_two);
            }
    }
    return Q_SUPER(&QHsmTst_MOVING_two);
}

#endif






