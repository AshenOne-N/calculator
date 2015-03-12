#ifndef TYPEDEFINE_H_INCLUDED
#define TYPEDEFINE_H_INCLUDED

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
#define X86_ENABLED  0
#define C51_EMABLED 1
#if X86_ENABLED
typedef unsigned char     U8;
typedef signed   char     S8;
typedef unsigned short    U16;
typedef signed   short    S16;
typedef unsigned int      U32;
typedef signed   int      S32;
typedef float             E32;
typedef double            E64;

#elif C51_EMABLED
typedef unsigned char     U8;
typedef signed   char     S8;
typedef unsigned int      U16;
typedef signed   int      S16;
typedef unsigned long int U32;
typedef signed  long  int S32;
typedef float             E32;
typedef double            E64;

#endif // X86_ENABLED
#endif // TYPEDEFINE_H_INCLUDED
