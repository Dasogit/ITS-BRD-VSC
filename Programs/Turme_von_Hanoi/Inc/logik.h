/**
  ******************************************************************************
  * @file    logik.h 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Interface des Moduls logik.
  ******************************************************************************
  */

#ifndef _LOGIK_H
#define _LOGIK_H
#include <stdbool.h>

void initSpiel(void);

bool bewegeStein(const unsigned char richtung);

#endif
//EOF
