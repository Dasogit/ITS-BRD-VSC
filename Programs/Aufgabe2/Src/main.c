/**
  ******************************************************************************
  * @file    main.c
  * @author  Franz Korf
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */



/* Includes ------------------------------------------------------------------*/
#include "calc.h"
#include "inputHandler.h"
#include "stm32f4xx_hal.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include <stdint.h>
#include <timer.h>
#include "outputHandler.h"
#include "fsm.h"



int main(void) {
	initITSboard();    // Initialisierung des ITS Boards
	
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch

	//init 
	initTimer();
	printInit();
	state_init();
	double my_speed = 0.0, my_angle = 0.0;

	while(1) {
		uint32_t now = getTimeStamp();
		int phaseNow = input_readRaw(); // 0..3
		state_decoder(phaseNow);
		//set_cur_state_test();
		my_angle = angle_calc();
		my_speed = speed_calc(now, my_angle);

		outputLoop(my_angle, my_speed);
		led_handler_status();
		led_handler_movement();
		led_Error_Off();
	}
}

// EOF
