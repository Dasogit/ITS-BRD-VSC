/**
  * @file stack.c
  * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg 
  * @date   Oct 2025
  * @brief this file is the implementation of a stack for the Calculator
*/

#include "display.h" 
#include "stack.h"
#include "errorHandler.h"

int stack[STACKSIZE];
int last = -1;


/*
 ****************************************************************************************
 *  @brief      pushs the number to the stack
 *  @param      number being pushed to the memory
 *  @return     int
 ****************************************************************************************/
int push(int theNumber) {
    if(last + 1 >= STACKSIZE){
        return userStackUnderFlow;
    }
    stack[++last] = theNumber;
    return SUCCESS;
}


/*
 ****************************************************************************************
 *  @brief      returns the number from the stack 
 *  @param      pointer to the integer of 4 byte value 
 *  @return     int
 ****************************************************************************************/
int pop(int* pToken){
    if(last < 0){ 
         return userInvalidInput;
    }
    *pToken = stack[last--]; // at the address of pToken, save the last entry of stack 
    return SUCCESS; 
}


/*
 ****************************************************************************************
 *  @brief      reads the last value/entry that was pushed to the stack (LiFo)
 *  @param      
 *  @return     int
 ****************************************************************************************/
int getLast(){
    return last; //aka top of the stack
}


/*
 ****************************************************************************************
 *  @brief      sets the last value/entry that is on stack (cutting the line)
 *  @param      number to be set to
 *  @return     void
 ****************************************************************************************/
void setLast(int token){
    last = token;
}


/*
 ****************************************************************************************
 *  @brief      gets the number where the pointer to integer of 4 byte value is pointing to
 *  @param      number to get , pointer to the integer of 4 byte value (de/referencing the number)
 *  @return     int
 ****************************************************************************************/
int getNumber(int number, int* pNumber){
    * pNumber = stack[number];
    return SUCCESS;
}


/*
 ****************************************************************************************
 *  @brief      gets the stack size
 *  @param      none
 *  @return     int
 ****************************************************************************************/
int getStackSize(){
    return STACKSIZE;
}


/*
 ****************************************************************************************
 *  @brief      clears the stack
 *  @return     int
 ****************************************************************************************/
int clearStack(){
    last = -1;
    clearStdout();
    return SUCCESS;
}
