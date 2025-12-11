/**
 * @file decoder.C
 * @author your name (you@domain.com)
 * @brief decodes the RLE 8 bit per pixel and uses the Color pallete
 * @version 0.1
 * @date 2025-12-03
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "decoder.h"
#include "BMP_types.h"
#include "LCD_GUI.h"
#include "LCD_general.h"
#include "errorhandler.h"
#include "input.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

#define USE_GUI_WRITELINE   1 // 0 = Punktweise (Aufgabe a), 1 = WriteLine (Aufgabe b)
#define MAX_SRC_WIDTH   (LCD_WIDTH * 5)
#define MAX_SCALE_FACTOR    5
#define MAX_BOX_SIZE        5
static RGBQUAD myPalett[MAX_COLOR_TABLE_SIZE];

#if USE_GUI_WRITELINE
static COLOR lineBuf[LCD_WIDTH]; // Zeilenpuffer
static int imgWidthClipped;      // tatsächliche Breite für WriteLine(min(Bildbreite, LCD_WIDTHidth))
#endif

static bool  gScaleMode = false;
static int   gSrcWidth  = 0;
static int   gSrcHeight = 0;
static int   gOutWidth  = 0;
static int   gOutHeight = 0;
static int   gBoxWidth  = 1;
static int   gBoxHeight = 1;
static COLOR gSrcBuf[MAX_BOX_SIZE][MAX_SRC_WIDTH];
static COLOR gOutLine[LCD_WIDTH];
static int   gRowCount  = 0;       // wie viele Zeilen bisher eingelesen

/**
 * @brief Draws one pixel and cuts everything that is outside of 480x320 and
 * then calls GUI_drawPoint()
 *
 * @param x
 * @param y
 * @param color
 */
