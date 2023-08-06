#ifndef buttons_included
#define buttons_included

#include <msp430.h>

#define BUTTON1 BIT1 // P1.1
#define BUTTON2 BIT2 // P1.2
#define BUTTON3 BIT3 // P1.3
#define BUTTON4 BIT4 // P1.4
#define BUTTONS (BIT1|BIT2|BIT3|BIT4)

void buttons_init();
int button_down(unsigned char button);

#endif // included