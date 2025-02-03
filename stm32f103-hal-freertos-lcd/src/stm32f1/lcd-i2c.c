/* @page lcd-i2c.c
 *       LCD-I2C driver (common protocol)
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2025, atgroup09@yandex.ru
 */

#include "lcd-i2c.h"


/** @brief  LCD.I2C: Send Command/Data byte.
 *  @param  ByteIn - byte of command/data to send.
 *  @param  TypeIn - byte type:
 *  @arg    = PLC_LCD_COMMAND - command
 *  @arg    = PLC_LCD_DATA    - data/string-character
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE  - success
 */
static uint8_t PlcLCD_I2C_Send(PlcLCD_t *CtxIn, uint8_t ByteIn, uint8_t TypeIn)
{
	if(CtxIn && (TypeIn == PLC_LCD_COMMAND || TypeIn == PLC_LCD_DATA))
	{
		//address for HAL.I2C
		uint8_t Addr = (CtxIn->Addr << 1);

		//waiting for the device is ready
		HAL_StatusTypeDef Res = HAL_I2C_IsDeviceReady(&(CtxIn->hi2c), Addr, 1, HAL_MAX_DELAY);
		//failed, nobody answered
		if(Res != HAL_OK) return (BIT_FALSE);

		//split byte to Higher and Lower parts
		uint8_t ByteHi = (ByteIn & 0xF0);
		uint8_t ByteLo = ((ByteIn << 4) & 0xF0);

		//buffer
		uint8_t Buff[4];
		// 4-7 bits contains info, bits 0-3 contains configuration
		Buff[0] = (ByteHi|TypeIn|(CtxIn->Backlight)|PLC_LCD_BIT_EN);
		Buff[1] = (ByteHi|TypeIn|(CtxIn->Backlight));
		Buff[2] = (ByteLo|TypeIn|(CtxIn->Backlight)|PLC_LCD_BIT_EN);
		Buff[3] = (ByteLo|TypeIn|(CtxIn->Backlight));

		//transmit
		Res = HAL_I2C_Master_Transmit(&(CtxIn->hi2c), Addr, Buff, sizeof(Buff), HAL_MAX_DELAY);
		HAL_Delay(8);
		if(Res == HAL_OK) return (BIT_TRUE);
	}

	return (BIT_FALSE);
}


void PlcLCD_SendCmd(PlcLCD_t *CtxIn, uint8_t CmdIn)
{
	PlcLCD_I2C_Send(CtxIn, CmdIn, PLC_LCD_COMMAND);
}

void PlcLCD_SendStr(PlcLCD_t *CtxIn, const char *StrIn)
{
	if(CtxIn && StrIn)
	{
		while(*StrIn)
		{
			PlcLCD_I2C_Send(CtxIn, (uint8_t)(*StrIn), PLC_LCD_DATA);
			StrIn++;
		}
	}
}

void PlcLCD_Clear(PlcLCD_t *CtxIn)
{
	PlcLCD_SendCmd(CtxIn, PLC_LCD_CLEARDISPLAY);
}

void PlcLCD_SetHome(PlcLCD_t *CtxIn)
{
	PlcLCD_SendCmd(CtxIn, PLC_LCD_RETURNHOME);
}

void PlcLCD_SetBacklight(PlcLCD_t *CtxIn, uint8_t StateIn)
{
	if(CtxIn) CtxIn->Backlight = ((StateIn) ? BIT_TRUE : BIT_FALSE);
	PlcLCD_SendCmd(CtxIn, 0);
}

void PlcLCD_SetBlink(PlcLCD_t *CtxIn, uint8_t StateIn)
{
	if(CtxIn)
	{
		CtxIn->Control = ((StateIn) ? (CtxIn->Control|PLC_LCD_BLINKON) : (CtxIn->Control&~PLC_LCD_BLINKON));
		PlcLCD_SendCmd(CtxIn, (PLC_LCD_DISPLAYCONTROL|PLC_LCD_DISPLAYON|CtxIn->Control));
	}
}

void PlcLCD_ShowCursor(PlcLCD_t *CtxIn, uint8_t StateIn)
{
	if(CtxIn)
	{
		CtxIn->Control = ((StateIn) ? (CtxIn->Control|PLC_LCD_CURSORON) : (CtxIn->Control&~PLC_LCD_CURSORON));
		PlcLCD_SendCmd(CtxIn, (PLC_LCD_DISPLAYCONTROL|PLC_LCD_DISPLAYON|CtxIn->Control));
	}
}

void PlcLCD_SetCursorPos(PlcLCD_t *CtxIn, uint8_t ColIn, uint8_t RowIn)
{
	if(CtxIn)
	{
		if(ColIn < CtxIn->Cols && RowIn < CtxIn->Rows)
		{
			uint8_t RowOffset[] = { 0x00, 0x40, 0x14, 0x54 };
			PlcLCD_SendCmd(CtxIn, (PLC_LCD_SETDDRAMADDR|(ColIn+RowOffset[RowIn])));
		}
	}
}

void PlcLCD_Init(PlcLCD_t *CtxIn, uint8_t AddrIn, uint8_t ColsIn, uint8_t RowsIn, uint8_t ControlIn, uint8_t BacklightIn)
{
	if(CtxIn)
	{
		CtxIn->Addr		 = AddrIn;
		CtxIn->Cols   	 = ColsIn;
		CtxIn->Rows   	 = RowsIn;
		CtxIn->Control   = ControlIn;
		CtxIn->Backlight = BacklightIn;

		PlcLCD_SendCmd(CtxIn, PLC_LCD_FUNCTIONSET|PLC_LCD_8BITMODE);
		HAL_Delay(5);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_FUNCTIONSET|PLC_LCD_8BITMODE);
		HAL_Delay(150);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_FUNCTIONSET|PLC_LCD_4BITMODE);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_FUNCTIONSET|PLC_LCD_4BITMODE|PLC_LCD_5x8DOTS|PLC_LCD_2LINE);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_DISPLAYCONTROL|PLC_LCD_DISPLAYOFF|PLC_LCD_CURSOROFF|PLC_LCD_BLINKOFF);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_CLEARDISPLAY);
		HAL_Delay(5);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_ENTRYMODESET|PLC_LCD_ENTRYLEFT|PLC_LCD_ENTRYSHIFTDECREMENT);
		PlcLCD_SendCmd(CtxIn, PLC_LCD_DISPLAYCONTROL|PLC_LCD_DISPLAYON|(CtxIn->Control));
	}
}
