/* @page led.h
 *       LED driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

/** @note
 *        PC13 <- LED_USER (OFF/ON)
 */

#ifndef PLC_LED_H
#define PLC_LED_H

#include "gpio.h"


/** @def LED_USER
 */
#define PLC_LED_USER_PORT        GPIOC
#define PLC_LED_USER_PIN         GPIO_PIN_13
#define PLC_LED_USER_PULL        GPIO_NOPULL
#define PLC_LED_USER_MODE		 GPIO_MODE_OUTPUT_OD
#define PLC_LED_USER_DO_MODE     PLC_GPIO_DO_OD


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


/** @def LED blink period, msec
 */
#ifdef DEBUG
#define PLC_LED_BLINK_PERIOD  5000u
#else
#define PLC_LED_BLINK_PERIOD  1000u
#endif


/** @var LED settings
 */
extern PlcLED_t PLC_LED_USER;


/** @brief  Init LED.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
uint8_t PlcLed_Init(void);

/** @brief  DeInit LED.
 *  @param  None.
 *  @return None.
 */
void PlcLed_DeInit(void);

#endif //PLC_LED_H
