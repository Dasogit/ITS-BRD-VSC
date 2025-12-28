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
#define MAX_SENSORS 4


/**
 * @brief Read ROM (0x33) - only valid if exactly ONE device on the bus
 * This command can only be used when there is one slave on  the  bus.  It
 * allows  the  bus  master  to  read  the  slave’s  64-bit  ROM  code  without
 * using  the  Search  ROM  proce-dure.  If  this  command  is  used  when there
 * is  more  than  one  slave  present  on  the  bus,  a  data  collision  will
 * occur  when all the slaves attempt to respond at the same time.
 * @param rom
 * @return uint8_t 1 = ok, 0 = error (no presence / bus failure)
 */
uint8_t ow_readROM(uint8_t rom[8]);

/**
 * @brief Match ROM (0x55) - selects a specific device
 The  match  ROM  command  followed  by  a  64-bit  ROM  code  sequence  allows
 the  bus  master  to  address  a  specific  slave  device  on  a  multidrop  or
 single-drop  bus.  Only the slave that exactly matches the 64-bit ROM code
 sequence  will  respond  to  the  function  command  issued  by  the  master;
 all  other  slaves  on  the  bus  will  wait  for  a  reset pulse.
 *
 * @param rom
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_matchROM(const uint8_t rom[8]);

/**
 * @brief Skip ROM (0xCC) - addresses all devices (use only if one device is
 * present)
 * The master can use this command to address all devices on the bus
 * simultaneously without sending out any ROM code  information.  For  example,
 * the  master  can  make  all  DS18B20s on the bus perform simultaneous
 * temperature conversions by issuing a Skip ROM command followed by a Convert T
 * [44h] command. Note  that  the  Read  Scratchpad  [BEh]  command  can  follow
 * the  Skip  ROM  command  only  if  there  is  a  single  slave  device  on
 * the  bus.  In  this  case,  time  is  saved  by  allowing the master to read
 * from the slave without send-ing the device’s 64-bit ROM code. A Skip ROM
 * command followed  by  a  Read  Scratchpad  command  will  cause  a  data
 * collision  on  the  bus  if  there  is  more  than  one  slave since multiple
 * devices will attempt to transmit data  simultaneously.
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_skipROM(void);

/**
 * @brief Search ROM (0xF0) - iterate devices
 * The operation of this command is identical to the operation of the Search ROM
 * command except that only slaves with a  set  alarm  flag  will  respond. This
 * command  allows  the  master device to determine if any DS18B20s experienced
 * an  alarm  condition  during  the  most  recent  temperature  conversion.
 * After  every  Alarm  Search  cycle  (i.e.,  Alarm  Search  command  followed
 * by  data  exchange),  the  bus  master must return to Step 1 (Initialization)
 * in the transac-tion sequence. See the Operation—Alarm Signaling sec-tion for
 * an explanation of alarm flag operation.
 * @param rom
 * @return uint8_t 1 = found next device and filled rom[8], 0 = no more / error
 */
int ow_searchNextROM(uint8_t rom[MAX_SENSORS][8]);

#endif // _ONEWIRE_ROM_H 
// EOF
