#ifndef HAL_H_INCLUDED
#define HAL_H_INCLUDED

/************************************************************************!
* \file .h
* \brief ¸ÅÊö
*
*ÏêÏ¸¸ÅÊö
*
* \author  Vincent,vicentcj@163.com
* \version V
* \date
*************************************************************************/
#include "stc5a60s2.h"

sbit LED1=P2^7;
sbit LED2=P2^6;
sbit LED3=P2^5;
sbit LED4=P2^4;

sbit SDA=P0^1;
sbit SCL=P0^0;

sbit PCC=PSW^0;
sbit UART1_RW_FLAG=P0^2;
sbit UART2_RW_FLAG=P0^3;

#define READ  1;
#define WRITE 0;
#define RS485_READ   0
#define RS485_WRITE  1

extern void start_timer0(void);
extern void feed_dog(void);
extern void reset_system(void);
extern void uart1_send_string(void);
extern void uart2_send_string(void);
#endif // HAL_H_INCLUDED
