/* @page tim2.h
 *       TIM2 driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *
 *        PA0 <- TIM2.CH1.PWM <- DO.0.Settings[.PSC, .ARR]
 *
 *        TIM settings
 *        - .FREQ.BUS = 100 MHz (1 bus-tick is 10 ns)
 *        - .PSC      = 100     (16 bit, 1 TIM-tick is 1000000 Hz)
 *        - .RCR      = 0       (8  bit)
 *        - .ARR      = T       (32 bit)
 *           where T is period  (10 ... 1000000000)
 *
 *        TIM2 is 32-bit timer
 */

#ifndef PLC_TIM2_H
#define PLC_TIM2_H

#include "tim.h"


/** @def GPIO references
 */
#define PLC_TIM2_DO_CH                           (uint32_t)TIM_CHANNEL_1


/** @def TIM tick frequency
 */
#define PLC_TIM2_HZ                              (uint32_t)1000000  //Hz
#define PLC_TIM2_MS                              (float)0.001       //ms

/** #def TIM prescaler
 */
// (.PSC)
#define PLC_TIM2_PRESCALER                       (uint32_t)((PLC_APB1_TCLK_FREQ/PLC_TIM2_HZ)-1)	 //100 counts for 1 TIM-tick

/** @def TIM period (quantity of ticks to reload)
 */
// (.ARR)
#define PLC_TIM2_PERIOD__MIN                     (uint32_t)(10-1)
#define PLC_TIM2_PERIOD__1HZ                     (uint32_t)(1000000-1)
#define PLC_TIM2_PERIOD__10SEC                   (uint32_t)(10000000-1)
#define PLC_TIM2_PERIOD__MAX                     (uint32_t)(1000000000-1)


/** @brief  Init. TIM2
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
uint8_t PlcTim2_Init(void);

/** @brief  DeInit. TIM2
 *  @param  None.
 *  @return None.
 */
void PlcTim2_DeInit(void);

#endif //PLC_TIM2_H
