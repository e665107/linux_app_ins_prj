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
#ifdef NET_COMMUNICATION_APP
#include "net_communication_thread.h"
#endif // MACRO
#ifdef HTTP_CLIENT_APP
#include "http_client_thread.h"
#endif // MACRO
#ifdef HTTPD_APP
#include "httpd_thread.h"
#endif // MACRO
#ifdef ENIC_APP
#include "enic_thread.h"
#endif // MACRO


void app_init(void)
{
#ifdef HELLO_WORLD_APP
    create_thread();
#endif // MACRO
#ifdef STRUCTURE_APP
    create_structure_threads();
#endif // MACRO
#ifdef UART_COMMUNICATION_APP
    create_uart_threads();
#endif // MACRO
#ifdef HTTP_CLIENT_APP
    create_http_client_threads();
#endif // MACRO
#ifdef HTTPD_APP
    create_httpd_threads();
#endif // MACRO
#ifdef ENIC_APP
     create_enic_threads();
#endif // MACRO

}
