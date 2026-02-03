/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Die Klausuraufgabe Kniffel.
 *
 ******************************************************************************
 */

#include "main.h"
#include "LCD_GUI.h"
#include "display.h"
#include "init.h"
#include "io.h"
#include "kniffel.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

uint8_t whichButton() { return (uint8_t)(GPIOD->IDR & 0xFF); }
void s7(int counter) {}

int main(void) {
  // Initialisierung der HW
  initITSboard();
  GUI_init(DEFAULT_BRIGHTNESS);

#ifdef AUFGABE3
  testIO();
#endif

#ifdef AUFGABE4
  testDisplay();
#endif

#ifdef AUFGABE5
  testKniffel();
#endif
  // INIT
  int counter = 1;
  int counterFeit = 1;
  clearDisplay();
  releaseDice();
  rollDice();
  for (int i = 0; i < NO_DICE; i++) {
    displayDie(i, getDie(i), GREEN);
  }
  for (;;) {
    for (int i = 0; i < NO_DICE; i++) {
      if (buttonPressed(i)) {
        fixDie(i);
        displayDie(i, getDie(i), MAGENTA);
      }
    }
    if (buttonPressed(5)) {
      releaseDice();
      for (int i = 0; i < NO_DICE; i++) {
        displayDie(i, getDie(i), GREEN);
      }
    }

    if (buttonPressed(6)) {
      rollDice();
      counter += counterFeit;
      for (int i = 0; i < NO_DICE; i++) {
        if (!(isFixed(i))) {
          displayDie(i, getDie(i), GREEN);
        } else {
          displayDie(i, getDie(i), MAGENTA);
        }
      }
    }
    if (buttonPressed(7)) {
      counter = 1;
      clearDisplay();
      releaseDice();
      rollDice();
      for (int i = 0; i < NO_DICE; i++) {
        displayDie(i, getDie(i), GREEN);
      }
    }
    if (isStreet() || isKniffel()) {
      for (int i = 0; i < NO_DICE; i++) {
        displayDie(i, getDie(i), YELLOW);
      }
      while (true) {
        if (buttonPressed(7)) {
          break;
        }
      }
    }
    setLEDs(counter);
    if (counter > 15) {
      counterFeit++;
      setLEDs(2);
    }
  }
}
// EOF