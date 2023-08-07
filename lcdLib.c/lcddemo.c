#include <msp430.h>
#include <stdint.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "buttons.h"

#define SQUARE_SIZE 20

int squareX = 64; // X-coordinate of the square center
int squareY = 64; // Y-coordinate of the square center
int squareSize = SQUARE_SIZE; // Current size of the square (initially 20)

u_int colors[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE}; // Array of colors to cycle through
int currentColorIndex = 0; // Index of the current color in the array

int buttonDownFlag = 0; // flag to track if a button is currently pressed

void drawSquare() {
  fillRectangle(squareX - squareSize/2, squareY - squareSize/2, squareSize, squareSize, colors[currentColorIndex]);
}

void growSquare() {
  if (squareSize < 100) {
    squareSize += 5;
    drawSquare();
  }
}

void shrinkSquare() {
  if (squareSize > 5) {
    squareSize -= 5;
    drawSquare();
  }
}

void rotateSquare() {
  clearScreen(BLACK);

  // Increment the orientation angle (0, 1, 2, 3), representing (0, 90, 180, 270) degrees
  static int currentOrientation = 0;
  currentOrientation = (currentOrientation + 1) % 4;

  // Calculte the new square coordinates after rotation
  int centerX = squareX;
  int centerY = squareY;
  int newX, newY;
  
  // Update the LCD orientation based on the currentOrientation variable
  switch (currentOrientation) {
      case 0:
	newX = centerX;
	newY = centerY;
        break;
      case 1:
        newX = centerY;
	newY = screenHeight - centerX;
        break;
      case 2:
        newX = screenWidth - centerX;
	newY = screenHeight - centerY;
        break;
      case 3:
        newX = screenWidth - centerY;
	newY = centerX;
        break;
  }

  squareX = newX;
  squareY = newY;
  drawSquare();
}

void cycleColors() {
  currentColorIndex = (currentColorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
  drawSquare();
}

void checkButtons() {
  
  int buttonPressed = 0;
  
  if (button_down(BUTTON1)) {
    buttonPressed = 1;
  }
  else if (button_down(BUTTON2)) {
    buttonPressed = 2;
  }
  else if (button_down(BUTTON3)) {
    buttonPressed = 3;
  }
  else if (button_down(BUTTON4)) {
    buttonPressed = 4;
  }

  switch(buttonPressed) {
  case 1:
    if (!buttonDownFlag) {
      growSquare();
      buttonDownFlag = 1;
    }
    break;

  case 2:
    if (!buttonDownFlag) {
      shrinkSquare();
      buttonDownFlag = 1;
    }
    break;
      
  case 3:
    if (!buttonDownFlag) {
      rotateSquare();
      buttonDownFlag = 1;
    }
    break;
      
  case 4:
    if (!buttonDownFlag) {
      cycleColors();
      buttonDownFlag = 1;
    }
    break;

  default:
    buttonDownFlag = 0;
  }
}

void main() {
  WDTCTL = WDTPW | WDTHOLD; // Disable Watchdog Timer

  configureClocks();
  lcd_init();
  buttons_init();

  clearScreen(BLACK);
  drawSquare();
  
  while (1) {
     checkButtons();
  }
  
}

void __interrupt_vec(PORT2_VECTOR) Port_2() {
  if (P2IFG & BUTTONS) {
    P2IFG &= ~BUTTONS;
    button_interrupt_handler();
  }
}


