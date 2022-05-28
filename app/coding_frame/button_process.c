#ifdef BUTTON_PROCESS
/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "button_process.h"

/* bsp */
#include "bsp_button.h"


/* func */
/* #include "func_name_f.h" */

#define BUTTON_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

static void button_task(void *parameter);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;
SemaphoreHandle_t button_b_sem;

void button_task_create(uint8_t priority_1)
{
    button_b_sem = xSemaphoreCreateBinary();
    configASSERT(button_b_sem);
    xTaskCreate(button_task, "button_process", BUTTON_TASK_STACK_SIZE, NULL, priority_1, NULL);
}

static void button_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;

    (void) parameter;
    
    for (;;)
    {
        if(is_button_detected())
        {
            time_cnt_temp++;
        }
        switch (state)
        {
            case 0:
                
                break;
            case 1:
                
                        
                break;
            case 2:

                break;
            default:
                break;
        }
        vTaskDelay(10);
    }
}

uint32_t is_button_detected()
{
    uint32_t result = 0;
    xSemaphoreTake(button_b_sem, portMAX_DELAY);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    if(bsp_button_in(GPIOH, GPIO_PIN_3) == RESET)
    {
        result = 1;
    }
    else
    {
        result = 0;
    }
    return result;
}

#endif











 
