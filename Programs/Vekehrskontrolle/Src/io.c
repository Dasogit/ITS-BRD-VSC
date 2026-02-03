/**
 ******************************************************************************
 * @file    io.c
 * @author  <I H R  N A M E>
 * @date    22.01.2020
 * @brief   Dieses Modul implementiert GPIO basiertes IO.
 ******************************************************************************
 */

#include "io.h"
#include "init.h"
#include <stm32f4xx.h>

#define BOUNCE_RETRY 5
#define BOUNCE_DELAY 20000

/**
 ******************************************************************************
 * @brief  Diese Funktion initialisiet die verwendeten Ports.
 *
 * @retval None
 *****************************************************************************/
extern void initIO(void) { initITSboard(); }

/**
 ******************************************************************************
 * @brief  Diese Funktion setzt die Error LED.
 *
 * @param  on Ist der Parameter true, wird die Error LED angeschaltet. Ansonsten
 *         wird sie ausgeschaltet.
 *
 * @retval None
 *****************************************************************************/
extern void setErrLED(bool on) {
  if (on) {
    GPIOD->BSRR = (1u << (5 + 16));
    
  } else {
    GPIOD->BSRR = (1u << 5);
  }
}

/**
 ******************************************************************************
 * @brief  Diese Funktion setzt die Status LED.
 *
 * @param  on Ist der Parameter true, wird die Status LED angeschaltet.
 * Ansonsten wird sie ausgeschaltet.
 *
 * @retval None
 *****************************************************************************/
extern void setStatusLED(bool on) {
  if (on) {
    GPIOE->BSRR = (1u << (4 + 16));

  } else {
    GPIOE->BSRR = (1u << 4);
  }
}

/**
 ******************************************************************************
 * @brief  Diese Funktion fragt den Taster ab. Er wird softwaremaessig
 *         entprellt.
 *
 * @retval  BUTTON_NOT_PRESSED : Der Taster ist nicht gedrueckt.
 *          BUTTON_PRESSED     : Der Taster ist gedrueckt.
 *          BUTTON_ERR         : Fehlerfall
 *****************************************************************************/
extern int8_t buttonPressed(void) {

  /*  if ((GPIOF->IDR & (1u << 1)) == 0u) {
     return BUTTON_PRESSED;
   } else if (!((GPIOF->IDR & (1u << 1)) == 0u)) {
     return BUTTON_NOT_PRESSED;
   } else {
     return BUTTON_ERR;
   } */
  return ((GPIOF->IDR & (1u << 1)) == 0u) ? BUTTON_PRESSED : BUTTON_NOT_PRESSED;
}

// EOF
