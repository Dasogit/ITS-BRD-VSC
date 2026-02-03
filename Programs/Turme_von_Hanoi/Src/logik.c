/**
  ******************************************************************************
  * @file    logik.c 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Das Modul logik implementiert das Modell / die Logik des Spiels.
  ******************************************************************************
  */
#include "logik.h"
#include "general.h"
#include "spielfeld.h"
#include <stdbool.h>


/**
* @brief Diese Funktion initialisiert das Spiel. Auf Turm A werden alle Steine
*        gestapelt. Auf die beiden anderen Tuerme werden Steine der Groesse 0
*        gelegt.
*        Das TFT Display wird entsprechend belegt.
* @param None
* @retval None
*/
void initSpiel(void) {
}

/**
* @brief Diese Funktion bewegt einen Stein gemaess dem Parameter richtung
*        von einem Quellturm zu einem Zielturm.
*        Das TFT Display wird entsprechend angesteuert.
*        Bei einem nicht zulaessigen Eingabeparameter oder bei einem nicht 
*        zulaessigen Spielzug (z.B. der Stein kann aufgrund seiner Groesse nicht
*        auf den Zielturm gelegt werden) wird keine Funktion ausgefuehrt.
* @param richtung Definition von Quell- und Zielturm gemaess der Definition aus 
*        general.h (MOV_A_B ...)
* @retval true genau dann wenn ein Stein bewegt wurde
*/

bool bewegeStein(const unsigned char richtung) {
}
// EOF
