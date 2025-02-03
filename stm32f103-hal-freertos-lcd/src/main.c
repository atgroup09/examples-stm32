/* @page main.c
 *       Main task
 *       2025, atgroup09@yandex.ru
 */

#include "config.h"
#include "error.h"

#include "rtos-led.h"
#include "rtos-lcd.h"


/* @var Main task counter
 */
volatile uint32_t MainCnt = 0;


/** @brief  Main task function.
 *  @param  None.
 *  @return 1 - Error.
 */
int main(void)
{
	/** INIT: nonRTOS
	 */


	/** INIT: RTOS
	 */

	//LED

	RTOS_LED_T = NULL;
	if(xTaskCreate(RTOS_LED_Task, RTOS_LED_T_NAME, RTOS_LED_T_STACK_SZ, NULL, RTOS_LED_T_PRIORITY, &RTOS_LED_T) != pdTRUE)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

	//LCD

	RTOS_LCD_T = NULL;
	if(xTaskCreate(RTOS_LCD_Task, RTOS_LCD_T_NAME, RTOS_LCD_T_STACK_SZ, NULL, RTOS_LCD_T_PRIORITY, &RTOS_LCD_T) != pdTRUE)
	{
		_Error_Handler(__FILE__, __LINE__);
	}


    /** PRESTART
     */


    /** START: nonRTOS
     */


    /** START: RTOS
     */

	vTaskStartScheduler();


	/** ERROR: doesn't start
	 */

    _Error_Handler(__FILE__, __LINE__);

    return (1);
}
