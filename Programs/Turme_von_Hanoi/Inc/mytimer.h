/**
 ******************************************************************************
 * @file    mytimer.h
 * @author  <IHR NAME>
 * @date    22.1.2019
 * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von
 * Hanoi Interface des Moduls mytimer, das  einfache Timer Funktionen
 *          realisiert.
 ******************************************************************************
 */
#include <stdint.h>
#ifndef _MYTIMER_H
#define _MYTIMER_H


/**
* @brief Initialisierung des Moduls mytimer und der verwendeten Module.
* @param None
* @retval None
*/

void initMyTimer(void);

/**
* @brief Diese Funktion verz�gert die Ausf�hrung um delay Mikrosekunden.
* @param delay Mikrosekunden, um die die Funktion verzoegert.
*        delay * CONVERT2US muss kleiner als UINT32_MAX sein. Dies wird 
*        nicht ueberprueft.
* @retval None
*/
void sleep(const uint32_t delay);
#endif
// EOF
