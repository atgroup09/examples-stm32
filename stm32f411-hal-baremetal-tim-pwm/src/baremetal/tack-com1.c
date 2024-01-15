/* @page task-com1.c
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#include "task-com1.h"


/** @var Tx-buffer
 */
#define COM1_TX_BUFF_SZ  250U
static uint8_t COM1_TX_BUFF[COM1_TX_BUFF_SZ];
static uint8_t COM1_TX_BUFF_IDX = 0;

/** @var Rx-buffer
 */
#define COM1_RX_BUFF_SZ  100U
static uint8_t COM1_RX_BUFF[COM1_RX_BUFF_SZ];


/* @var Rx-counter
 */
static volatile uint32_t COM1_RxCnt = 0;

/* @var Tx-counter
 */
static volatile uint32_t COM1_TxCnt = 0;


/* @var Menu ID
 */
static uint8_t COM1_MenuID = COM1_MENU_MAIN;

/* @var SubMenu ID
 */
static uint8_t COM1_SubMenuID = COM1_MENU_MAIN;

/* @var Menu mode
 */
static uint8_t COM1_MenuMode = COM1_MENU_MODE_PRINT;


/** @brief  Reset index of string-buffer.
 *  @param  None.
 *  @return None.
 */
static void COM1_BUFF_TX_rst(void)
{
	COM1_TX_BUFF_IDX = 0;
}

/** @brief  Add Formatted String into TX-buffer.
 *  @param  None.
 *  @return None.
 */
static void COM1_BUFF_TX_add(const char *StrIn, ...)
{
	if(StrIn)
	{
		uint16_t Sz       = (uint16_t)strlen(StrIn);
		uint16_t FutureSz = (COM1_TX_BUFF_IDX+Sz);

		if(FutureSz < COM1_TX_BUFF_SZ)
		{
			va_list arp;
			va_start(arp, StrIn);
			xsprintfa((char *)&COM1_TX_BUFF[COM1_TX_BUFF_IDX], StrIn, arp);
			COM1_TX_BUFF_IDX += (uint8_t)strlen((char *)&COM1_TX_BUFF[COM1_TX_BUFF_IDX]);
			va_end(arp);
		}
	}
}


/** @brief  Menu: Main.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_Main(void)
{
	COM1_BUFF_TX_add("\r\n== MAIN MENU\r\n");
	COM1_BUFF_TX_add("--\r\n");
	COM1_BUFF_TX_add("%c - Info\r\n", COM1_MENU_INFO);
	COM1_BUFF_TX_add("%c - Counters\r\n", COM1_MENU_COUNTERS);
	COM1_BUFF_TX_add("%c - DO\r\n", COM1_MENU_DO);
	COM1_BUFF_TX_add("%c - Main menu\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: Main (value).
 *  @param  ValIn - input byte.
 *  @return None.
 */
static void COM1_Menu_Main_Value(uint8_t ValIn)
{
	COM1_BUFF_TX_add("%c\r\n", ValIn);

	if(ValIn == COM1_MENU_MAIN || ValIn == COM1_MENU_INFO || ValIn == COM1_MENU_COUNTERS || ValIn == COM1_MENU_DO)
	{
		COM1_MenuID = ValIn;
		if(COM1_MenuID == COM1_MENU_DO) COM1_SubMenuID = COM1_MENU_DO;

		COM1_BUFF_TX_add("OK\r\n");
	}
	else
	{
		COM1_BUFF_TX_add("ERROR\r\n");
	}

	COM1_MenuMode = COM1_MENU_MODE_PRINT;
}


/** @brief  Menu: Info.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_Info(void)
{
	COM1_BUFF_TX_add("\r\n== INFO\r\n");
	COM1_BUFF_TX_add("PLC         : v.%d.%d\r\n", PLC_HW_CODE, PLC_HW_VAR);
	COM1_BUFF_TX_add("RTE         : v.%d (%d %d)\r\n", PLC_RTE_VERSION, PLC_RTE_YYYY, PLC_RTE_DDMM);
	COM1_BUFF_TX_add("SysCoreClock: %lu\r\n", SystemCoreClock);
	COM1_BUFF_TX_add("SysTick     : %lu\r\n", SysTick->LOAD);
	COM1_BUFF_TX_add("--\r\n");
	COM1_BUFF_TX_add("%c - Repeat\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: Info (value).
 *  @param  ValIn - input byte.
 *  @return None.
 */
