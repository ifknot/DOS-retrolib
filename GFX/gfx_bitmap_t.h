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
#ifndef GFX_BITMAP_T_H
#define GFX_BITMAP_T_H

#include <iomanip>
#include <ostream>

#include <stdlib.h>

#include "gfx_constants.h"
#include "gfx_types.h"

#define IHDR_TAG 0x52444849     // "IHDR" ascii hex NB little endian
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
            static const uint16_t size = 6;
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
            uint16_t size;
            static const uint32_t type = IDAT_TAG;    
            char* data;
        };

        /**
         *  @struct plte_t
         *  @brief  The PLTE chunk contains a at least 1 rgb_t RGB tuple but no more than 256
         *  @note   There is a hard limit of 64K bytes palette size for retrolib
         */
        struct plte_t {
            uint16_t size;   
            static const uint32_t type = PLTE_TAG;
            gfx::rgb_t* data;
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

            struct ihdr_t ihdr;
            struct plte_t plte;
            struct idat_t idat;

        };
       
        /**
         *  @brief Initialise a gfx::simple_bitmap_t
         *  @param bmp            - 
         *  @param width          - 
         *  @param height         - 
         *  @param bit_depth      - 
         *  @param colour_type    - 
         *  @param palette_data   - 
         *  @param palette_length - 
         *  @param image_data     - 
         *  @param image_length   - 
         */
        void init_simple_bitmap(
            simple_bitmap_t* bmp,
            uint16_t width = 0,
            uint16_t height = 0,
            uint8_t bit_depth = 1,
            uint8_t colour_type = 0,

            rgb_t* palette_data = NULL,
            uint16_t palette_size = 0,

            char* image_data = NULL,
            uint16_t image_size = 0
        ) {
            assert(bmp);
            // set chunk default values
            bmp->ihdr.width = width;
            bmp->ihdr.height = height;
            bmp->ihdr.bit_depth = bit_depth;
            bmp->ihdr.colour_type = colour_type;
            bmp->plte.data = palette_data;
            bmp->plte.size = palette_size;
            bmp->idat.data = image_data;
            bmp->idat.size = image_size;
        }

        gfx::simple_bitmap_t* create_simple_bitmap(
                uint16_t width = 0,
                uint16_t height = 0,
                uint8_t bit_depth = 1,
                uint8_t colour_type = 0,
            
                rgb_t* palette_data = NULL,
                uint16_t palette_size = 0,

                char* image_data = NULL,
                uint16_t image_size = 0
            ) { 
            // create bitmap and sanity check
            simple_bitmap_t* bmp = new simple_bitmap_t;
            assert(bmp);
            init_simple_bitmap(bmp, width, height, bit_depth, colour_type, palette_data, palette_size, image_data, image_size);
            return bmp;
        }

        /*void copy_simple_bitmap(gfx::simple_bitmap_t bmp, gfx::simple_bitmap_t other) {
            copy over the ihdr metrics and plte and idat lengths
            free plte data and idat data 
            malloc new mem same as other
            copy over plte and idat data
        }*/

        /**
         *  @brief Free any malloc'd memory used by a simple bitmap.
         *  @note  The simple bitmap structure itself is *not* deleted.
         *  @param bmp - pointer to an extant gfx::simple_bitmap_t
         */
        void free_simple_bitmap(gfx::simple_bitmap_t* bmp) {
            if (bmp) {
                if (bmp->idat.data) free(bmp->idat.data);  // free the image data
                if (bmp->plte.data) free(bmp->plte.data);  // free the palette data                           
            }
        }

}

std::ostream& operator<<(std::ostream& os, const gfx::ihdr_t& ihdr) {
    char* name = (char*)&ihdr.type;
    os << ihdr.size << ' ' << name[0] << name[1] << name[2] << name[3] << ' '
        << ihdr.width << ' ' << ihdr.height << ' ' << (int)ihdr.bit_depth << ' ' << (int)ihdr.colour_type;
    return os;
}

std::ostream& operator<< (std::ostream& os, const gfx::plte_t& plte) {
    char* name = (char*)&plte.type;
    os << plte.size << ' ' << name[0] << name[1] << name[2] << name[3] << ' ';
    if (plte.data) {
        os << '\n' << std::hex << std::setfill('0');
        for (uint16_t i = 0; i < plte.size; ++i) {
            os << '{' << std::setw(2) << (int)(plte.data + i)->r << ',' << std::setw(2) << (int)(plte.data + i)->g << ',' << std::setw(2) << (int)(plte.data + i)->b << "} ";
            if (i % 7 == 7) os << '\n';
        }
    }
    return os;
}

std::ostream& operator<< (std::ostream& os, const gfx::idat_t& idat) {
    char* name = (char*)&idat.type;
    os << idat.size << ' ' << name[0] << name[1] << name[2] << name[3] << ' ';
    if (idat.data) {
        os << '\n' << std::hex << std::setfill('0');
        for (uint16_t i = 0; i < idat.size; ++i) {
            os << std::setw(2) << (int)(*(idat.data + i)) << ' ';
            if (i % 15 == 15) os << '\n';
        }
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const gfx::simple_bitmap_t& bmp) {
    os << bmp.ihdr << '\n';
    os << bmp.plte << '\n';
    os << bmp.idat;
    return os;
}

#endif