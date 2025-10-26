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
 *  @return    void
 ****************************************************************************************/
void intToString(int, char*);


/*
 ****************************************************************************************
 *  @brief     prints the last value/entry on the stack
 *  @param     
 *  @return    void
 ****************************************************************************************/
void printLast ();


/*
 ****************************************************************************************
 *  @brief     print all the value/entries that is on the stack
 *  @param      
 *  @return    void
 ****************************************************************************************/
void printAll();


/*
 ****************************************************************************************
 *  @brief     clears the stack 
 *  @param      
 *  @return    void
 ****************************************************************************************/
void clearAll();


/*
 ****************************************************************************************
 *  @brief     duplicate the last value/entry
 *  @param      
 *  @return    void
 ****************************************************************************************/
void doubleLast();


/*
 ****************************************************************************************
 *  @brief     swaps the last two value/entries
 *  @param      
 *  @return    void
 ****************************************************************************************/
void swapLast();



#endif
// EOF