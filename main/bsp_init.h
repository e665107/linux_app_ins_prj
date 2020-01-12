#ifndef _BSP_INIT_H
#define _BSP_INIT_H

#include "app_config.h"

#ifdef SPI_USART_APP
#define BSP_USART2
#define BSP_SPI2
#define BSP_UART
#define BSP_LED
#endif

#ifdef TEST_IO
#define BSP_IO_TEST
#endif // TEST_IO

#ifdef UART2_TEST_APP
#define BSP_UART2
#endif // UART2_TEST_APP

#ifdef UART_TEST_APP
#define BSP_UART
#endif

#ifdef TIM_TEST_APP
#define BSP_TIM
#define BSP_LED
#endif

#ifdef  LED_TEST_APP
#define BSP_LED
#endif

#ifdef I2C_TEST_APP
#define BSP_I2C
#endif // I2C_TEST_APP

#ifdef MUL_CHINNAL_ADC_TEST_APP
#define BSP_ADC
#endif // MUL_CHINNAL_ADC_TEST_APP

#ifdef USB_DEVICE_APP
#define BSP_USB_DEVICE
#endif // USB_DEVICE_APP

#ifdef USBD_MSC_APP
#define BSP_USBD_MSC
#define BSP_SDCARD
#endif // USB_DEVICE_APP

#ifdef NANTONG_APP
#define BSP_ETH
#define BSP_UART5
#define BSP_UART3
#define BSP_RS485
#define BSP_24C512
#define BSP_WEIGEN
#define BSP_CD4052
#endif // USB_DEVICE_APP

#ifdef UART_COMMUNICATION_APP
#define BSP_TTYUSB0
#endif // MACRO

void bsp_init(void);

#endif /* _BSP_INIT_H */







