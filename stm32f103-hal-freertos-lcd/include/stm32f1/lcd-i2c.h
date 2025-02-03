/* @page lcd-i2c.h
 *       LCD-I2C driver (common protocol)
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2025, atgroup09@yandex.ru
 */

#ifndef PLC_LCD_I2C_H
#define PLC_LCD_I2C_H

#include "gpio.h"


/** @def LCD.Protocol: Main commands
 */
#define PLC_LCD_CLEARDISPLAY			0x01
#define PLC_LCD_RETURNHOME				0x02
#define PLC_LCD_ENTRYMODESET			0x04
#define PLC_LCD_DISPLAYCONTROL			0x08
#define PLC_LCD_CURSORSHIFT				0x10
#define PLC_LCD_FUNCTIONSET				0x20
#define PLC_LCD_SETCGRAMADDR			0x40
#define PLC_LCD_SETDDRAMADDR			0x80

/** @def LCD.Protocol: Entry mode
 */
#define PLC_LCD_ENTRYRIGHT				0x00
#define PLC_LCD_ENTRYLEFT				0x02
#define PLC_LCD_ENTRYSHIFTINCREMENT		0x01
#define PLC_LCD_ENTRYSHIFTDECREMENT		0x00

/** @def LCD.Protocol: Display/Cursor Control-flags
 */
#define PLC_LCD_DISPLAYON				0x04
#define PLC_LCD_DISPLAYOFF				0x00
#define PLC_LCD_CURSORON				0x02
#define PLC_LCD_CURSOROFF				0x00
#define PLC_LCD_BLINKON					0x01
#define PLC_LCD_BLINKOFF				0x00

/** @def LCD.Protocol: Display/Cursor Shift-flags
 */
#define PLC_LCD_DISPLAYMOVE				0x08
#define PLC_LCD_CURSORMOVE				0x00
#define PLC_LCD_MOVERIGHT				0x04
#define PLC_LCD_MOVELEFT				0x00

/** @def LCD.Protocol: Display Settings-flags
 */
#define PLC_LCD_8BITMODE				0x10
#define PLC_LCD_4BITMODE				0x00
#define PLC_LCD_2LINE					0x08
#define PLC_LCD_1LINE					0x00
#define PLC_LCD_5x10DOTS				0x04
#define PLC_LCD_5x8DOTS					0x00

/** @def LCD.Protocol: Display Backlight Control-flags
 */
#define PLC_LCD_BACKLIGHT				0x08
#define PLC_LCD_NOBACKLIGHT				0x00

/** @def LCD.Protocol: Command/Data type
 */
#define PLC_LCD_COMMAND					0
#define PLC_LCD_DATA					1

/** @def LCD.Protocol: Functional bits
 */
#define PLC_LCD_BIT_EN					0b00000100  // Enable bit
#define PLC_LCD_BIT_RW					0b00000010  // Read/Write bit
#define PLC_LCD_BIT_RS					0b00000001  // Register select bit


/** @typedef Main context structure
 */
typedef struct PlcLCD_t_
{
	//I2C handle context
	I2C_HandleTypeDef hi2c;

	//LCD address (real, ex.: 0x26, 0x27, ...)
	uint8_t Addr;

	//LCD settings
	uint8_t Control;
	uint8_t Backlight;
	uint8_t Cols;
	uint8_t Rows;

	//flags
	uint8_t Inited;

} PlcLCD_t;


/** @brief  LCD: Send command.
 *  @param  CmdIn - command.
 *  @return None.
 */
void PlcLCD_SendCmd(PlcLCD_t *CtxIn, uint8_t CmdIn);

/** @brief  LCD: Send string.
 *  @param  StrIn - string.
 *  @return None.
 */
void PlcLCD_SendStr(PlcLCD_t *CtxIn, const char *StrIn);

/** @brief  LCD: Clear display.
 *  @param  None.
 *  @return None.
 */
void PlcLCD_Clear(PlcLCD_t *CtxIn);

/** @brief  LCD: Set cursor to home.
 *  @param  None.
 *  @return None.
 */
void PlcLCD_SetHome(PlcLCD_t *CtxIn);

/** @brief  LCD: Set display backlight mode.
 *  @param  StateIn - state of the mode:
 *  @arg    = BIT_FALSE - off
 *  @arg    = BIT_TRUE  - on
 *  @return None.
 */
void PlcLCD_SetBacklight(PlcLCD_t *CtxIn, uint8_t StateIn);

/** @brief  LCD: Set cursor blink mode.
 *  @param  StateIn - state of the mode:
 *  @arg    = BIT_FALSE - off
 *  @arg    = BIT_TRUE  - on
 *  @return None.
 */
void PlcLCD_SetBlink(PlcLCD_t *CtxIn, uint8_t StateIn);

/** @brief  LCD: Show/Hide cursor.
 *  @param  StateIn - state of cursor view:
 *  @arg    = BIT_FALSE - hide
 *  @arg    = BIT_TRUE  - show
 *  @return None.
 */
void PlcLCD_ShowCursor(PlcLCD_t *CtxIn, uint8_t StateIn);

/** @brief  LCD: Set cursor position.
 *  @param  ColIn - column:
 *  @arg    = 0 ... PLC_LCD_COLS-1
 *  @param  RowIn - row:
 *  @arg    = 0 ... PLC_LCD_ROWS-1
 *  @return None.
 */
void PlcLCD_SetCursorPos(PlcLCD_t *CtxIn, uint8_t ColIn, uint8_t RowIn);

/** @brief  LCD: Init.
 *  @param  CtxIn       - pointer to the main context (with INITED I2C-handle).
 *  @param  AddrIn      - display address.
 *  @param  ColsIn      - the number of columns.
 *  @param  RowsIn      - the number of rows.
 *  @param  ControlIn   - Display/Cursor Control-flags.
 *  @param  BacklightIn - Display Backlight Control-flags.
 *  @return None.
 */
void PlcLCD_Init(PlcLCD_t *CtxIn, uint8_t AddrIn, uint8_t ColsIn, uint8_t RowsIn, uint8_t ControlIn, uint8_t BacklightIn);


#endif //PLC_LCD_I2C_H
