#ifndef RS485_RTU_H_INCLUDED
#define RS485_RTU_H_INCLUDED

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
#define NODE_ADDR    0x10

typedef struct rtu_struct {
        U8 functype;
        U8 start_addr;
        U8 length;
        U8 err_flag;
        U8 err_type;
} RS485_RTU,*RS485;

extern xdata RS485_RTU rs_node;
extern xdata RS485 rs485;
//extern U8 check_rtu_msg(void);
extern void refresh_list(void);
extern void reset_rs485_struct(void);
extern U8 get_start_addr(U8 addr);
extern void instruction_resolve(void);
extern void instruction_excute(void);
extern void write_to_list(void);
extern void list_to_eeprom(void);
#endif // RS485_RTU_H_INCLUDED
