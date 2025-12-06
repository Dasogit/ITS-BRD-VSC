/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/

#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "decoder.h"
#include "headers.h"
#include "init.h"
#include "input.h"
#include "buttons.h"
#include <stdbool.h>

static BITMAPFILEHEADER fileHdr;
static BITMAPINFOHEADER infoHdr;

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch

  initInput();

  while (1) {
    openNextFile();
    readHeaders();
    getFileHeader(&fileHdr);
    getInfoHeader(&infoHdr);
    decodeAndDisplayRLE(&fileHdr, &infoHdr);
    while (buttonPress()) {
    }
    while (!buttonPress()){
    }
  }
}

// EOF
