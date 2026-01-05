/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "additionalFonts.h"
#include "crc.h"
#include "error.h"
#include "fontsFLASH.h"
#include "init.h"
#include "lcd.h"
#include "oneWire.h"
#include "oneWireROM.h"
#include "outputHandler.h"
#include "sensorDriver.h"
#include "stm32f4xx_hal.h"
#include "timer.h"
#include <stdint.h>

#define MODE_SENSOR_COUNT 1 // 0 ist einzel 1 ist multi sensor 

int main(void) {
  initITSboard();               // Initialisierung des ITS Boards
  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch

  uint8_t rom[8];
  uint8_t roms[MAX_SENSORS][8];
  uint8_t sp[9];
  int32_t temp_mC;

  while (1) {
    #if !MODE_SENSOR_COUNT
      ow_readROM(rom);
      ow_matchROM(rom);
      ds_startConversion();
      ds_readScratchpad(rom,sp);
      ds_tempDecode(sp, &temp_mC);
      output_printROM(rom);
      output_printTemp_mC(temp_mC);
    #else 
      ow_searchNextROM(&rom);
      ow_skipROM();
      ow_
    #endif

	ow_reset();
	ow_matchROM(rom); // or ow_skipROM() if exactly one device or broadcast convert 
	ow_writeByte(CONVERT_T_CMD); // or ds_startConversion() if it only does only that 
	//wait conversion time 
	ds_readScratchpad(rom, sp);
  ow_readROM(rom); 
	ow_matchROM(rom); //or skip
  ds_startConversion();
  ds_readScratchpad(rom, sp);
	ds_tempDecode(sp, &temp_mC);
	output_printROM(rom);
	output_printTemp_mC(temp_mC);
  

  }
}

// EOF
