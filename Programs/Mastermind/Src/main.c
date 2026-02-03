/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf
 * hinzugefuegt
 ******************************************************************************
 */

#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "display.h"
#include "error.h"
#include "fontsFLASH.h"
#include "init.h"
#include "io.h"
#include "masterMind.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX_TRYS 16 // Maximale Anzahl an Versuchen
#define NO_DIGITS 4 // Anzahl Stellen der gesuchten Zahl

// Die gesuchte und die akt. geratene Zahl werden als ein Feld von ASCII Zeichen
// dargestellt.
static uint8_t sno[NO_DIGITS];   // Die gesuchte Zahl
static uint8_t guess[NO_DIGITS]; // Die akt. geratene Zahl

void printUsage() {
  printStr("C -> Neues Spiel\n"
           "* -> Neustart + Hilfe\n",
           DEFAULT_COLOR);
}

void printInfo() {
  clearDisplay();
  printStr("auferderung: neuen zahl als eingabe \n", DEFAULT_COLOR);
  void printUsage();
}

void printHint(void) { printNumber("Tipp: Zahl ist ", NO_DIGITS, sno, NULL); }

int main(void) {
  initITSboard();               // Initialisierung des ITS Boards
  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch
  if (!checkVersionFlashFonts()) {
    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
    Error_Handler();
  }

  // testIO();
  // testDisplay();
  // testMasterMind();
  
  initDisplay();
  genNewNumber(NO_DIGITS, sno);
  printInfo();
  printStr("Eingabe: ", DEFAULT_COLOR);



  int noTurns = 0;
  bool win = false;
  bool lose = false;
  bool reset = false;
  bool init = false;
  bool hint = false;
  // Super Loop gemaess DDC
  while (1) {
	// == Input == 
	char c = nextInput(reset, NO_DIGITS, guess);


	// == Calculation == 
	switch (c){
		case RESET_KEY:
			genNewNumber(NO_DIGITS, sno);
			noTurns = 0;
			reset = false;
			init = true;
			break;
		case RESET_AND_HELP_KEY:
			genNewNumber(NO_DIGITS, sno);
			noTurns = 0;
			reset = false;
			init = true;
			hint = true;
			break;
		case NEXT_GUESS_READ:
		++noTurns;
		if(won(NO_DIGITS, sno, guess)){
			reset = true;
			win = true;
		}
		else if (noTurns >= MAX_TRYS){
			reset = true;
			lose = true;
		}
		break;
	}
	// == Output == 

	if( c == NEXT_GUESS_READ){
		printNumber("", NO_DIGITS, sno, guess);
	}
	if (init){
		init = false;
		printHint();
	}
	if(win){
		win = false;
		printStr("gewonnen \n", DEFAULT_COLOR);
		printUsage();
	}
	if(lose){
		lose = false;
		printStr("verloren \n",DEFAULT_COLOR);
		printUsage();
	}
	printStr("EIgabe? \n", DEFAULT_COLOR);
	setLEDs(noTurns);
  }
}

// EOF
