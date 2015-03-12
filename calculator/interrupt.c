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

void timer0_isr(void) interrupt 1 {
        TF0 = 0;
        if(SECOND >= clock_hand->count_ms)
                ++(clock_hand->count_ms);
        else
        {
                clock_hand->count_ms = 0;
                ++(clock_hand->count_sec);
        }
        if(MINUTE <= clock_hand->count_sec)
        {
                status_list->start_exchange = VALID;
                ++(clock_hand->count_min);
                clock_hand->count_sec = 0;
        }
        if(HOUR <= clock_hand->count_min)
        {
                clock_hand->reset_flag = VALID;
                clock_hand->count_min = 0;
        }
        if(PROCESS_GOING == uart1->receive_status)
        {
                ++uart1->receive_stamp;
                if(UART1_WAIT_TIME < uart1->receive_stamp ) {
                        uart1->receive_status = PROCESS_END;
                        uart1->length = uart1->counter;
                }
        }
        if(PROCESS_GOING == uart2->receive_status)
        {
                ++uart2->receive_stamp;
                if(UART2_WAIT_TIME < uart2->receive_stamp) {
                        uart2->receive_status = PROCESS_END;
                        uart2->length = uart2->counter;
                }
        }
        if(PROCESS_GOING == uart2->send_status)
                ++uart2->send_stamp;
}
void uart1_isr(void) interrupt 4 {
        if(RI)
        {
                RI = 0;
                if(PROCESS_END != uart1->receive_status) {
                        if(PROCESS_START == uart1->receive_status) {
                                uart1->receive_status = PROCESS_GOING;
                                uart1->counter = 0;
                                uart1->err_flag = INVALID;
                        }
                        if(1) {
                                LED1 = !LED1;
                                uart1->receive_stamp = 0;
                                if(uart1->counter <= MAX_UART1_BUF_SIZE) {
                                        uart1_buf[uart1->counter++] = SBUF;
                                } else {
                                        uart1->receive_status = PROCESS_END;
                                        uart1->length = uart1->counter;
                                }
                        } else {
                                uart1->err_flag = VALID ;
                                uart1_buf[7]=uart1->counter;
                        }
                }
        } else
        {
                TI = 0;
                LED2 =!LED2;
                if(uart1->counter < uart1->length)
                {
                        ACC = uart1_buf[uart1->counter];
                        TB8 = PCC;
                        SBUF = uart1_buf[uart1->counter++];
                } else
                {
                        UART1_RW_FLAG =  RS485_READ;
                        LED2 = 1;
                }
        }
}
void uart2_isr(void) interrupt 8 {
        if(S2CON & 0x01)
        {
                S2CON &= ~0X01;
                if(PROCESS_END != uart2->receive_status) {
                        if(0 == uart2->receive_status) {
                                uart2->receive_status = PROCESS_GOING;
                                uart2->counter = 0;
                        }
                        LED3 = !LED3;
                        uart2->receive_stamp = 0;
                        if(uart2->counter <= MAX_UART2_BUF_SIZE)
                                uart2_buf[uart2->counter++] = S2BUF;
                        else {
                                uart2->receive_status = PROCESS_END;
                                uart2->length = uart2->counter;
                        }
                }
        } else
        {
                S2CON &= ~0x02;
                LED4 = !LED4;
                if(uart2->counter < uart2->length)
                        S2BUF = uart2_buf[uart2->counter++];
                else
                {
                        LED4 = 1;
                        UART2_RW_FLAG = RS485_READ;
                }
        }
}
