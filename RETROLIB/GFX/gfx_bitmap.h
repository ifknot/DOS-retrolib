/****/
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "../MEM/mem.h"

namespace gfx {

	namespace bmp {

		const char PBM_EXT[] = "PBM";

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
        * Greyscale             0                  1, 2, 4, 8, 16                greyscale sample
        * Truecolour            2                  8, 16                               RGB triple
        * Indexed-colour  3                  1, 2, 4, 8                    palette index
        * Greyscale alpha 4                  8, 16                               greyscale sample & alpha value (0 transparent 255 opaque)
        * Truecolour alpha      6                  8, 16                               RGB triple & alpha value
        *
        * Palette data - true colour (256 shades red, green, blue)
        * Always for colour type 3, possible for colour types 2 and 6
        * Invalid for colour types 0 and 4.
        */
        struct bitmap_t {

            uint16_t width;               // max 65535 x 65535 image
            uint16_t height;              // raster rectangle dimensions
            uint8_t bit_depth;            // bits per pixel (1, 2, 4, 8 , 16) or palette index
            uint8_t colour_type;          // Greyscale 0, Truecolour 2, Indexed colour 3, Greyscale alpha 4, Truecolour alpha 6
            uint8_t* raster_data;         // ptr to pixel data raster image
            uint32_t raster_size;         // size of the pixel data
            uint8_t* palette_data;        // ptr to palette data - 24-bit values for the RGB color space, 16,777,216 color variations
            uint32_t palette_size;        // size of the palette data

        };

        /**
        * @brief Load a Portable BitMap .pbm monochrome image into arena memory
        * and populate the bitmap_t descriptor correctly
        * @note white = 0, black = 1 and, therefore, to display correctly image will need inverting
        * this can be acheived by setting auto_invert = true or calling bitmap::invert seperately
        * @url https://en.wikipedia.org/wiki/Netpbm
        */
		void load_file_pbm(const char* file_path, bitmap_t* bmp, mem::arena::arena_t* pool, bool auto_invert = true);

        /**
       * @brief Convert bitmap_t pixel data to its negative image depending on its colour type
       * @details
       * Monochrome/Grayscale negative image is a total inversion, in which light areas appear dark and vice versa.
       * Colour image is additionally color-reversed, with red areas appearing cyan, greens appearing magenta, and blues appearing yellow, and vice versa.
       * @note the Alpha component of the image will be the same as the original image
       */
       //void invert(bitmap_t* bmp);
       //switch colour_type
       //case GREYSCALE: not each byte

	}

}

#endif
