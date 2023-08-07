#include "buttons.h"

int buttons = 0;

static char button_update_interrupt_sense() {
  char p2val = P2IN;

  P2IES |= (p2val & BUTTONS);
  P2IES &= (p2val | ~BUTTONS);
  return p2val;
}

void buttons_init() {
  P2DIR &= ~BUTTONS; // Set buttons as inputs
  P2REN |= BUTTONS; // Enable pull-up resistors
  P2OUT |= BUTTONS; // Set pull-up resistors
  P2IE |= BUTTONS; // enable interrupts from buttons
  button_update_interrupt_sense();
}

int button_down(unsigned char button) {
  return !(P2IN & button);
}

void button_interrupt_handler() {
  char p2val = button_update_interrupt_sense();
  buttons = ~p2val & BUTTONS;
}
