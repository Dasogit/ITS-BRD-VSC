/**
  * @file outputHandler.h
  * @author M. Sohrab Danandeh, HAW Hamburg 
  * @date Oct 2025
  * @brief Handles the output of the program 
*/

#ifndef outputHandler_h
#define outputHandler_h
#include <error.h>
#include "display.h"

/*
 ****************************************************************************************
 *  @brief     integer to string
 *  @param     the number, pointer to character of 8 bit (kinda like a string)
 *  @return    int
 ****************************************************************************************/
int intToString(int, char*);


/*
 ****************************************************************************************
 *  @brief     prints the last value/entry on the stack
 *  @param     
 *  @return    int
 ****************************************************************************************/
int printLast ();


/*
 ****************************************************************************************
 *  @brief     print all the value/entries that is on the stack
 *  @param      
 *  @return    int
 ****************************************************************************************/
int printAll();


/*
 ****************************************************************************************
 *  @brief     clears the stack 
 *  @param      
 *  @return    int
 ****************************************************************************************/
int clearAll();


/*
 ****************************************************************************************
 *  @brief     duplicate the last value/entry
 *  @param      
 *  @return    int
 ****************************************************************************************/
int doubleLast();


/*
 ****************************************************************************************
 *  @brief     swaps the last two value/entries
 *  @param      
 *  @return    int
 ****************************************************************************************/
int swapLast();



#endif
// EOF