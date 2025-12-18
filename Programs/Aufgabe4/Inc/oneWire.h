/**
 * @file oneWire.h
 * @author Danandeh, Naghashi
 * @brief pins, dirive low, release, read , timing constants and delay
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <stdint.h>

#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_
// input output	mask
#define MODER_MASK_PD0	(0x03U << (2 * 0))
#define OUTPUT_MASK_PD0	(0x01U << (2 * 0))

// BSRR Pins
#define BSRR_MASK_PD0		(0x01U)
#define BSRR_MASK_PD1		(0x01U << 1)
 
// input lesen
#define IDR_MASK_PD0		(0x01U )
#define IDR_MASK_PD1		(0x01U << 1)




void ow_driveLow(void);

void ow_release(void) ;


/**
 * @brief Reset + presence detect 
 * 
 * @return uint8_t 1 = presence detected, 0 = no device
 */
uint8_t ow_reset(void);

/* Bit IO */
/**
 * @brief Bit output
 * 
 * @param bit 
 */
void ow_writeBit(uint8_t bit);

/**
 * @brief bit input 
 * 
 * @return uint8_t 
 */
uint8_t ow_readBit(void);

/* Byte IO */
/**
 * @brief byte output
 * 
 * @param byte 
 */
void ow_writeByte(uint8_t byte);

/**
 * @brief bytte input 
 * 
 * @return uint8_t 
 */
uint8_t ow_readByte(void);

#endif /* ONEWIRE_H */