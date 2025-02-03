/* @page rtos.h
 *       RTE / RTOS: Global context
 *       2022-2025, atgroup09@yandex.ru
 */

#ifndef RTOS_H
#define RTOS_H

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "timers.h"
#include "config.h"


/** Global components
 *
 *  TASK
 *    *_T_NAME     - task name (for debug, strlen <= configMAX_TASK_NAME_LEN)
 *    *_T_STACK_SZ - task stack size (>= configMINIMAL_STACK_SIZE)
 *    *_T_PRIORITY - task priority (<= configMAX_PRIORITIES)
 *
 *  QUEUE
 *    *_Q_ISZ      - size of one queue-item (sizeof(t), where t is the item type)
 *    *_Q_SZ       - quantity of queue-items
 *    *_Q          - queue
 *
 *  MUTEX
 *    *_MTX        - mutex
 *
 *  SEMAPHORE (binary)
 *    *_SEMA       - semaphore
 */


/** @def RTOS tick time
 *       1kHz = 1000Hz = 1ms
 */
#define RTOS_TICK_MS (uint32_t)1        //ms
#define RTOS_TICK_NS (uint32_t)1000000  //ns


#endif //RTOS_H
