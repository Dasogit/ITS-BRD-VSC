/**
 * @file timeDelay.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-17
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#include "timer.h"

void delay_us (uint32_t us){
	uint32_t ticks = us * TICKS_PER_US; 				// delayzeit in ticks = die Zahl * 90
	uint32_t zeit1 = getTimeStamp();					// jetzige Zeit zwischenspeichern (in ticks)
	while ((getTimeStamp() - zeit1) < ticks){			// Solange neue Zeit (in ticks) - alte (in Ticks) < die delayzeit (in Ticks) 
	}								
}