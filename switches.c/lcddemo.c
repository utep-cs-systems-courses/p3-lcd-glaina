#include <msp430.h>
#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"
#include "switches.h"

#define SQUARE_SIZE 20

int squareX = 64; // X-coordinate of the square center
int squareY = 64; // Y-coordinate of the square center
int squareSize = SQUARE_SIZE; // Current size of the square (initially 20)

u_int colors[] = {COLOR_RED, COLOR_GREEN, COLOR_BLUE}; // Array of colors to cycle through
int currentColorIndex = 0; // Index of the current color in the array

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
  lcd_setOrientation((_orientation + 1) % 4); // Rotate orientation 90 degrees clockwise
  drawSquare();
}

void cycleColors() {
  currentColorIndex = (currentColorIndex + 1) % (sizeof(colors) / sizeof(colors[0]));
  drawSquare();
}

void main() {
  WDTCTL = WDTPW | WDTHOLD; // Disable Watchdog Timer

  configureClocks();
  lcd_init();
  switches_init();

  clearScreen(BLACK);
  drawSquare();

  while (1) {
    if (switch_down(SW1)) {
      growSquare();
    } else if (switch_down(SW2)) {
      shrinkSquare();
    } else if (switch_down(SW3)) {
      rotateSquare();
    } else if (switch_down(SW4)) {
      cycleColors();
    }
  }
}
