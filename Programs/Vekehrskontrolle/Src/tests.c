/**
 ******************************************************************************
 * @file    tests.c
 * @author  Franz Korf
 * @date    22.01.2020
 * @brief   Dieses Modul implementiert einfache Testfunktionen fuer den
 *          Code der Teilaufgaben A3, A4 und A5.
 *          Zum Test wird die entsprechende Testfunktion am Anfang von
 *          main aufgerufen.
 ******************************************************************************
 */

#include "tests.h"
#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "LCD_general.h"
#include "delay.h"
#include "io.h"
#include "lcd.h"
#include "my_tft.h"
#include "my_timer.h"
#include "timer.h"
#include <stdio.h>

void testA3(void) {
  // initTFTAndClr();
  TFTputWelcomeStr();
  // Auf dem Display wird der Welcome Text einmal angezeigt.
  delay(2000);
  TFTputTestResult(2);
  // Auf dem Bildschirm wird die Testzeit 2 ausgegeben
  delay(5000);
  TFTputTestResult(2.34567);
  // Auf dem Bildschirm wird die Testzeit 2,3 ausgegeben
  delay(5000);
  TFTputTestResult(2.9);
  // Auf dem Bildschirm wird die Testzeit 2,9 ausgegeben
  delay(5000);
  initTFTAndClr();
  // Auf dem TFT Display steht kein Text
  delay(2000);
  TFTputWelcomeStr();
  TFTputTestResult(1234.5178);
  // In den ersten drei Zeilen des Display steht der Welcome Text.
  // In der vierten Zeile wird die Zeit 1234,5 ausgegeben
  while (1) {
  };
}

void testA4(void) {
  initTFTAndClr();
  initMyTimer();
  TFTputWelcomeStr();
  int erg = wait(10 * 1000 * 1000); // wait for 10 seconds
  if (erg) {                        // Endlos Loop im Fehlerfall
    lcdGotoXY(7, 7);
    lcdPrintS("Fehler 1");
    while (1) {
    };
  }
  TFTputTestResult(10);
  uint32_t t1 = getTS();
  wait(5 * 1000 * 1000);
  float f = getTimeSpan(t1, getTS());
  f = f / (1000 * 1000); // Konvertiere in Sekunden
  TFTputTestResult(f);   // Ausgabe sollte 5 oder 5.1 sein
  if ((f < (float)5) || (f > (float)5.2)) {
    lcdGotoXY(7, 7);
    lcdPrintS("Fehler 2");
    while (1) {
    };
  }
  delay(2000);
  t1 = 0xFFFFFFFE;
  uint32_t t2 = t1 + (uint32_t)(15 * 1000 * 1000 * 90);
  f = getTimeSpan(t1, t2);
  f = f / (1000 * 1000); // Konvertiere in Sekunden
  TFTputTestResult(f);   // Ausgabe sollte 15 sein

  if ((f < (float)15) || (f > (float)15.1)) {
    lcdGotoXY(7, 7);
    lcdPrintS("Fehler 3");
    while (1) {
    };
  }

  if (wait(UINT32_MAX)) {
    lcdGotoXY(7, 7);
    lcdPrintS("Fehler richtig erkannt.");
    while (1) {
    };
  }

  while (1) {
  };
}

void testA5(void) {

  initTFTAndClr();
  initMyTimer();
  initIO();

  setErrLED(false);
  setStatusLED(false);
  // Status LED aus;  Err LED aus
  wait(2 * 1000 * 1000);
  setErrLED(true);
  // Status LED aus; Err LED an
  wait(2 * 1000 * 1000);
  setStatusLED(true);
  // Status LED an;  Err LED an
  wait(2 * 1000 * 1000);
  setErrLED(false);
  // Status LED an;  Err LED aus
  wait(2 * 1000 * 1000);
  setStatusLED(false);
  // Status LED aus;  Err LED aus

  while (buttonPressed() != 1) {
  }; // Warte, dass der Taster gedrueckt wird
  setErrLED(true);
  // Status LED aus;  Err LED an

  while (buttonPressed() != 0) {
  }; // Warte, dass der Taster losgelassen wird
  setErrLED(false);
  // Status LED aus;  Err LED aus
  while (1) {
  };
}

// EOF
