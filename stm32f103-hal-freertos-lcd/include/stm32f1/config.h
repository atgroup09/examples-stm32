/* @page config.h
 *       Configuration
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2023-2025, atgroup09@yandex.ru
 */

#ifndef PLC_CONFIG_H
#define PLC_CONFIG_H

#include <stdint.h>
#include <stdarg.h>

#include "bit.h"
#include "type.h"

#include "stm32f1xx.h"
#include "stm32f1xx_hal.h"


/** VERSIONS
 *  ===========================================================================
 */

/** @def    Pack RTE-version
 *  @param  MajorIn - Major
 *  @param  MinorIn - Minor
 *  @param  PatchIn - Patch
 *  @return Packed RTE-version
 */
#define PLC_RTE_VERSION_PACK(MajorIn, MinorIn, PatchIn) ((PatchIn<<8)+(MinorIn<<4)+MajorIn)

/** @def    Pack RTE-day.month
 *  @param  DayIn - Major
 *  @param  MonthIn - Minor
 *  @return Packed RTE-day.month
 */
#define PLC_RTE_DDMM_PACK(DayIn, MonthIn) ((DayIn<<4)+MonthIn)


/** @def PLC.code
 */
#define PLC_HW_CODE                              103

/** @def PLC.variant
 */
#define PLC_HW_VAR                               1

/** @def RTE.year
 */
#define PLC_RTE_YYYY                             2025

/** @def RTE.day-month
 */
#define PLC_RTE_DDMM                             (uint16_t)PLC_RTE_DDMM_PACK(28, 1)

/** @def RTE.version
 */
#define PLC_RTE_VERSION_MAJOR                    1
#define PLC_RTE_VERSION_MINOR                    0
#define PLC_RTE_VERSION_PATCH                    0

/** @def RTE.version (packed)
 */
#define PLC_RTE_VERSION                          (uint16_t)PLC_RTE_VERSION_PACK(PLC_RTE_VERSION_MAJOR, PLC_RTE_VERSION_MINOR, PLC_RTE_VERSION_PATCH)



/** RTE MODULES
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

// LED
#define RTE_MOD_LED



/** FREQUENCY DEFINES
 *  ===========================================================================
 */

/** @def MHz base
 *       1 MHz = 1000000 Hz
 */
#define MHZ_BASE                                 1000000UL

/** @def Flag values
 */
#define FLAG_RESET                               BIT_FALSE
#define FLAG_SET                                 BIT_TRUE

/** @def SysClock defines
 */
#define PLC_F_CPU                                (uint32_t)(72*MHZ_BASE)

#define PLC_HSE_FREQ                             (uint32_t)(8*MHZ_BASE)  //HSE
#define PLC_SYSCLK_FREQ                          (uint32_t)(72*MHZ_BASE) //SYSCLK
#define PLC_HCLK_FREQ                            (uint32_t)(72*MHZ_BASE)  //HCLK
#define PLC_AHB_FREQ                             PLC_HCLK_FREQ            //AHB
#define PLC_APB1_PCLK_FREQ                       (uint32_t)(36*MHZ_BASE)  //APB1 Peripheral clocks
#define PLC_APB1_TCLK_FREQ                       (uint32_t)(72*MHZ_BASE) //APB1 Timer clocks
#define PLC_APB2_PCLK_FREQ                       (uint32_t)(72*MHZ_BASE) //APB2 Peripheral clocks
#define PLC_APB2_TCLK_FREQ                       (uint32_t)(72*MHZ_BASE) //APB2 Timer clocks

/** @def SysTick freq.
 *       1-tick = 1000Hz = 1000us = 1ms
 *
 *       1kHz = 1000Hz = 1ms
 *       1MHz = 1000000Hz = 1us
 */
#define PLC_SYSTICK_FREQ_HZ                      1000   //Hz



/** IRQ PRIORITY DEFINES
 *  ===========================================================================
 *   0 is a higher priority
 *  15 is a lower priority
 */

// stm32f4xx_hal_conf.h::GROUP_INT
// __initialize_hardware(void)::HAL_Init()
//  4 bits for preemption priority (0...15)
//  0 bits for subpriority (0)
#define PLC_NVIC_PRIO_GROUP            			 NVIC_PRIORITYGROUP_4

//Lowest NVIC-priority
#define PLC_NVIC_PRIO_LOWEST                     15

//Max NVIC-priority of system-dependent IRQ
#define PLC_NVIC_PRIO_RTOS_SYSCALL               8


// SYSTEM-DEPENDENT ISR
// - PPRIO > PLC_NVIC_PRIO_RTOS_SYSCALL
// - that using RTOS API (*FromISR)
// - without interrupt the procedures of KERNEL or CRITICAL-SECTIONS (ISR is waiting for complete the procedures)

//SysTick
// __initialize_hardware(void)::SystemClock_Config()
#define PLC_NVIC_PPRIO_SYSTICK                   15
#define PLC_NVIC_SPRIO_SYSTICK                   0


// SYSTEM-INDEPENDENT ISR
// - PPRIO <= PLC_NVIC_PRIO_RTOS_SYSCALL
// - that NOT using RTOS API (*FromISR)
// - with interrupt the procedures of KERNEL or CRITICAL-SECTIONS (ISR is not waiting for complete the procedures)



/** DMA PRIORITY DEFINES
 *  ===========================================================================
 */



/** RTOS
 *  ===========================================================================
  */

/** @def RTOS used/not used
 */
#define PLC_RTOS



/** TASK PRIORITY DEFINES
 *  ===========================================================================
 *   0 is a lower priority (IDLE-task has zero priority)
 *  PLC_RTOS_PRIO_MAX-1 is a higher priority
 */

//Max NVIC-priority of system-dependent IRQ
#define PLC_RTOS_PRIO_MAX						10


// BLOCKING TASKS
// - higher priorities (4,5,6,7)
#define PLC_RTOS_T_LED_PRIO						4
#define PLC_RTOS_T_LCD_PRIO						4


// NON-BLOCKING TASKS
// - lower priorities (1,2,3)



/** DEBUG MODE
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

/** @def  Global permit Debug-flag
 *  @note remove compiler-option -DDEBUG to use this flag
 */
//#define DEBUG

/** @def Supported Debug-interfaces
 */
#define DEBUG_LOG_DST_NO                         0   //No output
#define DEBUG_LOG_DST_SWD                        1   //SWO

#ifdef DEBUG

/** @def Used Debug-interface
 */
#define DEBUG_LOG_DST                            DEBUG_LOG_DST_SWD

/** @def DebugLog Modules
 */
#define DEBUG_LOG_ERROR				         	 //RTOS errors
#define DEBUG_LOG_MAIN				             //Main
//#define DEBUG_LOG_LED					         //T_LED

#endif // DEBUG


#endif //PLC_CONFIG_H
