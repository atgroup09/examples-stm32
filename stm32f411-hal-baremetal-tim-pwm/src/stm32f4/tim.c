/* @page tim.c
 *       TIM Common drivers, handlers and callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "tim.h"


/** @var TIM Handlers
 */
TIM_HandleTypeDef PLC_TIM2;
TIM_HandleTypeDef PLC_TIM5;

/** @var TIM Callback user-functions
 */
PLC_TIM_UserFunc_t PLC_TIM2_USER_FUNC = { .Elapsed = NULL };
PLC_TIM_UserFunc_t PLC_TIM5_USER_FUNC = { .Elapsed = NULL };


HAL_StatusTypeDef PlcTim_StartChannel(TIM_HandleTypeDef *TimIn, uint32_t TimChIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		return (HAL_TIM_PWM_Start(TimIn, TimChIn));
	}
	return (HAL_ERROR);
}


HAL_StatusTypeDef PlcTim_StopChannel(TIM_HandleTypeDef *TimIn, uint32_t TimChIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		return (HAL_TIM_PWM_Stop(TimIn, TimChIn));
	}
	return (HAL_ERROR);
}


HAL_StatusTypeDef PlcTim_SetChannelPeriod(TIM_HandleTypeDef *TimIn, uint32_t PeriodIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_AUTORELOAD(TimIn, PeriodIn);
		return (HAL_OK);
	}
	return (HAL_ERROR);
}


HAL_StatusTypeDef PlcTim_SetChannelPulse(TIM_HandleTypeDef *TimIn, uint32_t TimChIn, uint32_t PulseIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_COMPARE(TimIn, TimChIn, PulseIn);
		return (HAL_OK);
	}
	return (HAL_ERROR);
}


HAL_StatusTypeDef PlcTim_Start(TIM_HandleTypeDef *TimIn)
{
	(void)TimIn;
	return (HAL_OK);
}


HAL_StatusTypeDef PlcTim_Stop(TIM_HandleTypeDef *TimIn)
{
	(void)TimIn;
	return (HAL_OK);
}


HAL_StatusTypeDef PlcTim_SetCnt(TIM_HandleTypeDef *TimIn, uint32_t CntIn)
{
	if(TimIn == &PLC_TIM2 || TimIn == &PLC_TIM5)
	{
		__HAL_TIM_SET_COUNTER(TimIn, CntIn);
		return (HAL_OK);
	}
	return (HAL_ERROR);
}


HAL_StatusTypeDef PlcTim_RstCnt(TIM_HandleTypeDef *TimIn)
{
	return (PlcTim_SetCnt(TimIn, (uint32_t)0));
}
