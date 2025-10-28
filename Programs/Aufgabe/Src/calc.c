/**
 * @file calc.h
 * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
 * @date Oct 2025
 * @brief This File is the calculater unit for a RPN Calculator
 */

#include "calc.h"
#include "errorHandler.h"
#include "token.h"
#include <stack.h>
#include "evaluateToken.h"

/*
 ****************************************************************************************
 *  @brief      adds the left and right number
 *  @param
 *  @return    int
 ****************************************************************************************/
int add() {
  int right = 0;
  if (pop(&right) != 0)
    return errno;
  int left = 0;
  if (pop(&left) != 0)
    return errno;

  if (arithmeticError(left, right, PLUS) != 0)
    return errno;

  push(left + right);
  return errno;
}

/*
 ****************************************************************************************
 *  @brief      subtracts the right number from the left
 *  @param
 *  @return    int
 ****************************************************************************************/
int sub() {
  int right = 0;
  if (pop(&right) != 0)
    return errno;
  int left = 0;
  if (pop(&left) != 0)
    return errno;

  if (arithmeticError(left, right, MINUS) != 0)
    return errno;
  push(left - right);
  return errno;
}

/*
 ****************************************************************************************
 *  @brief      multiplication of the left and right number
 *  @param
 *  @return     int
 ****************************************************************************************/
int mul() {
  int right = 0;
  if (pop(&right) != 0)
    return errno;
  int left = 0;
  if (pop(&left) != 0)
    return errno;

  if (arithmeticError(left, right, MULT) != 0)
    return errno;

  push(left * right);
  return errno;
}

/*
 ****************************************************************************************
 *  @brief      left number divided by the right number
 *  @param
 *  @return     int
 ****************************************************************************************/
int divi() {
  int right = 0;
  if (pop(&right) != 0)
    return errno;
  int left = 0;
  if (pop(&left) != 0)
    return errno;

  if (arithmeticError(left, right, DIV) != 0)
    return errno;

  push(left / right);
  return errno;
}
