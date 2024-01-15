/* @page do.c
 *       DO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "do.h"


/** @brief  Start DO.
 *  @param  DOIn - channel.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
static uint8_t PlcDO_Start(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		if(PlcTim_StartChannel(DOIn->Tim, DOIn->TimCh) == HAL_OK)
		{
			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}

/** @brief  Stop DO.
 *  @param  DOIn - channel.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
static uint8_t PlcDO_Stop(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		if(PlcTim_RstCnt(DOIn->Tim) == HAL_OK)
		{
			if(PlcTim_StopChannel(DOIn->Tim, DOIn->TimCh) == HAL_OK)
			{
				return (BIT_TRUE);
			}
		}
	}
	return (BIT_FALSE);
}

/** @brief  Convert Period (ms) into 32-bit register value (ARR).
 *  @param  PeriodIn - period (ms).
 *  @return 32-bit register value (ARR).
 */
static uint32_t PlcDO_ConvPeriodMsToArr(float PeriodIn)
{
	return ((uint32_t)(PeriodIn/PLC_TIM2_MS));
}

/** @brief  Convert Pulse (%) into 32-bit register value (CCR).
 *  @param  PulseIn - pulse (%).
 *  @param  KaIn - scale factor.
 *  @param  KbIn - scale factor.
 *  @return 32-bit register value (CCR).
 */
static uint32_t PlcDO_ConvPulsePercToCcr(float PulseIn, float KaIn, float KbIn)
{
	return ((uint32_t)ScaleA(PulseIn, KaIn, KbIn));
}

/** @brief  Set new period value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PeriodIn - new period value (ms).
 *  @return None.
 */
static void PlcDO_SetTimPeriod(PlcDO_t *DOIn, float PeriodIn)
{
	if(DOIn)
	{
		//recalculate ARR
		DOIn->Arr = PlcDO_ConvPeriodMsToArr(PeriodIn);

		//recalculate scale factors
		DOIn->Ka = ScaleA_Ka(0.0, DOIn->Arr, PLC_DO_PWM_D__MIN, PLC_DO_PWM_D__MAX);
		DOIn->Kb = ScaleA_Kb(0.0, DOIn->Arr, PLC_DO_PWM_D__MIN, PLC_DO_PWM_D__MAX);

		PlcTim_SetChannelPeriod(DOIn->Tim, DOIn->Arr);
	}
}

/** @brief  Set new pulse value (fill factor) into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  PulseIn - new pulse value (%).
 *  @return None.
 */
static void PlcDO_SetTimPulse(PlcDO_t *DOIn, float PulseIn)
{
	if(DOIn)
	{
		//recalculate CCR
		DOIn->Ccr = PlcDO_ConvPulsePercToCcr(PulseIn, DOIn->Ka, DOIn->Kb);
		PlcTim_SetChannelPulse(DOIn->Tim, DOIn->TimCh, DOIn->Ccr);
	}
}


