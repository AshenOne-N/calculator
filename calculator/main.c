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
#include "stc5a60s2.h"
#include "typedefine.h"
#include "hal.h"
#include "mydef.h"
#include "init.h"
#include "control.h"
#include "mydefine.h"

void main (void)
{
        init_system();
        load_memory();
        while(!scan_status());
        reset_system();
}
