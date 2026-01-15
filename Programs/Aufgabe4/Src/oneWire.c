/**
 * @file oneWire.c
 * @author Danandeh, Naghashi
 * @brief One wire bus IO functions 
 * @version Last version 
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "oneWire.h"
#include "stm32f429xx.h"
#include "timeDelay.h"
#include <stdbool.h>
#include <stdint.h>


/**
 * @brief Drive 1 1-wire bus idle high 
 * 
 * @return uint8_t 
 */
uint8_t ow_busIdleHigh(void) {
    ow_release();
    delay_us(5);
    return (GPIOD->IDR & IDR_MASK_PD0) != 0;
}


/**
 * @brief Drive the 1-Wire bus low (pull it to ground)
 * 
 */
void ow_driveLow(void) {
  GPIOD->BSRR = BSRR_MASK_PD0 << 16; // PD0 = 0
}

/**
 * @brief Release the 1-Wire bus (pull it high)
 * 
 */
void ow_release(void) {
  GPIOD->BSRR = BSRR_MASK_PD0; // PD0 = 1 (open-drain released)
}

/**
 * @brief Read the state of the 1-Wire bus pin 
 * internal help function
 *
 * @return uint8_t 0 = low, 1 = high
 */
static uint8_t ow_readPin(void) { return (GPIOD->IDR & IDR_MASK_PD0) != 0; }

/**
 * @brief Write a byte to the 1-Wire bus
 *
 * @param byte the byte to write to the bus to
 */
void ow_writeByte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    ow_writeBit(byte & 0x01);
    byte >>= 1;
  }
}

/**
 * @brief Read a byte from the 1-Wire bus
 *
 * @param bit the bit to write to the bus to
 * @return uint8_t the byte read from the bus
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
 * @brief Read a bit from the 1-Wire bus
 *
 * @return uint8_t the bit read from the bus
 */
uint8_t ow_readBit() {
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
 * @brief Read a byte from the 1-Wire bus
 *
 * @return uint8_t the byte read from the bus
 */
uint8_t ow_readByte() {
  uint8_t byte = 0;
  for (int i = 0; i < 8; i++) { // für 8 Bits iterieren
    uint8_t bit = ow_readBit();     // bit an der richtigen stelle verschieben
    byte |= (bit << i); // LSB first und mit dem bisher gelesenen verodern
  }
  return byte;
}

/**
 * @brief Reset + presence detect
 *
 * @return uint8_t 1 = presence, 0 = no presence
 */
uint8_t ow_reset() {
  uint8_t presence;

  ow_driveLow();
  delay_us(480);
  ow_release();

  delay_us(70);
  presence = (uint8_t)!ow_readPin(); // presence pulse pulls low

  delay_us(410);
  return presence;
}

//EOF