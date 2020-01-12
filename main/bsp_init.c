//Thousands of bsp drivers will be added
//For the acceleration
#include "bsp_init.h"

#ifdef BSP_LED
#include "bsp_led.h"
#endif // BSP_LED
#ifdef BSP_UART
#include "bsp_uart.h"
#endif // MACRO
#ifdef BSP_USART2
#include "bsp_usart2.h"
#endif // MACRO
#ifdef BSP_SPI2
#include "bsp_spi2.h"
#endif // MACRO
#ifdef BSP_
#include ".h"
#endif // MACRO
#ifdef BSP_ADC
#include "bsp_adc.h"
#endif // MACRO
#ifdef BSP_USBD_MSC
#include "bsp_usbd_msc.h"
#include "bsp_sdcard.h"
#endif // MACRO
#ifdef BSP_ETH
#include "bsp_eth.h"
#endif // MACRO
#ifdef BSP_UART5
#include "bsp_uart5.h"
#endif // MACRO
#ifdef BSP_24C512
#include "bsp_24c512.h"
#endif // MACRO
#ifdef BSP_I2C2
#include "bsp_i2c2.h"
#endif // MACRO
#ifdef BSP_WEIGEN
#include "bsp_weigen_card.h"
#endif // MACRO
#ifdef BSP_UART3
#include "bsp_uart3.h"
#endif // MACRO
#ifdef BSP_CD4052
#include "bsp_cd4052.h"
#endif // MACRO

#ifdef BSP_TTYUSB0
#include "bsp_ttyusb0.h"
#endif // MACRO

void bsp_init (void)
{
#ifdef BSP_LED
    bsp_led_init(LED0);  /* TEST IO */
#endif // BSP_LED
#ifdef BSP_IO_TEST
    bsp_led_init(LED2);  /* TEST IO */
#endif // BSP_LED
#ifdef BSP_SPI2
    bsp_spi2_init();
#endif // BSP_SPI
#ifdef BSP_UART2
    bsp_uart2_init();
#endif // #define BSP_UART2
#ifdef BSP_TIM
    bsp_tim_init();
#endif // #define BSP_UART2
#ifdef BSP_I2C
    bsp_i2c_init();
#endif // MACRO
#ifdef BSP_I2C2
    bsp_i2c2_init();
#endif // MACRO
#ifdef BSP_ADC
    bsp_adc_init();
#endif // bsp_adc
#ifdef BSP_USBD_MSC
    bsp_usbd_msc_init();
#endif // BSP_USB_MSC
#ifdef BSP_LED
    bsp_eth_init(); 
#endif // BSP_LED
#ifdef BSP_UART5
    bsp_uart5_init();
#endif
#ifdef BSP_24C512
    bsp_24c512_init();
#endif
#ifdef BSP_WEIGEN
    bsp_weigen_detect_init();
#endif
#ifdef BSP_WEIGEN
    bsp_weigen_detect_init();
#endif
#ifdef BSP_UART3
    bsp_uart3_init();
#endif
#ifdef BSP_CD4052
    bsp_cd4052_init();
#endif

#ifdef BSP_TTYUSB0
    bsp_ttyusb0_init();
#endif // MACRO
}









