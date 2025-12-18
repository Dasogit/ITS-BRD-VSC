/**
 * @file oneWire.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "oneWire.h"
#include "stm32f429xx.h"
#include "timeDelay.h"
#include <stdbool.h>
#include <stdint.h>

static void ow_driveLow(void) {
  GPIOD->BSRR = BSRR_MASK_PD0 << 16; // PD0 = 0
}

static void ow_release(void) {
  GPIOD->BSRR = BSRR_MASK_PD0; // PD0 = 1 (open-drain released)
}

static uint8_t ow_readPin(void) { return (GPIOD->IDR & IDR_MASK_PD0) != 0; }

/**
 * @brief
 *
 * @return
 */
void oW_writeByte(uint8_t byte) {
  for (uint8_t i = 0; i < 8; i++) {
    ow_writeBit(byte & 0x01);
    byte >>= 1;
  }
}

/**
 * @brief
 *
 * @param bit
 */
void ow_writeBit(uint8_t bit) {
  if (bit) {
    ow_driveLow();
    delay_us(6);
    ow_release();
    delay_us(64);
  } else {
    ow_driveLow();
    delay_us(60);
    ow_release();
    delay_us(10);
  }
}

/**
 * @brief
 *
 * @return int
 */
uint8_t oW_readBit() {
  uint8_t bit;

  /* Initiate read slot */
  ow_driveLow(); // pull bus low
  delay_us(6);   // ≥1 µs, <15 µs
  ow_release();  // release bus

  /* Sample window */
  delay_us(9);        // sample around 15 µs from start
  bit = ow_readPin(); // read bus state

  /* Finish time slot */
  delay_us(55); // complete 60 µs slot

  return bit;
}

/**
 * @brief
 *
 * @return int
 */
uint8_t oW_readByte() {
  uint8_t byte = 0;
  for (uint8_t i = 0; i < 8; i++) { // für 8 Bits iterieren
    uint8_t bit = ow_readBit(); // bit an der richtigen stelle verschieben 
    byte |= (bit << i);   // LSB first und mit dem bisher gelesenen verodern
  }
  return byte;
}

/**
 * @brief
 *
 * @return int
 */
uint8_t oW_reset();