/* @page gpio.c
 *       GPIO driver
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2023, atgroup09@gmail.com
 */

#include "gpio.h"


uint8_t PlcGpio_DO_On(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
             HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_RESET);
        }
        else
        {
        	HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_SET);
        }
        return (PLC_GPIO_ON);
    }
    return (PLC_GPIO_ERR);
}


uint8_t PlcGpio_DO_Off(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        if(PinModeIn)
        {
             HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_SET);
        }
        else
        {
        	HAL_GPIO_WritePin(PortIn, PinIn, GPIO_PIN_RESET);
        }
        return (PLC_GPIO_OFF);
    }
    return (PLC_GPIO_ERR);
}


uint8_t PlcGpio_DO_Toggle(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
        uint8_t State = PlcGpio_DO_Get(PortIn, PinIn, PinModeIn);
        return (State ? PlcGpio_DO_Off(PortIn, PinIn, PinModeIn) : PlcGpio_DO_On(PortIn, PinIn, PinModeIn));
    }
    return (PLC_GPIO_ERR);
}


uint8_t PlcGpio_DO_Set(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn, uint8_t StateIn)
{
    if(PortIn)
    {
    	return (!StateIn ? PlcGpio_DO_Off(PortIn, PinIn, PinModeIn) : PlcGpio_DO_On(PortIn, PinIn, PinModeIn));
    }
    return (PLC_GPIO_ERR);
}


uint8_t PlcGpio_DO_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    uint8_t Res = PLC_GPIO_ERR;

    if(PortIn)
    {
        assert_param(IS_GPIO_PIN(PinIn));
        Res = ((PortIn->ODR&PinIn) ? PLC_GPIO_ON : PLC_GPIO_OFF);
        if(PinModeIn) Res = !Res;
    }
    return (Res);
}


uint8_t PlcGpio_DI_Get(GPIO_TypeDef *PortIn, uint16_t PinIn, uint8_t PinModeIn)
{
    if(PortIn)
    {
    	GPIO_PinState Res = ((PinModeIn) ? !HAL_GPIO_ReadPin(PortIn, PinIn) : HAL_GPIO_ReadPin(PortIn, PinIn));
    	if(Res == GPIO_PIN_SET) return (BIT_TRUE);
    }
    return (BIT_FALSE);
}
