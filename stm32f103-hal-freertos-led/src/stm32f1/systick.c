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
	//HAL.Tick
	HAL_IncTick();

	//RTOS.Tick (if scheduler is started)
#if (INCLUDE_xTaskGetSchedulerState == 1 )
	if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
	{
#endif /* INCLUDE_xTaskGetSchedulerState */
		xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
	}
#endif /* INCLUDE_xTaskGetSchedulerState */
}
