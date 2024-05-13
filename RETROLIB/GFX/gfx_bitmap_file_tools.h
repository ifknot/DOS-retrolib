/**

    @file      gfx_bitmap_file_tools.h
    @brief     file load and save functions for gfx::bmp::bitmap_t
    @details   ~
    @author    Jeremy Thornton
    @date      13.05.2024
    @copyright © Jeremy Thornton, 2024. All right reserved.

**/
#ifndef GFX_BITMAP_FILE_TOOLS_H
#define GFX_BITMAP_FILE_TOOLS_H

namespace gfx {

    namespace bmp {

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

#endif