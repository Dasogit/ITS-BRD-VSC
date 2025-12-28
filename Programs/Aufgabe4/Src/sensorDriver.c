/**
 * @file sensorDriver.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "sensorDriver.h"
#include "crc.h"
#include "lcd.h"
#include "oneWire.h"
#include "oneWireROM.h"
#include "timeDelay.h"
#include <locale.h>
#include <stdint.h>


/**
 * @brief Start temperature conversion on the selected device.
 * Selection (match/skip ROM) is done outside this function, or you extend API
 * later. This command initiates a single temperature conversion. Following the
 * conversion, the resulting thermal data is stored in the 2-byte temperature
 * register in the scratchpad memory and the DS18S20 returns to its low-power
 * idle  state.  If  the  device  is  being  used  in  parasite  power  mode,
 * within  10μs  (max)  after  this command  is  issued  the  master  must
 * enable  a  strong  pullup  on  the  1-Wire  bus  for  the  duration  of  the
 * conversion (tCONV) as described in the Powering the DS18S20 section. If the
 * DS18S20 is powered by an external supply, the master can issue read-time
 * slots after the Convert T command and the DS18S20 will respond  by
 * transmitting 0  while the temperature conversion  is  in  progress and 1 when
 * the conversion  is done.  In  parasite  power  mode  this  notification
 * technique  cannot  be  used  since  the  bus  is  pulled  high  by the strong
 * pullup during the conversion
 *
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ds_startConversion(void) {
  ow_writeByte(CONVERT_T_CMD);
  delay_us(750);
  ow_driveLow();
  return 1;
}

/**
 * @brief Read 9-byte scratchpad from a specific device (rom) and store into
 * sp[9]. This command allows the master to read the contents of the scratchpad.
 * The data transfer starts with the least  significant  bit  of  byte  0  and
 * continues  through  the  scratchpad until  the  9th  byte  (byte  8  –  CRC)
 * is read. The master may issue a reset to terminate reading at any time if
 * only part of the scratchpad data is needed.
 * @param rom pointer to ROM of the device to read from
 * @param sp pointer to scratchpad array to store data
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ds_readScratchpad(const uint8_t rom[8], uint8_t sp[9]) {
  uint8_t presence = ow_reset();
  if (presence == 0) {
    // Return NOK ERROR
    lcdPrintS("NOK Presence on ow_matchROM from oneWireROM.c");
    return 0;
  }
  if (ow_matchROM(rom) == 0) {
    return 0;
  }
  ow_writeByte(READ_SCRTCHPD_CMD);
  for (int i = 0; i < 9; i++) {
    sp[i] = ow_readByte();
  }
  if (!checkCRC(9, sp))
    return 0;
  return 1;
}

/**
 * @brief Decode scratchpad into temperature.
 * Suggestion: return milli-Celsius via out parameter (no float).
 * @param sp pointer to scratchpad array
 * @param temp_mC_out pointer to store temperature in milli-Celsius
 * @return uint8_t 1 = ok, 0 = error (e.g. CRC fail)
 */
uint8_t ds_tempDecode(const uint8_t sp[9], int32_t *temp_mC_out) {
  if (sp == NULL || temp_mC_out == NULL) {
    return 0;
  }

  /* Combine temperature bytes (two’s complement) */
  int16_t raw = (int16_t)((sp[1] << 8) | sp[0]);

  /*
   * DS18B20 @ 12-bit:
   * LSB = 0.0625 °C = 1/16 °C
   * 0.0625 °C = 62.5 m°C
   */
  *temp_mC_out = (int32_t)raw * 625 / 10;

  return 1;

  // ODER
  // int16_t raw = (int16_t)((sp[1] << 8) | sp[0]);
  // int32_t temp_mC = (raw * 1000) >> 4;  // divide by 16
}
// EOF
