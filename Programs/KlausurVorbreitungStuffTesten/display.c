/**
 * @file display.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "display.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "error.h"
#include "fonts.h"
#include "io.h"
#include <stdint.h>

const struct{ Coordinate tl;  Coordinate bl;} quadc;

int32_t quadNumber(int button){
    return buttonEntprellen(button);
}

void drawQuadNNumber(COLOR c,Coordinate tl, Coordinate br ){
    Coordinate tm = {tl.x /2 , tl.y/2};
    GUI_disNum(tm, quadNumber(getButton()), &Font16, c, BLACK);
    GUI_drawRectangle(tl, br, getButton(), true ,DOT_PIXEL_5X5);
}

void clearDisp(){
    GUI_clear(WHITE);
}

/* 
void reiheDice(COLOR c,bool filled, DOT_PIXEL lineWeight){
    for(int i = 0 ; i < PER_ROW; i++){
        Coordinate tl = {tl.x + (RECT_W * i) + GAP , tl.y};
        Coordinate br = {br.x, br.y + (RECT_H * i) + GAP};
        drawQuadNNumber(c, tl,  br);
    }
}
 */