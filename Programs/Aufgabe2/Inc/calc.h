/**
 * @file calc.h
 * @author M. Sohrab Danandeh, HAW Hamburg
 * @date Oct 2025
 * @brief Drehgeber
 */

#ifndef calc_h
#define calc_h

#include <stdint.h>

/**
 * @brief angle calculation 
 *
 * @return int
 */
double angle_calc();

/**
 * @brief speed calculation
 * 
 * @param time 
 * @param angle 
 * @return speed of the angle  
 */
double speed_calc(uint32_t now, double angle);

#endif
