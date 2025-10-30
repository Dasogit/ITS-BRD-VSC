/**
  * @file evaluateToken.h
  * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @date   Oct 2025
  * @brief handles the tokens
*/

#ifndef evaluateToken_h
#define evaluateToken_h

#include "token.h"

/*
 ****************************************************************************************
 *  @brief      handles token that was pressed on the display keypad
 *  @param      token that was read (idk if neccessary)
 *  @return     int
 ****************************************************************************************/
int tokenHandler(T_token givenToken);

#endif