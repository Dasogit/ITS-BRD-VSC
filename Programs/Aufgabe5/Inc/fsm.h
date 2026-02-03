/**
 * @file   fsm.h
 * @author Danandeh, Naghashi
 * @brief 
 * @version 0.1
 * @date 2026
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef fsm_h
#define fsm_h

#include <stdbool.h>



/* IMPORTANT READ ME:
 * Future optimization:
 * Encoder direction can also be computed with a 16-entry Gray-code
 * transition table using key = (old << 2) | new. For this Praktikum
 * we use the simpler index-difference method for readability.
 */

//------------  EVENT of the STATE --------------
#define STATE_NO_ROTATION  0
#define STATE_FORWARD      1
#define STATE_BACKWARD     2
#define STATE_ERROR        3

//--------------- Phase transition ----------------
#define DELTA_NONE    0
#define DELTA_FORWARD 1
#define DELTA_BACK   -1
#define DELTA_ERROR1  2
#define DELTA_ERROR2 -2


extern int lastPhase;   // last phase 0..3
volatile extern int stepCounter; // signed step count
volatile extern int curState;

/**
 * @brief init state of fsm
 * @return int 
 */
void state_init(void);


/**
 * @brief decodes the state from the phases
 *
 * @return int the state we are in
 */
static inline void state_decoder(int currentPhase) {
  int delta = currentPhase - lastPhase;

  if (delta > 2)
    delta -= 4;
  else if (delta < -2)
    delta += 4;
  // lastPhase = currentPhase maybe nach der switch case machen wegen redundanz 

  switch (delta) {
  case DELTA_NONE:
    curState  = STATE_NO_ROTATION;
    break;
  case DELTA_FORWARD:
    stepCounter++;
    lastPhase = currentPhase;
    curState  = STATE_FORWARD;
    break;
  case DELTA_BACK:
    stepCounter--;
    lastPhase = currentPhase;
    curState  = STATE_BACKWARD;
    break;
  case DELTA_ERROR1: // raus nehmen?
  case DELTA_ERROR2:
  default:
    curState  = STATE_ERROR;
    break;
  }
}


/**
 * @brief 
 * 
 * @return int 
 */
int cur_state(void);

/**
 * @brief last direction of the rotation
 * @return int 
 */
int last_direction();


/**
 * @brief count the steps slits 
 * @return int 
 */
int step_count();

#endif