/* @page error.h
 *       Error handler
 *       2022, atgroup09@gmail.com
 */

#ifndef ERROR_H_
#define ERROR_H_

#include "config.h"


/** @brief  This function is executed in case of error occurrence.
 *  @param  FileIn - file name.
 *  @param  LineIn - line in file.
 *  @retval None.
 */
void _Error_Handler(const char *FileIn, int LineIn);


#endif /* ERROR_H_ */
