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

 #endif