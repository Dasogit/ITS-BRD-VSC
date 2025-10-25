/**
  * @file errorHandler.h
  * @author M. Sohrab Danandeh, HAW Hamburg 
  * @date Oct 2025
  * @brief Errors definitions for a RPN Calculator
*/

#ifndef errorHandler_h
#define errorHandler_h

//#include "display.h"

//initialise error
#define INIT -2   
//stackoverflow error from the user    
#define userStackOverFlow -3
//stackunderflow error from the user
#define userStackUnderFlow -4
//invalid input (is not possible due to GUI but it is still a case)
#define userInvalidInput -5
//denominator error divided by zero (can also return sqr(-1) aka. i aka. imaginary number. depends on the choice of the dev)
#define userDivideByZero -6
//an error that isnt covered by the expected cases (probabbly useless)
#define userUnknownError -7
//data type overflow ??
#define userOverRange -8
//data type underflow ??
#define userUnderRange -9  
//not sure tbh if its usefull
#define userArithmeticOverflow -10
//not sure tbh if its usefull
#define userArithemticUnderflow -11
//im not still sure how many of these we need but assumption is 6. more will be evaluated


#define STACKUNDERMSG "STACKUNDERFLOW"
#define STACKOVERMSG "STACKOVERFLOW"
#define DOMMSG "ARITHMETIC ERROR"
#define ARTUNDERMSG "ARITHMETIC UNDERFLOW"
#define ARTOVERMSG "ARITHMETIC OVERFLOW"


void handleError(int);

#endif

// EOF   
