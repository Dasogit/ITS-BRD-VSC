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


/*
 ****************************************************************************************
 *  @brief      adds the left and right number
 *  @param
 *  @return    int  result 
 ****************************************************************************************/
int add() {
  int right = 0;
  E(pop(&right));
  int left = 0;
  E(pop(&left));
  E(arithmeticError(left, right, PLUS));

  push(left + right);
  return SUCCESS;
}

/*
 ****************************************************************************************
 *  @brief      subtracts the right number from the left
 *  @param
 *  @return    int  result 
 ****************************************************************************************/
int sub() {
  int right = 0;
  E(pop(&right));
  int left = 0;
  E( pop(&left));

  E((arithmeticError(left, right, MINUS)));
  push(left - right);
  return SUCCESS;
}

/*
 ****************************************************************************************
 *  @brief      multiplication of the left and right number
 *  @param
 *  @return     int result
 ****************************************************************************************/
int mul() {
  int right = 0;
  E((pop(&right)));
  int left = 0;
  E((pop(&left)));

  E((arithmeticError(left, right, MULT) ));
  push(left * right);
  return SUCCESS;
}

/*
 ****************************************************************************************
 *  @brief      left number divided by the right number
 *  @param
 *  @return     int  result
 ****************************************************************************************/
int divi() {
  int right = 0;
  E((pop(&right)));
  int left = 0;
  E((pop(&left)));
     ((arithmeticError(left, right, DIV)));
  push(left / right);
  return SUCCESS;
}