static void COM1_Menu_Info_Value(uint8_t ValIn)
{
	COM1_BUFF_TX_add("%c\r\n", ValIn);

	if(ValIn == COM1_MENU_MAIN || ValIn == COM1_MENU_REPEAT)
	{
		if(ValIn == COM1_MENU_MAIN) COM1_MenuID = ValIn;

		COM1_BUFF_TX_add("OK\r\n");
	}
	else
	{
		COM1_BUFF_TX_add("ERROR\r\n");
	}

	COM1_MenuMode = COM1_MENU_MODE_PRINT;
}


/** @brief  Menu: Counters.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_Counters(void)
{
	COM1_BUFF_TX_add("\r\n== COUNTERS\r\n");
	COM1_BUFF_TX_add("RxCnt: %lu\r\n", COM1_RxCnt);
	COM1_BUFF_TX_add("TxCnt: %lu\r\n", COM1_TxCnt);
	COM1_BUFF_TX_add("--\r\n");
	COM1_BUFF_TX_add("%c - Repeat\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: Counters (value).
 *  @param  ValIn - input byte.
 *  @return None.
 */
static void COM1_Menu_Counters_Value(uint8_t ValIn)
{
	COM1_BUFF_TX_add("%c\r\n", ValIn);

	if(ValIn == COM1_MENU_MAIN || ValIn == COM1_MENU_REPEAT)
	{
		if(ValIn == COM1_MENU_MAIN) COM1_MenuID = ValIn;

		COM1_BUFF_TX_add("OK\r\n");
	}
	else
	{
		COM1_BUFF_TX_add("ERROR\r\n");
	}

	COM1_MenuMode = COM1_MENU_MODE_PRINT;
}


#ifdef PLC_MOD_DO

/** @val Info-context of selected channel
 */
static DO_Info_t DO_Info;


