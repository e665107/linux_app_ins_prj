/* os */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
 
#include "button_process.h"
#include "bsp_button.h"

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);
    
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    static BaseType_t xHigherPriorityTaskWoken;
    xHigherPriorityTaskWoken = pdFALSE;

    switch(GPIO_Pin)
    {
        case GPIO_PIN_0:
 
            break;
        case GPIO_PIN_2:
            
            break;
        case GPIO_PIN_3:
            xSemaphoreGiveFromISR(button_b_sem,&xHigherPriorityTaskWoken);
            if( xHigherPriorityTaskWoken != pdFALSE )
            {
                portYIELD_FROM_ISR(xHigherPriorityTaskWoken); /* switch to relate task */

            }
            
            break;

        case GPIO_PIN_13:
            
            break;
    }
}







