/**
 * @file sensorDriver.h
 * @author Danandeh, Naghashi
 * @brief DS18B20 Sensor driver
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _sensorDriver_H
#define _sensorDriver_H

#include <stdint.h>

#define READ_SCRTCHPD_CMD				    0xBE
#define CONVERT_T_CMD						0x44

/*
sp AKA scratchpad meanings 
sp[0]   temperatur LSB
sp[1]   temperatur MSB
sp[2]   th register
sp[3]   tl register
sp[4]   config
sp[5:7] reserved
sp[8]   crc
*/

/**
 * @brief Start temperature conversion on the selected device.
 * Selection (match/skip ROM) is done outside this function, or you extend API later.
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ds_startConversion(void);


/**
 * @brief Read 9-byte scratchpad from a specific device (rom) and store into sp[9].
 * 
 * @param rom 
 * @param sp 
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ds_readScratchpad(const uint8_t rom[8], uint8_t sp[9]);

/**
 * @brief Decode scratchpad into temperature.
 * Suggestion: return milli-Celsius via out parameter (no float).
 * @param sp 
 * @param temp_mC_out 
 * @return uint8_t 1 = ok, 0 = error (e.g. CRC fail)
 */
uint8_t ds_tempDecode(const uint8_t sp[9], int32_t *temp_mC_out);

#endif /* SENSOR_DRIVER_H */