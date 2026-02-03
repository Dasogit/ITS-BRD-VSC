/**
 * @file io.c
 * @author your name (you@domain.com)
 * @brief input output handler for leds und buttons 
 * @version 0.1
 * @date 2026-01-28
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "io.h"
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Diese Funktion liefert genau dann true zurück, wenn Schalter no (0 <=
 * no <= 7) gedrückt ist
 *
 * @param no int
 * @return true wenn Schalter no (0 <= no <= 7)
 * @return false wenn Schalter no !(0 <= no <= 7)
 */
bool buttonPressed(int no){
    /* uint8_t pinmask = (1u << no);
    bool pressed = false;
    if(0 <= no && no <= 7){
        pressed = pinmask !=(GPIOF->IDR & pinmask); // wenn das bit 0 ist dann pressed is true sonst false
    }
    return pressed; */


    return (0 <= no && no <= 7) && !((GPIOF->IDR >> no) & 1);
}

/**
 * @brief Diese Funktion steuert die Outputs OUT0 bis OUT15 und somit die LEDs
 * D8 bis D23 wie folgt: Ist Bit i des Parameters leds 1, dann wird OUT<i> auf
 * high gesetzt. Ist Bit i des Parameters leds 0, dann wird der Wert von OUT<i>
 * nicht verändert
 *
 * @param leds
 */
void switchLEDsOn(uint16_t leds){
    /*uint8_t mask2 = (leds >> 8) & 0xFF;
    uint8_t mask1 = leds & 0xFF;
    GPIOD->BSRR = mask1;
    GPIOE->BSRR = mask2;*/

    GPIOD->BSRR = leds & 0xFF;
    GPIOE->BSRR = (leds >> 8) & 0xFF;
}
 

// 2 bytes in zwei variable screiben (jedes byte) werden und dann dann GPIOD bsrr zu portvar und auch fürs andere 
// LED 2 byte 
// LEds sind auf 2 ports und jeder port hat 8 leds u
/**
 * @brief Diese Funktion steuert die Outputs OUT0 bis OUT15 und somit die LEDs
 * D8 bis D23 wie folgt: Ist Bit i des Parameters leds 1, dann wird OUT<i> auf
 * low gesetzt. Ist Bit i des Parameters leds 0, dann wird der Wert von OUT<i>
 * nicht verändert
 *
 * @param leds
 */
void switchLEDsOff(uint16_t leds){
    /*uint8_t mask2 = (leds >> 8) & 0xFF;
    uint8_t mask1 = leds & 0xFF;
    GPIOD->BSRR = mask1 << 16;
    GPIOE->BSRR = mask2 << 16;*/

    GPIOD->BSRR = (leds & 0xFF) << 16;
    GPIOE->BSRR = ((leds >> 8) & 0xFF) << 16;
}
