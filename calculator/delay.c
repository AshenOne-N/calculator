#include "typedefine.h"
#include "delay.h"
extern void delay_s(U16 time)
{
    while(--time);
       // --time;
}