/** @brief  Menu: DO - Main.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_Main(void)
{
	DO_GetChInfo(&DO_Info);

	COM1_BUFF_TX_add("\r\n== DO\r\n");
	COM1_BUFF_TX_add("Channel: %d\r\n", DO_Info.Ch);

	switch(DO_Info.Mode)
	{
		case PLC_DO_MODE_OFF:
			COM1_BUFF_TX_add("Mode   : %d (OFF)\r\n", DO_Info.Mode);
			break;

		case PLC_DO_MODE_NORM:
			COM1_BUFF_TX_add("Mode   : %d (NORM)\r\n", DO_Info.Mode);
			break;

		case PLC_DO_MODE_PWM:
			COM1_BUFF_TX_add("Mode   : %d (PWM)\r\n", DO_Info.Mode);
			break;
	}

	COM1_BUFF_TX_add("NormVal: %d\r\n", DO_Info.NormVal);
	COM1_BUFF_TX_add("PWM.T  : %f\r\n", DO_Info.PwmT);
	COM1_BUFF_TX_add("PWM.D  : %f\r\n", DO_Info.PwmD);
	COM1_BUFF_TX_add("--\r\n");
	COM1_BUFF_TX_add("%c - Select channel\r\n", DO_MENU_CH_SEL);
	COM1_BUFF_TX_add("%c - Set mode\r\n", DO_MENU_CH_MODE);
	COM1_BUFF_TX_add("%c - Set normal value\r\n", DO_MENU_CH_NORMVAL);
	COM1_BUFF_TX_add("%c - Set PWM.T value\r\n", DO_MENU_CH_PWM_T);
	COM1_BUFF_TX_add("%c - Set PWM.D value\r\n", DO_MENU_CH_PWM_D);
	COM1_BUFF_TX_add("%c - Repeat\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: DO - Select channel.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_ChSel(void)
{
	COM1_BUFF_TX_add("\r\n== DO: CHANNEL SELECT\r\n");
	COM1_BUFF_TX_add("--\r\n");

	for(uint8_t i=0; i<PLC_DO_SZ; i++)
	{
		COM1_BUFF_TX_add("%d - Channel %d\r\n", i, i);
	}

	COM1_BUFF_TX_add("%c - Repeat (without save)\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu (without save)\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("%c - Save and go to DO\r\n", COM1_MENU_SAVE);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: DO - Select mode.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_ChMode(void)
{
	COM1_BUFF_TX_add("\r\n== DO: CHANNEL MODE\r\n");
	COM1_BUFF_TX_add("--\r\n");
	COM1_BUFF_TX_add("%d - OFF\r\n", PLC_DO_MODE_OFF);
	COM1_BUFF_TX_add("%d - NORM\r\n", PLC_DO_MODE_NORM);
	COM1_BUFF_TX_add("%d - PWM\r\n", PLC_DO_MODE_PWM);
	COM1_BUFF_TX_add("%c - Repeat (without save)\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu (without save)\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("%c - Save and go to DO\r\n", COM1_MENU_SAVE);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: DO - Set normal value.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_ChNormVal(void)
{
	COM1_BUFF_TX_add("\r\n== DO: CHANNEL NORMAL VALUE\r\n");
	COM1_BUFF_TX_add("--\r\n");

	COM1_BUFF_TX_add("0 - Low level\r\n");
	COM1_BUFF_TX_add("1 - Hi level\r\n");
	COM1_BUFF_TX_add("%c - Repeat (without save)\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu (without save)\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("%c - Save and go to DO\r\n", COM1_MENU_SAVE);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: DO - Set PWM.T.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_ChPwmT(void)
{
	COM1_BUFF_TX_add("\r\n== DO: CHANNEL PWM.T\r\n");
	COM1_BUFF_TX_add("--\r\n");

	COM1_BUFF_TX_add("0.01 ... 1000000.0 - PWM Period in msec\r\n");
	COM1_BUFF_TX_add("%c - Repeat (without save)\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu (without save)\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("%c - Save and go to DO\r\n", COM1_MENU_SAVE);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}

/** @brief  Menu: DO - Set PWM.D.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO_ChPwmD(void)
{
	COM1_BUFF_TX_add("\r\n== DO: CHANNEL PWM.D\r\n");
	COM1_BUFF_TX_add("--\r\n");

	COM1_BUFF_TX_add("0.0 ... 100.0 - PWM fill factor in %\r\n");
	COM1_BUFF_TX_add("%c - Repeat (without save)\r\n", COM1_MENU_REPEAT);
	COM1_BUFF_TX_add("%c - Main menu (without save)\r\n", COM1_MENU_MAIN);
	COM1_BUFF_TX_add("%c - Save and go to DO\r\n", COM1_MENU_SAVE);
	COM1_BUFF_TX_add("> ");

	COM1_MenuMode = COM1_MENU_MODE_VALUE;
}


/** @val Value buffer
 */
#define VALUE_BUFF_SZ  20
static uint8_t ValueBuff[VALUE_BUFF_SZ];
static uint8_t ValueBuff_IDx = 0;
static uint8_t ValueBuff_Lim = 0;
static uint8_t ValueBuff_PtPos = VALUE_BUFF_SZ;

/** @def Value buffer limites
 */
#define VALUE_BUFF_LIM_DO_CH_SEL     2
#define VALUE_BUFF_LIM_DO_CH_MODE    2
#define VALUE_BUFF_LIM_DO_CH_NORMVAL 1
#define VALUE_BUFF_LIM_DO_CH_PWMT    10
#define VALUE_BUFF_LIM_DO_CH_PWMD    5

/** @def Value code
 */
#define VALUE_ERROR    0
#define VALUE_OK       1
#define VALUE_IN       2

/** @brief  Menu: Get integer part from buffer (before floating-pointer).
 *  @param  None.
 *  @return Value (uint32_t).
 */
static uint32_t COM1_Menu_GetValueIntPart(void)
{
	uint32_t Val = 0;
	uint32_t m;
	uint8_t i, Sz;

	if(ValueBuff_IDx)
	{
		Sz = ((ValueBuff_PtPos < ValueBuff_IDx) ? ValueBuff_PtPos : ValueBuff_IDx);

		for(i=Sz, m=10; i>0; i--)
		{
			if(i<Sz)
	        {
	            Val+= ValueBuff[i-1]*m;
	            m = m*10;
	        }
	        else
	        {
	            Val+= ValueBuff[i-1];
	        }
		}
	}
	return (Val);
}

