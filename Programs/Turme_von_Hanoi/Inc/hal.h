/**
  ******************************************************************************
  * @file    hal.h 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Interface des Moduls hal, das  den Zugriff auf die Hardware kapselt.
  ******************************************************************************
  */

#ifndef _HAL_H
#define _HAL_H
#include <stdbool.h>

// Zuweisung der Pins der Taster, die an Port E angeschlossen sind.
#define MOV_A_B_TASTER						6
#define MOV_A_C_TASTER						5
#define MOV_B_A_TASTER						4
#define MOV_B_C_TASTER						3
#define MOV_C_A_TASTER						2
#define MOV_C_B_TASTER						1
#define RESET_TASTER			  			0

void initHal(void);

void setzeLEDHighByte(const unsigned char v);

bool leseTaster(const unsigned char taster);
#endif
// EOF
