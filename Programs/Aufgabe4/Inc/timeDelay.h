/**
 * @file timeDelay.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-17
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _timeDelay_h
#define _timeDelay_h

#include <stdint.h>


/**
 * @brief delay in microseconds
 * 
 * @param us period to delay in microseconds
 */
void delay_us(uint32_t us);


/**
 * @brief delay in milliseconds
 * 
 * @param ms period to delay in milliseconds
 */
void delay_ms(uint32_t ms);


void myDelay(uint32_t us);

#endif // _timeDelay_h