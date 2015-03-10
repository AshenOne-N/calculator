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
        twinkle_leds();
        load_memory();
        //LED1 = 0;
        //LED2 =1;
        //while (!TF0)
        //LED3 = 0;
        while(scan_status());
        reset_system();
}

