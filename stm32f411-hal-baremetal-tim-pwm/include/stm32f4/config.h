/* @page config.h
 *       Configuration
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

#ifndef PLC_CONFIG_H
#define PLC_CONFIG_H

#include <stdint.h>
#include <stdarg.h>

#include "bit.h"
#include "type.h"

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"


/** @def Flag values
 */
#define FLAG_RESET  BIT_FALSE
#define FLAG_SET    BIT_TRUE


/** VERSION NUMBERS
 *  ===========================================================================
 */

/** @def    Pack RTE-version
 *  @param  MajorIn - Major
 *  @param  MinorIn - Minor
 *  @param  PatchIn - Patch
 *  @return Packed RTE-version
 */
#define PACK_PLC_RTE_VERSION(MajorIn, MinorIn, PatchIn) ((PatchIn<<8)+(MinorIn<<4)+MajorIn)

/** @def    Pack RTE-day.month
 *  @param  DayIn - Major
 *  @param  MonthIn - Minor
 *  @return Packed RTE-day.month
 */
#define PACK_PLC_RTE_DDMM(DayIn, MonthIn) ((DayIn<<4)+MonthIn)


/** @def PLC-code
 */
#define PLC_HW_CODE                              411

/** @def PLC-variant
 */
#define PLC_HW_VAR                               1

/** @def RTE-version
 */
#define PLC_RTE_VERSION_MAJOR                    1
#define PLC_RTE_VERSION_MINOR                    0
#define PLC_RTE_VERSION_PATCH                    0

/** @def RTE-version (packed)
 */
#define PLC_RTE_VERSION                          (uint16_t)PACK_PLC_RTE_VERSION(PLC_RTE_VERSION_MAJOR, PLC_RTE_VERSION_MINOR, PLC_RTE_VERSION_PATCH)

/** @def RTE-year
 */
#define PLC_RTE_YYYY                             2024

/** @def RTE-day.month
 */
#define PLC_RTE_DDMM                             (uint16_t)PACK_PLC_RTE_DDMM(11, 01)


/** MODULES
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

#define PLC_MOD_DEBUG_LOG                        //DEBUG_LOG
#define PLC_MOD_LED				                 //LED
#define PLC_MOD_COM1			                 //COM1
#define PLC_MOD_DO			 	                 //DO


/** DEBUG LOG
 *  ===========================================================================
 *  (comment/uncomment the required lines)
 */

#ifdef PLC_MOD_DEBUG_LOG

/** @def Supported DebugLog interfaces
 */
#define DEBUG_LOG_INTERFACE_NO                   0   //No output
#define DEBUG_LOG_INTERFACE_SWD                  1   //SWO

/** @def Used DebugLog interface
 */
#define DEBUG_LOG_INTERFACE                      DEBUG_LOG_INTERFACE_SWD

/** @def DebugLog modules
 */
#define DEBUG_LOG_ERROR				         	 //Error Handler
#define DEBUG_LOG_MAIN				             //Main
#define DEBUG_LOG_SYSTICK			             //System Timer

#endif //PLC_MOD_DEBUG_LOG


/** FREQUENCIES
 *  ===========================================================================
 */

/** @def 1 MHz = 1000000 Hz
 */
#define MHZ_BASE                                 1000000UL

/** @def SysClock defines
 */
#define PLC_F_CPU                                (uint32_t)(100*MHZ_BASE)

#define PLC_HSE_FREQ                             (uint32_t)(25*MHZ_BASE)   //HSE
#define PLC_SYSCLK_FREQ                          (uint32_t)(100*MHZ_BASE)  //SYSCLK
#define PLC_HCLK_FREQ                            (uint32_t)(100*MHZ_BASE)  //HCLK
#define PLC_AHB_FREQ                             PLC_HCLK_FREQ             //AHB
#define PLC_APB1_PCLK_FREQ                       (uint32_t)(50*MHZ_BASE)   //APB1 Peripheral clocks
#define PLC_APB1_TCLK_FREQ                       (uint32_t)(100*MHZ_BASE)  //APB1 Timer clocks
#define PLC_APB2_PCLK_FREQ                       (uint32_t)(100*MHZ_BASE)  //APB2 Peripheral clocks
#define PLC_APB2_TCLK_FREQ                       (uint32_t)(100*MHZ_BASE)  //APB2 Timer clocks

/** @def SysTick freq.
 *       1-tick = 1000Hz = 1000us = 1ms
 *
 *       1kHz = 1000Hz = 1ms
 *       1MHz = 1000000Hz = 1us
 */
#define PLC_SYSTICK_FREQ_HZ                      1000   //Hz


/** IRQ PRIORITIES
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

//COM1
// .DMA.UART.Tx
#define PLC_NVIC_PPRIO_COM1_DMA_TX           	 13
#define PLC_NVIC_SPRIO_COM1_DMA_TX           	 0
// .DMA.UART.Rx
#define PLC_NVIC_PPRIO_COM1_DMA_RX           	 13
#define PLC_NVIC_SPRIO_COM1_DMA_RX          	 0
// .UART
#define PLC_NVIC_PPRIO_COM1_UART           		 13
#define PLC_NVIC_SPRIO_COM1_UART          		 0

//COM2
// .DMA.UART.Tx
#define PLC_NVIC_PPRIO_COM2_DMA_TX           	 9
#define PLC_NVIC_SPRIO_COM2_DMA_TX           	 0
// .DMA.UART.Rx
#define PLC_NVIC_PPRIO_COM2_DMA_RX           	 9
#define PLC_NVIC_SPRIO_COM2_DMA_RX          	 0
// .UART
#define PLC_NVIC_PPRIO_COM2_UART           		 9
#define PLC_NVIC_SPRIO_COM2_UART          		 0

//SysTick
// stm32f4xx_hal_conf.h::TICK_INT_PRIORITY
// __initialize_hardware(void)::HAL_Init()
#define PLC_NVIC_PPRIO_SYSTICK                   15
#define PLC_NVIC_SPRIO_SYSTICK                   0


/** DMA PRIORITIES
 *  ===========================================================================
 */

//COM1
#define PLC_DMA_PRIO_COM1_RX					DMA_PRIORITY_LOW
#define PLC_DMA_PRIO_COM1_TX					DMA_PRIORITY_LOW

//COM2
#define PLC_DMA_PRIO_COM2_RX					DMA_PRIORITY_MEDIUM
#define PLC_DMA_PRIO_COM2_TX					DMA_PRIORITY_MEDIUM


/** RTOS PRIORITIES
 *  ===========================================================================
 *   0 is a lower priority (IDLE-task has zero priority)
 *  PLC_RTOS_PRIO_MAX-1 is a higher priority
 */


#endif //PLC_CONFIG_H
