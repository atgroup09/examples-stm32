/* @page rtos-lcd.c
 *       RTE / RTOS-task: LCD
 *       2025, atgroup09@yandex.ru
 */

#include "rtos-lcd.h"


/** @var LCD: Context.
 */
PlcLCD_t PlcLCD_Ctx;


/** @var LCD: RTOS-task
 */
TaskHandle_t RTOS_LCD_T;

/** @var LCD: RTOS-queue
 */
QueueHandle_t RTOS_LCD_Q;


/** @brief  Task Init.
 *  @param  None.
 *  @return None.
 */
static void RTOS_LCD_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LCD_Init\n");
#endif // DEBUG_LOG_MAIN

    PlcI2C2_Init(&(PlcLCD_Ctx.hi2c));
    PlcLCD_Init(&PlcLCD_Ctx, PLC_LCD_ADDR, PLC_LCD_COLS, PLC_LCD_ROWS, PLC_LCD_CONTROL_DEF, PLC_LCD_BACKLIGHT_DEF);
}

/** @brief  Task DeInit.
 *  @param  None.
 *  @return None.
 */
static void RTOS_LCD_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LCD_DeInit\n");
#endif // DEBUG_LOG_MAIN

    PlcI2C2_DeInit();
}

/** @brief  Task handler.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LCD_Task(void *ParamsIn)
{
	//variables
	//uint8_t RTOS_LCD_Q_Item;
	//BaseType_t RTOS_LCD_Q_Status;

	char Buff[20];
	uint16_t Cnt = 0;

    (void)ParamsIn; //fix unused

    //init
    RTOS_LCD_Init();

    //print start screen
    PlcLCD_SetCursorPos(&PlcLCD_Ctx, 0, 0);
	PlcLCD_SendStr(&PlcLCD_Ctx, "STM32F103C8T6");

    //PlcLCD_SendStr(&PLC_LCD_Ctx, "TEST STRING");

    //start
    for(;;)
    {
    	PlcLCD_SetCursorPos(&PlcLCD_Ctx, 0, 1);
    	xsprintf(Buff, "%04d             \0\n\r", Cnt);
    	PlcLCD_SendStr(&PlcLCD_Ctx, Buff);
    	Cnt++;
    	vTaskDelay(1000);

		//RTOS_UART0_Q: read (blocking mode)
    	/*
    	RTOS_LCD_Q_Status = xQueueReceive(RTOS_LCD_Q, &RTOS_LCD_Q_Item, portMAX_DELAY);
		if(RTOS_LCD_Q_Status == pdPASS)
		{
		}
		*/

        //fast switch to other task
        taskYIELD();
    }

    //error start
    RTOS_LCD_DeInit();
}
