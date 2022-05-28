#ifdef UART_485_PROCESS



/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* lib */
#include "stdio.h"
#include "common.h"

/* app */
#include "uart_485_process.h"

/* bsp */
#include "bsp_rs485.h"


/* func */
/* #include "func_name_f.h" */

#define UART_485_PROCESS_STACK_SIZE configMINIMAL_STACK_SIZE

static void uart_485_process_task(void *parameter);

static TickType_t delay_100ms = 100 / portTICK_PERIOD_MS;

void uart_485_process_task_create(uint8_t priority_1)
{
    xTaskCreate(uart_485_process_task, "uart_485_process_process", UART_485_PROCESS_STACK_SIZE, NULL, priority_1, NULL);

}

static void uart_485_process_task(void *parameter)
{
    static uint8_t state = 0;
    
    static uint8_t time_cnt_temp = 0;
    u8* temp_buf = "hello, world!";
    (void) parameter;
    
    for (;;)
    {
        switch (state)
        {
            case 0:
                bsp_rs485_Send_Data(temp_buf, sizeof(temp_buf)/sizeof(u8));
                /* state = 1; */
                break;

            case 1:
                
                /* state = 2; */
                break;

            case 2:

                break;
            default:
                break;
        }
        vTaskDelay(300);
        time_cnt_temp++;
    }
}

#endif /* UART_485_PROCESS_H */















 
