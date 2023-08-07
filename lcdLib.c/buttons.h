#ifndef buttons_included
#define buttons_included

#include <msp430.h>

#define BUTTON1 1 // P1.1
#define BUTTON2 2 // P1.2
#define BUTTON3 4 // P1.3
#define BUTTON4 8 // P1.4
#define BUTTONS 15

void buttons_init();
void button_interrupt_handler();
int button_down(unsigned char button);
static char button_update_interrupt_sense();

#endif // included
