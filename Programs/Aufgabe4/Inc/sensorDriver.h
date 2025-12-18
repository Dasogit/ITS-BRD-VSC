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
 This command initiates a single temperature conversion. Following the conversion, the resulting thermal 
data is stored in the 2-byte temperature register in the scratchpad memory and the DS18S20 returns to its 
low-power  idle  state.  If  the  device  is  being  used  in  parasite  power  mode,  within  10μs  (max)  after  this  
command  is  issued  the  master  must  enable  a  strong  pullup  on  the  1-Wire  bus  for  the  duration  of  the  
conversion (tCONV) as described in the Powering the DS18S20 section. If the DS18S20 is powered by an 
external supply, the master can issue read-time slots after the Convert T command and the DS18S20 will 
respond  by transmitting 0  while the temperature conversion  is  in  progress and 1 when the conversion  is 
done.  In  parasite  power  mode  this  notification  technique  cannot  be  used  since  the  bus  is  pulled  high  by 
the strong pullup during the conversion
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ds_startConversion(void);


/**
 * @brief Read 9-byte scratchpad from a specific device (rom) and store into sp[9].
 * This command allows the master to read the contents of the scratchpad.  The data transfer starts with the 
least  significant  bit  of  byte  0  and  continues  through  the  scratchpad  until  the  9th  byte  (byte  8  –  CRC)  is  
read. The master may issue a reset to terminate reading at any time if only part of the scratchpad data is 
needed.
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