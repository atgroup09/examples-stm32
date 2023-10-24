/* @page task-com1.c
 *       Baremetal task
 *       2023, atgroup09@gmail.com
 */

#include "task-com1.h"


/** @var Tx-buffer
 */
#define COM1_TX_BUFF_SZ  200U
static uint8_t COM1_TX_BUFF[COM1_TX_BUFF_SZ];

/** @var Rx-buffer
 */
#define COM1_RX_BUFF_SZ  100U
static uint8_t COM1_RX_BUFF[COM1_RX_BUFF_SZ];


/* @var Rx-counter
 */
static volatile uint32_t COM1_RxCnt = 0;

/* @var Tx-counter
 */
static volatile uint32_t COM1_TxCnt = 0;


/** @brief  Print Menu.
 *  @param  PageIn - page ID:
 *  @arg    = PLC_UART1_MENU_MAIN      - main menu
 *  @arg    = PLC_UART1_MENU_ABOUT_PLC - about PLC
 *  @arg    = PLC_UART1_MENU_COUNTERS  - print counters
 *  @return None.
 */
static void COM1_PrintMenu(uint8_t PageIn)
{
	switch(PageIn)
	{
		case COM1_MENU_MAIN:
			sprintf((char *)COM1_TX_BUFF, "%c\r\n****\r\n0 - menu\r\n1 - about PLC\r\n2 - value of main counter\r\n> ", PageIn);
			break;

		case COM1_MENU_ABOUT_PLC:
			sprintf((char *)COM1_TX_BUFF, "%c\r\n****\r\nPLC %d.%d RTE %d (%d %d)\r\nSystemCoreClock %lu\r\nSystemTick %lu\r\n> ", PageIn, PLC_HW_CODE, PLC_HW_VAR, PLC_RTE_VERSION, PLC_RTE_YYYY, PLC_RTE_DDMM, SystemCoreClock, SysTick->LOAD);
			break;

		case COM1_MENU_COUNTERS:
			sprintf((char *)COM1_TX_BUFF, "%c\r\n****\r\nRxCnt %lu\r\nTxCnt %lu\r\n> ", PageIn, COM1_RxCnt, COM1_TxCnt);
			break;

		default:
			sprintf((char *)COM1_TX_BUFF, "%c\r\n> ", PageIn);
			break;
	}

	PlcUart_StartTransmit(&PLC_UART1, COM1_TX_BUFF, strlen((char *)COM1_TX_BUFF));
}


/** @brief  User callback-function: Rx-completed.
 *  @param  None.
 *  @return None.
 */
static void COM1_RxCplt(void)
{
	COM1_RxCnt++;
	COM1_PrintMenu(COM1_RX_BUFF[0]);
}

/** @brief  User callback-function: Tx-completed.
 *  @param  None.
 *  @return None.
 */
static void COM1_TxCplt(void)
{
	COM1_TxCnt++;
#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ) || (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
	PlcUart_StartReceive(&PLC_UART1, COM1_RX_BUFF, 1u);
#endif
}


/** @brief  Init the Task.
 *  @param  None.
 *  @return Result:
 *          = BIT_FALSE - ERROR
 *          = BIT_TRUE  - OK
 */
static uint8_t COM1_Init(void)
{
#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_IRQ) || (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_DMA)
	//Set user callback-functions
	PLC_UART1_USER_FUNC.RxCplt = COM1_RxCplt;
	PLC_UART1_USER_FUNC.TxCplt = COM1_TxCplt;
#endif

	return (PlcUart1_Init());
}

/** @brief  DeInit the Task.
 *  @param  None.
 *  @return None.
 */
/*
static void COM1_DeInit(void)
{
	PlcUart1_DeInit();
}
*/


uint8_t COM1_Task_Start(void)
{
	uint8_t Res = COM1_Init();
	COM1_PrintMenu(COM1_MENU_MAIN);
	return (Res);
}


#if (PLC_UART1_TRANSFER == PLC_UART_TRANSFER_POLL)
void COM1_Task_Poll(void)
{
	//1-polling (use in main-loop)
	if(PlcUart_StartReceive(&PLC_UART1, COM1_RX_BUFF, 1u) == HAL_OK)
	{
		COM1_TxCplt();
		COM1_RxCplt();
	}
}
#endif
