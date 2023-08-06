#include "switches.h"

void switches_init() {
  P1DIR &= ~SWITCHES; // Set buttons as inputs
  P1REN |= SWITCHES; // Enable pull-up resistors
  P1OUT |= SWITCHES; // Set pull-up resistors
}

int switch_down(unsigned char sw) {
  return !(P1IN & sw); // Button is pressed if the corresponding bit is 0 (due to pull-up resistors)
}
