/* @page main.c
 *       Main task
 *       2025, atgroup09@yandex.ru
 */

#include "config.h"
#include "led.h"
#include "lcd.h"


/* @var Main task counter
 */
volatile uint32_t MainCnt = 0;


/** @brief  Main task function.
 *  @param  None.
 *  @return 1 - Error.
 */
int main(void)
{
	/** INIT
	 */

	PlcLed_Init();
	PlcLCD_Init(&PLC_LCD_Ctx, PLC_LCD_I2C, PLC_LCD_ADDR, PLC_LCD_COLS, PLC_LCD_ROWS);


    /** PRESTART
     */
	PlcLCD_SendCmd(&PLC_LCD_Ctx, 0b10000000);
	PlcLCD_SendStr(&PLC_LCD_Ctx, "STM32F103C8T6");

	PlcLCD_SendCmd(&PLC_LCD_Ctx, 0b11000000);
	PlcLCD_SendStr(&PLC_LCD_Ctx, "LCD1602.I2C");


    /** START
     */

	while(1)
	{
		MainCnt++;
	}

    /** START error
     */

    _Error_Handler(__FILE__, __LINE__);

    return (1);
}
