#include "buttons.h"

void buttons_init() {
  P2DIR &= ~BUTTONS; // Set buttons as inputs
  P2REN |= BUTTONS; // Enable pull-up resistors
  P2OUT |= BUTTONS; // Set pull-up resistors
}

int button_down(unsigned char button) {
  return !(P2IN & button); // Button is pressed if the corresponding bit is 0 (due to pull-up resistors)
}
