/**
 * @file io.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-03
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "io.h"
#include "stm32f429xx.h"
#include "error.h"

/**
 * @brief Diese Funktion setzt die LEDs D23 bis D8 wie folgt: Der Parameter
 * noLeds legt fest, wieviele LEDs angeschaltet werden. Bei D8 anfangend werden
 * noLeds LEDs angeschaltet. Die restlichen LEDs werden ausgeschaltet. Z.B.: Ist
 * noLeds == 0 werden alle LEDs ausgeschaltet. Ist noLeds == 2 werden die LEDs
 * D8 und D9 eingeschaltet. Die restlichen LEDs werden ausgeschaltet. Ist der
 * Parameter noLeds größer 16, dann springt die Funktion in den schon
 * definierten Errorhandler Error_Handler. Dieser liegt im Modul error in der
 * ITS_BRD_LIB.
 *
 * @param noLeds
 */
void setLEDs(uint8_t noLeds){
    if(noLeds > 16){
        Error_Handler();
    }
    GPIOE->BSRR 

}

/**
 * @brief Diese Funktion überprüft, ob der Taster mit der Nummer button gedrückt
 * ist. Die Funktion liefert true genau dann, wenn der entsprechende Button
 * gedrückt ist. Fehlerhafte Parameter werden wie in der Funktion setLEDs
 * behandelt. Der Datentyp bool ist in der Library stdbool.h definiert.
 *
 * @param button
 * @return true
 * @return false
 */
bool buttonPressed(uint8_t button){


}




// EOF