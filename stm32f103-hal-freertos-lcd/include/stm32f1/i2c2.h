/* @page i2c2.h
 *       I2C2 driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2025, atgroup09@yandex.ru
 */

/** @note
 * 			LCD-I2C
 *
 *        	I2C2.GPIO
 *        	- PB10 --- I2C2.SCL
 *        	- PB11 --- I2C2.SDA
 */

#ifndef PLC_I2C2_H
#define PLC_I2C2_H

#include "gpio.h"
#include "error.h"


/** @def I2C2: GPIO
 */
#define PLC_I2C2_GPIO_PORT			GPIOB
#define PLC_I2C2_GPIO_MODE			GPIO_MODE_AF_OD
#define PLC_I2C2_GPIO_SPEED			GPIO_SPEED_FREQ_HIGH
#define PLC_I2C2_GPIO_SCL_PIN		GPIO_PIN_10
#define PLC_I2C2_GPIO_SDA_PIN		GPIO_PIN_11

/** @def LCD.I2C2: Instance
 */
#define PLC_I2C2_INSTANCE			I2C2


/** @brief  I2C2: Init. hardware.
 *  @param  HandleIn - pointer to the I2C-handle.
 *  @return None.
 */
void PlcI2C2_Init(I2C_HandleTypeDef *HandleIn);

/** @brief  I2C2: DeInit.
 *  @param  None.
 *  @return None.
 */
void PlcI2C2_DeInit(void);


#endif //PLC_I2C2_H
