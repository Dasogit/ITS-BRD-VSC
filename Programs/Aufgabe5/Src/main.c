/**
 ******************************************************************************
 * @file    main.c
 * @author  Franz Korf
 * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "calc.h"
#include "fsm.h"
#include "init.h"
#include "inputHandler.h"
#include "myoutputHandler.h"
#include <stdint.h>
#include <timer.h>
#include "isr.h"

int main(void) {
  initITSboard(); // Initialisierung des ITS Boards

  GUI_init(DEFAULT_BRIGHTNESS); // Initialisierung des LCD Boards mit Touch
  TP_Init(false);               // Initialisierung des LCD Boards mit Touch

  // init
  initTimer();
  printInit();
  state_init();
  initISR();

  double my_speed = 0.0, my_angle = 0.0;

  // GPIOE->BSRR =  (0x01U << 5) ;
  while (1) {
    int counter = 0;
    uint32_t timestamp = 0;
    uint32_t ts = getTimeStamp();
    getCounterAndTimestamp(&counter, &timestamp);

    while (cur_state() == STATE_ERROR) {
      led_handler_status();
      if (getButton()) {
        GPIOE->BSRR = BSRR_MASK_D21 << 16;
        state_init();
        break;
      }
    }

    my_angle = angle_calc(counter);

    if((ts - timestamp) > 1000 * 1000 * TICKS_PER_US)
    {
      my_speed = 0;
    }
    else {
      my_speed = speed_calc(timestamp, my_angle);
    }

    outputLoop(my_angle, my_speed);
    led_handler_status();
    led_handler_movement();
  }
}

// EOF
