/* @page led.c
 *       LED driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2023-2025, atgroup09@yandex.ru
 */

#include "led.h"


PlcLED_t PLC_LED_USER;


void PlcLed_Init(void)
{
	GPIO_InitTypeDef GpioDef;

	//Enable clock
	__HAL_RCC_GPIOC_CLK_ENABLE();

	//GPIO configuration
	GpioDef.Speed = GPIO_SPEED_FREQ_LOW;

	//LED_USER
	// context
	PLC_LED_USER.Port    = PLC_LED_USER_PORT;
	PLC_LED_USER.Pin     = PLC_LED_USER_PIN;
	PLC_LED_USER.DOMode  = PLC_LED_USER_DO_MODE;
	// gpio
	GpioDef.Pin    		 = PLC_LED_USER.Pin;
	GpioDef.Mode   		 = PLC_LED_USER_MODE;
	GpioDef.Pull   		 = PLC_LED_USER_PULL;
	GpioDef.Speed		 = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(PLC_LED_USER.Port, &GpioDef);
	// set out by default
	PlcGpio_DO_Off(PLC_LED_USER.Port, PLC_LED_USER.Pin, PLC_LED_USER.DOMode);
}


void PlcLed_DeInit(void)
{
	HAL_GPIO_DeInit(PLC_LED_USER.Port, PLC_LED_USER.Pin);
}
