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


#endif //PLC_CONFIG_H
