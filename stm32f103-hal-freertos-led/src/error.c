/* @page error.c
 *       Error handler
 *       2023, atgroup09@yandex.ru
 */

#include "error.h"


void _Error_Handler(const char *FileIn, int LineIn)
{
	(void)FileIn;
	(void)LineIn;

	__disable_irq();

	while(1)
	{
	}
}
