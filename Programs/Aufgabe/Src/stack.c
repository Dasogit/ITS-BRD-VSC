/**
  * @file errorHandler.h
  * @author M. Sohrab Danandeh, HAW Hamburg 
  * @date Oct 2025
  * @brief This File is for all Errors for a RPN Calculator
*/


#include "stack.h"

int stack[STACKSIZE];
int last = -1;



/*
 ****************************************************************************************
 *  @brief      checks if the number being pushed to the memory is in range of the memory
 *  @param      number being pushed on the memory
 *  @return     _Bool  true = in range | false = not in range
 ****************************************************************************************/
_Bool inRange(int token){
    return token <= INT_MAX && token >= INT_MIN;
}


/*
 ****************************************************************************************
 *  @brief      pushs the number to the stack
 *  @param      number being pushed to the memory
 *  @return     int
 ****************************************************************************************/
int push(int token){
    if(!inRange(token)){
        errno = userStackOverFlow;
        return -1;
    }
    if(last + 1 >= STACKSIZE){
        errno = userStackUnderFlow;
        return -1;
    }
    stack[++last] = token;
    return 0;
}


/*
 ****************************************************************************************
 *  @brief      returns the number from the stack 
 *  @param      pointer to the integer of 4 byte value 
 *  @return     int
 ****************************************************************************************/
int pop(int* pToken){
    if(last < 0){
        errno = userStackUnderFlow;
        return -1;
    }
    *pToken = stack[last--]; // at the address of pToken, save the last entry of stack 
    return 0; 
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
    return 0;
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
    return 0;
}
