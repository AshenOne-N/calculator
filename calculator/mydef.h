#ifndef MYDEF_H_INCLUDED
#define MYDEF_H_INCLUDED

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
#include "typedefine.h"
#define  NONE   0
#define  ODD    1
#define  EVEN   2
#define MAX_UART1_BUF_SIZE 51
#define MAX_UART2_BUF_SIZE 119
#define MINUTE 6000
#define HOUR 60
#define RECEIVE_START    0
#define RECEIVE_PROCESS  1
#define RECEIVE_FINISHED 2

typedef struct clock_struct {
        U16 count_ms;      //base time
        U16 count_min;      //scan cycle
        U8  reset_flag;
} CLOCK_STRUCT,*CLOCK_HAND;

typedef struct meter_node {
        union {
                E32 edata[7];         // all data got from meter
                U8 data_array[28];
        } union_data;
} METER,*NODE;

typedef struct   {
        U8 mem_valid;               //indicate EEPROM are used and freshed recently 1--> valid
        U8 meter_valid;             //indicate meter is connected                   1--> valid
        U8 data_valid;              //indicate whether data should be freshed  0->note processed 1->processing 2->finish processing
        U8 process_flag;            //show the step of  data freshing from the meter
        U8 err_eeprom;              //fail to store data to EEPROM
        U8 err_connect;             //fail connect to the meter
        U8 err_type;
        U8 err_flag;
        U8 start_exchange;
        U8 meter_address;           //
        U8 eeprom_list[10];
        //      NODE meter_data;
} LIST,*METER_POSITION;

typedef struct uart_mode {
        U8  uart_config;
        U16 baudrate;
        //  U8  *cursor_msg;
        //  U8  *end_of_msg;
        U8  length;
        U8  counter;
        U8  err_flag;
        U16 receive_stamp;            //
        U8  receive_status;                //0->first time to receive 1->receiving 2->
        U16 send_stamp;
        U8  send_status;
        //U16  wait_config;
} UART_STRUCT,*UART_POSITION;

typedef struct rtu_struct {
        U8 functype;
        U8 start_addr;
        U8 length;
        U8 err_flag;
        U8 err_type;
} RS485_RTU,*RS485;

extern xdata CLOCK_STRUCT local_clock;
extern xdata CLOCK_HAND clock_hand;

extern xdata METER crl_g_meter;
extern xdata NODE ptr_crl;
extern xdata LIST meter_node;
extern xdata METER_POSITION status_list;

extern xdata UART_STRUCT uart1_struct,uart2_struct;
extern xdata UART_POSITION uart1,uart2;
extern xdata U8 uart1_buf[MAX_UART1_BUF_SIZE];
extern xdata U8 uart2_buf[MAX_UART2_BUF_SIZE];

extern xdata RS485_RTU rs_node;
extern xdata RS485 rs485;

//extern U8 TEMPFLAG1;
//extern U8 TEMPFLAG2;

#endif // MYDEF_H_INCLUDED
