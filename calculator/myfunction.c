#include <STC5A60S2.H>
#include <intrins.h>   //_nop_();
#include <string.h> /* string and memory functions */
#include <absacc.h>
#include "mydefine.h"
//extern enum  eepromtype ;
//extern enum  eepromtype EepromType;
extern bit   RW24XX(unsigned char *DataBuff,unsigned char ByteQuantity,unsigned int Address,
                    unsigned char ControlByte/*,enum eepromtype EepromType*/)
{
    void Delay(unsigned char DelayCount);
    void IICStart(void);
    void IICStop(void);
    bit  IICRecAck(void);
    void IICNoAck(void);
    void IICAck(void);
    unsigned char IICReceiveByte(void);
    void IICSendByte(unsigned char sendbyte);
    unsigned char data j,i=ERRORCOUNT;
    bit      errorflag=1;
    while(i--)
    {
        IICStart();
        IICSendByte(ControlByte&0xfe);
        if(IICRecAck())
            continue;
        /*if(EepromType>M2416)
           {
           IICSendByte((unsigned char)(Address>>8));
           if(IICRecAck())
              continue;
           }*/
        IICSendByte((unsigned char)Address);
        if(IICRecAck())
            continue;
        if(!(ControlByte&0x01))
        {
            j=ByteQuantity;
            errorflag=0;                      //********clr errorflag
            while(j--)
            {
                IICSendByte(*DataBuff++);
                if(!IICRecAck())
                    continue;
                errorflag=1;
                break;
            }
            if(errorflag==1)
                continue;
            break;
        }
        else
        {
            IICStart();
            IICSendByte(ControlByte);
            if(IICRecAck())
                continue;
            while(--ByteQuantity)
            {
                *DataBuff++=IICReceiveByte();
                IICAck();
            }
            *DataBuff=IICReceiveByte();        //read last byte data
            IICNoAck();
            errorflag=0;
            break;
        }
    }
    IICStop();
    if(!(ControlByte&0x01))
    {
        Delay(255);
        Delay(255);
        Delay(255);
        Delay(255);
    }
    return(errorflag);
}


/*****************以下是对IIC总线的操作子程序***/
/*****************启动总线**********************/
extern void IICStart(void)
{
    SCL=0;                  //
    SDA=1;
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    SDA=0;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    SCL=0;
    SDA=1;                  //
}

/*****************停止IIC总线****************/
extern void IICStop(void)
{
    SCL=0;
    SDA=0;
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    SDA=1;
    _nop_();
    _nop_();
    _nop_();
    SCL=0;
}

/**************检查应答位*******************/
extern bit IICRecAck(void)
{
    SCL=0;
    SDA=1;
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    CY=SDA;                 //因为返回值总是放在CY中的
    SCL=0;
    return(CY);
}

/***************对IIC总线产生应答*******************/
extern void IICACK(void)
{
    SDA=0;
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    SCL=0;
    _nop_();
    SDA=1;
}

/*****************不对IIC总线产生应答***************/
extern void IICNoAck(void)
{
    SDA=1;
    SCL=1;
    _nop_();
    _nop_();
    _nop_();
    _nop_();
    SCL=0;
}

/*******************向IIC总线写数据*********************/
extern void IICSendByte(unsigned char sendbyte)
{
    unsigned char data j=8;
    for(; j>0; j--)
    {
        SCL=0;
        sendbyte<<=1;        //无论C51怎样实现这个操作，始终会使CY=sendbyte^7;
        SDA=CY;
        SCL=1;
    }
    SCL=0;
}

/**********************从IIC总线上读数据子程序**********/
extern unsigned char IICReceiveByte(void)
{
    register receivebyte,i=8;
    SCL=0;
    while(i--)
    {
        SCL=1;
        receivebyte=(receivebyte<<1)|SDA;
        SCL=0;
    }
    return(receivebyte);
}

/***************一个简单延时程序************************/
extern void Delay(unsigned char DelayCount)
{
    while(DelayCount--);
}
//24256
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//延时程序************************************************
/*
void delay_50(unsigned char t)
{
idata unsigned char i,j;
for(i=0;i<t;i++)
	for(j=0;j<50;j++)
		_nop_();
}
*/
//延时程序************************************************
/*extern void delay_100(unsigned long t)
{
idata unsigned long i,j;
for(i=0;i<t;i++)
	for(j=0;j<100;j++)
		{
		_nop_();
		//WDT_CONTR=0x35;//开狗、喂狗
		}
}////////*/



