/* @page uart.h
 *       UART common handlers and callbacks
 *       Platform-Dependent Code (STM32F4-HAL)
 *       2022-2023, atgroup09@gmail.com
 */

#ifndef PLC_UART_H
#define PLC_UART_H

#include "config.h"
#include "error.h"

#ifdef DEBUG_LOG_ERROR
#include "debug-log.h"
#endif // DEBUG_LOG_ERROR


/** @typedef UART Callback user-functions
 */
typedef struct
{
    void (*TxCplt)(void);
    void (*RxCplt)(void);
    void (*Err)(void);
    void (*Idle)(uint32_t RxCntIn);

} PLC_UART_UserFunc_t;


/** @def UART Poll-delay, msec
 */
#define PLC_UART_POLL_DELAY  1000u


/** @def UART transfer modes
 */
#define PLC_UART_TRANSFER_OFF   0  //off
#define PLC_UART_TRANSFER_POLL  1  //polling (blocking)
#define PLC_UART_TRANSFER_IRQ   2  //IRQ     (not blocking)
#define PLC_UART_TRANSFER_DMA   3  //DMA     (not blocking)


/** @var UART Handlers
 */
extern UART_HandleTypeDef PLC_UART1;	//COM1
extern UART_HandleTypeDef PLC_UART2;	//COM2

/** @var UART user callback-functions
 */
extern PLC_UART_UserFunc_t PLC_UART1_USER_FUNC;
extern PLC_UART_UserFunc_t PLC_UART2_USER_FUNC;

/** @def UART transfer mode
 */
#define PLC_UART1_TRANSFER  PLC_UART_TRANSFER_DMA
#define PLC_UART2_TRANSFER  PLC_UART_TRANSFER_OFF


/** @brief  Start Transmit transfer driver.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn - pointer to Tx-buffer.
 *  @param  DataSzIn - amount of data elements to be sent.
 *  @return HAL status:
 *  @arg    = HAL_OK
 *  @arg    = HAL_ERROR
 *  @arg    = HAL_BUSY
 *  @arg    = HAL_TIMEOUT
 */
HAL_StatusTypeDef PlcUart_StartTransmit(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn);

/** @brief  Start Receive transfer driver.
 *  @param  HandleIn - pointer to UART-handle.
 *  @param  DataIn   - pointer to Rx-buffer.
 *  @param  DataSzIn - amount of data elements to be receive (maximum size of DataIn).
 *  @return HAL status:
 *  @arg    = HAL_OK
 *  @arg    = HAL_ERROR
 *  @arg    = HAL_BUSY
 *  @arg    = HAL_TIMEOUT
 */
HAL_StatusTypeDef PlcUart_StartReceive(UART_HandleTypeDef *HandleIn, uint8_t *DataIn, uint16_t DataSzIn);

/** @brief  UART Idle Callback.
 *  @param  HandleIn - pointer to UART-handle.
 *  @return None.
 *  @note   USER Implementation.
 */
void PlcUart_IdleCallback(UART_HandleTypeDef *HandleIn);


#endif //PLC_UART_H
