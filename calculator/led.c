#include "mydef.h"
#include "hal.h"
extern void leds_on(void)
{
        LED1 = TURN_ON;
        LED2 = TURN_ON;
        LED3 = TURN_ON;
        LED4 = TURN_ON;
}
extern void leds_off(void)
{
        LED1 = TURN_OFF;
        LED2 = TURN_OFF;
        LED3 = TURN_OFF;
        LED4 = TURN_OFF;
}
