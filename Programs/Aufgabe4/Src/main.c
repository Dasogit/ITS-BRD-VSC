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
#include "timeDelay.h"
#include "timer.h"
#include <stdint.h>
#include <stdlib.h>

#define MODE_SENSOR_COUNT 1 // 0 = single sensor, 1 = multi sensor (exactly 4)

int main(void) {
  initITSboard();
  initTimer();
  GUI_init(DEFAULT_BRIGHTNESS);
  TP_Init(false);

  uint8_t rom[8];
  uint8_t roms[4][8]; // exactly 4 sensors
  uint8_t sp[9];
  int32_t temp_mC;
  int printed = 0;
  int32_t last_temp_mC = 0;
  uint8_t has_last = 0;
  int32_t last_temp_mC_mul[4] = {0};
  uint8_t has_last_mul[4] = {0};

  while (1) {

    if (!printed) {

#if !MODE_SENSOR_COUNT
      ow_readROM(rom);
      ow_matchROM(rom);
      ds_startConversion();

      ds_readScratchpad(rom, sp);
      ds_tempDecode(sp, &temp_mC);
      if (!has_last || temp_mC != last_temp_mC) {
        output_printTemp_mC(temp_mC);
        last_temp_mC = temp_mC;
        has_last = 1;
      }

      output_printROM(rom);
      output_printTemp_mC(temp_mC);

#else
      ow_searchNextROM(roms);
      ow_skipROM();
      ds_startConversion();

      for (int i = 0; i < 4; i++) {
        ds_readScratchpad(roms[i], sp);
        ds_tempDecode(sp, &temp_mC);
        // output_printROM(roms[i]);
        // output_printTemp_mC(temp_mC);
        if (!has_last_mul[i] || abs(temp_mC - last_temp_mC_mul[i]) >= 100) {
          output_printROM(roms[i]); // optional: only print ROM when temp changes
          output_printTemp_mC(temp_mC);
          last_temp_mC_mul[i] = temp_mC;
          has_last_mul[i] = 1;
        }
      }
#endif

      printed = 1; // stop further printing
    }
  }
}

// EOF
