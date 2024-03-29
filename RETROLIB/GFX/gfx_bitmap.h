/****/
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "gfx_types.h"

#include "../MEM/mem.h"

#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		const char      PBM_EXT[]       = "PBM";    // valid file extension for portable bitmap
        const uint16_t  PBM_MAGIC_RAW       = 0x3450;   // little endian ascii 4P
        const int       PBM_MIN_SIZE    = 6;        // minimum valid size - a 1 byte image

        enum colour_type_t {
            GREYSCALE = 0,
            TRUECOLOUR = 2,
            INDEXED_COLOUR,
            GREYSCALE_ALPHA,
            TRUECOLOUR_ALPHA = 6
        };

        /**
        * @brief Raster image descriptor - 128 bytes
        * @details Describes how to interpret the pixel data array
        * (heavily influenced by the PNG IHDR format)
        *
        * Image     type  Colour type       Allowed bit depths            Each pixel is a...
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

            uint16_t    width;          // 0 max 65535 x 65535 image
            uint16_t    height;         // 2 raster rectangle dimensions
            uint8_t     bit_depth;      // 4 bits per pixel (1, 2, 4, 8 , 16) or palette index
            uint8_t     colour_type;    // 5 Greyscale 0, Truecolour 2, Indexed colour 3, Greyscale alpha 4, Truecolour alpha 6
            char*       raster_data[8]; // 6 ptr to pixel data raster image and any pre x-shifted optimisations for bit depths 1,2, and 4
            uint16_t    raster_size;    // 38 size of the pixel data
            char*       palette_data;   // 40 ptr to palette data - 24-bit values for the RGB color space, 16,777,216 color variations
            uint16_t    palette_size;   // 44 size of the palette data

        };

#define OFFSET_RASTER_DATA 6
#define OFFSET_RASTER_SIZE 38

        /**
        * @brief helper function to create a new bitmap in an arena_t memory pool with over-rideable default settings 
        */
        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width = 0,
            uint16_t height = 0,
            uint8_t bit_depth = 1,
            uint8_t colour_type = 0,
            char* raster_data[8] = NULL_PTR,  
            uint32_t raster_size = 0,
            char* palette_data = NULL_PTR,
            uint32_t palette_size = 0
        );

        /**
        * @brief helper function to set up raster data in a bitmap_t 
        * @note behaviour is defined by passed arguments
        * @details
        * 
        * new_raster_data(bmp, pool) 
        * - reserve memory in pool as per extant bit_depth, width and height and calculate raster_size
        * 
        * new_raster_data(bmp, pool, width, height) 
        * - reserve memory in pool as per extant bit_depth, passed width and height and calculate raster_size  
        * @note sets the whole raster_data pointer array to the same reserved memory pointer
        * 
        * new_raster_data(bmp, pool, width, height, raster_data)
        * - with extant bit_depth set width and height, calculate new raster_size and set raster_data pointer array
        * @note the array of raster_data pointers is COPIED to the bitmap's array of raster_data pointers
        *
        */
        void new_raster_data(bitmap_t* bmp, mem::arena::arena_t* pool, uint16_t width = 0, uint16_t height = 0, char* raster_data[] = NULL_PTR);

        /**
        * @brief fill a bitmap with a colour
        * @note undefined behaviour for odd raster_size bitmap_t
        */
        void fill(gfx::bmp::bitmap_t* bmp, gfx::colours::high_colour_t colour);

        namespace pbm {

            /**
            * @brief Load a Portable BitMap .pbm monochrome image into arena memory
            * and populate the bitmap_t descriptor correctly
            * @note white = 0, black = 1 and, therefore, to display correctly image will need inverting
            * this can be acheived by setting auto_invert = true, or calling bitmap::invert seperately - or preconverting the actual file data
            *
            * @url https://en.wikipedia.org/wiki/Netpbm
            */
            void load_file(mem::arena::arena_t* pool, bitmap_t* bmp, const char* file_path);

        }

	}

}

std::ostream& operator<< (std::ostream& os, const gfx::bmp::bitmap_t& addr);

#endif
