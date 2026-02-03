/**
 ******************************************************************************
 * @file    display.c
 * @author  Franz Korf
 *          HAW-Hamburg
 *          Labor fuer technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.0
 *
 * @date    22. Jan. 2025
 * @brief   Dieses Modul implementiert die LCD Ausgabe der W�rfel.
 ******************************************************************************
 */

#include "display.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "error.h"
#include "main.h"


// Dieses Feld speichert die Positionen der W�rfel. Die Position eines W�rfels
// ist durch seine linke obere und rechte untere Ecke beschrieben.

const struct {
  Coordinate tl;
  Coordinate br;
} dicePosData[NO_DICE] = {
    {.tl = {.x = 382, .y = 40}, .br = {.x = 465, .y = 123}},
    {.tl = {.x = 292, .y = 40}, .br = {.x = 375, .y = 123}},
    {.tl = {.x = 202, .y = 40}, .br = {.x = 285, .y = 123}},
    {.tl = {.x = 112, .y = 40}, .br = {.x = 195, .y = 123}},
    {.tl = {.x = 22, .y = 40}, .br = {.x = 105, .y = 123}}};

// Von der linken oberen Ecke eines W�rfels ausgehend, beschreiben folgende
// Konstanten den Offset der Mittelpunkte der einzelnen Positionen der
// W�rfelaugen / W�rfelpunkte.
//
//           |-------------------------|
//           |                         |
//           |  Pos1             Pos2  |
//           |                         |
//           |  Pos3    Pos4     Pos5  |
//           |                         |
//           |  Pos6             Pos7  |
//           |                         |
//           |-------------------------|

const Coordinate offsetPos1 = {.x = 1 * 21, .y = 1 * 21};
const Coordinate offsetPos2 = {.x = 3 * 21, .y = 1 * 21};
const Coordinate offsetPos3 = {.x = 1 * 21, .y = 2 * 21};
const Coordinate offsetPos4 = {.x = 2 * 21, .y = 2 * 21};
const Coordinate offsetPos5 = {.x = 3 * 21, .y = 2 * 21};
const Coordinate offsetPos6 = {.x = 1 * 21, .y = 3 * 21};
const Coordinate offsetPos7 = {.x = 3 * 21, .y = 3 * 21};

const Coordinate dotCoords[] = { 
	{.x = 1 * 21, .y = 1 * 21},
	{.x = 3 * 21, .y = 1 * 21},
	{.x = 1 * 21, .y = 2 * 21},
	{.x = 2 * 21, .y = 2 * 21},
	{.x = 3 * 21, .y = 2 * 21},
	{.x = 1 * 21, .y = 3 * 21},
	{.x = 3 * 21, .y = 3 * 21},
};

const uint8_t dotDefine[] =
{
	//    7654321
	0b0001000,
	0b0100010,
	0b0101010,
	0b1100011,
	0b1101011,
	0b1110111
};

#define RADIUS_DICE_EYE 6 //

/**
 * @brief Diese Funktion f�llt den ganzen Bildschirm mit blau.
 */
void clearDisplay(void) { GUI_clear(BLUE); }

/**
 * @brief Diese Funktion zeichnet einen W�rfel auf dem Bildschirm.
 *
 * @param  die Die Nummer des W�rfels, die die Position auf dem Bildschirm
 *             festlegt. 0 ist der W�rfel rechts au�en. 4 ist der W�rfel
 *             links au�en.
 * @param  val Der Wert, der auf dem W�rfel dargestellt wird.
 * @param  c   Die Farbe des W�rfels.
 */
void displayDie(uint8_t die, uint8_t value, COLOR c) {
	GUI_drawRectangle(dicePosData[die].tl, dicePosData[die].br, BLUE, true, DOT_PIXEL_1X1);
	GUI_drawRectangle(dicePosData[die].tl, dicePosData[die].br, c, false, DOT_PIXEL_2X2);

	int pattern = dotDefine[value - 1];
	for(int i = 0; i < 7; ++i)
	{
		if(pattern & (1 << i))
		{
			Coordinate pos = {dotCoords[i].x + dicePosData[die].tl.x, dotCoords[i].y + dicePosData[die].tl.y};
			GUI_drawCircle(pos, RADIUS_DICE_EYE, 
				c, true, DOT_PIXEL_1X1);
		}
	}
}
// EOF