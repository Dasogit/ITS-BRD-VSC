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
#include <locale.h>
#include <stdint.h>

uint8_t ds_tempDecode(const uint8_t sp[9], int32_t *temp_mC_out)
{
    if (sp == NULL || temp_mC_out == NULL)
    {
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


    //ODER
//int16_t raw = (int16_t)((sp[1] << 8) | sp[0]);
//int32_t temp_mC = (raw * 1000) >> 4;  // divide by 16

}
