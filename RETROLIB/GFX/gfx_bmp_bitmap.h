/**
 *
 *  @file      gfx_bitmap.h
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "gfx_types.h"

#include "../MEM/mem.h"

#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		const char      PBM_EXT[]       = "PBM";        // valid file extension for portable bitmap
        const uint16_t  PBM_MAGIC_RAW   = 0x3450;       // little endian ascii '4P'
        const int       PBM_MIN_SIZE    = 6;            // minimum valid size - a 1 byte of raster data image

        /**
        * Raster image colour types
        * @see bitmap_t
        */
        enum colour_type_t {
            GREYSCALE = 0,
            TRUECOLOUR = 2,
            INDEXED_COLOUR,
            GREYSCALE_ALPHA,
            TRUECOLOUR_ALPHA = 6
        };

        /**
        * @brief Raster image descriptor - 40 bytes
        * @details Describes how to interpret the pixel data array
        * (heavily influenced by the PNG IHDR format)
        *
        * Image type          Colour type      Allowed bit depths           Each pixel is a...
        * Greyscale             0                  1, 2, 4, 8, 16           greyscale sample
        * Truecolour            2                  8, 16                    RGB triple
        * Indexed-colour        3                  1, 2, 4, 8               palette index
        * Greyscale alpha       4                  8, 16                    greyscale sample & alpha value (0 transparent 255 opaque)
        * Truecolour alpha      6                  8, 16                    RGB triple & alpha value
        *
        * Palette data - true colour (256 shades red, green, blue)
        * Always for colour type 3, possible for colour types 2 and 6
        * Invalid for colour types 0 and 4.
        */
        struct bitmap_t {	
                                        // offset
            uint16_t    width;          //  0       max 65535 x 65535 image
            uint16_t    height;         //  2       raster rectangle dimensions
            uint8_t     bit_depth;      //  4       bits per pixel (1, 2, 4, 8 , 16) or palette index
            uint8_t     colour_type;    //  5       Greyscale 0, Truecolour 2, Indexed colour 3, Greyscale alpha 4, Truecolour alpha 6
            char*       raster_data;    //  6       ptr to pixel data raster image and any pre x-shifted optimisations for bit depths 1,2, and 4
            uint16_t    raster_size;    //  10      size of the pixel data
            char*       palette_data;   //  12      ptr to palette data - 24-bit values for the RGB color space, 16,777,216 color variations
            uint16_t    palette_size;   //  16      size of the palette data
                                        //  18      bytes sizeof bitmap_t struct

        };

#define OFFSET_RASTER_DATA 6
#define OFFSET_RASTER_SIZE 10

        /**
        * @brief create a new bitmap w all the trimmings
        */
        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width,
            uint16_t height,
            uint8_t bit_depth,
            uint8_t colour_type,
            char* raster_data,  
            uint32_t raster_size,
            char* palette_data,
            uint32_t palette_size
        );

        /**
        * @brief helper function to calculate_raster_size
        */
        uint32_t calculate_raster_size(uint16_t width, uint16_t height, uint8_t bit_depth);

        /**
        * @brief create a new 'blank' bitmap
        */
        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width,
            uint16_t height,
            uint8_t bit_depth,
            uint8_t colour_type
        );

        /**
        * @brief create a new bitmap with nothing allocated eg ready for loading from a file
        */
        bitmap_t* new_bitmap(mem::arena::arena_t* pool);
        

        /**
        * @brief fill a bitmap with a repeating byte
        */
        void fill(gfx::bmp::bitmap_t* bmp, uint8_t fill_byte);

        void inline clear(gfx::bmp::bitmap_t* bmp) {
            fill(bmp, 0);
        }

	}

}

std::ostream& operator<< (std::ostream& os, const gfx::bmp::bitmap_t& addr);

#endif