static void putPixelClipped(int x, int y, uint16_t color) {
  if (x < 0 || x >= LCD_WIDTH || y < 0 || y >= LCD_HEIGHT)
    return;

  Coordinate crd = {x, y};
  GUI_drawPoint(crd, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
}

/**
 * @brief Get the Color From Palette object (RGB565 color) from the BMP (8 bit
 * indexed BMPS)
 * @param index
 * @return uint16_t
 */
static COLOR getColorFromPalette(uint8_t index) {
  RGBQUAD color = myPalett[index];
  return (COLOR)(((color.rgbRed >> 3) << 11) | ((color.rgbGreen >> 2) << 5) |
                 color.rgbBlue >> 3);
}


static void emitPixelNormal(int x, int y, uint8_t colorIndex) {
#if USE_GUI_WRITELINE
  // schnelle Variante: in Zeilenpuffer schreiben
  if (x < 0 || x >= LCD_WIDTH || y < 0 || y >= LCD_HEIGHT)
    return;
  if (x >= imgWidthClipped)
    return; // nicht mehr als Bildbreite
  lineBuf[x] = getColorFromPalette(colorIndex);
#else
  // langsame Variante: direkt zeichnen
  putPixelClipped(x, y, getColorFromPalette(colorIndex));
#endif
}

static void endOfLineNormal(int y) {
#if USE_GUI_WRITELINE
  if (y < 0 || y >= LCD_HEIGHT)
    return;
  Coordinate crd = {0, y};
  GUI_WriteLine(crd, imgWidthClipped, lineBuf);
  // lineBuf wird in der nächsten Zeile einfach überschrieben
#endif
}

static void scaledEmitPixel(int x, int y, uint8_t colorIndex) {
  if (x < 0 || x >= MAX_SRC_WIDTH)
    return;

  int srcYTop = gSrcHeight - 1 - y; // 0..H-1 von oben gezählt
  if (srcYTop < 0 || srcYTop >= gSrcHeight)
    return;

  int row = srcYTop % gBoxHeight; // Ringbufferindex
  gSrcBuf[row][x] = getColorFromPalette(colorIndex);
}

/* static void scaledEndOfLine(int yBottomUp) {
  int srcY = gSrcHeight - 1 - yBottomUp; // 0..H-1 von oben gezählt

  if (((srcY % gBoxHeight) != gBoxHeight - 1) && (srcY != gSrcHeight - 1)) {
    return; // noch nicht genug Zeilen für eine Box
  }

  int dstY = srcY / gBoxHeight;
  if (dstY >= gOutHeight)
    return;

  for (int dstX = 0; dstX < gOutWidth; dstX++) {
    int xStart = dstX * gBoxWidth;
    int xEnd = xStart + gBoxWidth - 1;
    if (xEnd >= gSrcWidth)
      xEnd = gSrcWidth - 1;

    int yStart = srcY - gBoxHeight + 1;
    if (yStart < 0)
      yStart = 0;
    int yEnd = srcY;
    if (yEnd >= gSrcHeight)
      yEnd = gSrcHeight - 1;

    gOutLine[dstX] = averageBox(xStart, xEnd, yStart, yEnd);
  }

  Coordinate crd = {0, dstY};
  GUI_WriteLine(crd, gOutWidth, outLine);
}
 */
static void processPixel(int x, int y, uint8_t colorIndex) {
  if (gScaleMode) {
    scaledEmitPixel(x, y, colorIndex);
  } else {
    emitPixelNormal(x, y, colorIndex);
  }
}

static void processEndOfLine(int y) {
  if (gScaleMode) {
    //scaledEndOfLine(y);
  } else {
    endOfLineNormal(y);
  }
}



static void initScaling(const BITMAPINFOHEADER *info)
{
    gSrcWidth  = info->biWidth;
    gSrcHeight = info->biHeight;

    // Skalierungsfaktor bestimmen
    double sx = (double)LCD_WIDTH  / gSrcWidth;
    double sy = (double)LCD_HEIGHT / gSrcHeight;
    double s  = (sx < sy) ? sx : sy;

    // Grenzen 1 .. 1/5
    if (s > 1.0) s = 1.0;
    if (s < 1.0 / MAX_SCALE_FACTOR) s = 1.0 / MAX_SCALE_FACTOR;

    gBoxWidth  = (int)ceil(1.0 / s);
    gBoxHeight = (int)ceil(1.0 / s);

    gOutWidth  = LCD_WIDTH;
    gOutHeight = LCD_HEIGHT;

    gRowCount = 0;
}


/**
 * @brief core function to proccess the RLE blocks (8-bit RLE). takes data from
 * nextChar() from input.c interprets the Run length and escape codes end of
 * line end of bitmap etc.
 *
 * @param infoHdr
 * @return int
 */
static int decodeRLE8(const BITMAPINFOHEADER *infoHdr) {
  int height = infoHdr->biHeight;
  int width = infoHdr->biWidth;

#if USE_GUI_WRITELINE
  imgWidthClipped = (width > LCD_WIDTH) ? LCD_WIDTH : width;
#endif

  int x = 0;
  int y = height - 1; // BMP is Bottom-up

  while (1) {
    int c = nextChar(); // 1 byte
    int v = nextChar(); // 2 byte
    if (c == EOF || v == EOF) {
      return NOK; // oder Fehlerhandler
    }
    uint8_t count = (uint8_t)c;
    uint8_t value = (uint8_t)v;

    /**
        * Bedeutung: „Wiederhole den Pixel mit Index value genau count-mal in
       der aktuellen Zeile.“ Für i = 0..count-1:     Pixel ausgeben (x,y) mit
       colorIndex = value x um 1 erhöhen Du musst darauf achten, dass x nicht
       über width hinausläuft (falls das BMP fehlerhaft ist → Fehler behandeln).
        */
    if (count > 0) { // encoded mode

      for (int i = 0; i < count; i++) {
        // pixel ausgeben mit (x,y) mit colorIndex = value danach x um 1 erhöhen
        // x nicht über width hinauslaufen
        processPixel(x, y, value);
        x++;
      }
    } else { // Escape mode/ control mode aka non Encoded mode
      switch (value) {
      case 0: // End of Line (EOL)
        processEndOfLine(y);
        x = 0;
        y--;
        break;
      case 1: // End of Bitmap (EOB)
        // pic is finished
        processEndOfLine(y);
        return EOK;
      case 2: {
        int dx = nextChar();
        int dy = nextChar();

        if (dx == EOF || dy == EOF)
          return NOK;
        x += (uint8_t)dx;
        y -= (uint8_t)dy; // bottom-up
        break;
      }
      default: // absolute mode
        // read value single byte
        // ausgeben für jedes pixel aus (x,y) und erhöhst x
        for (int i = 0; i < value; i++) {
          // pixel ausgeben mit (x,y) mit colorIndex = value danach x um 1
          // erhöhen x nicht über width hinauslaufen
          int b = nextChar();
          if (b == EOF)
            return NOK;
          processPixel(x, y, (uint8_t)b);
          x++;
        }
        // wenn value ungerade dann kommt ein Padding byte das wir lesen aber
        // ignorieren
        if (value & 1) {
          if (nextChar() == EOF)
            return NOK;
        }
        break;
      }
    }
  }
}

/**
 * @brief looks up at the Color table directly after the header (BMP 256 colors
 * -> 256 x 4 byte palette entry)
 *
 */
static int loadColorPalette(const BITMAPINFOHEADER *infoHdr) {
  int palleteSize = (infoHdr->biClrUsed == 0) ? 256 : infoHdr->biClrUsed;
  COMread((char *)myPalett, sizeof(RGBQUAD),
          palleteSize); // because we know exactly how many bytes and how big
                        // our structure is

  return palleteSize;
}

/**
 * @brief main function to call to do all the functions of decoding
 *
 * @param fileHdr
 * @param infoHdr
 * @return int
 */
int decodeAndDisplayRLE(const BITMAPFILEHEADER *fileHdr,const BITMAPINFOHEADER *infoHdr) {
  if (infoHdr->biCompression != BI_RLE8 || infoHdr->biBitCount != 8) {
    return ERR_HANDLER(true, "decodeAndDisplayRLE: Unsupported BMP format.");
  }
  int paletteSize = loadColorPalette(infoHdr);
  if (paletteSize <= 0) {
    return NOK;
  }
  gScaleMode = false; // wichtig
#if USE_GUI_WRITELINE
  imgWidthClipped =
      (infoHdr->biWidth > LCD_WIDTH) ? LCD_WIDTH : infoHdr->biWidth;
#endif
  return decodeRLE8(infoHdr);
}


int displayScaledRLE(const BITMAPFILEHEADER *fileHdr,const BITMAPINFOHEADER *infoHdr) {
    (void)fileHdr;

    if (infoHdr->biCompression != BI_RLE8 || infoHdr->biBitCount != 8) {
        return ERR_HANDLER(true, "displayScaledRLE: Unsupported BMP format.");
    }

    if (infoHdr->biWidth > MAX_SRC_WIDTH ||
        infoHdr->biHeight > LCD_HEIGHT * MAX_SCALE_FACTOR) {
        return ERR_HANDLER(true, "displayScaledRLE: image too large.");
    }

    int paletteSize = loadColorPalette(infoHdr);
    if (paletteSize <= 0) {
        return NOK;
    }

    initScaling(infoHdr);   // setzt gSrcWidth/Height, gBoxWidth/Height, gOutWidth/Height

    gScaleMode = true;      // jetzt Scaling-Backend benutzen
    int res = decodeRLE8(infoHdr);
    gScaleMode = false;     // zur Sicherheit wieder zurück
    return res;
}

// int aufgabeC(const BITMAPFILEHEADER *fileHdr, const BITMAPINFOHEADER *infoHdr) {
//   // array[][5]
//   // array2[][]
//   // if fileHdr && infoHdr > kirekhar
//   //     for loop posX{0 ; 5}
//   //         mittelwert(inputa)
//   //         save in array2
//   // return array2

//   if (infoHdr->biWidth <= LCD_WIDTH && infoHdr->biHeight <= LCD_HEIGHT) {
//     // kein Scaling nötig → normale RLE-Darstellung
//   } else {
//     // Scaling-Variante
//   }
// }

// int decodeAndDisplayRLE(const BITMAPFILEHEADER *fileHdr,const
// BITMAPINFOHEADER *infoHdr) {
//     if (infoHdr->biCompression == BI_RLE8) {
//         int palleteSize = loadColorPalette(infoHdr);
//         /*int padding = fileHdr->bfOffBits - sizeof(BITMAPFILEHEADER) -
//         sizeof(BITMAPINFOHEADER) - palleteSize * sizeof(RGBQUAD); for(int i =
//         0; i < padding; i++)
//         {
//             nextChar();
//         }*/

//         return decodeRLE8(infoHdr);
//     }

//     return EOK;
// }
