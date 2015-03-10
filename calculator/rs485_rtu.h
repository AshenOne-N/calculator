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
extern U8 check_rtu_msg(void);
extern void refresh_list(void);
extern void reset_rs485_struct(void);
extern U8 get_start_addr(U8 addr);
extern void instruction_resolve(void);
extern void instruction_excute(void);
#endif // RS485_RTU_H_INCLUDED
