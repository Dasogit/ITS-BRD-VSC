/**
  * @file errorHandler.c
  * @author M. Sohrab Danandeh, HAW Hamburg 
  * @date Oct 2025
  * @brief This File is for all Errors for a RPN Calculator
*/

#include "errorHandler.h"
#include "outputHandler.h"
#include <stdio.h>
#include "errno.h"



/*
 ****************************************************************************************
 *  @brief     decodes the error and returns the matching error number with the msg  
 *  @param     error number
 *  @return    void
 ****************************************************************************************/
void handleError(int errorNumber){
  switch(errorNumber){
    case userStackOverFlow :
    setErrMode();
    printf((char*) STACKOVERMSG);
  }


}


/*
 ****************************************************************************************
 *  @brief     assesses if theres an arithmetic error
 *  @param     left number/operand , right number/operand, operation
 *  @return    int code of error 
 ****************************************************************************************/
int arithmeticError(int left, int right, char operation);




