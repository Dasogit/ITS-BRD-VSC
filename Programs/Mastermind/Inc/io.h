/**
 * @file io.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-01-31
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef _io_h
#define _io_h

/**
 * @brief Diese Funktion setzt die LEDs D23 bis D8 wie folgt: Der Parameter
 * noLeds legt fest, wieviele LEDs angeschaltet werden. Bei D23 anfangend werden
 * noLeds LEDs angeschaltet. Die restlichen LEDs werden ausgeschaltet. Z.B.:
 * Ist noLeds == 0 werden alle LEDs ausgeschaltet.
 * Ist noLeds == 1 wird LED D23 eingeschaltet. Die restlichen LEDs werden
 * ausgeschaltet.
 * Ist noLeds == 2 werden die LEDs D23 und D22 eingeschaltet. Die restlichen LEDs werden ausgeschaltet. 
 * Ist der Parameter noLeds kleiner 0 oder größer 16, dann springt die Funktion in den schon definierten Errorhandler
 * Error_Handler. Dieser liegt im Modul error in der ITS_BRD_LIB.
 *
 * @param noLeds
 */
void setLEDs(int noLeds);

#endif
// EOF