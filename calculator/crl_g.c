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
{		feed_dog();
        uart2_buf[0] = 0x2a;
        uart2_buf[1] = 0X41;
        uart2_buf[2] = 0x4a;
        uart2->length = 3;
        UART2_RW_FLAG = RS485_WRITE;
        //UART2_RW_FLAG = RS485_READ;
        //LED4 = !LED4;
		feed_dog();
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
        //if(uart2_buf[1] == status_list->meter_address) {
        if(uart2_buf[1] == 0x41) {
                if(uart2_buf[uart2->length - 1] == lrccheck(uart2_buf,3,uart2->length - 1 )) {
                        return 1;
                }
        }
        return 0;
}
extern U8 bcd_to_byte(U8 binary_coded_decimal)
{
        return (binary_coded_decimal>>4) * 10 + (binary_coded_decimal & 0x0f);
}
extern float switch_data(U8 *data_array, U16 multiple, U8 bits)
{
//        int flag = 0,temp = 0;
//        long   sum = 0;
//        float esum = 0;
//	      int i ;
//        for(i = 0; i < bits; ++i) {
//                if((data_array[i] != 0x30) && (flag == 0)) {
//                        if(data_array[i] != 0x2d) {
//                                sum = sum*10 +(data_array[i] - 0x30);
//                        } else {
//                                temp = 1;
//                        }
//                        flag = 1;
//                } else if (flag != 0) {
//                        sum *= 10;
//                        sum += (data_array[i] - 0x30);
//                }
//        }
//        if(temp)
//                return (0.0 - sum)/multiple;
//        return  (sum*1.0)/multiple;
        E32 temp = 0;
        U8 i ;
        for(i = 0; i < bits; ++i) {
                temp = temp*100 + bcd_to_byte(*(data_array+i));
        }
        return temp / multiple;
}
extern void refresh_mem(void)
{
        crl_g_meter.union_data.edata[0] = switch_data(&uart2_buf[3],CALIBER,4);
        crl_g_meter.union_data.edata[1] = switch_data(&uart2_buf[7],1000,4);
        crl_g_meter.union_data.edata[2] = switch_data(&uart2_buf[11],CALIBER,4);
        crl_g_meter.union_data.edata[3] = switch_data(&uart2_buf[15],100,4);
        crl_g_meter.union_data.edata[4] = switch_data(&uart2_buf[19],100,4);
        crl_g_meter.union_data.edata[5] = switch_data(&uart2_buf[23],10,4);
        crl_g_meter.union_data.edata[6] = switch_data(&uart2_buf[27],1,4);
        crl_g_meter.union_data.edata[7] = switch_data(&uart2_buf[31],1,1);
}
extern void write_back_eeprom(void)
{
feed_dog();
        while(RW24XX(&crl_g_meter.union_data.data_array[0],8,0x20,WRITE_EEPROM));
		feed_dog();
		while(RW24XX(&crl_g_meter.union_data.data_array[8],8,0x28,WRITE_EEPROM));
		feed_dog();
		while(RW24XX(&crl_g_meter.union_data.data_array[16],8,0x30,WRITE_EEPROM));
		feed_dog();
		while(RW24XX(&crl_g_meter.union_data.data_array[24],8,0x38,WRITE_EEPROM));
		feed_dog();
}

extern void no_reply_err(void)
{
        if(1 > status_list->err_connect)
                ++status_list->err_connect;
        else
                {
                    status_list->mem_valid = 0;
                    status_list->meter_valid = 0;
                    status_list->data_valid = 0;
                    status_list->err_connect = 0;
        status_list->err_type |= 0x01;
        status_list->start_exchange =0;
                }
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
