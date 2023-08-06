#ifndef switches_included
#define switches_included

#include <msp430.h>

#define SW1 1 // P1.3
#define SW2 2 // P1.2
#define SW3 4 // P1.1
#define SW4 8 // P1.4

#define SWITCHES 15

void switches_init();
int switch_down(unsigned char sw);

#endif // included
