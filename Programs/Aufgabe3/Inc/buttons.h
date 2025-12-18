/**
 * @file buttons.h
 * @author Naghashi, Danandeh
 * @brief it reads the buttons and loads next picture
 * @version 0.1
 * @date 2025-12-04
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef _buttons_h
#define _buttons_h
#include <stdbool.h>

/**
 * @brief if button was pressed
 * 
 * @return true yes it was
 * @return false no it wasnt 
 */
bool buttonPress();
/**
 * @brief waiting for the next image after the button push 
 * 
 */
void waitForNextImageButton();
#endif