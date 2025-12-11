/**
 * @file decoder.C
 * @author Naghashi, Danandeh
 * @brief decodes the RLE 8 bit per pixel and uses the Color palettee
 * @version 0.4
 * @date 2025-12-11
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
#define MAX_SRC_WIDTH (LCD_WIDTH * 5)
#define MAX_SCALE_FACTOR    5
#define MAX_BOX_SIZE        5

static RGBQUAD myPalett[MAX_COLOR_TABLE_SIZE];

#if USE_GUI_WRITELINE
static COLOR lineBuf[LCD_WIDTH];    // Zeilenpuffer
static int imgWidthClipped;         // tatsächliche Breite für WriteLine(min(Bildbreite,LCD_WIDTHidth))
#endif

/** Variables and all the stuff for rescaling AUFGABE C  */
static bool  gScaleMode  = false;
static int   gSrcWidth    = 0;
static int   gSrcHeight   = 0;
static int   gOutWidth    = 0;
static int   gOutHeight   = 0;
static int   gBoxWidth    = 1;
static int   gBoxHeight   = 1;
static COLOR gSrcBuf[MAX_BOX_SIZE][MAX_SRC_WIDTH];
static COLOR gOutLine[LCD_WIDTH];
static int   gRowCount    = 0; // wie viele Zeilen bisher eingelesen


/**
 * @brief Draws one pixel and cuts everything that is outside of 480x320 and
 * then calls GUI_drawPoint()
 *
 * @param x cordinates on the x axis
 * @param y cordinates on the y axis
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
 * @param index index of the color palette
 * @return uint16_t the color will be returned
 */
static COLOR getColorFromPalette(uint8_t index) {
  RGBQUAD color = myPalett[index];
  return (COLOR)(((color.rgbRed >> 3) << 11) | ((color.rgbGreen >> 2) << 5) | color.rgbBlue >> 3);
}

/**
 * @brief Switches between PixelPoint and DrawLine and emits the Pixel on the
 * display without rescaling
 * @param x cordinates on the x axis
 * @param y cordinates on the y axis
 * @param colorIndex color from the palette
 */
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

/**
 * @brief checks if End of line coordinates met for non scaled variants
 *
 * @param y coordinateon the y axis
 */
static void endOfLineNormal(int y) {
#if USE_GUI_WRITELINE
  if (y < 0 || y >= LCD_HEIGHT)
    return;
  Coordinate crd = {0, y};
  GUI_WriteLine(crd, imgWidthClipped, lineBuf);
  // lineBuf wird in der nächsten Zeile einfach überschrieben
#endif
}

/**
 * @brief emit pixel but for the scaled pics aufgabe c
 *
 * @param x cordinates for x axis
 * @param y cordinates for y axis
 * @param colorIndex color index of the palette
 */
static void scaledEmitPixel(int x, int y, uint8_t colorIndex) {
  if (x < 0 || x >= MAX_SRC_WIDTH)
    return;

  int srcYTop = gSrcHeight - 1 - y; // 0..H-1 von oben gezählt
  if (srcYTop < 0 || srcYTop >= gSrcHeight)
    return;

  int row = srcYTop % gBoxHeight; // Ringbufferindex
  gSrcBuf[row][x] = getColorFromPalette(colorIndex);
}


/**
 * @brief Mittelwert über eine Box von Quellpixeln bilden
 * 
 * @param xStart coordinate for x axis Start
 * @param xEnd   coordinate for x axis end 
 * @param yStart coordinate for y axis start
 * @param yEnd   coordinate for y axis end 
 * @return COLOR of the point
 */
static COLOR averageBox(int xStart, int xEnd, int yStart, int yEnd) {
    unsigned int sumR = 0;
    unsigned int sumG = 0;
    unsigned int sumB = 0;
    unsigned int count = 0;

    for (int y = yStart; y <= yEnd; y++) {
        int row = y % gBoxHeight;      // Ringpuffer-Zeilenindex
        for (int x = xStart; x <= xEnd; x++) {
            COLOR c = gSrcBuf[row][x];

            unsigned int r = (c >> 11) & 0x1F;
            unsigned int g = (c >> 5)  & 0x3F;
            unsigned int b =  c        & 0x1F;

            sumR += r;
            sumG += g;
            sumB += b;
            count++;
        }
    }

    if (count == 0) {
        return BLACK;  // Sicherheitsfallback
    }

    unsigned int rAvg = sumR / count;
    unsigned int gAvg = sumG / count;
    unsigned int bAvg = sumB / count;

    return (COLOR)((rAvg << 11) | (gAvg << 5) | bAvg);
}


/**
 * @brief same function line endOfLine but for scaled pictures
 *
 * @param yBottomUp coordinatefrom bottom to the top for emiting
 */
static void scaledEndOfLine(int yBottomUp) {
  int srcY = yBottomUp; // 0..H-1 von oben gezählt

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
  GUI_WriteLine(crd, gOutWidth, gOutLine);
} 

