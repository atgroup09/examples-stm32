/* @page task-do.h
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#ifndef TASK_DO_H
#define TASK_DO_H

#include "xprintf.h"
#include "do.h"


/** @brief  Start the Task.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
uint8_t DO_Task_Start(void);


/** @def Menu ID
 */
#define DO_MENU_CH         (uint8_t)'3'  //channel
#define DO_MENU_CH_SEL     (uint8_t)'c'  //channel: select
#define DO_MENU_CH_MODE    (uint8_t)'m'  //channel: mode
#define DO_MENU_CH_NORMVAL (uint8_t)'v'  //channel: normal value
#define DO_MENU_CH_PWM_T   (uint8_t)'t'  //channel: PWM.T (Period, ms)
#define DO_MENU_CH_PWM_D   (uint8_t)'d'  //channel: PWM.D (FillFactor, %)


/** @typedef Info-context
 */
typedef struct DO_Info_t_
{
	//@var Channel number
	uint8_t Ch;

    //@var Channel mode
   	uint8_t Mode;

   	//@var Normal value
   	uint8_t NormVal;

    //@var PWM period (ms)
    float PwmT;

    //@var PWM fill factor (%)
    float PwmD;

} DO_Info_t;


/** @brief  Get info about selected channel.
 *  @param  BuffIn - pointer to buffer for save the info-context.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_GetChInfo(DO_Info_t *BuffIn);

/** @brief  Set channel number.
 *  @param  ChIn - channel number.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_SetCh(uint8_t ChIn);

/** @brief  Set channel mode.
 *  @param  ModeIn - channel mode.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_SetMode(uint8_t ModeIn);

/** @brief  Set channel normal value.
 *  @param  NormValIn - channel normal value.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_SetNormVal(uint8_t NornValIn);

/** @brief  Set channel PWM.T value.
 *  @param  ValIn - channel PWM.T value.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_SetPwmT(float ValIn);

/** @brief  Set channel PWM.D value.
 *  @param  ValIn - channel PWM.D value.
 *  @return Result:
 *  @arg    = BIT_FALSE - error
 *  @arg    = BIT_TRUE - ok
 */
uint8_t DO_SetPwmD(float ValIn);

#endif //TASK_DO_H
