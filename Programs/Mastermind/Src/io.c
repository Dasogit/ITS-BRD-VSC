/**
 * @file io.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-31
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "io.h"
#include "error.h"
#include "stm32f429xx.h"
#include <stdint.h>

/**
 * @brief Diese Funktion setzt die LEDs D23 bis D8 wie folgt: Der Parameter
 * noLeds legt fest, wieviele LEDs angeschaltet werden. Bei D23 anfangend werden
 * noLeds LEDs angeschaltet. Die restlichen LEDs werden ausgeschaltet. Z.B.:
 * Ist noLeds == 0 werden alle LEDs ausgeschaltet.
 * Ist noLeds == 1 wird LED D23 eingeschaltet. Die restlichen LEDs werden
 * ausgeschaltet.
 * Ist noLeds == 2 werden die LEDs D23 und D22 eingeschaltet. Die restlichen
 * LEDs werden ausgeschaltet. usw....... Ist der Parameter noLeds kleiner 0 oder
 * größer 16, dann springt die Funktion in den schon definierten Errorhandler
 * Error_Handler. Dieser liegt im Modul error in der ITS_BRD_LIB.
 *
 * @param noLeds
 */
void setLEDs(int noLeds) {
  if (noLeds < 0 || noLeds > 16) {
    Error_Handler();
  }
  GPIOE->BSRR = 0xFFu << 16;
  GPIOD->BSRR = 0xFFu << 16;
  if (noLeds == 0) {
    return;
  }
  if (noLeds <= 8) {
    GPIOE->BSRR = (0xFFu << (8 - noLeds)) & 0xFFu;
    
  } else {
    GPIOE->BSRR = 0xFFu;

    GPIOD->BSRR = (0xFFu << (8-(noLeds - 8 ))) & 0xFFu;
  }
}