/**
 * @brief processs the pixel with either scaled variant or normal variant of the
 * picture (non/sclaed)
 *
 * @param x coordinate of x axis on the display
 * @param y coordinate of y axis on the display
 * @param colorIndex the color from the color palette
 */
static void processPixel(int x, int y, uint8_t colorIndex) {
  if (gScaleMode) {
    scaledEmitPixel(x, y, colorIndex);
  } else {
    emitPixelNormal(x, y, colorIndex);
  }
}

/**
 * @brief process the EOL to set the y cordinates for non/scaled
 *
 * @param y coordinate of y axis on the display
 */
static void processEndOfLine(int y) {
  if (gScaleMode) {
    scaledEndOfLine(y);
  } else {
    endOfLineNormal(y);
  }
}

/**
 * @brief initilizing the scaling for aufgabe c
 *
 * @param info the file infos on its type
 */
static void initScaling(const BITMAPINFOHEADER *info) {
  gSrcWidth = info->biWidth;
  gSrcHeight = info->biHeight;

  // Skalierungsfaktor bestimmen
  double sx = (double)LCD_WIDTH / gSrcWidth;
  double sy = (double)LCD_HEIGHT / gSrcHeight;
  double s = (sx < sy) ? sx : sy;

  // Grenzen 1 .. 1/5
  if (s > 1.0)
    s = 1.0;
  if (s < 1.0 / MAX_SCALE_FACTOR)
    s = 1.0 / MAX_SCALE_FACTOR;

  gBoxWidth = (int)ceil(1.0 / s);
  gBoxHeight = (int)ceil(1.0 / s);

  gOutWidth = LCD_WIDTH;
  gOutHeight = LCD_HEIGHT;

  gRowCount = 0;
}

/**
 * @brief core function to proccess the RLE blocks (8-bit RLE). takes data from
 * nextChar() from input.c interprets the Run length and escape codes end of
 * line end of bitmap etc.
 *
 * @param infoHdr
 * @return int EOK or NOK
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
      case 2: { // delta
        int dx = nextChar();
        int dy = nextChar();

        if (dx == EOF || dy == EOF)
          return NOK;
        x += (uint8_t)dx;
        y -= (uint8_t)dy; // bottom-up
        break;
      }
      default: 
        // absolute mode
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
 * @param infoHdr
 * @return int paletteSize
 */
static int loadColorPalette(const BITMAPINFOHEADER *infoHdr) {
  int paletteSize = (infoHdr->biClrUsed == 0) ? 256 : infoHdr->biClrUsed;
  COMread((char *)myPalett, sizeof(RGBQUAD),paletteSize); // because we know exactly how many bytes and how big our structure is
  return paletteSize;
}

/**
 * @brief main function to call to do all the functions of decoding
 *
 * @param fileHdr file header
 * @param infoHdr info header
 * @return int EOK or NOK
 */
int decodeAndDisplayRLE(const BITMAPFILEHEADER *fileHdr,const BITMAPINFOHEADER *infoHdr) {
  if (infoHdr->biCompression != BI_RLE8 || infoHdr->biBitCount != 8) {
    return ERR_HANDLER(true, "decodeAndDisplayRLE: Unsupported BMP format.");
  }
  int paletteSize = loadColorPalette(infoHdr);
  if (paletteSize <= 0) {
    return NOK;
  }

  gScaleMode = false; // wichtig für aufgabe c

#if USE_GUI_WRITELINE
  imgWidthClipped =
      (infoHdr->biWidth > LCD_WIDTH) ? LCD_WIDTH : infoHdr->biWidth;
#endif
  return decodeRLE8(infoHdr);
}

/**
 * @brief displays a scaled picture aufgabe c
 *
 * @param fileHdr file header
 * @param infoHdr info header
 * @return int EOK or NOK
 */
int displayScaledRLE(const BITMAPFILEHEADER *fileHdr, const BITMAPINFOHEADER *infoHdr) {
  (void)fileHdr;

  if (infoHdr->biCompression != BI_RLE8 || infoHdr->biBitCount != 8) {
    return ERR_HANDLER(true, "displayScaledRLE: Unsupported BMP format.");
  }

  if (infoHdr->biWidth > MAX_SRC_WIDTH || infoHdr->biHeight > LCD_HEIGHT * MAX_SCALE_FACTOR) {
    return ERR_HANDLER(true, "displayScaledRLE: image too large.");
  }

  int paletteSize = loadColorPalette(infoHdr);
  if (paletteSize <= 0) {
    return NOK;
  }

  initScaling(infoHdr); // setzt gSrcWidth/Height, gBoxWidth/Height, gOutWidth/Height

  gScaleMode = true; // jetzt Scaling-Backend benutzen

  int res = decodeRLE8(infoHdr);
  gScaleMode = false; // zur Sicherheit wieder zurück

  return res;


}

