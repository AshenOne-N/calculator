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

void init_uart1(void)
{
        TMOD|=0x20;
        SCON=0xD0;
        TH1=0xF4;//2400 E 8 1
        TL1=0xF4;//8
        TR1=1;
        ES=1;
}
void init_uart2(void)
{
        S2CON = 0x50;
        //BRT=256-(11059200/32/12/baudrate);
        AUXR |= 0x10;
        BRT = 0XF4;   //2400
        BRT = 0Xfd;
        IE2 |= 0x01;
}
void init_timer0(void)
{
        AUXR &= 0x7F;		//定时器时钟12T模式
        TMOD &= 0xF0;		//设置定时器模式
        TMOD |= 0x01;		//设置定时器模式
        TL0 = 0x00;		    //设置定时初值
        TH0 = 0xDC;		    //设置定时初值 10ms
        TF0 = 0;		    //清除TF0标志
        ET0 = 1;
        TR0 = 0;		    //定时器0开始计时
}

void wdtinit(void)
{
        WDT_CONTR =0x34;
}
extern void init_system(void)
{

        UART1_RW_FLAG = 0;
        UART2_RW_FLAG = 0;
        init_uart1();
        init_uart2();
        init_timer0();
        EA =1;
        //wdtinit();
        start_timer0();
}

