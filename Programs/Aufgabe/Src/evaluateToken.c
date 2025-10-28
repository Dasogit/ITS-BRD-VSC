/**
  ******************************************************************************
  * @file    evaluateToken.c
  * @author  M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @brief   handles Tokens
  ******************************************************************************
  */

#include "calc.h"
#include "outputHandler.h"
#include "stack.h"
#include "token.h"
#include <stdbool.h>
#include "evaluateToken.h"




/*
 ****************************************************************************************
 *  @brief      is the token a number
 *  @param
 *  @return     yes or no
 ****************************************************************************************/
int tokenIsNumber(T_token tokenPressed){
    return tokenPressed.tok == NUMBER ? true : false;
}


/*
 ****************************************************************************************
 *  @brief      getter for the number 
 *  @param
 *  @return     the number 
 ****************************************************************************************/
int getTokenNumber(){
    return myNumber;
}


/*
 ****************************************************************************************
 *  @brief      setter for the number that is about to be pushed to stack
 *  @param
 *  @return     void
 ****************************************************************************************/
void setTokenNumber(T_token tokenPressed){
    myNumber = tokenPressed.val;
}

/*
 ****************************************************************************************
 *  @brief      is the token an operator
 *  @param
 *  @return     either we run the operator/operation or we return failure 
 ****************************************************************************************/
_Bool tokenIsOperator(T_token tokenPressed){
    switch (tokenPressed.tok) {
        case PLUS: case MINUS: case DIV: case MULT:
            return true;
            break;
        default:
            return false;
            break;
  }
}

/*
 ****************************************************************************************
 *  @brief      is the token an operator
 *  @param
 *  @return     either we run the operator/operation or we return failure 
 ****************************************************************************************/
int operatorHandler(T_token tokenPressed){
    switch (tokenPressed.tok) {
        case PLUS: 
            add();
            break;
        case MINUS: 
            sub();
            break;
        case DIV: 
            divi();
            break;
        case MULT:
            mul();
            break;
        default:
            return errno;
            break;
  }
}



/*
 ****************************************************************************************
 *  @brief      is the token a command 
 *  @param
 *  @return     either success or error (-1)
 ****************************************************************************************/
_Bool tokenIsCommand(T_token tokenPressed){
    switch (tokenPressed.tok) {
        case PRT:  
            printLast();
            break;
        case SWAP: 
            swapLast();
            break;
        case PRT_ALL: 
            printAll();
            break;
        case CLEAR: 
            clearStack();
            break;
        case DOUBLE: 
            doubleLast();
            break;
        case ENTER:
            push(myNumber);
            break;
        default:
            return false;
            break;
  }
}



/*
 ****************************************************************************************
 *  @brief      is the token a command 
 *  @param
 *  @return     either success or error (-1)
 ****************************************************************************************/
int commandHandler(T_token tokenPressed){
    switch (tokenPressed.tok) {
        case PRT:  case SWAP: case PRT_ALL: case CLEAR: case DOUBLE: case ENTER:
            return true;
            break;
        default:
            return false;
            break;
  }
}


/*
 ****************************************************************************************
 *  @brief      handles token that was pressed on the display keypad
 *  @param      token that was read (idk if neccessary)
 *  @return     int
 ****************************************************************************************/
int tokenHandler(T_token givenToken){
    if (tokenIsCommand(givenToken)){
        commandHandler(givenToken);
    }
    if (tokenIsNumber(givenToken)){
        getTokenNumber(givenToken);
    }
    if (tokenIsOperator(givenToken)){
        operatorHandler(givenToken);
    }
}