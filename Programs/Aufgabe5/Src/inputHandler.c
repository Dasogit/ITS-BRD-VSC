/**
 * @file    inputHandler.c
 * @author  Danandeh, Naghashi
 * @brief
 * @version 3
 * @date    2026
 * @copyright Copyright (c) 2025
 */

#include "inputHandler.h"
#include <stdbool.h>
#include <stm32f429xx.h>

/**
 * @brief Buttons lesen
 * @param Input ist der/die Pins/ Buttons die gelesen werden sollen
 * @return if it was pressed 
 */
bool getButton() {
 /* int input       = GPIO_BSRR_BS6;
  uint8_t pinMask = (0x1u << input);
  bool pressed    = false;

  if (0 <= input && input <= 7) {
    pressed = (pinMask != (GPIOF->IDR & pinMask));
  }*/

  return GPIO_BSRR_BS6_Msk != (GPIOF->IDR & GPIO_BSRR_BS6_Msk);
  //return (GPIO_BSRR_BS6_Msk != (GPIOF->IDR & GPIO_BSRR_BS6_Msk));
}