/** @brief  Menu: Get floating part from buffer (before floating-pointer).
 *  @param  None.
 *  @return Value (float).
 */
static float COM1_Menu_GetValueFloPart(void)
{
    float Val = 0.0;
    float m;
    uint8_t i;

    if(ValueBuff_PtPos < ValueBuff_IDx)
    {
        for(i=ValueBuff_PtPos+1, m=10.0; i<ValueBuff_IDx; i++)
        {
            Val+= ((float)ValueBuff[i])/m;
            m = m*10.0;
        }
    }
    return (Val);
}


/** @brief  Menu: DO - Select Channel (save changed value)
 *  @param  None.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - ok
 */
static uint8_t COM1_Menu_DO_Save_ChSel(void)
{
	uint32_t Val = COM1_Menu_GetValueIntPart();
	return (DO_SetCh((uint8_t)Val));
}


/** @brief  Menu: DO - Select Channel Mode (save changed value)
 *  @param  None.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - ok
 */
static uint8_t COM1_Menu_DO_Save_ChMode(void)
{
	uint32_t Val = COM1_Menu_GetValueIntPart();
	return (DO_SetMode((uint8_t)Val));
}

/** @brief  Menu: DO - Set Channel Normal value (save changed value)
 *  @param  None.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - ok
 */
static uint8_t COM1_Menu_DO_Save_ChNormVal(void)
{
	uint32_t Val = COM1_Menu_GetValueIntPart();
	return (DO_SetNormVal((uint8_t)Val));
}

/** @brief  Menu: DO - Set Channel PWM.T value (save changed value)
 *  @param  None.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - ok
 */
static uint8_t COM1_Menu_DO_Save_ChPwmT(void)
{
	float IntPart = (float)COM1_Menu_GetValueIntPart();
	float FloPart = COM1_Menu_GetValueFloPart();
	float Val     = IntPart + FloPart;
	return (DO_SetPwmT(Val));
}

/** @brief  Menu: DO - Set Channel PWM.D value (save changed value)
 *  @param  None.
 *  @return Result:
 *  @arg    = 0 - error
 *  @arg    = 1 - ok
 */
static uint8_t COM1_Menu_DO_Save_ChPwmD(void)
{
	float IntPart = (float)COM1_Menu_GetValueIntPart();
	float FloPart = COM1_Menu_GetValueFloPart();
	float Val     = IntPart + FloPart;
	return (DO_SetPwmD(Val));
}


/** @brief  Menu: DO (value).
 *  @param  ValIn - input byte.
 *  @return None.
 */
