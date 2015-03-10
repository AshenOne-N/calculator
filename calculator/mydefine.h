#ifndef MYDEFINE_H_INCLUDED
#define MYDEFINE_H_INCLUDED

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
xdata CLOCK_STRUCT local_clock={0,0};
xdata CLOCK_HAND clock_hand = &local_clock;

xdata METER crl_g_meter = {0,0,0,0,0,0,0};
xdata NODE  ptr_crl = &crl_g_meter;

xdata LIST meter_node = {0};
xdata METER_POSITION status_list = &meter_node;

xdata UART_STRUCT uart1_struct = {0};
xdata UART_STRUCT uart2_struct = {0};
xdata UART_POSITION uart1 = &uart1_struct;
xdata UART_POSITION uart2 = &uart2_struct;
xdata U8 uart1_buf[MAX_UART1_BUF_SIZE] = {0};
xdata U8 uart2_buf[MAX_UART2_BUF_SIZE] = {0};

xdata RS485_RTU rs_node = {0};
xdata RS485 rs485 = &rs_node;

//U8 TEMPFLAG1 =0;
//U8 TEMPFLAG2 =0;
#endif // MYDEFINE_H_INCLUDED
