/**
 * @file outputHandler.c
 * @author Danandeh
 * @brief Print ROMs on the display 
 * @version Last 
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
    static const char hex[] = "0123456789ABCDEF"; //LUP 

    for (int i = 0; i < 8; i++) {
        uint8_t b = rom[i];
        lcdPrintC(hex[(b >> 4) & 0x0F]);  // high nibble shift the higher/upper 4 bits downwards & 0x0F mask to select only 4 bits
        lcdPrintC(hex[b & 0x0F]);         // low nibble takes the 4 lower bits 
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

    int32_t intPart = temp_mC / 1000; //ganzzahliger anteil grad
    int32_t fracPart = temp_mC % 1000; // nachkommastellen mili grad rest 

    lcdPrintInt(intPart);
    lcdPrintC('.');

    //manuell 0 fill so wie have always 3 "nachkommastellen" otherwise 25.5 would look like 25.005
    if (fracPart < 100) lcdPrintC('0'); 
    if (fracPart < 10)  lcdPrintC('0');
    lcdPrintInt(fracPart);

    lcdPrintlnS(" C");
    //no float and no FPU and it is deterministic 
    //formatting without sprintf. spares saving on memory
}


//EOF