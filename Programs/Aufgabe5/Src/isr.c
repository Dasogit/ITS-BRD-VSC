/**
 * @file isr.c
 * @author Danandeh, Naghashi
 * @brief Intrupt service routine 
 * @version 0.1
 * @date 2026-01-08
 * 
 * @copyright Copyright (c) 2026
 * 
 */



#include "isr.h"
#include "fsm.h"
#include "inputHandler.h"
#include "stm32f429xx.h"
#include "timer.h"
#include <stdint.h>

volatile uint32_t lastTimeStamp = 0;
extern volatile int stepCounter;
extern volatile int curState;
 
// Initialisierung
// Routing, interruptevents, Prioritäten, und Aktivierung
void initISR(void){  
	// Enable clock
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN; 													// reset and Clock Controll mit auswahl des Portes
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;													// system config erlaubt das routing von pins auf EXTIs

	// Routing
	SYSCFG->EXTICR[0] &= ~((0xF <<  (4 * 0)) | (0xF << (4 * 1))); // remove Old Selection
	SYSCFG->EXTICR[0] |= (0x5 <<  (4 * 0)) | (0x5 << (4 * 1));		// select port F

	// Defintion des Interruptevents (reaktion auf steigende und fallende flanken) 
		// wir wählen EXTI also ein externes Interrupt
								// pin 0 	 // pin1
	EXTI->IMR  |= (1U << 0) | (1U << 1);   												// Interrupt Mask Register schaltet interruots frei
	EXTI->RTSR |= (1U << 0) | (1U << 1);   												// Rising Trigger Selection löst bei steigender Flanke aus für 1-en
	EXTI->FTSR |= (1U << 0) | (1U << 1);   												// Falling Triffer Sekection löst bei fallender Flanke aus für 0-en

	// Prioritäten setzen
	NVIC_SetPriority(EXTI0_IRQn, 0);															// 0 größte prio
	NVIC_SetPriority(EXTI1_IRQn, 0);															// 0 größte Prio
	
	// Interrupts aktivieren
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);

    lastTimeStamp = getTimeStamp();
}

void EXTI0_IRQHandler(){
	EXTI->PR = (1<< 0);
	isr();

}

void EXTI1_IRQHandler(){
	EXTI->PR = (1<< 1);
	isr();
}

static inline void isr(){
	lastTimeStamp = getTimeStamp();
    int phaseNow = input_readRaw(); // 0..3
    state_decoder(phaseNow);
}

void getCounterAndTimestamp(int *counter, uint32_t *timestamp)
{
	for(int attempt = 0; attempt < 10; attempt++)
	{
		int c1 = stepCounter;
		int t1 = lastTimeStamp;

		int c2 = stepCounter;
		int t2 = lastTimeStamp;

		if(c1 == c2 && t1 == t2)
		{
			*counter = c1;
			*timestamp = t1;
			return;
		}
	}

	curState = STATE_ERROR;
}


 // EOD //