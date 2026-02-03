/**
 ******************************************************************************
 * @file    	main.c
 *
 * @brief   Implementation eines einfachen Drogentesters.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
// #include <HAW_init.h>
#include "LCD_general.h"
#include "tests.h"
// #include "HAW_lcd.h"
#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "delay.h"
#include "error.h"
#include "fontsFLASH.h"
#include "init.h"
#include "io.h"
#include "lcd.h"
#include "my_tft.h"
#include "stm32f4xx_hal.h"
#include "tests.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*******************************************************************************
 * @brief  Diese  Funktion implementiert den Tester gemaess DDC.
 *****************************************************************************/

int main(void) {

  int i = 0;
  initIO();
  initTFTAndClr();
  TP_Init(false);
  //testA3();
  //testA4();
  testA5();

  // Initialisierung

  // Zustandvariablen

  while (i < 1000) { // DDC
                     // read sensors
    i += 1;
    // update state

    // calcuate output

    // drive output
  }
}
// EOF
