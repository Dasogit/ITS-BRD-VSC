/**
 * @file main.c
 * @author Danandeh, Naghashi
 * @brief main to run the 1-Wire Bus programm with parasitic power draw
 * @version last hopefully
 * @date 2026-01-08
 * @copyright Copyright (c) 2026
 *
 */


#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "init.h"
#include "lcd.h"
#include "oneWire.h"
#include "oneWireROM.h"
#include "outputHandler.h"
#include "sensorDriver.h"
#include "timeDelay.h"
#include "timer.h"
#include <stdint.h>


int main(void) {
  initITSboard();
  initTimer();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);

  uint8_t rom[8];

  uint8_t roms[4][8]; // exactly 4 sensors
  uint8_t sp[9];
  int32_t temp_mC;

  while (1) {
    int count = ow_searchNextROM(roms);
    
    lcdGotoXY(1, 1);
    if (count <= 0) {
      lcdPrintlnS("kein sensor");
      delay_ms(5000);
    }
    if (!ow_skipROM()) {
      lcdPrintlnS("SkipROM error");
      delay_ms(5000);
      continue;
    }
    ds_startConversion();
    for (int i = 0; i < count; i++) {
      if (ds_readScratchpad(roms[i], sp)) {        
        if (ds_tempDecode(sp, &temp_mC)) {
          output_printROM(roms[i]);
          output_printTemp_mC(temp_mC);
        } else {
          output_printROM(roms[i]);
          lcdPrintS("decode error");
        }
      } else {
        output_printROM(roms[i]);
        lcdPrintlnS("read/CRC error");
      }
    }
    int x = 4 - count + 1;
    for (int j = 0; j < x; j++) {
      lcdPrintlnS(" ");
    }
    delay_ms(4150); // because we already have 750 ms delay in conversion
  }
}

// EOF
