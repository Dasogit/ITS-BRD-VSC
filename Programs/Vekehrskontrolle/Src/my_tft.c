
/**
 ******************************************************************************
 * @file    my_tft.c
 * @author  <I H R  N A M E>
 * @date    22.01.2020
 * @brief   Dieses Modul implementiert eine einfache Textausgabe auf dem TFT
 *          Display.
 ******************************************************************************
 */
#include "my_tft.h"
#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "LCD_general.h"
#include "lcd.h"
#include "stdio.h"
#include <fonts.h>
#include <stdio.h>
#include <string.h>


#define LCDXSTART 1            //x Start der Textausgabe
#define LCDYSTART 0            //y Start der Textausgabe
#define STARTFONTWIDTH  11
#define STARTFONTHEIGHT 16
#define line2 1
#define line3 2
#define line4 3

/**
 ******************************************************************************
 * @brief  Diese Funktion loescht die aktuelle Ausgabe auf dem TFT Display und
 *         initialisiert es für die zeilenweise Ausgabe von Text.
 *
 * @retval None
 *****************************************************************************/
void initTFTAndClr(void) {
  GUI_init(DEFAULT_BRIGHTNESS);
}

/**
 ******************************************************************************
 * @brief  Diese Funktion gibt folgende Textzeilen auf den ersten drei
 *         Zeilen des TFT Display aus:
 *                Druecken Sie den Taster.
 *                Warten Sie 10 Sekunden.
 *                Druecken Sie den Taster erneut.
 *         Jede Zeile wird mit einem Zeilenumbruch beendet.
 * @retval None
 *****************************************************************************/
void TFTputWelcomeStr(void) {
  lcdGotoXY(LCDXSTART, LCDYSTART);
  lcdPrintlnS("Druecken Sie den Taster.");
  lcdPrintlnS("Warten Sie 10 Sekunden.");
  lcdPrintlnS("Druecken Sie den Taster erneut.");
}

/**
 ******************************************************************************
 * @brief  Diese Funktion gibt eine Zeitspanne gemaess des folgenden printf
 *         Formatstrings aus:
 *                   "Zeitspanne %.1f Sekunden.\n\r"
 *         wobei die Zeitspanne die im Formatstring referenzierte float Variable
 *         ist.
 *         Diese Ausgabe wird immer in Zeile 4 geschrieben. Somit werden alte
 *         Ausgaben ueberschrieben.
 *
 * @param  time  Die auszugebende Zeitspanne in Sekunden.
 *
 * @retval None
 *****************************************************************************/
void TFTputTestResult(float time) {
  // GUI_disStr(tl, "Zeitspanne %.1f Sekunden.\n\r", &Font20, WHITE, BLACK);
  // int size = strlen("Zeitspanne Sekunden.\n\r");
  //  char string[] = {"Zeitspanne %.1f Sekunden.\n\r"};
  //  snprintf(string, size,"", ...)
  // snprintf("Zeitspanne Sekunden.\n\r", size ,"%.1f", time);
  char buff[64];
  snprintf(buff, sizeof(buff), "Zeitspanne %.1f Sekunden.\n", time);
  lcdGotoXY(LCDXSTART, line4);
  lcdPrintReplS(buff);
}

// EOF
