/* @page uart.c
 *       UART common handlers and callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#include "uart.h"


UART_HandleTypeDef  PLC_UART1;
UART_HandleTypeDef  PLC_UART2;

PLC_UART_UserFunc_t PLC_UART1_USER_FUNC = { .TxCplt = NULL, .RxCplt = NULL, .Err = NULL, .Idle = NULL };
PLC_UART_UserFunc_t PLC_UART2_USER_FUNC = { .TxCplt = NULL, .RxCplt = NULL, .Err = NULL, .Idle = NULL };


HAL_StatusTypeDef PlcUart_StartTransmit(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn)
{
	HAL_StatusTypeDef Res = HAL_ERROR;

	if(DataIn && DataSzIn)
	{
		//Use default HAL Tx-driver

		if(HandleIn == &PLC_UART1)
		{
#if   (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_POLL)
			//Pool (blocking mode)
			Res = HAL_UART_Transmit(HandleIn, DataIn, DataSzIn, PLC_UART_POLL_DELAY);
#elif (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ)
			//IT
			Res = HAL_UART_Transmit_IT(HandleIn, DataIn, DataSzIn);
#elif (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
			//DMA
			Res = HAL_UART_Transmit_DMA(HandleIn, DataIn, DataSzIn);
#endif
		}
		else if(HandleIn == &PLC_UART2)
		{
#if   (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_POLL)
			//Pool (blocking mode)
			Res = HAL_UART_Transmit(HandleIn, DataIn, DataSzIn, PLC_UART_POLL_DELAY);
#elif (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_IRQ)
			//IT
			Res = HAL_UART_Transmit_IT(HandleIn, DataIn, DataSzIn);
#elif (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_DMA)
			//DMA
			Res = HAL_UART_Transmit_DMA(HandleIn, DataIn, DataSzIn);
#endif
		}
	}
	return (Res);
}


HAL_StatusTypeDef PlcUart_StartReceive(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn)
{
	HAL_StatusTypeDef Res = HAL_ERROR;

	if(DataIn && DataSzIn)
	{
		//Use default HAL Rx-driver

		if(HandleIn == &PLC_UART1)
		{
#if   (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_POLL)
			//Pool (blocking mode)
			Res = HAL_UART_Receive(HandleIn, DataIn, DataSzIn, PLC_UART_POLL_DELAY);
#elif (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ)
			//IT
			Res = HAL_UART_Receive_IT(HandleIn, DataIn, DataSzIn);
			//__HAL_UART_ENABLE_IT(HandleIn, UART_IT_IDLE);
#elif (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
			//DMA
			Res = HAL_UART_Receive_DMA(HandleIn, DataIn, DataSzIn);
			//__HAL_UART_ENABLE_IT(HandleIn, UART_IT_IDLE);
#endif
		}
		else if(HandleIn == &PLC_UART2)
		{
#if   (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_POLL)
			//Pool (blocking mode)
			Res = HAL_UART_Receive(HandleIn, DataIn, DataSzIn, PLC_UART_POLL_DELAY);
#elif (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_IRQ)
			//IT
			Res = HAL_UART_Receive_IT(HandleIn, DataIn, DataSzIn);
			//__HAL_UART_ENABLE_IT(HandleIn, UART_IT_IDLE);
#elif (PLC_UART2_TRANSFER == PLC_UART_TRANSFER_DMA)
			//DMA
			Res = HAL_UART_Receive_DMA(HandleIn, DataIn, DataSzIn);
			//__HAL_UART_ENABLE_IT(HandleIn, UART_IT_IDLE);
#endif
		}
	}
	return (Res);
}


void PlcUart_IdleCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn)
	{
		__HAL_UART_DISABLE_IT(HandleIn, UART_IT_IDLE);
		__HAL_UART_CLEAR_IDLEFLAG(HandleIn);
		HAL_UART_AbortReceive(HandleIn);

		if(HandleIn == &PLC_UART1)
		{
			if(PLC_UART1_USER_FUNC.Idle != NULL) PLC_UART1_USER_FUNC.Idle(__HAL_DMA_GET_COUNTER(HandleIn->hdmarx));
		}
		else if(HandleIn == &PLC_UART2)
		{
			if(PLC_UART2_USER_FUNC.Idle != NULL) PLC_UART2_USER_FUNC.Idle(__HAL_DMA_GET_COUNTER(HandleIn->hdmarx));
		}
	}
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.Err != NULL) PLC_UART1_USER_FUNC.Err();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.Err != NULL) PLC_UART2_USER_FUNC.Err();
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.TxCplt != NULL) PLC_UART1_USER_FUNC.TxCplt();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.TxCplt != NULL) PLC_UART2_USER_FUNC.TxCplt();
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *HandleIn)
{
	if(HandleIn == &PLC_UART1)
	{
		if(PLC_UART1_USER_FUNC.RxCplt != NULL) PLC_UART1_USER_FUNC.RxCplt();
	}
	else if(HandleIn == &PLC_UART2)
	{
		if(PLC_UART2_USER_FUNC.RxCplt != NULL) PLC_UART2_USER_FUNC.RxCplt();
	}
}
