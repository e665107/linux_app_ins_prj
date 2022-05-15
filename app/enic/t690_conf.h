/**
  ******************************************************************************
  * @file    Project/Template/Temp/MCore/t690_conf.h
  * @author  TIH Driver Team
  * @version V1.0.0
  * @date    04-November-2016
  * @brief   Library configuration file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __T690_CONF_H
#define __T690_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Uncomment the line below to enable peripheral header file inclusion */
/* #include "misc.h" */
/* #include "t690_adc.h" */
/* #include "t690_cana.h" */
/* #include "t690_canb.h" */
/* #include "t690_dac.h" */
/* #include "t690_dma.h" */
#include "t690_gmac.h"
/* #include "t690_fmc.h" */
/* #include "t690_gpio.h" */
/* #include "t690_i2c.h" */
/* #include "t690_ltdc.h" */
/* #include "t690_rccs.h" */
/* #include "t690_rtc.h" */
/* #include "t690_sci.h" */
/* #include "t690_sddc.h" */
/* #include "t690_sdio.h" */
/* #include "t690_spi.h" */
/* #include "t690_ssi.h" */
/* #include "t690_tim.h" */
/* #include "t690_uart.h" */
/* #include "t690_mintc.h" */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* If an external clock source is used, then the value of the following define
   should be set to the value of the external clock source, else, if no external
   clock is used, keep this define commented */
/*#define I2S_EXTERNAL_CLOCK_VAL   12288000 */ /* Value of the external clock in Hz */


/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
 /* #define USE_FULL_ASSERT    1 */

/* Exported macro ------------------------------------------------------------*/
#define RUNTIME_HOST_CCORE
#define CONSOLE_UART  UART5
#define DEBUG_FPGA

#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function
  *   which reports the name of the source file and the source
  *   line number of the call that failed.
  *   If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __T690_CONF_H */

/************************ (C) COPYRIGHT TIH **********************END OF FILE****/
