/**
 * @file    inputHandler.c
 * @author  Danandeh, Naghashi
 * @brief
 * @version 3
 * @date    2025-11-26
 * @copyright Copyright (c) 2025
 */

#include "inputHandler.h"
#include <stdint.h>
#include <stm32f429xx.h>

int phase_lut[4] = { 0, 1, 3, 2 }; // look up table


/**
 * @brief read the two first bits of the raw input data 
 * @return phases of the channels
 */
uint8_t input_readRaw() {
  uint32_t port_val = GPIOF->IDR;     // atomic read GPIOF* IDR
  return phase_lut[port_val & 0x03]; //casting to uint8 so i only read the 8 pins 
}


/**
 * @brief Buttons lesen
 * @param Input ist der/die Pins/ Buttons die gelesen werden sollen
 * @return if it was pressed 
 */
bool getButton() {
 int input = GPIO_BSRR_BS6  ;
  uint8_t pinMask = (0x1u << input);
  bool pressed = false;
  if (0 <= input && input <= 7) {
    pressed = (pinMask != (GPIOF->IDR & pinMask));
  }
  return pressed;
  //return (GPIO_BSRR_BS6_Msk != (GPIOF->IDR & GPIO_BSRR_BS6_Msk));
}
