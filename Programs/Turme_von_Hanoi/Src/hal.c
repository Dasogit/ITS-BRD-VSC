/**
  ******************************************************************************
  * @file    hal.c 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Dieses Modul kapselt den Zugriff auf die Hardware.
  ******************************************************************************
  */

#include "hal.h"
#include <stdint.h>
#include <stdbool.h>
#include "TI_memory_map.h"
#include "mytimer.h"

// Der Zugriff auf die Taster ist softwaremässig entprellt.
// Ein Taster prellt maximal DELTA_PRELLEN us
// Wenn ein Taster prellt, werden maximal ANZAHL_LESEVERSUCHE_PRELLEN Zugriffe auf 
// den Taster durchgefuehrt.

#define DELTA_PRELLEN   							20 // us
#define ANZAHL_LESEVERSUCHE_PRELLEN		5

#define MAX_TASTER										6  // Groesster Pin, an dem ein verwendeter Taster angeschlossen ist.

/**
* @brief Diese Funktion fuehrt die Initialisierung der Hardware durch, die von den
*        in Init_TI_Board() umgesetzten Standardeinstellungen abweicht.
* @param None
* @retval None
*/
void initHal(void) {
}
 
/**
* @brief Diese Funktion setzt die oberen 8 an Port G angeschlossenen LEDs
*        gemaess dem in v uebergebenen Wert.
* @param v Wert, der binaer auf den LEDs ausgegeben wird.
* @retval None
*/
void setzeLEDHighByte(const unsigned char v) {
}

/**
* @brief Diese Funktion liest den in taster uebergebenen Taster aus.
*        Der Zugriff auf den Taster wird softwareseitig entprellt.
*        Es werden maximal ANZAHL_LESEVERSUCHE_PRELLEN Leseversuche
*        durchgefuehrt. 
*        Die Prelldauer eines Tasters betraegt maximal DELTA_PRELLEN us.
* @param taster Nummer des Tasters, der ausgelesen wird.
* @retval true, wenn der Taster gedrueckt ist. Ansonsten und im Fehlerfall
*         (nicht zulaessiger Taster oder Anzahl Leseversuche ueberschritten)
*         ist der Rueckgabewert false.
*/
bool leseTaster(const unsigned char taster) {
}
// EOF
