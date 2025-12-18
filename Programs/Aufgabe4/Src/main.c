/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
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
#include "timer.h"
#include <stdint.h>
#include "main.h"
#include "oneWire.h"
#include "oneWireROM.h"
#include "sensorDriver.h"
#include "outputHandler.h"
#include "crc.h"


int main(void) {
	initITSboard();   						 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);  	 // Initialisierung des LCD Boards mit Touch
	TP_Init(false);              		    // Initialisierung des LCD Boards mit Touch

	uint8_t rom[8];
	uint8_t roms[MAX_SENSORS][8];
	uint8_t sp[9];
    int32_t temp_mC;
	
	while(1) {
		
	}
}


//TODO read scratchpad und write Scratchpad Family code 0x10 s11


// EOF
