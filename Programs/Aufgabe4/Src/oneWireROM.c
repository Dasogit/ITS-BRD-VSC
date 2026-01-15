/**
 * @file oneWireROM.c
 * @author Danandeh, Naghashi
 * @brief One Wire bus ROM functions 
 * @version 0.1
 * @date 2025-12-18
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "oneWireROM.h"
#include "oneWire.h"

#define multiSensor 1 // 1 erfolg 0 fehler

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
uint8_t ow_readROM(uint8_t rom[8]) {
  uint8_t presence = ow_reset();
  if (presence == 0) {
    // Return NOK ERROR
    // lcdPrintS("NOK Presence on ow_readROM from oneWireROM.c");
    return 0;
  }
  ow_writeByte(READ_ROM_CMD);
  for (int i = 0; i < 8; i++) {
    rom[i] = ow_readByte();
  }
  return 1;
}

// maybe 0 or 1 should be swapped in the upper function

/**
 * @brief Match ROM (0x55) - selects a specific device
 * The  match  ROM  command  followed  by  a  64-bit  ROM  code  sequence allows
 * the  bus  master  to  address  a  specific  slave  device  on  a  multidrop
 * or single-drop  bus.  Only the slave that exactly matches the 64-bit ROM code
 * sequence  will  respond  to  the  function  command  issued  by  the  master;
 * all  other  slaves  on  the  bus  will  wait  for  a  reset pulse.
 *
 * @param rom
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_matchROM(const uint8_t rom[8]) {
  // Ja → ow_reset()  Nein → sofort abbrechen
  uint8_t presence = ow_reset();
  if (presence == 0) {
    // Return NOK ERROR
    //lcdPrintS("NOK Presence on ow_matchROM from oneWireROM.c");
    return 0;
  }
  ow_writeByte(MATCH_ROM_CMD);
  for (int i = 0; i < 8; i++) {
    ow_writeByte(rom[i]);
  }
  return 1;

  // MATCH ROM schreibt eine Adresse auf den Bus.
}

/**
 * @brief Skip ROM (0xCC) - addresses all devices (use only if one device is
 * present) The master can use this command to address all devices on the bus
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
 *
 * @return uint8_t 1 = ok, 0 = error
 */
uint8_t ow_skipROM(void) { // quasi Broadcast
  uint8_t presence = ow_reset();
  if (presence == 0) {
    // Return NOK ERROR
    //lcdPrintS("NOK Presence on ow_matchROM from oneWireROM.c");
    return 0;
  }
  ow_writeByte(SKIP_ROM_CMD);
  return 1;
}

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
 *
 * this is basically the search all 
 *
 */
  // binäre baum wo überall ein 0 ist, ist gehen wir rein bis ende und da ist
  // quasi unser
 int ow_searchNextROM(uint8_t roms[MAX_SENSORS][8]) {
    int remaining = 1;
    int count = 0;
    static int lengths[MAX_SENSORS];
    static uint64_t paths[MAX_SENSORS];

    lengths[0] = 0;
    paths[0] = 0;

    while (remaining > 0) {

        // stop if we already collected enough sensors
        if (count >= MAX_SENSORS) {
            return count;
        }

        remaining--;
        int len = lengths[remaining];
        uint64_t path = paths[remaining];

        if (!ow_reset()) {
            return count; // no presence -> stop search
        }

        ow_writeByte(SEARCH_ROM_CMD);

        for (int i = 0; i < 64; i++) {
            int bit = ow_readBit();
            int compBit = ow_readBit();
            int pair = (bit << 1) | compBit;

            switch (pair) {
                case 0b00:
                    // discrepancy (both 0 and 1 exist)
                    if (i < len) {
                        ow_writeBit((uint8_t)((path >> i) & 1ULL));
                    } else {
                        // choose 0 for this path
                        ow_writeBit(0);

                        // push alternative branch (1) only if space
                        if (remaining < MAX_SENSORS) {
                            paths[remaining] = path | (1ULL << i);
                            lengths[remaining] = i + 1;
                            remaining++;
                        }
                    }
                    break;

                case 0b01:
                    // actual bit = 0
                    ow_writeBit(0);
                    break;

                case 0b10:
                    // actual bit = 1
                    ow_writeBit(1);
                    path |= (1ULL << i);
                    break;

                case 0b11:
                    // no device responded / error
                    return count;
            }
        }

        // store ROM (LSB first)
        for (int i = 0; i < 8; i++) {
            roms[count][i] = (uint8_t)((path >> (8 * i)) & 0xFF);
        }

        count++;
    }

    return count;
}




// int ow_searchNextROM(uint8_t roms[MAX_SENSORS][8]) {
//     int remaining = 1;
//     int count = 0;
//     int lengths[MAX_SENSORS];
//     uint64_t paths[MAX_SENSORS];

//     lengths[0] = 0;
//     paths[0] = 0;

//     while (remaining > 0) {
//         remaining--;

//         int len = lengths[remaining];
//         uint64_t path = paths[remaining];

//         // reset + presence
//         if (!ow_reset()) {
//             return count; // no bus presence or reset failed
//         }

//         ow_writeByte(SEARCH_ROM_CMD);

//         for (int bitIndex = 0; bitIndex < 64; bitIndex++) {
//             int bit = ow_readBit();
//             int compBit = ow_readBit();
//             int pair = (bit << 1) | compBit;

//             switch (pair) {
//                 case 0b00:
//                     // discrepancy: both 0 and 1 exist
//                     if (bitIndex < len) {
//                         ow_writeBit((path >> bitIndex) & 1);
//                     } else {
//                         // choose 0 for current path
//                         ow_writeBit(0);

//                         // push the alternative branch (1) if we have space
//                         if (remaining < MAX_SENSORS) {
//                             paths[remaining] = path | (1ULL << bitIndex);
//                             lengths[remaining] = bitIndex + 1;
//                             remaining++;
//                         } else {
//                             // no space for more branches
//                             // continue search but we cannot store all devices
//                         }
//                     }
//                     break;

//                 case 0b01:
//                     // bit=0, comp=1 => actual bit is 0
//                     ow_writeBit(0);
//                     break;

//                 case 0b10:
//                     // bit=1, comp=0 => actual bit is 1
//                     ow_writeBit(1);
//                     path |= (1ULL << bitIndex);
//                     break;

//                 case 0b11:
//                     // no device responded (or bus error)
//                     return count;
//             }
//         }

//         // store found ROM if we still have capacity
//         if (count >= MAX_SENSORS) {
//             return count;
//         }

//         for (int i = 0; i < 8; i++) {
//             roms[count][i] = (uint8_t)(path >> (8 * i));
//         }

//         count++;
//     }

//     return count;
// }


// EOF