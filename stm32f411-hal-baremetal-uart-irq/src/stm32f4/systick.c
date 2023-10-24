/* @page systick.h
 *       System Timer driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

#include "systick.h"


volatile uint16_t LedCnt = 0;



/** @brief  SysTick Handler.
 *  @param  None.
 *  @return None.
 */
void SysTick_Handler(void)
{
	//HAL.tick
	HAL_IncTick();

	LedCnt++;
	if(LedCnt == PLC_LED_BLINK_PERIOD)
	{
		PlcGpio_DO_Toggle(PLC_LED_USER.Port, PLC_LED_USER.Pin, PLC_LED_USER.DOMode);
		LedCnt = 0;
	}
}
