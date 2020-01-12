#include "app_init.h"

#if 0
#include "led_flash.h"
#include "semphore_t.h"
#include "queue_t.h"
#include "com_serial.h"
#include "usart_spi_com.h"
#include "mul_adc_sample.h"
#endif
#ifdef ONE_BUTTON_APP
#include "count_of_button.h"
#endif // ONE_BUTTON_APP

#ifdef PROJECT_0_APP
#include "button_detect.h"
#include "finger_sensor_detect.h"
#include "tft_display.h"
#endif
#ifdef USB_DEVICE_APP
#include "usb_device_app.h"
#endif // 
#ifdef USBD_MSC_APP
#include "usbd_msc_app.h"
#endif // 
#ifdef HELLO_WORLD_APP
#include "hello_world_thread.h"
#endif // 
#ifdef STRUCTURE_APP
#include "structures_thread.h"
#endif // 
#ifdef UART_COMMUNICATION_APP
#include "uart_thread.h"
#endif // MACRO

void app_init(void)
{
#ifdef TEST_IO
    vStartLED2FlashTasks( TEST1_TASK_PRIORITY );
#endif // TEST_IO
#ifdef SPI_USART_APP
    usart_spi_task_create(TEST4_TASK_PRIORITY, TEST2_TASK_PRIORITY);
#endif
#ifdef UART2_TEST_APP
    uart2_task_create(TEST1_TASK_PRIORITY, TEST2_TASK_PRIORITY);
#endif // UART2_TEST_APP
#ifdef UART_TEST_APP
    uart_task_create(TEST1_TASK_PRIORITY);
#endif // UART_TEST_APP
#ifdef TIM_TEST_APP
    tim_task_create(TEST3_TASK_PRIORITY);
#endif // TIM_TEST_APP
#ifdef LED_TEST_APP
    vStartLED0FlashTasks( TEST2_TASK_PRIORITY );
#endif // TIM_TEST_APP
#ifdef I2C_TEST_APP
#endif //
#ifdef MUL_CHINNAL_ADC_TEST_APP
    adc_task_create(TEST2_TASK_PRIORITY);
#endif // MUL_CHINNAL_ADC_TEST_APP    
#ifdef USB_DEVICE_APP
    usb_device_task_create(TEST2_TASK_PRIORITY);
#endif // USB_DEVICE_APP
#ifdef USBD_MSC_APP
    usbd_msc_task_create(TEST2_TASK_PRIORITY);
#endif // USB_MSC_APP

#ifdef NANTONG_APP
    net_process_task_create(TEST10_TASK_PRIORITY);
    net_process_up_down_task_create(TEST8_TASK_PRIORITY);
    open_the_cabit_task_create(TEST3_TASK_PRIORITY);
    card_reader_task_create(TEST9_TASK_PRIORITY);
    screen_task_create(TEST4_TASK_PRIORITY);
    period_task_create(TEST2_TASK_PRIORITY);
    /* master_485_task_create(TEST2_TASK_PRIORITY); */
#endif // NANTONG_APP

#ifdef HELLO_WORLD_APP
    create_thread();
    /* create_process(); */
#endif // MACRO
#ifdef STRUCTURE_APP
    create_structure_threads();
#endif // MACRO
#ifdef UART_COMMUNICATION_APP
    create_uart_threads();
#endif // MACRO
}





