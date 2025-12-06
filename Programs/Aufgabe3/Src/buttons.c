/**
 * @file buttons.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2025-12-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "buttons.h"
#include "stm32f429xx.h"
#include <stdbool.h>


/*
* Buttons lesen
* @param n ist der/die Pins/ Buttons die gelesen werden sollen
* @retval pressed, ob der jeweilige oder die jeweiligen Buttons gedruckt sind
*/
bool buttonPress(){
	return GPIO_BSRR_BS6_Msk != (GPIOF->IDR & GPIO_BSRR_BS6_Msk);
}