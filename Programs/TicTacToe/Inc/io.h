/**
 * @file io.h
 * @author your name (you@domain.com)
 * @brief Input output handler
 * @version 0.1
 * @date 2026-01-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include <stdbool.h>
#include <stdint.h>
#ifndef _io_h_
#define _io_h_


/**
 * @brief Diese Funktion liefert genau dann true zurück, wenn Schalter no (0 <= no <= 7) gedrückt ist
 * 
 * @param no int 
 * @return true wenn Schalter no (0 <= no <= 7)
 * @return false wenn Schalter no !(0 <= no <= 7)
 */
bool buttonPressed(int no);


/**
 * @brief Diese Funktion steuert die Outputs OUT0 bis OUT15 und somit die LEDs D8 bis D23 wie folgt: 
 * Ist Bit i des Parameters leds 1, dann wird OUT<i> auf high gesetzt. 
 * Ist Bit i des Parameters leds 0, dann wird der Wert von OUT<i> nicht verändert
 * 
 * @param leds 
 */
void switchLEDsOn(uint16_t leds);


/**
 * @brief Diese Funktion steuert die Outputs OUT0 bis OUT15 und somit die LEDs D8 bis D23 wie folgt: 
 * Ist Bit i des Parameters leds 1, dann wird OUT<i> auf low gesetzt. 
 * Ist Bit i des Parameters leds 0, dann wird der Wert von OUT<i> nicht verändert
 * 
 * @param leds 
 */
void switchLEDsOff (uint16_t leds);


#endif
//_io_h_
// EOP