static void COM1_Menu_DO_Value(uint8_t ValIn)
{
	uint8_t Res = VALUE_IN;

	COM1_BUFF_TX_add("%c", ValIn);

	switch(ValIn)
	{
		case DO_MENU_CH_SEL:

			//go to submenu DO: Select Channel
			ValueBuff_IDx = 0;
			ValueBuff_Lim = VALUE_BUFF_LIM_DO_CH_SEL;
			COM1_SubMenuID = DO_MENU_CH_SEL;
			COM1_MenuMode  = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case DO_MENU_CH_MODE:

			//go to submenu DO: Select Channel Mode
			ValueBuff_IDx = 0;
			ValueBuff_Lim = VALUE_BUFF_LIM_DO_CH_MODE;
			COM1_SubMenuID = DO_MENU_CH_MODE;
			COM1_MenuMode  = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case DO_MENU_CH_NORMVAL:

			//go to submenu DO: Set Channel Normal value
			ValueBuff_IDx = 0;
			ValueBuff_Lim = VALUE_BUFF_LIM_DO_CH_NORMVAL;
			COM1_SubMenuID = DO_MENU_CH_NORMVAL;
			COM1_MenuMode  = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case DO_MENU_CH_PWM_T:

			//go to submenu DO: Set Channel PWM.T
			ValueBuff_IDx   = 0;
			ValueBuff_Lim   = VALUE_BUFF_LIM_DO_CH_PWMT;
			ValueBuff_PtPos = VALUE_BUFF_SZ;
			COM1_SubMenuID  = DO_MENU_CH_PWM_T;
			COM1_MenuMode   = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case DO_MENU_CH_PWM_D:

			//go to submenu DO: Set Channel PWM.D
			ValueBuff_IDx   = 0;
			ValueBuff_Lim   = VALUE_BUFF_LIM_DO_CH_PWMD;
			ValueBuff_PtPos = VALUE_BUFF_SZ;
			COM1_SubMenuID  = DO_MENU_CH_PWM_D;
			COM1_MenuMode   = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case COM1_MENU_REPEAT:

			//reprint the submenu (without save changes)
			ValueBuff_IDx = 0;
			COM1_MenuMode = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case COM1_MENU_MAIN:

			//go to Main menu (without save changes)
			COM1_MenuID    = COM1_MENU_MAIN;
			COM1_SubMenuID = COM1_MENU_DO;
			COM1_MenuMode  = COM1_MENU_MODE_PRINT;
			Res = VALUE_OK;
			break;

		case COM1_MENU_SAVE:

			Res = VALUE_OK;

			if(COM1_SubMenuID == DO_MENU_CH_SEL)
			{
				//select channel
				if(!COM1_Menu_DO_Save_ChSel())
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Invalid channel number!");
					Res = VALUE_ERROR;
				}
			}
			else if(COM1_SubMenuID == DO_MENU_CH_MODE)
			{
				//select channel
				if(!COM1_Menu_DO_Save_ChMode())
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Invalid channel mode!");
					Res = VALUE_ERROR;
				}
			}
			else if(COM1_SubMenuID == DO_MENU_CH_NORMVAL)
			{
				//select channel
				if(!COM1_Menu_DO_Save_ChNormVal())
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Invalid channel normal value!");
					Res = VALUE_ERROR;
				}
			}
			else if(COM1_SubMenuID == DO_MENU_CH_PWM_T)
			{
				//select channel
				if(!COM1_Menu_DO_Save_ChPwmT())
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Invalid channel PWM.T value!");
					Res = VALUE_ERROR;
				}
			}
			else if(COM1_SubMenuID == DO_MENU_CH_PWM_D)
			{
				//select channel
				if(!COM1_Menu_DO_Save_ChPwmD())
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Invalid channel PWM.D value!");
					Res = VALUE_ERROR;
				}
			}

			//go to DO menu (with save changes)
			ValueBuff_IDx = 0;
			if(Res == VALUE_OK) COM1_SubMenuID = COM1_MENU_DO;
			COM1_MenuMode = COM1_MENU_MODE_PRINT;
			break;

		default:

			if(COM1_SubMenuID == DO_MENU_CH_SEL || COM1_SubMenuID == DO_MENU_CH_MODE || COM1_SubMenuID == DO_MENU_CH_NORMVAL || COM1_SubMenuID == DO_MENU_CH_PWM_T || COM1_SubMenuID == DO_MENU_CH_PWM_D)
			{
				//get value

				if(ValueBuff_IDx <= ValueBuff_Lim)
				{
					if(ValIn >= COM1_ASCII_0 && ValIn <= COM1_ASCII_9)
					{
						ValueBuff[ValueBuff_IDx] = (ValIn-COM1_ASCII_0);
						ValueBuff_IDx++;
						break;
					}
					else if(ValIn == COM1_ASCII_DOT)
					{
						ValueBuff_PtPos = ValueBuff_IDx;
						ValueBuff_IDx++;
						break;
					}
				}
				else
				{
					COM1_BUFF_TX_add("\r\n");
					COM1_BUFF_TX_add("Data buffer overflow!");
				}
			}

			//reprint the menu / submenu
			ValueBuff_IDx = 0;
			COM1_MenuMode  = COM1_MENU_MODE_PRINT;
			Res = VALUE_ERROR;
			break;
	}

	if(Res == VALUE_ERROR)
	{
		COM1_BUFF_TX_add("\r\n");
		COM1_BUFF_TX_add("ERROR\r\n");
	}
	else if(Res == VALUE_OK)
	{
		COM1_BUFF_TX_add("\r\n");
		COM1_BUFF_TX_add("OK\r\n");
	}
}

