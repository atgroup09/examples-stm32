/* @page task-com1.h
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#ifndef TASK_COM1_H
#define TASK_COM1_H

#include "xprintf.h"

#include "uart1.h"

#ifdef PLC_MOD_DO
#include "task-do.h"
#endif //PLC_MOD_DO


/** @def Menu ID
 */

#define COM1_MENU_MAIN       (uint8_t)'q'
#define COM1_MENU_INFO       (uint8_t)'1'
#define COM1_MENU_COUNTERS   (uint8_t)'2'
#define COM1_MENU_DO         (uint8_t)'3'

#define COM1_MENU_REPEAT     (uint8_t)'r'
#define COM1_MENU_SAVE       (uint8_t)'s'


/** @def ASCII codes
 */
#define COM1_ASCII_0         (uint8_t)'0'
#define COM1_ASCII_1         (uint8_t)'1'
#define COM1_ASCII_2         (uint8_t)'2'
#define COM1_ASCII_3         (uint8_t)'3'
#define COM1_ASCII_4         (uint8_t)'4'
#define COM1_ASCII_5         (uint8_t)'5'
#define COM1_ASCII_6         (uint8_t)'6'
#define COM1_ASCII_7         (uint8_t)'7'
#define COM1_ASCII_8         (uint8_t)'8'
#define COM1_ASCII_9         (uint8_t)'9'
#define COM1_ASCII_DOT       (uint8_t)'.'


/** @def Menu mode
 */
#define COM1_MENU_MODE_PRINT (uint8_t)0   //print menu-string
#define COM1_MENU_MODE_VALUE (uint8_t)1   //entering a value


/** @brief  Start the Task.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
uint8_t COM1_Task_Start(void);

#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_POLL)
/** @brief  Process the Task.
 *  @param  None.
 *  @return None.
 */
void COM1_Task_Poll(void);
#endif

#endif //TASK_COM1_H
