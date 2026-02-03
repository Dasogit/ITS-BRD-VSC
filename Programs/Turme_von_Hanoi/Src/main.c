/**
  ******************************************************************************
  * @file    main.c 
  * @author  <IHR NAME>
  * @date    22.1.2019
  * @brief   Diese Datei gehoert zur GS Klausur WS 2018-19 Version 1 Tuerme von Hanoi
	*          Diese Datei steuert das Spiel gemaess direct digital control.
	*          Weiterhin enthaelt Sie die Testfunktionen für die Teilaufgaben.
  ******************************************************************************
  */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "init.h"
#include "spielfeld.h"
#include "stm32f4xx_hal.h"
#include <stdbool.h>
#include <stdint.h>
//#include "tft.h"
#include "logik.h"
#include "mytimer.h"
#include "hal.h"

/**
  * @brief  Rudimentaerer Test der Module hal und mytimer
  * @param  None
  */
void testA3(void){
	 initHal();
	 initMyTimer();
	 uint32_t warteZeit      = 4  * 1000 * 1000 ; // Wartezeit in us
	 uint32_t zeitspanne15s  = 15 * 1000 * 1000 ; // Wartezeit in us
	
// Warte bis Taster MOV_A_B_TASTER (S6) gedrueckt wird
	 while (!leseTaster(MOV_A_B_TASTER)){ }
// Ausgabe 1 auf den LEDs
	 setzeLEDHighByte(1);
// Warte bis Taster RESET_TASTER (S0) gedrueckt und anschliessend losgelassen wird
	 while (!leseTaster(RESET_TASTER)){ }
	 while (leseTaster(RESET_TASTER)){ }
// Ausgabe 2 auf den LEDs
	 setzeLEDHighByte(2);
	 sleep(warteZeit);
// Ausgabe 5 auf den LEDs
	 setzeLEDHighByte(5);
// Warte 15 Sekunden
	 sleep(zeitspanne15s);
// Loesche alle LEDs
	 setzeLEDHighByte(0);
	 sleep(warteZeit);	 
// Setze alle LEDs
	 setzeLEDHighByte(255);
// Test fertig
	 while (1) ;
}

/**
  * @brief  Rudimentaerer Test des Moduls spielfeld
  * @param  None
  */
void testA4(void){
	 uint32_t warteZeit = 2 * 1000 * 1000 ; // Wartezeit in us
	 initMyTimer();
	 initSpielfeld();
// Spielfeld mit mit weisser Grundlinie wirf auf dem Bildschirm dargestellt
	 sleep(2*warteZeit);
// Turm A wird aufgebaut
	 for (unsigned char x = 0 ; x < ANZAHL_STEINE; x++) {
			 printTurm(TurmA, x, ANZAHL_STEINE - x);
		   sleep(warteZeit);
	 }
	 sleep(warteZeit);
// Loesche unteren Stein aus Turm A
   printTurm(TurmA, 0, 0);
	 sleep(2*warteZeit);
// Zeichne Pyramide aus den drei kleinsten Steinen auf Turm B
   printTurm(TurmB, 0, 3);
   printTurm(TurmB, 1, 2);
   printTurm(TurmB, 2, 1);
	 printTurm(TurmB, 4, 0);  // Test, ob Ausgabe von keinem Element arbeitet
	 sleep(2*warteZeit);	 
// Loesche die zwei oberen Elemente von Turm B - auf B liegt nur noch der 3-Stein - also 5 Sterne
   printTurm(TurmB, 2, 0);
   printTurm(TurmB, 1, 0);
	 sleep(2*warteZeit);	 	 
// Zeichne Turm C nur mit ungeraden Steinen
   printTurm(TurmC, 0, 5);
   printTurm(TurmC, 1, 3);
   printTurm(TurmC, 2, 1);
	 sleep(warteZeit);	 
// Ergaenze Turm C zu zwei aufeinander stehenden Dreiecken
   printTurm(TurmC, 3, 3);
   printTurm(TurmC, 4, 5);
	 sleep(2*warteZeit);	 
// TEST falsche Eingabe - der Bildschirm darf sich nicht veraendern
   printTurm(TurmA, 6, 3);   sleep(warteZeit);
   printTurm(TurmB, 0, 7);   sleep(warteZeit);
   printTurm(TurmC, 22, 33); sleep(warteZeit);
// Test fertig	 
	 while(1) ;
}

/**
  * @brief  Rudimentaerer Test des Moduls logik
  * @param  None
  */
void testA5(void){
	 uint32_t warteZeit = 2 * 1000 * 1000 ; // Wartezeit in us
	 initMyTimer();
	 initSpielfeld();
	 initSpiel();
// Auf Turm A liegen alle Steine
   sleep(2*warteZeit);	
// Erstelle auf Turm C einen 2 Stein Turm	
	 bewegeStein(MOV_A_B); sleep(warteZeit);
	 bewegeStein(MOV_A_C); sleep(warteZeit);
	 bewegeStein(MOV_B_C); sleep(warteZeit);
	 sleep(2*warteZeit);
// Erstelle auf Turm B einen 3 Stein Turm
	 bewegeStein(MOV_A_B); sleep(warteZeit);
	 bewegeStein(MOV_C_A); sleep(warteZeit);
	 bewegeStein(MOV_C_B); sleep(warteZeit);
	 bewegeStein(MOV_A_B); sleep(warteZeit);
	 sleep(2*warteZeit);	
// Erstelle auf Turm C einen 4 Stein Turm
	 bewegeStein(MOV_A_C); sleep(warteZeit);
	 bewegeStein(MOV_B_C); sleep(warteZeit);
	 bewegeStein(MOV_B_A); sleep(warteZeit);
	 bewegeStein(MOV_C_A); sleep(warteZeit);
	 bewegeStein(MOV_B_C); sleep(warteZeit);
	 bewegeStein(MOV_A_B); sleep(warteZeit);
	 bewegeStein(MOV_A_C); sleep(warteZeit);
	 bewegeStein(MOV_B_C); sleep(warteZeit);
	 sleep(2*warteZeit);	
// nicht erlaubte Zuege - das Spielfeld darf sich nicht veraendern
	 bewegeStein(MOV_B_C); sleep(warteZeit);
	 bewegeStein(MOV_A_C); sleep(warteZeit);
	 bewegeStein(0x00);    sleep(warteZeit);
	 sleep(2*warteZeit);	
// Initialisiere neu, also muss der Turm A wieder vollstaendig aufgebaut sein
	 initSpiel();
	 sleep(2*warteZeit);	
// unerlaubter Zug - Spielfeld darf sich nicht veraendern
	 bewegeStein(MOV_B_A);
	 sleep(2*warteZeit);	
// erlaubter Zug - schiebe einen Stein auf Turm B
	 bewegeStein(MOV_A_B);
// Test beendet	
	 while(1) ;
}

/**
  * @brief  Diese Funktion steuert das Spiel gemaess direct digital control.
  * @param  None
  */
static void ddc(void) {
	
   // initialisiere Spiel
	
   while (1) { // Super Loop gemaess DDC

	 } // End of Super Loop
}	

/**
  * @brief  Main program
  * @param  None
  */

int main(void) {
  initITSboard();
	// testA3();
	// testA4();
	// testA5();
  ddc();
  return 0;
}

// EOF
