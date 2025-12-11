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
#include "LCD_general.h"
#include "buttons.h"
#include "decoder.h"
#include "headers.h"
#include "init.h"
#include "input.h"
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
    GUI_clear(BLACK);
    if (infoHdr.biWidth <= LCD_WIDTH && infoHdr.biHeight <= LCD_HEIGHT) {
      decodeAndDisplayRLE(&fileHdr, &infoHdr);
    } else {
      displayScaledRLE(&fileHdr, &infoHdr);
    }
    waitForNextImageButton();
  }
}

//TODO: Bild umdrehen
//EXTRA TODO: Scaling zu display max anpassen

// EOF
