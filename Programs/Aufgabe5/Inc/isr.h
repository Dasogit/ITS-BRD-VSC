/**
 * @file isr.h
 * @author  Danandeh
 * @brief Intrupt service routine 
 * @version 0.1
 * @date 2026-01-08
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef _ISR_H_
#define _ISR_H_

#include <stdint.h>

/*
 schritt 1: Routing des Interrupts 
 Verbindung eines Pins eines GPIOs mit einem Eingang des Interrupt Controllers 
 16 Interrupts stehen zur Verfügung (EXTI0 - EXTI15)
 auf EXTLi kann nur Pin i eines Ports vie eines Multiplexers gebunden 
 interrupt soll bei jeder fallenden Flanke ausgelöst werden
 DIe ISR soll die globale Variable counter um 1 erhöhen.


 	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; 													// reset and Clock Controll mit auswahl des Portes AKA Clco k for GPIO Port G 
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;													// system config erlaubt das routing von pins auf EXTIs AKA System conf. Clock enable 

	// Routing
	SYSCFG->EXTICR[0] &= ~((0xF <<  (4 * 0)) | (0xF << (4 * 1))); // remove Old Selection Pin 0 
	SYSCFG->EXTICR[0] |= (0x5 <<  (4 * 0)) | (0x5 << (4 * 1));		// select port F
*/

/*
Schritt 2: Definiere IRQ Event und Unmask IRQ: (Teil 2 der Initialiserung)
Definiere Ereignisse auf der INT Leitung die einen Interrupt auslösen
Hier: Flanken getriggert Auswahl: Positive Flanke Negative Flanke beide Flanke 
*/


/**
 * @brief ISR Init 
 * 
 */
void initISR(void);


/**
 * @brief ISR Requesst handlerfor for port a 
 * 
 */
void EXIT0_IRQHandler(void);

/**
 * @brief ISR Requesst handler for port b 
 * 
 */
void EXIT1_IRQHandler(void);

/**
 * @brief 
 * 
 */
static inline void isr(void);

/**
 * @brief Get the Counter And Timestamp object
 * 
 * @param counter 
 * @param timestamp 
 */
void getCounterAndTimestamp(int *counter, uint32_t *timestamp);

#endif 

 // EOD //