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
#include "delay.h"
#include "stm32f429xx.h"

#include <stdbool.h>
#include <stdint.h>
#include "time.h"

// Mapping (wie oben im Disclaimer beschrieben)
static inline void ledD_setBit(uint8_t bit /*0..7*/, uint8_t on) {
    // PD8..PD15 -> bit 0..7 mapped to pin (8+bit)
    uint32_t pin = 8u + bit;
    if (on) GPIOD->BSRR = (1u << pin);
    else    GPIOD->BSRR = (1u << (pin + 16u));
}

static inline void ledE_setBit(uint8_t bit /*0..6*/, uint8_t on) {
    // PE8..PE14 -> bit 0..6 mapped to pin (8+bit)
    uint32_t pin = 8u + bit;
    if (on) GPIOE->BSRR = (1u << pin);
    else    GPIOE->BSRR = (1u << (pin + 16u));
}

void io_init(void){
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;	
}

// Buttons: Bit i == 1 => Button Si gedrückt
uint8_t io_buttonsRaw(void){
    /* for(int i = 0 ; i < 8; i++){
        uint8_t mask = GPIOF->IDR &(1 << i);
        if(mask== 0){
            arr[i] = true;
        }
    } */

    uint8_t raw = GPIOF->IDR & 0xFFu;
    return ~raw;
    
}

// einfache Entprellung als Gruppe (ohne ISR)
// Rückgabe: stabiler Button-Zustand (bitmask), aber nur wenn stabil (sonst
// alter Wert)
uint8_t io_buttonsDebounced(uint8_t lastStable){
    uint8_t raw1 = io_buttonsRaw();
    delay(3);
    uint8_t raw2 = io_buttonsRaw();
    if(raw1 == raw2){
        return raw1;
    }
    return lastStable;
}

// LEDs: 0..14
void io_ledSet(uint8_t ledIndex, uint8_t on){
    if(ledIndex < 8){
        ledD_setBit(ledIndex, on);
    }else if(ledIndex < 15){
        ledE_setBit(ledIndex, on);
    }
}

// 15 LEDs als Maske schreiben:
// bit0..bit7  -> D8..D15
// bit8..bit14 -> D17..D23
void io_ledWriteMask(uint16_t mask15){
    uint8_t mask1 = 1&(8 << mask15);
    uint8_t mask2 = 1&(8 >> mask15);
    GPIOD->BSRR = 1u << mask1;
    GPIOE->BSRR = 1u << mask2;
}

// Hilfsfunktionen für Tests
void io_ledAllOff(void){
    GPIOD->BSRR = 0xff << (16u + 8u);
    GPIOE->BSRR = 0xff << (16u + 8u);
}
void io_ledAllOn(void){
    GPIOD->BSRR = 0xff << (8u);
    GPIOE->BSRR = 0xff << (8u);
}

//EOP