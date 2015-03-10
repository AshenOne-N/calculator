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
#include "at24c02.h"
#include "crl_g.h"
#include "rs485_rtu.h"
#include "led.h"
#include "delay.h"

//extern void write_to_list(void)
//{
//    status_list->mem_valid = status_list->eeprom_list[0];               //indicate EEPROM are used and freshed recently 1--> valid
//    status_list->meter_valid = status_list->eeprom_list[1];             //indicate meter is connected                   1--> valid
//    status_list->data_valid = status_list->eeprom_list[2];              //indicate whether data should be freshed  0->note processed 1->processing 2->finish processing
//    status_list->process_flag = status_list->eeprom_list[3];            //show the step of  data freshing from the meter
//    status_list->err_eeprom = status_list->eeprom_list[4];              //fail to store data to EEPROM
//    status_list->err_connect = status_list->eeprom_list[5];             //fail connect to the meter
//    status_list->err_type = status_list->eeprom_list[6];
//    status_list->err_flag = status_list->eeprom_list[7];
//    status_list->start_exchange = status_list->eeprom_list[8];
//    status_list-> meter_address = status_list->eeprom_list[9];
//}
extern void twinkle_leds(void)
{
        U8 i;
        for(i=0; i<4; ++i) {
                leds_on();
                feed_dog();
                delay_s(50000);
                leds_off();
                feed_dog();
				delay_s(50000);
        }
}
extern void load_memory(void)
{
        feed_dog();
        while(RW24XX(&status_list->mem_valid,1,status_list_START,READ_EEPROM));
		feed_dog();
        if(status_list->mem_valid)
                while(RW24XX(&(status_list->eeprom_list),5,status_list_START,READ_EEPROM));
        feed_dog();
        if(status_list->meter_valid)
                while(RW24XX(&(ptr_crl->union_data.data_array[0]),32,0x20,WRITE_EEPROM));
        feed_dog();
        write_to_list();
}

extern U8 scan_status (void)
{
        if((status_list->start_exchange)&&(!uart2->send_status)) {
                feed_dog();
                uart2->send_status = 1;
                //LED3 =!LED3;
                send_msg();
				feed_dog();
        } else if(uart2->send_status && (uart2->send_stamp >= 70)) {
                feed_dog();
                no_reply_err();                         //通讯失败，写入第七个浮点数
                reset_uart2();
                list_to_eeprom();
				feed_dog();
                while(RW24XX(&(status_list->eeprom_list),5,status_list_START,WRITE_EEPROM));
				feed_dog();
                //LED2 =!LED2;
                LED3 = 1;
                feed_dog();
        } else if(RECEIVE_FINISHED == uart2->receive_status) {
                // LED4 = 0;
                feed_dog();
                if((!uart2->err_flag) &&(check_crl_g_msg())) {
                        //if((!uart2->err_flag) {
                        //  LED3 = !LED3;
						feed_dog();
                        refresh_mem();
						feed_dog();
                        write_back_eeprom();
						feed_dog();
                        refresh_list();
						feed_dog();
                        //list_to_eeprom();
                        //while(RW24XX(&(status_list->eeprom_list),5,status_list_START,WRITE_EEPROM));
                } else {
                        // ++meter_node->err_connect;
                        //uart2->err_flag = 0;
                        // meter_node->process_flag  = 0;//未考虑未收到
                        // uart2->send_status = 0 ;
                        LED3 = 1;
						feed_dog();
                        check_failed_err();
                        //reset_uart2();
                }
                reset_uart2();
				feed_dog();
                list_to_eeprom();
				feed_dog();
                while(RW24XX(&(status_list->eeprom_list),5,status_list_START,WRITE_EEPROM));
                feed_dog();
        }
        if(RECEIVE_FINISHED == uart1->receive_status) {
                feed_dog();
                //LED2 = 0;
                //if((!uart1->err_flag) &&(check_rtu_msg())) {
//                        if(!uart1->err_flag)  {
                instruction_resolve();
				feed_dog();
                instruction_excute();
//                }
//                else{
//                        instruction_resolve();
//               // LED4 =0;
//                        instruction_excute();
                // }
        }
         if(!clock_hand->reset_flag)
                feed_dog();
        if(clock_hand->reset_flag)
                while(1);
        return 1;
}
