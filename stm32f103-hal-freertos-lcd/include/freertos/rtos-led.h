/* @page rtos-led.h
 *       RTE / RTOS-task: LED
 *       2022-2025, atgroup09@yandex.ru
 */

#ifndef RTOS_LED_H
#define RTOS_LED_H

#include "led.h"
#include "rtos.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @def Task settings (blocking)
 */
#define RTOS_LED_T_NAME                "LED"
#define RTOS_LED_T_STACK_SZ            (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_LED_T_PRIORITY            (UBaseType_t)PLC_RTOS_T_LED_PRIO
extern TaskHandle_t RTOS_LED_T;


/** @brief  Task handler.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LED_Task(void *ParamsIn);

#endif //RTOS_LED_H
