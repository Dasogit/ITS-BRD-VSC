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


#include "LCD_general.h"
#include <stdbool.h>
#include <stdint.h>


#define LESEVERSUCHE 8

uint8_t getButtons(void);
//uint8_t getButton();
void setOn(uint16_t leds);
void setOff(uint16_t leds);
uint8_t buttons_pressed_events(void);
//bool buttonEntprellen(uint8_t button);

void button_update_1ms();
//void button_update_1ms(int arr[], int size);
uint32_t zeitDiff(uint32_t z1, uint32_t z2);
#endif


// EOP