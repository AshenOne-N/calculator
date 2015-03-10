#ifndef CRL_G_H_INCLUDED
#define CRL_G_H_INCLUDED

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
extern void send_msg(void);
extern unsigned char lrccheck(unsigned char *lrcbuf,unsigned char stnum,unsigned char lrclength);
extern U8 check_crl_g_msg(void);
extern float switch_data(U8 *data_array, U16 multiple, U8 bits);
extern void refresh_mem(void);
extern void write_back_eeprom(void);
extern void no_reply_err(void);
extern void reset_uart2(void);
extern void check_failed_err(void);
#endif // CRL_G_H_INCLUDED
