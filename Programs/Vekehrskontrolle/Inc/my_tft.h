/**
 * @file my_tft.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-01
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _MY_TFT_H
#define _MY_TFT_H

/**
 ******************************************************************************
 * @brief  Diese Funktion loescht die aktuelle Ausgabe auf dem TFT Display und
 *         initialisiert es f�r die zeilenweise Ausgabe von Text.
 *
 * @retval None
 *****************************************************************************/
void initTFTAndClr(void);

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
void TFTputWelcomeStr(void);

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
void TFTputTestResult(float time);

#endif
// EOF
