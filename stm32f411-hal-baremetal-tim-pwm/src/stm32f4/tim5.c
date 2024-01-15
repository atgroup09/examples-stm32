/* @page tim5.c
 *       TIM5 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include <tim5.h>


uint8_t PlcTim5_Init(void)
{
	TIM_ClockConfigTypeDef         TimClockCfg;
	TIM_MasterConfigTypeDef        TimMasterCfg;
	TIM_OC_InitTypeDef             TimOcCfg;

	//Enable clock
	__HAL_RCC_TIM5_CLK_ENABLE();

	//Counter settings
	PLC_TIM5.Instance				= TIM5;
	PLC_TIM5.Init.Prescaler         = PLC_TIM5_PRESCALER;
	PLC_TIM5.Init.CounterMode       = TIM_COUNTERMODE_UP;
	PLC_TIM5.Init.Period            = PLC_TIM5_PERIOD__1HZ;
	PLC_TIM5.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
	PLC_TIM5.Init.RepetitionCounter = 0;
	PLC_TIM5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if(HAL_TIM_Base_Init(&PLC_TIM5) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Clock source
	TimClockCfg.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if(HAL_TIM_ConfigClockSource(&PLC_TIM5, &TimClockCfg) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//PWM init.
	if(HAL_TIM_PWM_Init(&PLC_TIM5) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//Trigger settings
	TimMasterCfg.MasterOutputTrigger = TIM_TRGO_RESET;
	TimMasterCfg.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
	if(HAL_TIMEx_MasterConfigSynchronization(&PLC_TIM5, &TimMasterCfg) != HAL_OK)
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
	if(HAL_TIM_PWM_ConfigChannel(&PLC_TIM5, &TimOcCfg, PLC_TIM5_DO_CH) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	return (BIT_TRUE);
}


void PlcTim5_DeInit(void)
{
	PlcTim_StopChannel(&PLC_TIM5, PLC_TIM5_DO_CH);
	__HAL_RCC_TIM5_CLK_DISABLE();
}
