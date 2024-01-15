/* @page tim2.c
 *       TIM2 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include <tim2.h>


uint8_t PlcTim2_Init(void)
{
	TIM_ClockConfigTypeDef         TimClockCfg;
	TIM_MasterConfigTypeDef        TimMasterCfg;
	TIM_OC_InitTypeDef             TimOcCfg;

	//Enable clock
	__HAL_RCC_TIM2_CLK_ENABLE();

	//Counter settings
	PLC_TIM2.Instance				= TIM2;
	PLC_TIM2.Init.Prescaler         = PLC_TIM2_PRESCALER;
	PLC_TIM2.Init.CounterMode       = TIM_COUNTERMODE_UP;
	PLC_TIM2.Init.Period            = PLC_TIM2_PERIOD__1HZ;
	PLC_TIM2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	PLC_TIM2.Init.RepetitionCounter = 0;
	PLC_TIM2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&PLC_TIM2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Clock source
	TimClockCfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if(HAL_TIM_ConfigClockSource(&PLC_TIM2, &TimClockCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//PWM init.
	if(HAL_TIM_PWM_Init(&PLC_TIM2) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Trigger settings
	TimMasterCfg.MasterOutputTrigger = TIM_TRGO_RESET;
	TimMasterCfg.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
	if(HAL_TIMEx_MasterConfigSynchronization(&PLC_TIM2, &TimMasterCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Channel settings
	TimOcCfg.OCMode       = TIM_OCMODE_PWM1;
	TimOcCfg.Pulse        = 0;
	TimOcCfg.OCPolarity   = TIM_OCPOLARITY_HIGH;
	TimOcCfg.OCNPolarity  = TIM_OCNPOLARITY_HIGH;
	TimOcCfg.OCFastMode   = TIM_OCFAST_DISABLE;
	TimOcCfg.OCIdleState  = TIM_OCIDLESTATE_RESET;
	TimOcCfg.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if(HAL_TIM_PWM_ConfigChannel(&PLC_TIM2, &TimOcCfg, PLC_TIM2_DO_CH) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	return (BIT_TRUE);
}


void PlcTim2_DeInit(void)
{
	PlcTim_StopChannel(&PLC_TIM2, PLC_TIM2_DO_CH);
	__HAL_RCC_TIM2_CLK_DISABLE();
}
