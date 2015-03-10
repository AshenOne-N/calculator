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
extern void load_memory(void)
{
        while(RW24XX(&status_list->mem_valid,1,status_list_START,READ_EEPROM));
        if(status_list->mem_valid)
                while(RW24XX(&(status_list->eeprom_list),sizeof(LIST),status_list_START,READ_EEPROM));
        if(status_list->meter_valid)
                while(RW24XX(&(ptr_crl->union_data.data_array[0]),24,0x20,WRITE_EEPROM));
        //feed_dog();
}

extern U8 scan_status (void)
{
        if((status_list->start_exchange)&&(!uart2->send_status)) {
                uart2->send_status = 1;
                send_msg();
        } else if(uart2->send_status && (uart2->send_stamp >= 1000)) {
                no_reply_err();                         //ͨѶʧ�ܣ�д����߸�������
                reset_uart2();
        } else if(RECEIVE_FINISHED == uart2->receive_status) {
                if((!uart2->err_flag) &&(check_crl_g_msg())) {
                        //if((!uart2->err_flag) {
                        refresh_mem();
                        write_back_eeprom();
                        refresh_list();
                } else {
                        // ++meter_node->err_connect;
                        //uart2->err_flag = 0;
                        // meter_node->process_flag  = 0;//δ����δ�յ�
                        // uart2->send_status = 0 ;
                        check_failed_err();
                        reset_uart2();
                }
        }
        if(RECEIVE_FINISHED == uart1->receive_status) {
            LED2 = 0;
                //if((!uart1->err_flag) &&(check_rtu_msg())) {
                        if(!uart1->err_flag)  {
                        instruction_resolve();
                //LED4 =0;
                        instruction_excute();
                }
                else{
                        instruction_resolve();
               // LED4 =0;
                        instruction_excute();
                }
        }
        // if(!clock_hand->reset_flag)
        //        feed_dog();
        return 1;
}
