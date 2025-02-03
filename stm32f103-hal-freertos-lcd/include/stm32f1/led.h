/* @page led.h
 *       LED driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2023-2025, atgroup09@yandex.ru
 */

/** @note
 *        PC13 <- LED_USER (OFF/ON)
 */

#ifndef PLC_LED_H
#define PLC_LED_H

#include "gpio.h"


/** @def GPIO
 */
#define PLC_LED_USER_PORT        	GPIOC
#define PLC_LED_USER_PIN         	GPIO_PIN_13
#define PLC_LED_USER_PULL        	GPIO_NOPULL
#define PLC_LED_USER_MODE		 	GPIO_MODE_OUTPUT_OD
#define PLC_LED_USER_DO_MODE     	PLC_GPIO_DO_OD

/** @def Blink period, msec
 */
#define PLC_LED_USER_BLINK_PERIOD	1000u


/** @typedef LED-channel settings
 *           main type
 */
typedef struct PlcLED_t_
{
	//GPIO

	//@var PORT
	GPIO_TypeDef *Port;

	//@var PIN
	uint16_t Pin;

	//@var DO MODE
	uint8_t DOMode;

} PlcLED_t;


/** @var LED settings
 */
extern PlcLED_t PLC_LED_USER;


/** @brief  LED Init.
 *  @param  None.
 *  @return None.
 */
void PlcLed_Init(void);

/** @brief  LED DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcLed_DeInit(void);

/** @brief  LED Toggle.
 *  @param  None.
 *  @return None.
 */
void PlcLed_Toggle(void);

#endif //PLC_LED_H
