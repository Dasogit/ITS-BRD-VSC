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
#include <stdio.h>
#include <stdlib.h>
#include "outputHandler.h"
#include "lcd.h"




/**
 * @brief prints rom on the display     
 * 
 * @param rom array of 8 bytes representing the ROM code 
 */

void output_printROM(const uint8_t rom[8]){
    lcdPrintlnS((char * )rom);
}

/**
 * @brief prints temperature in milli degrees Celsius on the display
 * 
 * @param temp_mC temperature in milli degrees Celsius
 */
void output_printTemp_mC(int32_t temp_mC){
    bool isNegative = false;
    if(temp_mC < 0){
        isNegative = true;
        lcdPrintC('-');
    }
    int abs_mc = abs(temp_mC);
    lcdPrintInt(abs_mc);
    lcdPrintlnS(""); 
}

/**
 * @brief prints all temperatures on the display
 * 
 */
void output_printAllTemps(void){
    lcdPrintlnS("All Temps:");
    // TODO: Implement printing all temperatures
}

/**
 * @brief automate output handling and display updates 
 * 
 */
void output_automate(void){
    // TODO: Implement output automation logic
}

//EOF