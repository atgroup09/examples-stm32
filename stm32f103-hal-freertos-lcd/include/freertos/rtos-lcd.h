/* @page rtos-lcd.h
 *       RTE / RTOS-task: LCD
 *       2025, atgroup09@yandex.ru
 */

#ifndef RTOS_LCD_H
#define RTOS_LCD_H

#include "i2c2.h"
#include "lcd-i2c.h"
#include "rtos.h"
#include "xprintf.h"

#ifdef DEBUG
#include "debug-log.h"
#endif // DEBUG


/** @def LCD: Settings (by default)
 */
#define PLC_LCD_CONTROL_DEF				(PLC_LCD_DISPLAYON|PLC_LCD_CURSOROFF|PLC_LCD_BLINKOFF)
#define PLC_LCD_BACKLIGHT_DEF			(PLC_LCD_NOBACKLIGHT)

#define PLC_LCD_ADDR					0x27
#define PLC_LCD_COLS					16
#define PLC_LCD_ROWS					2


/** @def Task settings (blocking)
 */
#define RTOS_LCD_T_NAME                "LCD"
#define RTOS_LCD_T_STACK_SZ            (configSTACK_DEPTH_TYPE)configMINIMAL_STACK_SIZE
#define RTOS_LCD_T_PRIORITY            (UBaseType_t)PLC_RTOS_T_LCD_PRIO
extern TaskHandle_t RTOS_LCD_T;

/** @def Queue LCD_Q
 *  @note to LCD_T (commands)
 */
#define RTOS_LCD_Q_ISZ    			   (UBaseType_t)sizeof(uint8_t)
#define RTOS_LCD_Q_SZ     			   (UBaseType_t)(4)
extern QueueHandle_t RTOS_LCD_Q;


/** @brief  Task handler.
 *  @param  ParamsIn - pointer to additional task parameters.
 *  @return None.
 */
void RTOS_LCD_Task(void *ParamsIn);

#endif //RTOS_LCD_H
