/**
 * @file io.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-03
 *
 * @copyright Copyright (c) 2026
 *
 */
// io.h
#ifndef _IO_H
#define _IO_H

#include <stdint.h>

void io_init(void);

// Buttons: Bit i == 1 => Button Si gedrückt
uint8_t io_buttonsRaw(void);

// einfache Entprellung als Gruppe (ohne ISR)
// Rückgabe: stabiler Button-Zustand (bitmask), aber nur wenn stabil (sonst alter Wert)
uint8_t io_buttonsDebounced(uint8_t lastStable);

// LEDs: 0..14
void io_ledSet(uint8_t ledIndex, uint8_t on);

// 15 LEDs als Maske schreiben:
// bit0..bit7  -> D8..D15
// bit8..bit14 -> D17..D23
void io_ledWriteMask(uint16_t mask15);

// Hilfsfunktionen für Tests
void io_ledAllOff(void);
void io_ledAllOn(void);

#endif


// EOP