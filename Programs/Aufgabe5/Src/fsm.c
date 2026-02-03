/**
 * @file fsm.c
 * @author Danandeh, Naghashi
 * @brief 
 * @version 0.1
 * @date 2026
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#include "fsm.h"

#include "inputHandler.h"
#include <stdbool.h>



int lastPhase;   // last phase 0..3
volatile int stepCounter; // signed step count
volatile int curState;
 

/**
 * @brief init state
 *
 */
void state_init() {
  lastPhase   = input_readRaw();
  stepCounter = 0;
  curState    = 0;
}


/**
 * @brief getter for cur_state 
 * 
 * @return int current state 
 */
int cur_state(void)
{
  return curState;
}


/**
 * @brief counts the steps
 *
 * @return int steps counter
 */
int step_count() 
{ 
  return stepCounter; 
}


