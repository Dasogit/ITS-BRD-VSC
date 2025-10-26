/**
  * @file errorHandler.h
  * @author M. Sohrab Danandeh, HAW Hamburg 
  * @date Oct 2025
  * @brief This File is for all Errors for a RPN Calculator
*/

#include "outputHandler.h"
#include "display.h"
#include "stack.h"
#include <errno.h>


/*
 ****************************************************************************************
 *  @brief     integer to string
 *  @param     the number, pointer to character of 8 bit (kinda like a string)
 *  @return    void
 ****************************************************************************************/
void intToString(int number, char* pStrArray){
  int i = 0;
  int sign = number;
  if(number < 0){
    number = -number;
  }
  while(number > 0){
    pStrArray[i++] = number % 10 + '0';
  }
  if(sign < 0){
    pStrArray[i++] = '-';
  }
  pStrArray[i] = '\0';
  // Reverse the string to get the correct order
  for(int j = 0 , k = i -1 ; j < k ; j++ , k--){
    char tmp = pStrArray[j];
    pStrArray[j] = pStrArray[k];
    pStrArray[k] = tmp;
  }
}


/*
 ****************************************************************************************
 *  @brief     prints the last value/entry on the stack
 *  @param     
 *  @return    void
 ****************************************************************************************/
void printLast (){
  clearStdout();
  char numbers[15]; //length of the terminal of the display
  int i = 0;
  getNumber(getLast(), &i); //take the last number and save its value at the address of i
  intToString(i, numbers); //take the number and turn the array of them to a string basically read from the array
  printStdout((char *) &numbers);
}


/*
 ****************************************************************************************
 *  @brief     print all the value/entries that is on the stack
 *  @param      
 *  @return    void
 ****************************************************************************************/
void printAll(){
  clearStdout();
  int printAllandLast = getLast();                    //cach for the stackpointer     
    char numbers[15];
    int i = 0;
  for(; printAllandLast >= 0; printAllandLast--){     //for-loop for printing every value/entry of the stack
    getNumber(printAllandLast, &i);
    intToString(i, numbers);
    //printStdout((char*) &numbers);
    printStdout(numbers);
  }
}


/*
 ****************************************************************************************
 *  @brief     clears the stack 
 *  @param      
 *  @return    void
 ****************************************************************************************/
void clearAll(){
  setLast(-1);
  errno = 0;
  clearStdout();
  setNormalMode();
}

/*
 ****************************************************************************************
 *  @brief     duplicate the last value/entry
 *  @param      
 *  @return    void
 ****************************************************************************************/
void doubleLast(){
  int i = 0;
  getNumber(getLast(), &i);
  push(i);
}

/*
 ****************************************************************************************
 *  @brief     swaps the last two value/entries
 *  @param      
 *  @return    void
 ****************************************************************************************/
void swapLast(){
 int slot1 = 0;
 int slot2 = 0;
 pop(&slot2);
 pop(&slot1);
 push(slot2);
 push(slot1); 
}

