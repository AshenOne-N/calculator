#include "mydef.h"
#include "hal.h"
extern void leds_on(void)
{
   LED1 = 0;
   LED2 = 0;
   LED3 = 0;
   LED4 = 0;
}
extern void leds_off(void)
{
    LED1 = 1;
    LED2 = 1;
    LED3 = 1;
    LED4 = 1;
}