uint8_t PlcDO_Init(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		GPIO_InitTypeDef GpioDef;

		//Enable clock
		__HAL_RCC_GPIOA_CLK_ENABLE();

		//GPIO Init (common settings)
		GpioDef.Mode  = GPIO_MODE_AF_PP;
		GpioDef.Pull  = GPIO_NOPULL;
		GpioDef.Speed = GPIO_SPEED_FREQ_LOW;

		//GPIO Init (individual settings by channel)
		switch(DOIn->Ch)
		{
			case PLC_DO_00:
				GpioDef.Pin       = PLC_DO_00__PIN;
				GpioDef.Alternate = GPIO_AF1_TIM2;
				PlcTim2_Init();
				DOIn->Port        = GPIOA;
				DOIn->Pin         = GPIO_PIN_0;
				DOIn->Tim         = &PLC_TIM2;
				DOIn->TimCh       = PLC_TIM2_DO_CH;
				break;

			case PLC_DO_01:
				GpioDef.Pin       = PLC_DO_01__PIN;
				GpioDef.Alternate = GPIO_AF2_TIM5;
				PlcTim5_Init();
				DOIn->Port        = GPIOA;
				DOIn->Pin         = GPIO_PIN_1;
				DOIn->Tim         = &PLC_TIM5;
				DOIn->TimCh       = PLC_TIM5_DO_CH;
				break;
		}

		//GPIO Init
		HAL_GPIO_Init(GPIOA, &GpioDef);
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


uint8_t PlcDO_DeInit(PlcDO_t *DOIn)
{
	if(DOIn)
	{
		PlcDO_Stop(DOIn);
		//GPIO DeInit
		HAL_GPIO_DeInit(DOIn->Port, DOIn->Pin);
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


uint8_t PlcDO_SetMode(PlcDO_t *DOIn, uint8_t ModeIn)
{
	if(DOIn)
	{
		if(ModeIn == PLC_DO_MODE_OFF || ModeIn == PLC_DO_MODE_NORM || ModeIn == PLC_DO_MODE_PWM)
		{
			if(ModeIn == PLC_DO_MODE_OFF)
			{
				PlcDO_Stop(DOIn);
			}
			else
			{
				if(ModeIn == PLC_DO_MODE_NORM)
				{
					PlcDO_SetNormVal(DOIn, DOIn->NormVal);
				}
				else
				{
					PlcDO_SetPwmD(DOIn, DOIn->PwmD);
				}

				if(DOIn->Mode == PLC_DO_MODE_OFF)
				{
					PlcDO_Start(DOIn);
				}
			}

			DOIn->Mode = ModeIn;

			return (BIT_TRUE);
		}
	}
	return (BIT_FALSE);
}


uint8_t PlcDO_SetNormVal(PlcDO_t *DOIn, uint8_t ValIn)
{
	if(DOIn)
	{
		if(DOIn->NormVal != ValIn)
		{
			DOIn->NormVal = ((ValIn) ? BIT_TRUE : BIT_FALSE);

			if(DOIn->Mode == PLC_DO_MODE_NORM)
			{
				if(!DOIn->NormVal)
				{
					PlcDO_SetTimPulse(DOIn, PLC_DO_PWM_D__MIN);
				}
				else
				{
					PlcDO_SetTimPulse(DOIn, PLC_DO_PWM_D__MAX);
				}
			}
		}
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


uint8_t PlcDO_SetPwmT(PlcDO_t *DOIn, float ValIn)
{
	if(DOIn)
	{
		if(DOIn->PwmT != ValIn)
		{
			if(ValIn < PLC_DO_PWM_T__MIN)
			{
				DOIn->PwmT = PLC_DO_PWM_T__MIN;
			}
			else if(ValIn > PLC_DO_PWM_T__MAX)
			{
				DOIn->PwmT = PLC_DO_PWM_T__MAX;
			}
			else
			{
				DOIn->PwmT = ValIn;
			}

			if(DOIn->Mode == PLC_DO_MODE_PWM)
			{
				PlcDO_SetTimPeriod(DOIn, DOIn->PwmT);
			}
		}
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


uint8_t PlcDO_SetPwmD(PlcDO_t *DOIn, float ValIn)
{
	if(DOIn)
	{
		if(DOIn->PwmD != ValIn)
		{
			if(ValIn < PLC_DO_PWM_D__MIN)
			{
				DOIn->PwmD = PLC_DO_PWM_D__MIN;
			}
			else if(ValIn > PLC_DO_PWM_D__MAX)
			{
				DOIn->PwmD = PLC_DO_PWM_D__MAX;
			}
			else
			{
				DOIn->PwmD = ValIn;
			}

			if(DOIn->Mode == PLC_DO_MODE_PWM)
			{
				PlcDO_SetTimPulse(DOIn, DOIn->PwmD);
			}
		}
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}
