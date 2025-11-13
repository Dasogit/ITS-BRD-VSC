/**
  ******************************************************************************
  * @file    evaluateToken.c
  * @author  M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @brief   handles Tokens
  ******************************************************************************
  */

#include "calc.h"
#include "errorHandler.h"
#include "outputHandler.h"
#include "stack.h"
#include "token.h"
#include <stdbool.h>
#include "evaluateToken.h"

/*
 ****************************************************************************************
 *  @brief      handles token that was pressed on the display keypad
 *  @param      token that was read (idk if neccessary)
 *  @return     int
 ****************************************************************************************/
int tokenHandler(T_token givenToken) {
    switch (givenToken.tok) {
        case PLUS:    return add();
        case MINUS:   return sub();
        case DIV:     return divi();
        case MULT:    return mul();
        case PRT:     return printLast();
        case SWAP:    return swapLast();
        case PRT_ALL: return printAll();
        case CLEAR:   return clearStack();
        case DOUBLE:  return doubleLast();
        case NUMBER:  return push(givenToken.val); // display doesnt allow to input bigger than INT_Max ?? why? 
        case OVERFLOW: return userOverRange;
        case UNEXPECTED: return userUnknownError;
        default:      return SUCCESS; //Disskusion : gebe Error auf Blick zukunftige HW
    }
}
