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
 *  + IDAT - image data as a rectangular pixel array, left-to-right pixels per line and top-to-bottom lines
 *
 *      The optional chunks are (as of 20.03.2023):
 *      + PLTE - palette of 1 to 256 indexed entries of 3 byte RGB tuples
 *
 *  @note 1. The chunk names are case sensitive with the same case meaning as the PNG specification
 *  @note 2. Unlike the 4 bytes used by PNG chunks the retrolib chunks omit the CRC and have 2 byte lenght as a memory sapce compromise
 *  @url http://www.libpng.org/pub/png/spec/1.2/PNG-DataRep.html#DR.Image-layout
 *  @author    Jeremy Thornton
 *  @date      20.03.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
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
          *  @struct IHDR
          *  @brief  The IHDR chunk is always the first chunk and contains critical image metrics
          *  @details
          *  + width (2 bytes)
          *  + height (2 bytes)
          *  + bit depth (1 byte, values 1, 2, 4, 8, or 16)
          *  + colour type (1 byte, values 0, 2, 3, 4, or 6)
          */
        struct IHDR {
                static const uint16_t length = 6;
                static const uint32_t type = IHDR_TAG;
                uint16_t width;
                uint16_t height;
                uint8_t bit_depth;
                uint8_t colour_type;
        };

         /**
          *  @struct IDAT
          *  @brief  The IDAT chunk contains the actual image data
          *  @details There can be multiple IDAT chunks
          *  + data (length bytes of image data as left-to-right pixels per line and top-to-bottom lines)
          */
        struct IDAT {
                uint16_t length;
                static const uint32_t type = IDAT_TAG;    
                char* data;
        };

        /**
         *  @struct PLTE
         *  @brief  The PLTE chunk contains a at least 1 rgb_t RGB tuple but no more than 256
         */
        struct PLTE {
                uint16_t length;
                static const uint32_t type = PLTE_TAG;
                rgb_t* data;
        };

        /**
         *  @struct bitmap_t
         *  @brief  The most basic Device Independent bitmap built from chunks ideal for HGA CGA monochrome and CGA 4 colour
         */
        struct simple_bitmap_t {

            struct IHDR* ihdr;
            struct IDAT* idat;

        };

}

#endif