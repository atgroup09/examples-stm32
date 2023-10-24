/* @page main.c
 *       Main task
 *       2023, atgroup09@gmail.com
 */

#include "config.h"
#include "error.h"

#ifdef PLC_MOD_LED
#include "led.h"
#endif //PLC_MOD_LED

#ifdef PLC_MOD_DEBUG_LOG
#include "debug-log.h"
#endif //PLC_MOD_DEBUG_LOG


/* @var Main task counter
 */
volatile uint32_t MainCnt = 0;


/** @brief  Main task function.
 *  @param  None.
 *  @return 1 - Error.
 */
int main(void)
{
	uint8_t ResInit = BIT_FALSE;

	/** INIT
	 */

#ifdef PLC_MOD_DEBUG_LOG
	DebugLog_Init();
#endif //PLC_MOD_DEBUG_LOG

#ifdef DEBUG_LOG_MAIN
    DebugLog("===================\n");
    DebugLog("PLC%d.%d RTE.%d\n", PLC_HW_CODE, PLC_HW_VAR, PLC_RTE_VERSION);
#endif //DEBUG_LOG_MAIN

#ifdef PLC_MOD_LED
    ResInit = PlcLed_Init();

#ifdef DEBUG_LOG_MAIN
    if(ResInit)
         DebugLog("MOD_LED [OK]\n");
    else DebugLog("MOD_LED [ERROR]\n");
#endif //DEBUG_LOG_MAIN
#endif //PLC_MOD_LED


    /** PRESTART
     */


    /** START
     */

	while(1)
	{
		MainCnt++;

#ifdef DEBUG_LOG_MAIN
		if(!(MainCnt % PLC_HSE_FREQ))
		{
			DebugLog("MainCnt.tick\n");
		}
#endif //DEBUG_LOG_MAIN
	}

    /** START error
     */

    _Error_Handler(__FILE__, __LINE__);

    return (1);
}
