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
#endif //HELLO_WORLD_APP
#ifdef HAPPY_HACK1_APP
#include "happy_hack1_thread.h"
#endif //HAPPY_HACK1_APP
#ifdef HAPPY_HACK_APP
#include "happy_hack_thread.h"
#endif //HAPPY_HACK_APP
#ifdef QT_TST1_APP
#include "qt_tst1_thread.h"
#endif //QT_TST1_APP
#ifdef TEST9_APP
#include "test9_thread.h"
#endif //TEST9_APP
#ifdef TEST7_APP
#include "test7_thread.h"
#endif //TEST7_APP
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
#ifdef CHAT_SERVER_APP
#include "chat_server_thread.h"
#endif // MACRO
#ifdef QT_HELLO_WORLD_APP
#include "qt_hello_thread.h"
#endif // MACRO
#ifdef MYSQL_ACCESS_APP
#include "mysql_access_thread.h"
#endif // MACRO


void app_init(void)
{
#ifdef HELLO_WORLD_APP
    create_thread();
#endif // HELLO_WORLD_APP
#ifdef HAPPY_HACK1_APP
    create_happy_hack1_threads();
#endif //HAPPY_HACK1_APP
#ifdef HAPPY_HACK_APP
    create_happy_hack_threads();
#endif //HAPPY_HACK_APP
#ifdef QT_TST1_APP
    create_qt_tst1_threads();
#endif //QT_TST1_APP
#ifdef TEST9_APP
    create_test9_threads();
#endif //TEST9_APP
#ifdef TEST7_APP
    create_test7_threads();
#endif //TEST7_APP
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
#ifdef CHAT_SERVER_APP
     create_chat_server_thread();
#endif // MACRO
#ifdef QT_HELLO_WORLD_APP
     create_qt_hello_threads();
#endif // MACRO
#ifdef MYSQL_ACCESS_APP
     create_mysql_access_threads();
#endif // MACRO

}
