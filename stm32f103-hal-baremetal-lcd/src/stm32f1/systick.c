/* @page systick.h
 *       System Timer driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2023-2025, atgroup09@yandex.ru
 */

#include "systick.h"


/** @brief  SysTick Handler.
 *  @param  None.
 *  @return None.
 */
void SysTick_Handler(void)
{
	//HAL.tick
	HAL_IncTick();

	//LED_USER.blink
	if(!(HAL_GetTick() % PLC_LED_BLINK_PERIOD))
	{
		PlcGpio_DO_Toggle(PLC_LED_USER.Port, PLC_LED_USER.Pin, PLC_LED_USER.DOMode);
	}
}
