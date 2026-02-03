/**
 * @file    inputHandler.h
 * @author  Danandeh,Naghashi
 * @brief 
 * @version 0.1
 * @date 2026
 * 
 * @copyright Copyright (c) 2025
 * 
 */



#ifndef inputHandler_h
#define inputHandler_h

#include <stdbool.h>
#include <stdint.h>
#include <stm32f429xx.h>

/**
 * @brief read the two first bits of the raw input data 
 * @return phases of the channels
 */
static inline uint8_t  input_readRaw() {
  const static int phase_lut[4] = { 0, 1, 3, 2 }; // look up table

  uint32_t port_val = GPIOF->IDR;     // atomic read GPIOF* IDR
  return phase_lut[port_val & 0x03]; //casting to uint8 so i only read the 8 pins 
}

/**
 * @brief Get the Button object
 * 
 * @param input 
 * @return true 
 * @return false 
 */
bool getButton();



#endif