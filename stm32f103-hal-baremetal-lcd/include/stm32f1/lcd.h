/* @page lcd.h
 *       LCD driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2025, atgroup09@yandex.ru
 */

/** @note
  *        I2C1.GPIO
 *        - PB6  --- I2C1.SCL
 *        - PB7  --- I2C1.SDA
 *
 *        I2C2.GPIO
 *        - PB10 --- I2C2.SCL
 *        - PB11 --- I2C2.SDA
 */

#ifndef PLC_LCD_H
#define PLC_LCD_H

#include "gpio.h"


/** @def LCD.I2C: GPIO
 */
#define PLC_LCD_I2C_GPIO_PORT			GPIOB

#define PLC_LCD_I2C_GPIO_MODE			GPIO_MODE_AF_OD
#define PLC_LCD_I2C_GPIO_SPEED			GPIO_SPEED_FREQ_HIGH
// for I2C1
//#define PLC_LCD_I2C_GPIO_SCL_PIN		GPIO_PIN_6
//#define PLC_LCD_I2C_GPIO_SDA_PIN		GPIO_PIN_7
// for I2C2
#define PLC_LCD_I2C_GPIO_SCL_PIN		GPIO_PIN_10
#define PLC_LCD_I2C_GPIO_SDA_PIN		GPIO_PIN_11

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

/** @def LCD.Protocol: Display/Cursor control
 */
#define PLC_LCD_DISPLAYON				0x04
#define PLC_LCD_DISPLAYOFF				0x00
#define PLC_LCD_CURSORON				0x02
#define PLC_LCD_CURSOROFF				0x00
#define PLC_LCD_BLINKON					0x01
#define PLC_LCD_BLINKOFF				0x00

/** @def LCD.Protocol: Display/Cursor shift
 */
#define PLC_LCD_DISPLAYMOVE				0x08
#define PLC_LCD_CURSORMOVE				0x00
#define PLC_LCD_MOVERIGHT				0x04
#define PLC_LCD_MOVELEFT				0x00

/** @def LCD.Protocol: Display functions
 */
#define PLC_LCD_8BITMODE				0x10
#define PLC_LCD_4BITMODE				0x00
#define PLC_LCD_2LINE					0x08
#define PLC_LCD_1LINE					0x00
#define PLC_LCD_5x10DOTS				0x04
#define PLC_LCD_5x8DOTS					0x00

/** @def LCD.Protocol: Backlight control
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


/** @def LCD: Settings (by default)
 */
#define PLC_LCD_CONTROL_DEF				(PLC_LCD_CURSOROFF|PLC_LCD_BLINKOFF)
#define PLC_LCD_BACKLIGHT_DEF			(PLC_LCD_NOBACKLIGHT)

#define PLC_LCD_I2C						I2C2
#define PLC_LCD_ADDR					0x27
#define PLC_LCD_COLS					16
#define PLC_LCD_ROWS					2


/** @typedef Main context structure
 */
typedef struct PlcLCD_t_
{
	//I2C handle context
	I2C_HandleTypeDef hi2c;

	//LCD address (real, ex.: 0x26)
	uint8_t Addr;

	//LCD settings
	uint8_t Control;
	uint8_t Backlight;
	uint8_t Cols;
	uint8_t Rows;

	//flags
	uint8_t Inited;

} PlcLCD_t;

/* @var LCD: Main context.
 */
extern PlcLCD_t PLC_LCD_Ctx;


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
 *  @param  CtxIn  - pointer to the main context.
 *  @param  I2cIn  - pointer to the I2C instance.
 *  @param  AddrIn - display address.
 *  @param  ColsIn - the number of columns.
 *  @param  RowsIn - the number of rows.
 *  @return None.
 */
void PlcLCD_Init(PlcLCD_t *CtxIn, I2C_TypeDef *I2cIn, uint8_t AddrIn, uint8_t ColsIn, uint8_t RowsIn);

/** @brief  LCD: DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcLCD_DeInit(void);


#endif //PLC_LCD_H
