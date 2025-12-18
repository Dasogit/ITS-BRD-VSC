/**
 * @file buttons.c
 * @author Danandeh, Naghashi
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


/**
 * @brief Buttons read
 * 
 * @return true 
 * @return false 
 */
bool buttonPress(){
	return GPIO_BSRR_BS6_Msk != (GPIOF->IDR & GPIO_BSRR_BS6_Msk);
}

/**
 * @brief waiting for button being pressed 
 * 
 */
void waitForNextImageButton(){
	while (buttonPress()) {
    }
    while (!buttonPress()){
    }
}