/****/
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "../MEM/mem.h"

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
        struct bitmap_t;

        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width = 0,
            uint16_t height = 0,
            uint8_t bit_depth = 1,
            uint8_t colour_type = 0,
            char* raster_data[] = NULL_PTR,
            uint32_t raster_size = 0,   
            char* palette_data = NULL_PTR,
            uint32_t palette_size = 0
        );

        void new_raster_data(mem::arena::arena_t* pool, bitmap_t* bmp);

        void new_palette_data(mem::arena::arena_t* pool, bitmap_t* bmp, uint32_t palette_size);

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
