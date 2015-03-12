#ifndef AT24C02_H_INCLUDED
#define AT24C02_H_INCLUDED

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

#define READ_EEPROM    0xa1
#define WRITE_EEPROM   0xa0

#define status_list_START     0X00
#define METER_ADDRESS_START  0X08
#define NODE1_DATA_START     0X20
#define NODE1_DATA_END       0X3B
#define RTU_DATA_START       0X18
#define RTU_DATA_END         0X0E
#define ERRORCOUNT           10

//sbit     SDA = P0^1;
//sbit     SCL = P0^0;

extern bit  RW24XX(unsigned char *DataBuff,unsigned char ByteQuantity,unsigned int Address,
             unsigned char ControlByte);
extern void IICStart(void);
extern void IICStop(void);
extern bit  IICRecAck(void);
extern void IICACK(void);
extern void IICNoAck(void);
extern void IICSendByte(unsigned char sendbyte);
extern unsigned char IICReceiveByte(void);
extern void Delay(unsigned char DelayCount);
extern void delay_100(unsigned long t);
#endif // AT24C02_H_INCLUDED
