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
#include "mydef.h"
#include "hal.h"
#include "at24c02.h"
extern void send_msg(void)
{
        uart2_buf[0] = 0x2a;
        uart2_buf[1] = status_list->meter_address;
        uart2_buf[2] = 0x3a;
        uart2_buf[3] = 0x52;
        uart2->length = 4;
        UART1_RW_FLAG = RS485_WRITE;
        uart2_send_string();
}
extern unsigned char lrccheck(unsigned char *lrcbuf,unsigned char stnum,unsigned char lrclength)
{
        unsigned char i,j;
        j = 0;
        for(i=stnum; i<lrclength; i++) {
                j += lrcbuf[i];
        }
        return j;
}
extern U8 check_crl_g_msg(void)
{
        if(uart2_buf[1] == status_list->meter_address) {
                if(uart2_buf[uart2->length - 1] == lrccheck(uart2_buf,3,uart2->length )) {
                        return 1;
                }
        }
        return 0;
}
extern float switch_data(U8 *data_array, U16 multiple, U8 bits)
{
        int flag = 0,temp = 0;
        long   sum = 0;
        float esum = 0;
	      int i ;
        for(i = 0; i < bits; ++i) {
                if((data_array[i] != 0x30) && (flag == 0)) {
                        if(data_array[i] != 0x2d) {
                                sum = sum*10 +(data_array[i] - 0x30);
                        } else {
                                temp = 1;
                        }
                        flag = 1;
                } else if (flag != 0) {
                        sum *= 10;
                        sum += (data_array[i] - 0x30);
                }
        }
        if(temp)
                return (0.0 - sum)/multiple;
        return  (sum*1.0)/multiple;

}
extern void refresh_mem(void)
{
        crl_g_meter.union_data.edata[0] = switch_data(uart2_buf,1000,4);
        crl_g_meter.union_data.edata[1] = switch_data(uart2_buf,1000,4);
        crl_g_meter.union_data.edata[2] = switch_data(uart2_buf,1000,4);
        crl_g_meter.union_data.edata[3] = switch_data(uart2_buf,1000,4);
        crl_g_meter.union_data.edata[4] = switch_data(uart2_buf,1000,4);
        crl_g_meter.union_data.edata[5] = switch_data(uart2_buf,1000,4);

}
extern void write_back_eeprom(void)
{
        while(RW24XX(&crl_g_meter.union_data.data_array,28,0x20,WRITE_EEPROM));
}

extern void no_reply_err(void)
{
        if(5 > status_list->err_connect)
                ++status_list->err_connect;
        else
                status_list->meter_valid = 0;
        status_list->err_type |= 0x01;
}
extern void reset_uart2(void)
{
        uart2->send_status = 0;
        uart2->send_stamp  = 0;
        uart2->err_flag    = 0;
        uart2->receive_status = 0;
}
extern void check_failed_err(void)
{
        status_list->data_valid = 0;
        if(uart2->err_flag)
                status_list->err_type   |= 0x02;
}
//void
