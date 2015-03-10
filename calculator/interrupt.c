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
//void Timer0_Rountine(void) interrupt 1 using 1{
        TF0 = 0;
        //LED4 = 0;
        //while(1);
        //LED3 = !LED3;
        if(20 >= clock_hand->count_ms)
                ++(clock_hand->count_ms);
        else
        {
                clock_hand->count_ms = 0;
                ++(clock_hand->count_min);
                status_list->start_exchange = 1;
                //LED2 = 0;
        }
        if(60 <= clock_hand->count_min)
        {
                clock_hand->reset_flag = 1;
                clock_hand->count_min = 0;
        }
        //LED2 = 0;
        if(1 == uart1->receive_status)
        {
                ++uart1->receive_stamp;
                if(2 < uart1->receive_stamp ) {
                        uart1->receive_status = 2;
                        uart1->length = uart1->counter;
                        //LED2 =0;
                }
        }
        if(1 == uart2->receive_status)
        {
                ++uart2->receive_stamp;
                if(35 < uart2->receive_stamp) {
                        uart2->receive_status = 2;
                        uart2->length = uart2->counter;
                }
        }
        if(1 == uart2->send_status)
        {
                ++uart2->send_stamp;
        }
}
void uart1_isr(void) interrupt 4 {
        // EA =0;
        if(RI)
        {
                RI = 0;
                //LED1 =0;
                if(2 != uart1->receive_status) {
                        //LED2 =0;
                        if(0 == uart1->receive_status) {
                                // LED3 = 0;
                                uart1->receive_status = 1;
                                uart1->counter = 0;
                                uart1->err_flag = 0;
                        }
                       // ACC = SBUF;
                       // TEMPFLAG1 = PCC;
                        //TEMPFLAG2 = TB8;
                        //if(TEMPFLAG1 == TB8) {
                       if(1){
                                //LED4 =0;
                                uart1->receive_stamp = 0;
                                if(uart1->counter <= MAX_UART1_BUF_SIZE) {
                                        //LED1 =0;
                                        uart1_buf[uart1->counter++] = SBUF;
                                } else {
                                        uart1->receive_status = 2;
                                        uart1->length = uart1->counter;
                                }
                        } else {
                                uart1->err_flag = 1 ;
                                //LED3 = 0;
                                uart1_buf[7]=uart1->counter;
                        }
                }
        } else
        {
                TI = 0;
                if(uart1->counter < uart1->length)
                {
                        ACC = uart1_buf[uart1->counter];
                        TB8 = PCC;
                        SBUF = uart1_buf[uart1->counter++];
                } else
                        UART1_RW_FLAG =  RS485_READ;

        }
		//EA=1;
}
void uart2_isr(void) interrupt 8 {
    //TEMPFLAG1 = S2CON;
   // LED1 = !LED1;
        if(S2CON & 0x01)
        {
          LED1 = !LED1;
                S2CON &= ~0X01;
                if(2 != uart2->receive_status) {
                        if(0 == uart2->receive_status) {
                                uart2->receive_status = 1;
                                uart2->counter = 0;
                                LED2 =!LED2;
                        }
                        uart2->receive_stamp = 0;
                        if(uart2->counter <= MAX_UART2_BUF_SIZE)
                                uart2_buf[uart2->counter++] = S2BUF;
                        else {
                                uart2->receive_status = 2;
                                uart2->length = uart2->counter;
                        }
                }
        } else
        {
            //LED3 = 0;
                S2CON &= ~0x02;
                if(uart2->counter < uart2->length)
                {
                        S2BUF = uart2_buf[uart2->counter++];
                } else
                {
                    LED2 =!LED2;
                    UART2_RW_FLAG = RS485_READ;
                }
                        //UART2_RW_FLAG = RS485_READ;
        }
}
