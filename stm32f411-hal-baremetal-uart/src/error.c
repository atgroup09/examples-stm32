/* @page error.c
 *       Error handler
 *       2023, atgroup09@gmail.com
 */

#include "error.h"


void _Error_Handler(const char *FileIn, int LineIn)
{
#ifdef DEBUG_LOG_ERROR
	if(FileIn)
		 DebugLog("ERROR IN %s:%d\n", FileIn, LineIn);
	else DebugLog("ERROR\n");
	DebugLog_Wait();
#else
	(void)FileIn;
	(void)LineIn;
#endif //DEBUG_LOG_ERROR

	__disable_irq();

	while(1)
	{
	}
}
