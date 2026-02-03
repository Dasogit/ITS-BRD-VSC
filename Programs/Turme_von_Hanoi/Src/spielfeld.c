/**
  ******************************************************************************
  * @file    spielfeld.c 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Dieses Modul implementiert die Darstellung des 
	*          Spielfelds auf dem TFT Displays.
  ******************************************************************************
  */
#include "spielfeld.h"
#include "general.h"
#include "tft.h"

// Darstellung der Steine (bei 6 Steinen)
//	Kleinster Stein       *
//          :            ***
//          :           *****
//          :          *******
//          :         *********
//  Groesster Stein  ***********


/**
* @brief Auf dem Spielfeld werden die drei Tuerme von Hanoi dargestellt. Diese Funktion druckt einen Stein
*        der Groesse stein an der Position hoehe von Turm turm aus. 
*        Der Stein wird mittig zum Turm ausgegeben.
*        Liegt ein Parameter (hoehe, stein) ausserhalb seines Wertebereiches, wird keine Ausgabe gemacht.
*        Weitere Ueberpruefungen, wie zum Beispiel ob der Stein an der Stelle platziert werden darf, 
*        werden nicht durchgefuehrt.
*	@param turm Turm, auf dem der Stein platziert werden sollen.
* @param hoehe Position in Turm, an der der Stein platziert werden soll. Bereich: 0 bis ANZAHL_STEINE-1
* @param stein Groesse des Steins, der platziert werden soll. Bereich: 0 bis ANZAHL_STEIN
*              stein == 0 : Der aktuelle dort platzierte Stein soll geloescht werden 
*              stein = 1 : Ein Stein der Breite BREITE_STEIN(stein) soll platziert werden.
* @retval none
*/
void printTurm(const enum TurmNummer turm, TurmHoehe hoehe, SteinGroesse stein) {
}

/**
* @brief Diese Funktion initialisiert das TFT Display und das Spielfeld.
*        Das Spielfeld ist ein Window mit dem Font FONT6x8.
*        Der Curser wird ausgeschaltet.
*        Die Tuerme stehen auf einer Grundlinie aus = Zeichen.
* @param none
* @retval none
*/
void initSpielfeld(void){
}
// EOF
