/* @page task-com1.h
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#ifndef TASK_COM1_H
#define TASK_COM1_H

#include "uart1.h"


/** @def Menu ID
 */
#define COM1_MENU_MAIN       (uint8_t)'0'
#define COM1_MENU_ABOUT_PLC  (uint8_t)'1'
#define COM1_MENU_COUNTERS   (uint8_t)'2'


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
