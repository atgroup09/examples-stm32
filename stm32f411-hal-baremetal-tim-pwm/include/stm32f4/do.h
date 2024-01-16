/* @page do.h
 *       DO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

/** @note
 *        PA0 <- TIM2.CH1.PWM <- DO.0.Settings
 *        PA1 <- TIM5.CH2.PWM <- DO.1.Settings
 *
 *        TIMx.CHx.PWM is using to control GPIO:
 *
 *        - mode 0 (Off):
 *          TIMx.T = PLC_DO_PWM_T_CODE__MAX
 *          TIMx.D = PLC_DO_PWM_T__MIN
 *          TIMx.PWM -> DOx
 *
 *        - mode 1 (Norm):
 *          TIMx.T = PLC_DO_PWM_T_CODE__MAX
 *          TIMx.D = PLC_DO_PWM_T__MIN
 *          TIMx.PWM -> DOx
 *          or
 *          TIMx.T = PLC_DO_PWM_T_CODE__MAX
 *          TIMx.D = PLC_DO_PWM_T__MAX
 *          TIMx.PWM  -> DOx
 *
 *        - mode 3 (PWM):
 *          TIMx.T = DOx.PwmT
 *          TIMx.D = DOx.PwmD
 *          TIMx.PWM -> DOx
 */

#ifndef PLC_DO_H
#define PLC_DO_H

#include "config.h"
#include "error.h"

#include "tim2.h"
#include "tim5.h"

#include "scale.h"


/** @def Channel number
 */
#define PLC_DO_00                                0
#define PLC_DO_01                                1

/** @def Quantity of channels
 */
#define PLC_DO_SZ                                (uint8_t)(PLC_DO_01+1)

/** @def GPIO references
 */
#define PLC_DO_00__PORT                          GPIOA
#define PLC_DO_00__PIN                           GPIO_PIN_0
#define PLC_DO_00__PIN_MODE     				 PLC_GPIO_DO_PP

#define PLC_DO_01__PORT                          GPIOA
#define PLC_DO_01__PIN                           GPIO_PIN_1
#define PLC_DO_01__PIN_MODE     				 PLC_GPIO_DO_PP


/** @def PWM Period
 */
// limites (ms)
#define PLC_DO_PWM_T__MIN                        (float)0.01        //100.0   kHz
#define PLC_DO_PWM_T__1HZ                        (float)1000.0      //1.0     Hz
#define PLC_DO_PWM_T__MAX                        (float)1000000.0   //0.001   Hz

/** @def PWM Pulse (fill factor)
 */
// limites (%)
#define PLC_DO_PWM_D__MIN              		     (float)0.0
#define PLC_DO_PWM_D__50               		     (float)50.0
#define PLC_DO_PWM_D__MAX              		     (float)100.0


/** @typedef DO channel
 */
typedef struct PlcDO_t_
{
	//CONSTANTS

	//@var Channel number
	//@arg = 0..15
	uint8_t Ch;

	//SETTINGS

    //@var Channel mode
   	//@arg = 0..15
   	uint8_t Mode;

    //@var PWM period (ms)
    float PwmT;

	//VALUES

    //@var Normal value
    uint8_t NormVal;

    //@var PWM fill factor (%)
    float PwmD;

	//STATUSES

	//@var Status code
	//@arg = 0..255
	uint8_t Status;

	//GPIO

	//@var PORT
	GPIO_TypeDef *Port;

	//@var PIN
	uint16_t Pin;

	//@var TIM Handler
	TIM_HandleTypeDef *Tim;

	//@var TIM Channel
	uint32_t TimCh;

	//OTHER

	//@var PWM period (32-bit register value, ARR)
	//@note must be recalculated after change PwmT
	uint32_t Arr;

	//@var PWM pulse (32-bit register value, CCR)
	//@note must be recalculated after change PwmD
	uint32_t Ccr;

	//@var  Scale factors to convert PwmD (%) into 32-bit register value (CCR)
	//@note must be recalculated after change PwmT
	float Ka;
	float Kb;

} PlcDO_t;


/** @def Modes
 */
#define PLC_DO_MODE_OFF                          (uint8_t)0  //off
#define PLC_DO_MODE_NORM                         (uint8_t)1  //normal
#define PLC_DO_MODE_PWM                          (uint8_t)2  //PWM

/** @def Settings by default
 */
#define PLC_DO_MODE_DEF      	                 PLC_DO_MODE_NORM
#define PLC_DO_PWM_T_DEF                         PLC_DO_PWM_T__1HZ
#define PLC_DO_PWM_D_DEF    		             PLC_DO_PWM_D__MIN
#define PLC_DO_PWM_ALLOW_DEF           			 BIT_FALSE
#define PLC_DO_NORM_VAL_DEF                 	 BIT_TRUE

/** @def Status codes
 */
#define PLC_DO_STATUS_OFF                        PLC_DO_MODE_OFF
#define PLC_DO_STATUS_NORM                       PLC_DO_MODE_NORM
#define PLC_DO_STATUS_PWM_ON                     PLC_DO_MODE_PWM
#define PLC_DO_STATUS_PWM_OFF                    (uint8_t)(PLC_DO_MODE_PWM*10)


/** @brief  Init. DO.
 *  @param  DOIn - channel.
 *  @return Result:
 *  @arg    = BIT_FALSE - ERROR
 *  @arg    = BIT_TRUE  - OK
 */
uint8_t PlcDO_Init(PlcDO_t *DOIn);

/** @brief  DeInit. DO.
 *  @param  DOIn - channel.
 *  @return Result:
 *  @arg    = BIT_FALSE - ERROR
 *  @arg    = BIT_TRUE  - OK
 */
uint8_t PlcDO_DeInit(PlcDO_t *DOIn);

/** @brief  Set mode.
 *  @param  DOIn - channel.
 *  @param  ModeIn - new mode:
 *  @arg    = PLC_DO_MODE_OFF  (DO.Stop)
 *  @arg    = PLC_DO_MODE_NORM (DO.Start)
 *  @arg    = PLC_DO_MODE_PWM  (DO.Start)
 *  @return Result:
 *  @arg    = BIT_FALSE - ERROR
 *  @arg    = BIT_TRUE  - OK
 */
uint8_t PlcDO_SetMode(PlcDO_t *DOIn, uint8_t ModeIn);

/** @brief  Set new normal value into TIM.PWM.
 *  @param  DOIn - channel.
 *  @param  ValIn - new normal value:
 *  @arg    = BIT_FALSE - low output level
 *  @arg    = BIT_TRUE  - high output level
 *  @return Result:
 *  @arg    = BIT_FALSE - ERROR
 *  @arg    = BIT_TRUE  - OK
 */
uint8_t PlcDO_SetNormVal(PlcDO_t *DOIn, uint8_t ValIn);

/** @brief  Set channel PWM.T value.
 *  @param  ValIn - channel PWM.T value:
 *  @arg    = PLC_DO_PWM_T__MIN ... PLC_DO_PWM_T__MAX
 *  @return Result:
 *  @arg    = BIT_FALSE - ERROR
 *  @arg    = BIT_TRUE  - OK
 */
uint8_t PlcDO_SetPwmT(PlcDO_t *DOIn, float ValIn);

/** @brief  Set channel PWM.D value.
 *  @param  ValIn - channel PWM.D value:
 *  @arg    = PLC_DO_PWM_D__MIN ... PLC_DO_PWM_D__MAX
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
uint8_t PlcDO_SetPwmD(PlcDO_t *DOIn, float ValIn);

#endif //PLC_DO_H
