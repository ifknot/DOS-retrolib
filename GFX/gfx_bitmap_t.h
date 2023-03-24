/**
 *
 *  @brief     Device Independent Bitmap
 *  @details   Based on the PNG container format with critical and optional "chunks"
 *  Each chunk consists of:
 *
 *  | length  |   type  |  data   |
 *  | 2 bytes | 4 bytes | n bytes |
 *
 *  The critical chunks are:
 *      + IHDR - image header *must* appear first
 *      + IDAT - image data as a rectangular pixel array, left-to-right pixels per line and top-to-bottom lines
 *
 *  The optional chunks are (as of 20.03.2023):
 *      + PLTE - palette of 1 to 256 indexed entries of 3 byte RGB tuples
 *
 *  @note 1. The chunk names are case sensitive with the same case meaning as the PNG specification
 *  @note 2. Unlike the 4 bytes used by PNG chunks the retrolib chunks omit the CRC and have 2 byte lenght as a memory sapce compromise
 *  @url http://www.libpng.org/pub/png/spec/1.2/PNG-DataRep.html#DR.Image-layout
 *  @author    Jeremy Thornton
 *  @date      20.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "gfx_constants.h"
#include "gfx_types.h"

#define IHDR_TAG 0x52444849    // IHDR ascii hex NB little endian
#define IDAT_TAG 0x54414449     // "IDAT"
#define PLTE_TAG 0x45544c50     // "PLTE"

namespace gfx {

         /**
          *  @struct ihdr_t
          *  @brief  The IHDR chunk is always the first chunk and contains critical image metrics
          *  @details
          *  + width (2 bytes)
          *  + height (2 bytes)
          *  + bit depth (1 byte, values 1, 2, 4, 8, or 16)
          *  + colour type (1 byte, values 0, 2, 3, 4, or 6)
          * 
          * Valid bit depth - colour type combinations:
          * 
          * Color    Allowed    Interpretation
          * Type    Bit Depths
          * 0       1,2,4,8,16  Each pixel is a grayscale sample.
          * 2       8,16        Each pixel is an R,G,B triple.
          * 3       1,2,4,8     Each pixel is a palette index;
          *                     a PLTE chunk must appear.
          * 4       8,16        Each pixel is a grayscale sample,
          *                     followed by an alpha sample.
          * 6       8,16        Each pixel is an R,G,B triple,
          *                     followed by an alpha sample.
          */
        struct ihdr_t {
                static const uint16_t length = 6;
                static const uint32_t type = IHDR_TAG;
                uint16_t width;
                uint16_t height;
                uint8_t bit_depth;
                uint8_t colour_type;
        };

         /**
          *  @struct idat_t 
          *  @brief  The IDAT chunk contains the actual image data
          *  @note There is a hard limit of 64K bytes image size for retrolib
          *  @details There can be multiple IDAT chunks - except simple_bitmap_t
          *  + data (length bytes of image data as left-to-right pixels per line and top-to-bottom lines)
          */
        struct idat_t {
                uint16_t length;
                static const uint32_t type = IDAT_TAG;    
                char* data;
        };

        /**
         *  @struct plte_t
         *  @brief  The PLTE chunk contains a at least 1 rgb_t RGB tuple but no more than 256
         *  @note   There is a hard limit of 64K bytes palette size for retrolib
         */
        struct plte_t {
                uint16_t length;   
                static const uint32_t type = PLTE_TAG;
                rgb_t* data;
        };

        /**
         *  @struct bitmap_t
         *  @brief  The most basic Device Independent Bitmap built from chunks, suitable for
         *  + HGA monochrome
         *  + CGA monochrome
         *  + CGA colour
         *  + EGA colour
         *  @note   Only 1 IDAT chunk and it must be the last chunk
         */
        struct simple_bitmap_t {

            struct ihdr_t* ihdr;
            struct plte_t* plte;
            struct idat_t* idat;

        };

}

#endif