/**
  ******************************************************************************
  * @file    mytimer.c 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Das Modul mytimer implementiert einfache Timer Funktionen.
	*          Es basiert auf dem Modul timer.
  ******************************************************************************
  */
	
#include "mytimer.h"
#include "timer.h"

/**
* @brief Initialisierung des Moduls mytimer und der verwendeten Module.
* @param None
* @retval None
*/
void initMyTimer(void) {
}

/**
* @brief Diese Funktion verzögert die Ausführung um delay Mikrosekunden.
* @param delay Mikrosekunden, um die die Funktion verzoegert.
*        delay * CONVERT2US muss kleiner als UINT32_MAX sein. Dies wird 
*        nicht ueberprueft.
* @retval None
*/
void sleep(const uint32_t delay){

}
// EOF
