/**
 ******************************************************************************
 * @file    TFT_board.c
 * @author  XXX
 *
 * @date    3. Feb. 2023
 *
 * @brief   Darstellung des TicTacToe Boards auf dem TFT Display des ITS Boards.
 *
 ******************************************************************************
 */

#include "TFT_board.h"
#include "LCD_Demos.h"
#include "LCD_GUI.h"
#include "LCD_Touch.h"
#include "LCD_general.h"

#define COLOR_BG GRAY    // Hintergrundfarbe
#define COLOR_LINE BLACK // Farbe der Trennlinien des Spielfelds
#define COLOR_SP1 GREEN  // Farbe der runden Spielsteine
#define COLOR_SP2 BLUE   // Farbe der quadratischen Spielsteine

#define ZB 5    // Breite einer Trennlinie
#define QKL 101 // Kantenlaenge des Quadrats eines Felds des Spielbretts
#define ZL (3 * QKL + 2 * ZB) // Laenge einer Trennlinie des Spielfelds

#define U_X 83
#define U_Y 3

typedef struct {
  Coordinate topLeft;
  Coordinate bottomRight;
} Rectangle;

// Die vier Trennlinien werden als Rechtecke dargestellt.
// Das folgende Feld enthaelt die Koordinaten dieser Rechtecke.
static Rectangle line[] = {
    {.topLeft = {.x = U_X, .y = U_Y + QKL},
     .bottomRight = {.x = U_X + ZL, .y = U_Y + QKL + ZB}},
    {.topLeft = {.x = U_X, .y = U_Y + ZB + 2 * QKL},
     .bottomRight = {.x = U_X + ZL, .y = U_Y + ZB + 2 * QKL + ZB}},
    {.topLeft = {.x = U_X + QKL, .y = U_Y},
     .bottomRight = {.x = U_X + QKL + ZB, .y = U_Y + ZL}},
    {.topLeft = {.x = U_X + ZB + 2 * QKL, .y = U_Y},
     .bottomRight = {.x = U_X + ZB + 2 * QKL + ZB, .y = U_Y + ZL}}};

// Die Mittelpunkte der 9 Felder des Spielbretts
static Coordinate mp[] = {
    {.x = U_X + QKL / 2 + 1, .y = U_Y + QKL / 2 + 1},
    {.x = U_X + QKL / 2 + 1, .y = U_Y + (QKL + ZB) + QKL / 2 + 1},
    {.x = U_X + QKL / 2 + 1, .y = U_Y + 2 * (QKL + ZB) + QKL / 2 + 1},

    {.x = U_X + (QKL + ZB) + QKL / 2 + 1, .y = U_Y + QKL / 2 + 1},
    {.x = U_X + (QKL + ZB) + QKL / 2 + 1, .y = U_Y + (QKL + ZB) + QKL / 2 + 1},
    {.x = U_X + (QKL + ZB) + QKL / 2 + 1,
     .y = U_Y + 2 * (QKL + ZB) + QKL / 2 + 1},

    {.x = U_X + 2 * (QKL + ZB) + QKL / 2 + 1, .y = U_Y + QKL / 2 + 1},
    {.x = U_X + 2 * (QKL + ZB) + QKL / 2 + 1,
     .y = U_Y + (QKL + ZB) + QKL / 2 + 1},
    {.x = U_X + 2 * (QKL + ZB) + QKL / 2 + 1,
     .y = U_Y + 2 * (QKL + ZB) + QKL / 2 + 1}};

/**
 * @brief  Diese Funktion loescht den Bildschirm und zeichnet ein leeres
 * Spielbrett. Es besteht aus den vier Linien, die das Spielbrett in 9 Felder
 * unterteilen. Die Mittelpunkte der 9 Spielfelder werden mit einem 3x3 Pixel
 * Punkt gekennzeichnet.
 *
 * @retval none
 */
void drawNewBoard(void) {
  GUI_clear(GRAY);
  for (int i = 0; i < 4; i++) {
    GUI_drawRectangle(line[i].topLeft, line[i].bottomRight, BLACK, false,
                      DOT_PIXEL_3X3);
  }
  for (int i = 0; i < 9; i++) {
    GUI_drawPoint(mp[i], BLACK, DOT_PIXEL_3X3, DOT_FILL_AROUND);
  }
}

/**
 * @brief  Diese Funktion zeichnet einen gruenen Kreis auf ein Feld des
 * Spielbretts.
 *
 * @param  pos Nummer des Felds des Spielbretts, auf das der gruene Kreis
 * gezeichnet wird.
 * @retval none
 */
void drawCycle(int pos) { GUI_drawCircle(mp[pos], QKL / 2, GREEN, true, 1); }

/**
 * @brief  Diese Funktion zeichnet ein blaues Quadrat auf ein Feld des
 * Spielbretts.
 *
 * @param  pos Nummer des Felds des Spielbretts, auf das das blaue Quadart
 * gezeichnet wird.
 * @retval none
 */
void drawQuad(int pos) {
  Coordinate tl = {.x = mp[pos].x - 40, .y = mp[pos].y - 40};
  Coordinate br = {.x = mp[pos].x + 40, .y = mp[pos].y + 40};
  GUI_drawRectangle(tl, br, BLUE, true, 1);
}

int pointInRect(Coordinate p, Coordinate c, int size) {
  return (p.x >= c.x - size && p.y >= c.y - size && p.x < c.x + size &&
          p.y < c.y + size);
}

/**
 * @brief  Diese Funktion ueberprueft, ob gerade auf ein Feld des Spielfelds
 * gedrueckt wird.
 *
 * @retval Falls gerade auf ein Feld des Spielbretts gedrueckt wird, die Nummer
 * des Felds. Ansonsten -1 (z.B. Es wird nicht auf das LCD gedrueckt oder die
 * Koordinate des aktuellen Druckpunkts kann keinem Feld des Spielbretts
 * eindeutig zugeordnet werden.)
 */
int getTouch(void) {
  if (!TP_pressed()) {
    return -1;
  }
  Coordinate c = TP_get();
  if (!VALID_COORDINATE(c))
    return -1;

  for (int i = 0; i < 9; ++i) {
    if (pointInRect(c, mp[i], QKL / 2)) {
      return i;
    }
  }

  return -1;

#if 0

    // 1. Check if the touch is actually inside the board boundaries
    if (c.x < U_X || c.x > (U_X + ZL) || c.y < U_Y || c.y > (U_Y + ZL)) {
        return -1; 
    }
    // deltas
    int dx = c.x - U_X;
    int dy = c.y - U_Y;

    // 2. Calculate column (0, 1, or 2) and row (0, 1, or 2)
    int colIndex = dx / (QKL + ZB);
    int rowIndex = dy / (QKL + ZB);
    //linien 
    int colOffset = dx % (QKL + ZB);
    int rowOffset = dy % (QKL + ZB);
    // lininencheck 
    
    if(colOffset >= QKL || rowOffset >= QKL){
        return -1;
    }
    // 3. Convert row/col to the index (0-8)
    // This matches the order in your mp[] array (column-major based on your code)
    return (colIndex * 3) + rowIndex;
#endif
}

// EOF
