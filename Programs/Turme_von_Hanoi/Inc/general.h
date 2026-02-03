/**
  ******************************************************************************
  * @file    general.h 
  * @author  Franz Korf
  * @date    09.01.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Sie speichert allgemeine Daten.
  ******************************************************************************
  */
 
#ifndef _GENERAL_H
#define _GENERAL_H

#define ANZAHL_STEINE             6  // ANZAHL_STEINE der unterschiedlich grossen Steinschreiben

typedef unsigned char SteinGroesse;  // 0 : kein Stein , 1 : kleinster Stein, ANZAHL_STEINE : groesster Stein
#define KEIN_STEIN								0
#define MAX_STEIN									ANZAHL_STEINE

typedef unsigned char TurmHoehe;		 // 0 : Turm der Hoehe 1, 1 : Turm der Hoehe 2, ANZAHL_STEINE - 1 : hoechster Turm

enum TurmNummer {TurmA /* 0 */ , TurmB, TurmC /* 2 */ };

// Konstanten, dies das Verschieben von Turm x zu Turm y definieren 
#define MOV_A_B			0x01          // Verschiebe Stein von Turm A nach Turm B
#define MOV_A_C			0x02
#define MOV_B_A			0x10
#define MOV_B_C			0x12
#define MOV_C_A			0x20
#define MOV_C_B			0x21

#define QUELL_TURM(x) ((enum TurmNummer)((x>>4) & 0x0F))
#define ZIEL_TURM(x)  ((enum TurmNummer)((x)    & 0x0F))

#endif
// EOF
