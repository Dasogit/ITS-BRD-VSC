/**
 * @file decoder.h
 * @author your name (you@domain.com)
 * @brief decodes the RLE 8 bit per pixel and uses the Color pallete 
 * @version 0.1
 * @date 2025-12-03
 * 
 * @copyright Copyright (c) 2025
 * 
 */

 #ifndef decoder_h
 #define decoder_h

 #include "BMP_types.h"

/**
 * @brief main function to call to do all the functions of decoding
 * 
 * @param fileHdr 
 * @param infoHdr 
 * @return int W
 */
int decodeAndDisplayRLE(const BITMAPFILEHEADER *fileHdr, const BITMAPINFOHEADER *infoHdr);

//+++++++++++++++++++++++++++++++++++++++++++ BECAUSE STATIC WE DONT NEED THEM HERE CAUSE ITS LIKE A PRIVATE FUNC +++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @brief core function to proccess the RLE blocks (8-bit RLE). takes data from nextChar() from input.c
 * interprets the Run length and escape codes end of line end of bitmap etc. 
 * calls nextChar()
 * 
 * @param infoHdr 
 * @return int 
 */
//static int decodeRLE8(const BITMAPINFOHEADER *infoHdr);

/**
 * @brief Draws one pixel and cuts everything that is outside of 480x320 and then calls GUI_drawPoint()
 * 
 * @param x 
 * @param y 
 * @param color 
 */
//static void putPixelClipped(int x, int y, uint16_t color);


/**
 * @brief Get the Color From Palette object (RGB565 color) from the BMP (8 bit indexed BMPS)
 * @param index 
 * @return uint16_t 
 */
//static uint16_t getColorFromPalette(uint8_t index);

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/**
 * @brief looks up at the Color table directly after the header (BMP 256 colors -> 256 x 4 byte palette entry)
 * 
 */
void loadColorPalette();


/**
 * @brief resets x, y and the line length and borders 
 * 
 */
void resetDecoderState();


/**
 * @brief it splitts escape cases like (00 00 , 00 01 , 00 02 dx dy) 
 * 
 */
//void handleEscapeSequence(); // idk if necessary. 

/**
 * @brief indentation for the cursor on the display ? 
 * 
 */
//void advancePosition(); //also idk if necessary. 




 #endif