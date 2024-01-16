/* @page task-do.c
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#include "task-do.h"


/** @var DO-channels
 */
static PlcDO_t PLC_DO[PLC_DO_SZ];

/** @var DO-channel ID (menu selected)
 */
static uint8_t DO_Ch = PLC_DO_00;


/** @brief  Init the Task.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
static uint8_t DO_Init(void)
{
	for(uint8_t i=0; i<PLC_DO_SZ; i++)
	{
		PLC_DO[i].Ch = i;

		PlcDO_Init(&PLC_DO[i]);

		//set values by default
		DO_SetCh(PLC_DO[i].Ch);
		DO_SetNormVal(PLC_DO_NORM_VAL_DEF);
		DO_SetPwmT(PLC_DO_PWM_T_DEF);
		DO_SetPwmD(PLC_DO_PWM_D_DEF);

		if(DO_SetMode(PLC_DO_MODE_DEF))
		{
			PLC_DO[i].Status = PLC_DO[i].Mode;
		}
	}

	//select channel by default
	DO_SetCh(PLC_DO_00);

	return (BIT_TRUE);
}

/** @brief  DeInit the Task.
 *  @param  None.
 *  @return None.
 */
/*
static void DO_DeInit(void)
{
	for(uint8_t i=0; i<PLC_DO_SZ; i++)
	{
		PlcDO_DeInit(&PLC_DO[i]);
	}
}
*/


uint8_t DO_Task_Start(void)
{
	return (DO_Init());
}


uint8_t DO_GetChInfo(DO_Info_t *BuffIn)
{
	if(BuffIn)
	{
		BuffIn->Ch      = PLC_DO[DO_Ch].Ch;
		BuffIn->Mode    = PLC_DO[DO_Ch].Mode;
		BuffIn->NormVal = PLC_DO[DO_Ch].NormVal;
		BuffIn->PwmT    = PLC_DO[DO_Ch].PwmT;
		BuffIn->PwmD    = PLC_DO[DO_Ch].PwmD;
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


uint8_t DO_SetCh(uint8_t ChIn)
{
	if(ChIn < PLC_DO_SZ)
	{
		DO_Ch = ChIn;
		return (BIT_TRUE);
	}
	return (BIT_FALSE);
}


inline uint8_t DO_SetMode(uint8_t ModeIn)
{
	return (PlcDO_SetMode(&PLC_DO[DO_Ch], ModeIn));
}


inline uint8_t DO_SetNormVal(uint8_t NornValIn)
{
	return (PlcDO_SetNormVal(&PLC_DO[DO_Ch], NornValIn));
}


inline uint8_t DO_SetPwmT(float ValIn)
{
	return (PlcDO_SetPwmT(&PLC_DO[DO_Ch], ValIn));
}


inline uint8_t DO_SetPwmD(float ValIn)
{
	return (PlcDO_SetPwmD(&PLC_DO[DO_Ch], ValIn));
}
