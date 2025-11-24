#include "fsm.h"
#include "inputHandler.h"
#include <stdbool.h>

//--------------- Phase transition ----------------
#define DELTA_NONE 0
#define DELTA_FORWARD 1
#define DELTA_BACK -1
#define DELTA_ERROR1 2
#define DELTA_ERROR2 -2


static int lastPhase;   // last phase 0..3
static int stepCounter; // signed step count
static int lastDir;     // +1 forward, -1 backward, 0 none
static int curState;

/**
 * @brief init state
 *
 */
void state_init() {
  lastPhase = input_readRaw();
  stepCounter = 0;
  lastDir = 0;
  curState = 0;
}


/**
 * @brief decodes the state from the phases
 *
 * @return int the state we are in
 */
void state_decoder(int currentPhase) {
  int delta = currentPhase - lastPhase;

  if (delta > 2)
    delta -= 4;
  else if (delta < -2)
    delta += 4;
  // lastPhase = currentPhase maybe nach der switch case machen wegen redundanz 

  switch (delta) {
  case DELTA_NONE:
    curState = STATE_NO_ROTATION;
    break;
  case DELTA_FORWARD:
    stepCounter++;
    lastDir = +1;   //wollte ich +=1 oder 1 ??????
    lastPhase = currentPhase;
    curState = STATE_FORWARD;
    break;
  case DELTA_BACK:
    stepCounter--;
    lastDir = -1;
    lastPhase = currentPhase;
    curState = STATE_BACKWARD;
    break;
  case DELTA_ERROR1: // raus nehmen?
  case DELTA_ERROR2:
  default:
    curState = STATE_ERROR;
    break;
  }
}

int set_cur_state_test(){
  return curState = STATE_ERROR;
}

int cur_state(void)
{
  return curState;
}

/**
 * @brief
 *
 * @return int
 */
int last_direction() { return lastDir; }

/**
 * @brief counts the steps
 *
 * @return int steps counter
 */
int step_count() { return stepCounter; }


