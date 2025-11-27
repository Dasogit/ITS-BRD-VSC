/**
 * @file    outputHandler.c
 * @author  Danandeh, Naghashi
 * @brief
 * @version 3
 * @date 2025-11-26
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "outputHandler.h"
#include <main.h>
#include <stdbool.h>
#include <stdio.h>
#include "fsm.h"
#include "inputHandler.h"
#include "lcd.h"
#include "stm32f429xx.h"

#define OUTPUT_LEN 10

//------------- OLD AND NEW ANGLE AND SPEED ---------------
static char b_angle_old[OUTPUT_LEN];
static char b_speed_old[OUTPUT_LEN];

static char b_angle[OUTPUT_LEN];
static char b_speed[OUTPUT_LEN];

static int i_speed = 0, i_angle = 0;

//------------------ NO MAGIC NUMBERS LCD POSITION ----------------
#define X_ANGLE 16
#define Y_ANGLE 1

#define X_SPEED 16
#define Y_SPEED 4

/**
 * @brief init of the stuff printed on the display
 */
void printInit() {
  lcdGotoXY(1, Y_SPEED);
  lcdPrintlnS("Angle Speed:");
  lcdGotoXY(1, Y_ANGLE);
  lcdPrintlnS("Angle:");
}

/**
 * @brief looks up the current angle
 *
 * @param input from inputHandler
 */
void current_angle_change(double angle) {
  if(i_angle == 0)
  {
    snprintf(b_angle, sizeof(b_angle), "%9.2f", angle);
  }

  if(b_angle[i_angle] != b_angle_old[i_angle])
  {
    b_angle_old[i_angle] = b_angle[i_angle];
    lcdGotoXY(i_angle + X_ANGLE, Y_ANGLE);
    lcdPrintC(b_angle[i_angle]);
  }

  ++i_angle;
  if(i_angle == OUTPUT_LEN - 1)
  {
    i_angle = 0;
  }
}

/**
 * @brief looks up the current angle speed
 *
 * @param input from inputHandler
 */
void current_angle_speed_check(double speed) {
  if(i_speed == 0)
  {
    snprintf(b_speed, sizeof(b_speed), "%9.2f", speed);
  }

  if(b_speed[i_speed] != b_speed_old[i_speed])
  {
    b_speed_old[i_speed] = b_speed[i_speed];
    lcdGotoXY(i_speed + X_SPEED, Y_SPEED);
    lcdPrintC(b_speed[i_speed]);
  }

  ++i_speed;
  if(i_speed == OUTPUT_LEN - 1)
  {
    i_speed = 0;
  }
}


/**
 * @brief handles the leds on/off
 *
 * @param leds
 */
void led_handler_status(void)
{
  int on = 0;
  int off = 0;
  switch (cur_state()) {
    case STATE_FORWARD:
      on = BSRR_MASK_D23;
      off = BSRR_MASK_D21 | BSRR_MASK_D22;
      break;
    case STATE_BACKWARD:
      on = BSRR_MASK_D22;
      off = BSRR_MASK_D21 | BSRR_MASK_D23;
      break;
     case STATE_ERROR:
      on = BSRR_MASK_D21;
      off = BSRR_MASK_D22 | BSRR_MASK_D23;
      break; 
    default:
      break;
  }

  GPIOE->BSRR = on | (off << 16);
}

/**
 * @brief 
 * 
 */
void led_handler_movement(void)
{
  GPIOD->BSRR = 0xFF << 16;
  GPIOD->BSRR = step_count() & 0xFF;
}


/**
 * @brief 
 * 
 */
void led_Error_Off(){
  if(getButton()){
    GPIOE->BSRR = BSRR_MASK_D21 << 16;
  }
}



/**
 * @brief prints one char per loop
 *
 */
void outputLoop(double my_angle, double my_speed) {
	current_angle_change(my_angle);
	current_angle_speed_check(my_speed); 
}

/********************* MY CODE DUMP ****************** 


*  @brief SOLLEN WIR LIEBER FÜR DIE AUFGABE NICHT NUTZEN 
*
* void leds_show_step_count(int stepCounter)
* {
*    uint8_t lower8 = (uint8_t) stepCounter; // low 8 bits
*
*    // Clear PD0–PD7, then set according to lower8
*    uint32_t odr = GPIOD->ODR;
*    odr &= ~0xFFu;           // clear bits 0..7
*    odr |= lower8;           // set new pattern
*    GPIOD->ODR = odr;
* }
*
*
*/
