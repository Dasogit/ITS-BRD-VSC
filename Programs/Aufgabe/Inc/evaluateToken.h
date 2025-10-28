/**
  * @file evaluateToken.h
  * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @date   Oct 2025
  * @brief handles the tokens
*/

#ifndef evaluateToken_h
#define evaluateToken_h


#include "token.h"
#include "errorHandler.h"
#include "stack.h"
#include "calc.h"
#include "outputHandler.h"
#include <errno.h>

int myNumber = 0;


/*
 ****************************************************************************************
 *  @brief      is the token a number
 *  @param
 *  @return     yes or no
 ****************************************************************************************/
int tokenIsNumber(T_token tokenPressed);

/*
 ****************************************************************************************
 *  @brief      getter for the number 
 *  @param
 *  @return     the number 
 ****************************************************************************************/
int getTokenNumber();


/*
 ****************************************************************************************
 *  @brief      setter for the number that is about to be pushed to stack
 *  @param
 *  @return     void
 ****************************************************************************************/
void setTokenNumber(T_token tokenPressed);

/*
 ****************************************************************************************
 *  @brief      is the token an operator
 *  @param
 *  @return     either we run the operator/operation or we return failure 
 ****************************************************************************************/
_Bool tokenIsOperator(T_token tokenPressed);


/*
 ****************************************************************************************
 *  @brief      is the token an operator
 *  @param
 *  @return     either we run the operator/operation or we return failure 
 ****************************************************************************************/
int operatorHandler(T_token tokenPressed);




/*
 ****************************************************************************************
 *  @brief      is the token a command 
 *  @param
 *  @return     either success or error (-1)
 ****************************************************************************************/
_Bool tokenIsCommand(T_token tokenPressed);

/*
 ****************************************************************************************
 *  @brief      is the token a command 
 *  @param
 *  @return     either success or error (-1)
 ****************************************************************************************/
int commandHandler(T_token tokenPressed);

/*
 ****************************************************************************************
 *  @brief      handles token that was pressed on the display keypad
 *  @param      token that was read (idk if neccessary)
 *  @return     int
 ****************************************************************************************/
int tokenHandler(T_token givenToken);















#endif