/* @page i2c2.c
 *       I2C2 driver
 *       Platform-Dependent Code (STM32F1-HAL)
 *       2025, atgroup09@yandex.ru
 */

#include "i2c2.h"


void PlcI2C2_Init(I2C_HandleTypeDef *HandleIn)
{
	if(HandleIn)
	{
		//Peripheral clock enable
		__HAL_RCC_GPIOB_CLK_ENABLE();
		__HAL_RCC_I2C2_CLK_ENABLE();

		//GPIO init.
		GPIO_InitTypeDef GpioDef;
		GpioDef.Pin   = PLC_I2C2_GPIO_SCL_PIN|PLC_I2C2_GPIO_SDA_PIN;
		GpioDef.Mode  = PLC_I2C2_GPIO_MODE;
		GpioDef.Speed = PLC_I2C2_GPIO_SPEED;
		HAL_GPIO_Init(PLC_I2C2_GPIO_PORT, &GpioDef);

		//I2C2 init.
		HandleIn->Instance			   = PLC_I2C2_INSTANCE;
		HandleIn->Init.ClockSpeed	   = 100000;
		HandleIn->Init.DutyCycle	   = I2C_DUTYCYCLE_2;
		HandleIn->Init.OwnAddress1	   = 0;
		HandleIn->Init.AddressingMode  = I2C_ADDRESSINGMODE_7BIT;
		HandleIn->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		HandleIn->Init.OwnAddress2	   = 0;
		HandleIn->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		HandleIn->Init.NoStretchMode   = I2C_NOSTRETCH_DISABLE;

		if(HAL_I2C_Init(HandleIn) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}
	}
}

void PlcLCD_I2C2_DeInit(void)
{
	//Peripheral clock disable
	__HAL_RCC_I2C2_CLK_DISABLE();
	HAL_GPIO_DeInit(PLC_I2C2_GPIO_PORT, PLC_I2C2_GPIO_SCL_PIN);
	HAL_GPIO_DeInit(PLC_I2C2_GPIO_PORT, PLC_I2C2_GPIO_SDA_PIN);
}
