/**
 * @file decoder.h
 * @author Naghashi, Danandeh
 * @brief decodes the RLE 8 bit per pixel and uses the Color pallete 
 * @version 0.4
 * @date 2025-12-11
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
 * @return int EOK or NOK
 */
int decodeAndDisplayRLE(const BITMAPFILEHEADER *fileHdr, const BITMAPINFOHEADER *infoHdr);

/**
 * @brief rescales and then hands over the picture to the decoder
 * 
 * @param fileHdr 
 * @param infoHdr 
 * @return int int EOK or NOK
 */
int displayScaledRLE(const BITMAPFILEHEADER *fileHdr,const BITMAPINFOHEADER *infoHdr);
 #endif