/* @page swd.h
 *       SWD/SWO driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2022-2025, atgroup09@yandex.ru
 */


/** @note
 *        PA13 -- SWDIO
 *        PA14 -- SWCLK
 *        PB3  -- SWO
 */

#ifndef PLC_SWD_H
#define PLC_SWD_H

#include "config.h"


/** @def SWD/SWO Port number
 */
#define PLC_SWD_PORT	(uint8_t)0


/** @brief  Print byte.
 *  @param  ByteIn - byte.
 *  @return None.
 */
void PlcSwd_PrintByte(uint8_t ByteIn);

/** @brief  Print string.
 *  @param  StrIn - pointer to string.
 *  @param  StrLenIn - size of string.
 *  @return None.
 */
void PlcSwd_PrintStr(const char *StrIn, uint8_t StrLenIn);

/** @brief  Init.
 *  @param  None.
 *  @return None.
 */
void PlcSwd_Init(void);

#endif //PLC_SWD_H
