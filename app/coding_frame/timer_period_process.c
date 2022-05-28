#ifdef TIMER_PERIOD_PROCESS



/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "timer_period_process.h"

/* bsp */
#include "bsp_bsp_name.h"


/* func */
#include "func_name_f.h"

#define TIMER_PERIOD_PROCESS_STACK_SIZE configMINIMAL_STACK_SIZE

static void timer_period_process_task(void *parameter);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

void timer_period_process_task_create(uint8_t priority_1)
{
    xTaskCreate(timer_period_process_task, "timer_period_process_process", timer_period_process_TASK_STACK_SIZE, NULL, priority_1, (TaskHandle_t)NULL);

}

static void timer_period_process_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;

    (void) parameter;
    
    for (;;)
    {
        switch (state)
        {
            case 0:
                
                state = 1;
                break;

            case 1:
                
                state = 2;
                
                break;

            case 2:

                break;

            default:
                break;
        }
        vTaskDelay(100);
        time_cnt_temp++;
    }
}
#endif /* TIMER_PERIOD_PROCESS_H */

















