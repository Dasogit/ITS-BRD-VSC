/**
  ******************************************************************************
  * @file    main.c
  * @author  M. Sohrab Danandeh, Amirhossein Naghashi HAW Hamburg
  * @brief   Kleines Testprogramm fuer neu erstelle Fonts.
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/

#include "display.h"
#include "errorHandler.h"
#include "init.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "fontsFLASH.h"
#include "error.h"
#include "token.h"
#include "token.h"
#include "scanner.h"
#include "evaluateToken.h"


/**
  * @brief  Main program
  * @param  None
  * @retval 0
  */
int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	TP_Init(false);                 // Initialisierung des LCD Boards mit Touch
	if (!checkVersionFlashFonts()) {
	    // Ueberpruefe Version der Fonts im Flash passt nicht zur Software Version
		Error_Handler();
	}
	
	//makeKeyPad();										// KypadGui aufrufen
	initDisplay();									// Initialisierung des Displays
	int result = 0;

	while(1) {
		T_token token = nextToken();
		result = tokenHandler(token);
		if(result != SUCCESS)
		{
			handleError(result);
		}
	}
	return SUCCESS;
}