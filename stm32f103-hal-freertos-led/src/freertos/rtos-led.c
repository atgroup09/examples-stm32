/* @page rtos-led.c
 *       RTE / RTOS-task: LED
 *       2022-2025, atgroup09@yandex.ru
 */

#include "rtos-led.h"


/** @def  Tasks
 */
TaskHandle_t TASK_LED_T;


/** @brief  Task Init.
 *  @param  None.
 *  @return None.
 */
static void RTOS_LED_Init(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LED_Init\n");
#endif // DEBUG_LOG_MAIN

    PlcLed_Init();
}

/** @brief  Task DeInit.
 *  @param  None.
 *  @return None.
 */
static void RTOS_LED_DeInit(void)
{
#ifdef DEBUG_LOG_MAIN
    DebugLog("RTOS_LED_DeInit\n");
#endif // DEBUG_LOG_MAIN

    PlcLed_DeInit();
}

/** @brief  Task handler.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LED_Task(void *ParamsIn)
{
	//variables

    (void)ParamsIn; //fix unused

    //init
    RTOS_LED_Init();

    //start
    for(;;)
    {
    	PlcLed_Toggle();
    	vTaskDelay(PLC_LED_USER_BLINK_PERIOD);

        //fast switch to other task
        taskYIELD();
    }

    //error start
    RTOS_LED_DeInit();
}
