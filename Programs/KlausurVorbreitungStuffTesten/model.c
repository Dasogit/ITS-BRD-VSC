/**
 * @file model.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "model.h"
#include "LCD_GUI.h"
#include "init.h"
#include "io.h"
#include "display.h"
#include <string.h>

//            s0 red  s1 blue   s2 green
int dauer [3] = {0,0,0};

void model_init(void) { initITSboard(); }

void model_on_button_event(uint8_t pressedMask) {
  switch (pressedMask) {
    case CMD_RED:
        num
        break;
    case CMD_BLUE:
        drawQuadNNumber(BLUE, Coordinate tl, Coordinate br);
        break;
    case CMD_Green:
        drawQuadNNumber(GREEN, Coordinate tl, Coordinate br);
    default:
        break;
   }
}

bool model_s7(void){
    if(getButton() == 7){
        memset(dauer, 0, sizeof(dauer));
    }
    return true;
}
bool model_nextDraw(DrawCMD *cmd, uint16_t *number);
void model_clears7(){
    clearDisp();

}
