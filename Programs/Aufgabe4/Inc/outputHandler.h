/**
 * @file outputHandler.h
 * @author Danandeh, Naghashi
 * @brief output command to print temp etc.
 * @version 0.1
 * @date 2025-12-11
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include <stdint.h>

/**
 * @brief prints ROM address
 * 
 * @param rom 
 */
void output_printROM(const uint8_t rom[8]);

/**
 * @brief Prints the temperature for the Sensors s
 * 
 * @param temp_mC 
 */
void output_printTemp_mC(int32_t temp_mC);



#endif // OUTPUT_HANDLER_H
// EOF
