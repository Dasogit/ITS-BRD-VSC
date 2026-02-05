/**
 * @file display.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2026-02-04
 *
 * @copyright Copyright (c) 2026
 *
 */
#include "LCD_GUI.h"
#include <stdint.h>

#ifndef _DISPLAY_H
#define _DISPLAY_H

#define RECT_W 30

#define RECT_H 30

#define GAP 10

#define PER_ROW 10

void drawQuadNNumber(COLOR c, Coordinate tl, Coordinate br, uint16_t number);

void clearDisp();
//void reiheDraw();

#endif
// EOP 

