/* @page debug-log.h
 *       DebugLog
 *       2022-2023, atgroup09@gmail.com
 */


/** @note
 *        Print debug data over:
 *        + SWD/SWO interface
 */

#ifndef DEBUG_LOG_H
#define DEBUG_LOG_H

#include "config.h"
#include "xprintf.h"

#if (DEBUG_LOG_INTERFACE == DEBUG_LOG_INTERFACE_SWD)
#include "swd.h"
#endif


/** @def Size of local buffer
 */
#define DEBUG_LOG_BUFF_SZ  250


/** @brief  DebugLog init.
 *  @param  None.
 *  @return None.
 */
void DebugLog_Init(void);

/** @brief  Wait for Process is unlocked
 *  @param  None.
 *  @return None.
 */
void DebugLog_Wait(void);

/** @brief  DebugLog print.
 *  @param  FmtIn - pointer to string with format specificators.
 *  @param  ...   - arguments of format specificators.
 *  @return None.
 *  @note   !!! BLOCKING MODE IS USED             !!!
 *          !!! call from interrupts with caution !!!
 */
void DebugLog(const char *FmtIn, ...);

#endif //DEBUG_LOG_H
