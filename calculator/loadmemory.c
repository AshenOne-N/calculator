/************************************************************************!
* \file .c
* \brief
*
*
*
* \author Vincent, vicentcj@163.com
* \version V
* \date
*
*
*************************************************************************/
#include "at24c02.h"

unsigned char load_memory(void)
{
    if(!load_mem_flag())
    {
        if(!load_record())
        return 0£»
    }
    return 1£»
}
