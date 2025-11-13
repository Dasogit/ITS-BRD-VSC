/**
  * @file   errorHandler.h
  * @author M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @date  Oct 2025
  * @brief This File is for all Errors for a RPN Calculator
*/

#include "outputHandler.h"
#include "display.h"
#include "errorHandler.h"
#include "stack.h"



// TODO:  KEINE AHNUNG OB ICH ÜBERALL DIE ERRORS ÜBERPRÜFEN MUSS 

/*
 ****************************************************************************************
 *  @brief     integer to string
 *  @param     the number, pointer to character of 8 bit (kinda like a string)
 *  @return    int Error
 ****************************************************************************************/
int intToString(int number, char* pStrArray){ //destination array 
  int i = 0;
  int sign = number;
  if(number == 0){
    pStrArray[i++] = '0';
  }
 // if(number == INT32_MIN){
 //   pStrArray[i++] = (INT32_MIN) ; //-2.147.483.648 
 // }
  if(number < 0){
    number = -number;
  }
  while(number > 0){
    pStrArray[i++] = number % 10 + '0';
    number /= 10;
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
  return SUCCESS;
}


/*
 ****************************************************************************************
 *  @brief     prints the last value/entry on the stack
 *  @param     
 *  @return    int
 ****************************************************************************************/
int printLast (){
  clearStdout();
  char numbers[16]; //length of the terminal of the display
  int i = 0;
  getNumber(getLast(), &i); //take the last number and save its value at the address of i
  intToString(i, numbers); //take the number and turn the array of them to a string basically read from the array
  printStdout(numbers);
  return SUCCESS;
}


/*
 ****************************************************************************************
 *  @brief     print all the value/entries that is on the stack
 *  @param      
 *  @return    int
 ****************************************************************************************/
int printAll(){
  clearStdout();
  int printAllandLast = getLast();                    //cach for the stackpointer     
    char numbers[15];
    int i = 0;
  for( ;printAllandLast >= 0; printAllandLast--){     //for-loop for printing every value/entry of the stack
    getNumber(printAllandLast, &i);
    intToString(i, numbers);
    printStdout(numbers);
    printStdout((char*) newLine);
  }
  return SUCCESS;
}


/*
 ****************************************************************************************
 *  @brief     clears the stack 
 *  @param      
 *  @return    int
 ****************************************************************************************/
int clearAll(){
  setLast(-1);
  clearStdout();
  setNormalMode();
  return SUCCESS;
}

/*
 ****************************************************************************************
 *  @brief     duplicate the last value/entry
 *  @param      
 *  @return    int
 ****************************************************************************************/
int doubleLast(){
  int i = 0;
  getNumber(getLast(), &i);
  push(i);
  return SUCCESS;
}

/*
 ****************************************************************************************
 *  @brief     swaps the last two value/entries
 *  @param      
 *  @return    int
 ****************************************************************************************/
int swapLast(){ 
 int slot1 = 0; 
 int slot2 = 0;
 E(pop(&slot2));
 E(pop(&slot1));
 E(push(slot2));
 E(push(slot1));
 return SUCCESS;
}

