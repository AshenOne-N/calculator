/************************************************************************!
* \file .c
* \brief
*
*
*
* \author Vincent, vicentcj@163.com
* \version V
* \date /2014
*
*
*************************************************************************/
#include "stc5a60s2.h"
#include "typedefine.h"
#include "mydef.h"
#include "hal.h"

extern void start_timer0(void)
{
        TR0 = 1;
}
/*extern void stop_timer0(void)
{
        TR0=0;
        TF0=0;
}*/
extern void feed_dog(void)
{
        WDT_CONTR|=0X10;
}
extern void uart1_send_string(void)
{
        uart1->counter = 1;
        ACC = uart1_buf[0];
        TB8 = P;
        SBUF = uart1_buf[0];
        //uart1->cursor_msg = &uart1_buf[0];
        // SBUF =*uart1->cursor_msg++;
}
extern void uart2_send_string(void)
{
        uart2->counter = 1;
        S2BUF = uart2_buf[0];
        //uart2->cursor_msg = &uart2_buf[0];
        //S2BUF = *uart1->cursor_msg++;
}
extern void reset_system(void)
{
	while(1);
}