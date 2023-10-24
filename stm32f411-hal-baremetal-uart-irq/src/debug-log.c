/* @page debug-log.c
 *       DebugLog
 *       2022-2023, atgroup09@gmail.com
 */

#include "debug-log.h"


/** @var Process Locker
 */
volatile uint8_t DEBUG_LOG_LOCK = BIT_FALSE;


/** @var Local buffer
 */
#ifdef PLC_MOD_DEBUG_LOG
static char DEBUG_LOG_BUFF[DEBUG_LOG_BUFF_SZ];

/** @brief  Lock Process
 *  @param  None.
 *  @return None.
 */
static inline void DebugLog_Lock(void)
{
	DEBUG_LOG_LOCK = BIT_TRUE;
}

/** @brief  UnLock Process
 *  @param  None.
 *  @return None.
 */
static inline void DebugLog_UnLock(void)
{
	DEBUG_LOG_LOCK = BIT_FALSE;
}
#endif //PLC_MOD_DEBUG_LOG


void DebugLog_Init(void)
{
#if (DEBUG_LOG_INTERFACE == DEBUG_LOG_INTERFACE_SWD)
	PlcSwd_Init();
#endif
}


void DebugLog_Wait(void)
{
	while(DEBUG_LOG_LOCK);
}


void DebugLog(const char *FmtIn, ...)
{
#ifdef PLC_MOD_DEBUG_LOG
    if(FmtIn)
    {
    	DebugLog_Wait();
    	DebugLog_Lock();

        va_list arp;
        va_start(arp, FmtIn);
        xsprintfa(DEBUG_LOG_BUFF, FmtIn, arp);

#if (DEBUG_LOG_INTERFACE == DEBUG_LOG_INTERFACE_SWD)
        PlcSwd_PrintStr(DEBUG_LOG_BUFF, strlen(DEBUG_LOG_BUFF));
#endif
        va_end(arp);

        DebugLog_UnLock();
    }

#else
    (void)FmtIn;
#endif //PLC_MOD_DEBUG_LOG
}
