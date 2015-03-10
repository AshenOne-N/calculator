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
#include "rs485_rtu.h"
#include "crc16.h"
#include "at24c02.h"

extern unsigned int setword (unsigned char datah,unsigned char datal)
{
        return (((U16)datah) << 8) + datal;
}
extern U8 check_rtu_msg(void)
{
        if(uart1_buf[0] == NODE_ADDR) {
                if(crc16(uart1_buf,uart1->length - 2) ==
                    setword(uart1_buf[uart1->length - 2],uart1_buf[uart1->length - 1]))
                        return 1;
        }
        return 0;
}
extern void write_to_list(void)
{
    status_list->mem_valid = status_list->eeprom_list[0];               //indicate EEPROM are used and freshed recently 1--> valid
    status_list->meter_valid = status_list->eeprom_list[1];             //indicate meter is connected                   1--> valid
    status_list->data_valid = status_list->eeprom_list[2];              //indicate whether data should be freshed  0->note processed 1->processing 2->finish processing
    //status_list->process_flag = status_list->eeprom_list[3];            //show the step of  data freshing from the meter
    //status_list->err_eeprom = status_list->eeprom_list[4];              //fail to store data to EEPROM
    //status_list->err_connect = status_list->eeprom_list[5];             //fail connect to the meter
    status_list->err_type = status_list->eeprom_list[4];
    //status_list->err_flag = status_list->eeprom_list[7];
    if(!status_list->data_valid)
    {
        status_list->start_exchange = 1;
    }
    //status_list->start_exchange = status_list->eeprom_list[8];
    status_list-> meter_address = status_list->eeprom_list[3];
}
extern void list_to_eeprom(void)
{
    status_list->eeprom_list[0] = status_list->mem_valid;
    status_list->eeprom_list[1] = status_list->meter_valid;
    status_list->eeprom_list[2] = status_list->data_valid;
    status_list->eeprom_list[3] = status_list-> meter_address;
    status_list->eeprom_list[4] = status_list->err_type;
//    status_list->eeprom_list[5] =
//    status_list->eeprom_list[6] =
//    status_list->eeprom_list[7] =
//    status_list->eeprom_list[8] =
//    status_list->eeprom_list[9] = status_list-> meter_address;
}
extern void refresh_list(void)
{
        status_list->data_valid = 1;
        status_list->err_connect = 0;
        status_list->mem_valid  = 1;
        //if(status_list->err_eeprom)
        //        status_list->err_type |= 0x04;
        status_list->err_type &= 0xfc;
        status_list->start_exchange = 0;
}
extern void reset_rs485_struct(void)
{
        rs485->err_flag   = 0;
        rs485->err_type   = 0;
        rs485->functype   = 0;
        rs485->length     = 0;
        rs485->start_addr = 0;
}
extern U8 get_start_addr(U8 addr)
{
//        addr -= 24;
//        addr *= 2;
//        addr += 0x20;
        return (addr-24)*2+0X20;
}
extern void instruction_resolve(void)
{
        reset_rs485_struct();
        if(0x03 == uart1_buf[1]) {
                //ptr_thread->functype = *uart1->cursor_msg;
                // LED1 =!LED1;
                if(uart1_buf[5] <= 16 && uart1_buf[5] ) {
                        if((uart1_buf[3] >= 24) && (uart1_buf[3] + uart1_buf[5] <= 40)) {
                                if(status_list->data_valid) {
                                        // LED1 =!LED1;
                                        rs485->functype   = 0x03;
                                        rs485->length     = uart1_buf[5] * 2;
                                        rs485->start_addr = get_start_addr(uart1_buf[3]);
                                } else {
                                        // LED2 = !LED2;
                                        rs485->functype   = 0x83;
                                        rs485->err_type   = 0x04;
                                }

                        } else {
                                rs485->functype   = 0x83;
                                rs485->err_type   = 0x02;
                        }

                } else {
                        rs485->functype   = 0x83;
                        rs485->err_type   = 0x03;
                }

        } else if(0x10 == uart1_buf[1]) {
                if((uart1_buf[3] == 38) && (uart1_buf[5] == 1) && uart1_buf[6] == 2) {
                        //LED4 = 0;
                        rs485->functype = 0x10;
                        rs485->length   = 6;
                } else {
                        rs485->functype = 0x90;
                        rs485->err_type = 0x03;
                }
        } else {
                //LED2 = !LED2;
                rs485->functype   = 0x83;
                rs485->err_type   = 0x01;
                //LED4 = 0;
        }
}
extern void add_crc_to_frame(U8 *buf_array, U8 position)
{
    U16 temp;
    temp = crc16(buf_array,position);
    buf_array[position]   = (U8)(temp>>8);
    buf_array[position +1] = (U8)temp;
}
extern void instruction_excute(void)
{
        unsigned char temp=0;
        uart1->receive_status =0 ;
        switch(rs485->functype) {
        case  0x03:
                while(RW24XX(&uart1_buf[3],rs485->length,rs485->start_addr,READ_EEPROM));
//                temp = crc16(uart1_buf,uart1->length + 3);
//                uart1_buf[rs485->length + 3] = (unsigned char)temp>>8;
//                uart1_buf[rs485->length + 4] = (unsigned char)temp;

//                temp = uart1_buf[3];
//                uart1_buf[3] = uart1_buf[6];
//                uart1_buf[6] = temp;
//
//                temp = uart1_buf[4];
//                uart1_buf[4] = uart1_buf[5];
//                uart1_buf[5] = temp;

                uart1_buf[2] = rs485->length;
				add_crc_to_frame(uart1_buf,rs485->length + 3);
				uart1->length = rs485->length + 5;

                uart1_send_string();
                break;
        case 0x10:
                status_list->meter_address = uart1_buf[7];
//                temp = crc16(uart1_buf,uart1->length );
//                uart1_buf[rs485->length ] = (unsigned char)temp>>8;
//                uart1_buf[rs485->length + 1] = (unsigned char)temp;

			   add_crc_to_frame(uart1_buf,uart1->length + 3);
			    uart1->length = 8;

                uart1_send_string();
                //LED3 = 0;
                break;
        default:
                //LED3 = !LED3;
                uart1_buf[1] = rs485->functype;
                uart1_buf[2] = rs485->err_type;
//                temp = crc16(uart1_buf,3 );
//                uart1_buf[3 ] = (unsigned char)temp>>8;
//                uart1_buf[4] = (unsigned char)temp;
                //uart1_buf[0] =0xff;
                //uart1_buf[1] = 0x11;
				add_crc_to_frame(uart1_buf,3);
                uart1->length = 5;

                uart1_send_string();
                break;
        }
}
