/**
  ******************************************************************************
  * @file    main.c
  * @author  M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "additionalFonts.h"
#include "error.h"

int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
    // Begruessungstext	
	lcdPrintS("Calculator is in progress!");
	


	
	// Test in Endlosschleife
	while(1) {
		HAL_Delay(10000);
	}
}

// EOF