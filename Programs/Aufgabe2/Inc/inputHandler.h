/**
 * @file    inputHandler.h
 * @author  Danandeh,Naghashi
 * @brief 
 * @version 0.1
 * @date 2025-11-14
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#ifndef inputHandler_h
#define inputHandler_h

#include <stdbool.h>
#include <stdint.h>


/**
 * @brief reads the channel A and B 
 * 
 * @return int 
 */
uint8_t input_readRaw();



/**
 * @brief Get the Button object
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool getButton();



#endif