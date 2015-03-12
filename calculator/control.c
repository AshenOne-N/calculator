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
                uart2->send_status = 1;
                send_msg();
        } else if(uart2->send_status && (uart2->send_stamp >= 70)) {
                no_reply_err();                         //通讯失败，写入第七个浮点数
                reset_uart2();
                list_to_eeprom();
                while(RW24XX(&(status_list->eeprom_list),5,status_list_START,WRITE_EEPROM));
                LED3 = TURN_OFF;
        } else if(RECEIVE_FINISHED == uart2->receive_status) {
                if((!uart2->err_flag) &&(check_crl_g_msg())) {
                        refresh_mem();
						feed_dog();
                        write_back_eeprom();
						feed_dog();
                        refresh_list();
                } else {
                        LED3 = TURN_OFF;
                        check_failed_err();
                }
                reset_uart2();
                list_to_eeprom();
				feed_dog();
                while(RW24XX(&(status_list->eeprom_list),5,status_list_START,WRITE_EEPROM));
        }
        if(RECEIVE_FINISHED == uart1->receive_status) {
                instruction_resolve();
				feed_dog();
                instruction_excute();
        }
         if(!clock_hand->reset_flag)
                feed_dog();
        else
                while(1);
        return 1;
}
