/**
 * @file errorHandler.c
 * @author M. Sohrab Danandeh, HAW Hamburg
 * @date Oct 2025
 * @brief This File is for all Errors for a RPN Calculator
 */

#include "errorHandler.h"
#include <errno.h>
#include <stdio.h>
#include <limits.h>

/*
 ****************************************************************************************
 *  @brief     decodes the error and returns the matching error number with the
 * msg
 *  @param     error number
 *  @return    void
 ****************************************************************************************/
void handleError(int errorNumber) {
  switch (errorNumber) {
  case userStackOverFlow:
    errno = userStackOverFlow;
    printf((char *)STACKOVERMSG);
    break;
  case userStackUnderFlow:
    errno = userStackUnderFlow;
    printf((char *)STACKUNDERMSG);
    break;
  case userArithmeticOverflow:
    errno = userArithmeticOverflow;
    printf((char *)ARTOVERMSG);
    break;
  case userArithemticUnderflow:
    errno = userArithemticUnderflow;
    printf((char *)ARTUNDERMSG);
    break;
  case userDivideByZero:
    errno = userDivideByZero;
    printf((char *)DOMMSG);
    break;
  }
}

/*
 ****************************************************************************************
 *  @brief     assesses if theres an arithmetic error
 *  @param     left number/operand , right number/operand, operation
 *  @return    int code of error
 ****************************************************************************************/
int arithmeticError(int left, int right, char operation) {
  switch (operation) {
  case '+':
    if (right > 0 && left > INT_MAX - right) { // b = intMax & a = intMax
      return errno = userArithmeticOverflow;
    }
    if (right < 0 && left < INT_MIN - right) { // b = intMin & a = intMin
      return errno = userArithemticUnderflow;
    }
    return 0;
  case '-':
    if (right < 0 && left > INT_MAX + right) {
      return errno = userArithmeticOverflow; // a - (–|b|)  ?  +Overflow
    }
    if (right > 0 && left < INT_MIN + right) {
      return errno = userArithemticUnderflow; // a - (+|b|)  ?  -Underflow
    }
    return 0;
  case '*':
    if (left == 0 || right == 0) { // a or b is 0
      return 0;
    }
    if (right > 0) {                // b > 0
      if (left > INT_MAX / right) { // a = intMax b = intMax Overflow (+)
        // unused memory range ( that we want to use) is smaller than the other
        // number
        return errno = userArithmeticOverflow;
      }
      if (left < INT_MIN / right) { // a = intMin b = intMax  Underflow (-)
        // unused memory range (that we want to use) is not enough in the other
        // way
        return errno = userArithemticUnderflow;
      }
    }
    // right < 0
    if (left > 0 &&
        right < INT_MIN / left) { // a = intMax & b = intMin overflow
      return errno = userArithemticUnderflow;
    }
    if (left < 0 && right < 0 &&
        right < INT_MAX / left) { // a = intMin (smallest negative) & b =
                                  // intMin(smallest negative) & b is even
                                  // smaller than memoryrange underflow
      return errno = userArithmeticOverflow;
    }
  case '/':
    if (left == 0) { // denominator is 0
      return errno = userDivideByZero;
    }
    if (right == INT_MIN && right == -1) { // a = minInt / -1 overflow
      return errno = userArithmeticOverflow;
    }
  default:
    return -1;
  }
}
