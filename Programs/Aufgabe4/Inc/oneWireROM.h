/**
 * @file oneWireROM.h
 * @author Danandeh, Naghashi
 * @brief for addressing and discovery
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef ONEWIRE_ROM_H
#define ONEWIRE_ROM_H

// Command liste
#include <stdint.h>
#define READ_ROM_CMD    0x33
#define MATCH_ROM_CMD   0x55
#define SKIP_ROM_CMD    0xcc
#define SEARCH_ROM_CMD  0xF0


/**
 * @brief Read ROM (0x33) - only valid if exactly ONE device on the bus
 * 
 * @param rom 
 * @return uint8_t 1 = ok, 0 = error (no presence / bus failure)
 */
uint8_t ow_readROM(uint8_t rom[8]);

/**
 * @brief Match ROM (0x55) - selects a specific device
 * 
 * @param rom 
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_matchROM(const uint8_t rom[8]);

/**
 * @brief Skip ROM (0xCC) - addresses all devices (use only if one device is present)
 * 
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_skipROM(void);

/**
 * @brief Search ROM (0xF0) - iterate devices
 * 
 * @param rom 
 * @return uint8_t 1 = found next device and filled rom[8], 0 = no more / error
 */
uint8_t ow_searchNextROM(uint8_t rom[8]);

#endif /* ONEWIRE_ROM_H */