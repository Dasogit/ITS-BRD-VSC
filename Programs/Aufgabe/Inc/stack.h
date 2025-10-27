/**
  * @file stack.h
  * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @date   Oct 2025
  * @brief functions to R/W/O to/from the stack memory
*/

#ifndef stack_h
#define stack_h
#define STACKSIZE 10
#include <errorHandler.h>
#include <limits.h>


/*
 ****************************************************************************************
 *  @brief      checks if the number being pushed to the memory is in range of the memory
 *  @param      number being pushed on the memory
 *  @return     _Bool  true = in range | false = not in range
 ****************************************************************************************/
_Bool inRange(int);


/*
 ****************************************************************************************
 *  @brief      pushs the number to the stack
 *  @param      number being pushed to the memory
 *  @return     int
 ****************************************************************************************/
int push(int);


/*
 ****************************************************************************************
 *  @brief      returns the number from the stack 
 *  @param      pointer to the integer of 4 byte value 
 *  @return     int
 ****************************************************************************************/
int pop(int*);


/*
 ****************************************************************************************
 *  @brief      reads the last value/entry that was pushed to the stack (LiFo)
 *  @param      
 *  @return     int
 ****************************************************************************************/
int getLast();


/*
 ****************************************************************************************
 *  @brief      sets the last value/entry that is on stack (cutting the line)
 *  @param      number to be set to
 *  @return     void
 ****************************************************************************************/
void setLast(int);


/*
 ****************************************************************************************
 *  @brief      gets the number where the pointer to integer of 4 byte value is pointing to
 *  @param      number to get , pointer to the integer of 4 byte value (referencing the number)
 *  @return     int
 ****************************************************************************************/
int getNumber(int, int*);


/*
 ****************************************************************************************
 *  @brief      gets the stack size
 *  @param      none
 *  @return     int 
 ****************************************************************************************/
int getStackSize();


/*
 ****************************************************************************************
 *  @brief      clears the stack
 *  @return     int 
 ****************************************************************************************/
int clearStack();


#endif 
// EOF