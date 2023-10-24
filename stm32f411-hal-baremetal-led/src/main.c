/* @page main.c
 *       Main task
 *       2023, atgroup09@gmail.com
 */

#include "config.h"
#include "error.h"
#include "led.h"


/* @var Main task counter
 */
volatile uint32_t MainCnt = 0;


/** @brief  Main task function.
 *  @param  None.
 *  @return 1 - Error.
 */
int main(void)
{
	/** INIT
	 */

	PlcLed_Init();


    /** PRESTART
     */


    /** START
     */

	while(1)
	{
		MainCnt++;
	}

    /** START error
     */

    _Error_Handler(__FILE__, __LINE__);

    return (1);
}