/** @brief  Menu: DO.
 *  @param  None.
 *  @return None.
 */
static void COM1_Menu_DO(void)
{
	switch(COM1_SubMenuID)
	{
		case DO_MENU_CH:
			COM1_Menu_DO_Main();
			break;

		case DO_MENU_CH_SEL:
			COM1_Menu_DO_ChSel();
			break;

		case DO_MENU_CH_MODE:
			COM1_Menu_DO_ChMode();
			break;

		case DO_MENU_CH_NORMVAL:
			COM1_Menu_DO_ChNormVal();
			break;

		case DO_MENU_CH_PWM_T:
			COM1_Menu_DO_ChPwmT();
			break;

		case DO_MENU_CH_PWM_D:
			COM1_Menu_DO_ChPwmD();
			break;
	}
}

#endif //PLC_MOD_DO


/** @brief  Menu.
 *  @param  ValIn - input byte.
 *  @return None.
 */
static void COM1_Menu(uint8_t ValIn)
{
	COM1_BUFF_TX_rst();

	if(COM1_MenuMode == COM1_MENU_MODE_VALUE)
	{
		switch(COM1_MenuID)
		{
			case COM1_MENU_MAIN:
				COM1_Menu_Main_Value(ValIn);
				break;

			case COM1_MENU_INFO:
				COM1_Menu_Info_Value(ValIn);
				break;

			case COM1_MENU_COUNTERS:
				COM1_Menu_Counters_Value(ValIn);
				break;

			case COM1_MENU_DO:
				COM1_Menu_DO_Value(ValIn);
				break;
		}
	}

	if(COM1_MenuMode == COM1_MENU_MODE_PRINT)
	{
		switch(COM1_MenuID)
		{
			case COM1_MENU_MAIN:
				COM1_Menu_Main();
				break;

			case COM1_MENU_INFO:
				COM1_Menu_Info();
				break;

			case COM1_MENU_COUNTERS:
				COM1_Menu_Counters();
				break;

			case COM1_MENU_DO:
				COM1_Menu_DO();
				break;
		}
	}

	PlcUart_StartTransmit(&PLC_UART1, COM1_TX_BUFF, COM1_TX_BUFF_IDX);
}


/** @brief  User callback-function: Rx-completed.
 *  @param  None.
 *  @return None.
 */
static void COM1_RxCplt(void)
{
	COM1_RxCnt++;
	COM1_Menu(COM1_RX_BUFF[0]);
}

/** @brief  User callback-function: Tx-completed.
 *  @param  None.
 *  @return None.
 */
static void COM1_TxCplt(void)
{
	COM1_TxCnt++;
#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ) || (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
	PlcUart_StartReceive(&PLC_UART1, COM1_RX_BUFF, 1u);
#endif
}


/** @brief  Init the Task.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
static uint8_t COM1_Init(void)
{
#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ) || (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
	//Set user callback-functions
	PLC_UART1_USER_FUNC.RxCplt = COM1_RxCplt;
	PLC_UART1_USER_FUNC.TxCplt = COM1_TxCplt;
#endif

	COM1_MenuID   = COM1_MENU_MAIN;
	COM1_MenuMode = COM1_MENU_MODE_PRINT;

	return (PlcUart1_Init());
}

/** @brief  DeInit the Task.
 *  @param  None.
 *  @return None.
 */
/*
static void COM1_DeInit(void)
{
	PlcUart1_DeInit();
}
*/


uint8_t COM1_Task_Start(void)
{
	uint8_t Res = COM1_Init();
	COM1_Menu(COM1_MENU_MAIN);
	return (Res);
}


#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_POLL)
void COM1_Task_Poll(void)
{
	//1-polling (use in main-loop)
	if(PlcUart_StartReceive(&PLC_UART1, COM1_RX_BUFF, 1u) == HAL_OK)
	{
		COM1_TxCplt();
		COM1_RxCplt();
	}
}
#endif
