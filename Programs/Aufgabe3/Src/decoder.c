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
#include <stdbool.h>

static RGBQUAD myPalett[256];

/**
 * @brief Draws one pixel and cuts everything that is outside of 480x320 and
 * then calls GUI_drawPoint()
 *
 * @param x
 * @param y
 * @param color
 */
static void putPixelClipped(int x, int y, uint16_t color) {
    if(x < 0 || x >= 480 || y < 0 || y >= 320) return;

    Coordinate crd = { x, y };
    GUI_drawPoint(crd, color, DOT_PIXEL_1X1, DOT_FILL_AROUND);
}

/**
 * @brief Get the Color From Palette object (RGB565 color) from the BMP (8 bit
 * indexed BMPS)
 * @param index
 * @return uint16_t
 */
static uint16_t getColorFromPalette(uint8_t index) {
    RGBQUAD color = myPalett[index];
    return ((color.rgbRed>>3) << 11) | ((color.rgbGreen>>2) << 5) | color.rgbBlue >> 3;
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
    
    int x = 0;
    int y = height - 1;

    while (1) {
        uint8_t count = nextChar(); // 1 byte
        uint8_t value = nextChar(); // 2 byte
        if (count > 0) { // encoded mode
            /**
            * Bedeutung: „Wiederhole den Pixel mit Index value genau count-mal in der
                aktuellen Zeile.“
                Für i = 0..count-1:     Pixel ausgeben (x,y) mit colorIndex = value x
            um 1 erhöhen Du musst darauf achten, dass x nicht über width hinausläuft
            (falls das BMP fehlerhaft ist → Fehler behandeln).
            */
            for(int i = 0; i < count; i++){
                // pixel ausgeben mit (x,y) mit colorIndex = value danach x um 1 erhöhen
                // x nicht über width hinauslaufen
                putPixelClipped(x, y, getColorFromPalette(value));
                x++;
            }
        } else { // Escape mode/ control mode
            switch (value) {
                case 0: // End of Line (EOL)
                    x = 0;
                    y--;
                    break;
                case 1: // End of Bitmap (EOB)
                    // pic is finished
                    return EOK;
                case 2: // delta(dx, dy)
                    x += nextChar();
                    y -= nextChar();
                    break;
                default: // absolute mode
                    // read value single byte
                    // ausgeben für jedes pixel aus (x,y) und erhöhst x
                    for(int i = 0; i < value; i++){
                        // pixel ausgeben mit (x,y) mit colorIndex = value danach x um 1 erhöhen
                        // x nicht über width hinauslaufen
                        putPixelClipped(x, y, getColorFromPalette(nextChar()));
                        x++;
                    }

                    // wenn value ungerade dann kommt ein Padding byte das wir lesen aber
                    // ignorieren
                    if(value & 1)
                    {
                        nextChar();
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
    COMread((char *)myPalett, sizeof(RGBQUAD), palleteSize); // because we know exactly how many bytes and how big our structure is

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
    if (infoHdr->biCompression == BI_RLE8) {
        int palleteSize = loadColorPalette(infoHdr);
        /*int padding = fileHdr->bfOffBits - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - palleteSize * sizeof(RGBQUAD);
        for(int i = 0; i < padding; i++)
        {
            nextChar();
        }*/

        return decodeRLE8(infoHdr);
    }

    return EOK;
}
