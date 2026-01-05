/**
 * @file outputHandler.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdbool.h>
#include <stdint.h>
#include "outputHandler.h"
#include "lcd.h"




/**
 * @brief prints rom on the display     
 * 
 * @param rom array of 8 bytes representing the ROM code 
 */

void output_printROM(const uint8_t rom[8]) {
    static const char hex[] = "0123456789ABCDEF";

    for (int i = 0; i < 8; i++) {
        uint8_t b = rom[i];
        lcdPrintC(hex[(b >> 4) & 0x0F]);  // high nibble
        lcdPrintC(hex[b & 0x0F]);         // low nibble
    }
    lcdPrintlnS("");
}

/**
 * @brief prints temperature in milli degrees Celsius on the display
 * 
 * @param temp_mC temperature in milli degrees Celsius
 */
void output_printTemp_mC(int32_t temp_mC) {
    if (temp_mC < 0) {
        lcdPrintC('-');
        temp_mC = -temp_mC;
    }

    int32_t intPart = temp_mC / 1000;
    int32_t fracPart = temp_mC % 1000;

    lcdPrintInt(intPart);
    lcdPrintC('.');

    if (fracPart < 100) lcdPrintC('0');
    if (fracPart < 10)  lcdPrintC('0');
    lcdPrintInt(fracPart);

    lcdPrintlnS(" C");
}


//EOF