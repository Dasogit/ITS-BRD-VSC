/**
 * @file   fsm.h
 * @author Danandeh, Naghashi
 * @brief 
 * @version 0.1
 * @date 2025-11-14
 * 
 * @copyright Copyright (c) 2025
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


/**
 * @brief init state of fsm
 * @return int 
 */
void state_init(void);


/**
 * @brief 
 * 
 * @param code 
 * @return int 
 */
void state_decoder(int currentPhase);

/**
 * @brief Set the cur state test object
 * 
 * @return int 
 */
int set_cur_state_test();


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