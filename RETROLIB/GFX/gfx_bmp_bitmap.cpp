/**
 *
 *  @file      gfx_bitmap.cpp
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.12.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "gfx_bmp_bitmap.h"

//#include "../TEST/debug_macros.h"

namespace gfx {

    namespace bmp {

        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width,
            uint16_t height,
            uint8_t bit_depth,
            uint8_t colour_type,
            char* raster_data,
            uint16_t raster_size,
            char* palette_data,
            uint16_t palette_size
        ) {
            if (sizeof(bitmap_t) > mem::arena::size(pool)) {                                                // is there enough avaiable memory in the pool?
#ifndef NDEBUG
                    std::cout << "Error new_bitmap no room in arena memory pool for bitmap_t! - sizeof(bitmap_t) = " << sizeof(bitmap_t) << " arena pool size = " << mem::arena::size(pool) << std::endl;
#endif
                    return NULL_PTR;                                                                                                                                // nope, return
            }
            bitmap_t* bmp = (bitmap_t*)mem::arena::raw_alloc(pool, sizeof(bitmap_t));
            bmp->width = width;
            bmp->height = height;
            bmp->bit_depth = bit_depth;
            bmp->colour_type = colour_type;
            bmp->raster_size = raster_size;
            bmp->palette_data = palette_data;
            bmp->palette_size = palette_size;
            return bmp;
        }

        uint16_t calculate_raster_size(uint16_t width, uint16_t height, uint8_t bit_depth) {
            switch (bit_depth) {
            case 1: // fall through
            case 2: // .
            case 4: // .
            case 8: // .
                    return ((uint32_t)width * (uint32_t)height) / (8 / bit_depth);
            case 16:
                    return width * height * 2;
#ifndef NDEBUG
            default:
                    std::cout << "ERROR new_bitmap ILLEGAL bit depth " << bit_depth << std::endl;
#endif
                    return 0;
                }
        }

        bitmap_t* new_bitmap(
            mem::arena::arena_t* pool,
            uint16_t width,
            uint16_t height,
            uint8_t bit_depth,
            uint8_t colour_type
        ) {
            bitmap_t* bmp = new_bitmap(
                pool,
                width,
                height,
                bit_depth,
                colour_type,
                NULL_PTR,
                0,
                NULL_PTR,
                0
            );
            bmp->raster_size = calculate_raster_size(width, height, bit_depth);
            bmp->raster_data = (char*)mem::arena::raw_alloc(pool, bmp->raster_size);
            return bmp;
        }

        bitmap_t* new_bitmap(mem::arena::arena_t* pool) {
            return new_bitmap(
                pool,
                0,
                0,
                0,
                0,
                NULL_PTR,
                0,
                NULL_PTR,
                0
            );
        }

        void fill(gfx::bmp::bitmap_t* bmp, uint8_t fill_byte) {
            __asm {
                .8086
                push bp
                pushf

                lds     si, bmp                             ; DS:[SI] points to the bitmap_t metadata
                les     di, [si + OFFSET_RASTER_DATA]       ; ES:[DI] points to raster data area
                mov     cx, [si + OFFSET_RASTER_SIZE]       ; CX is the size of the raster data area
                mov     al, fill_byte                       ; AL is the repeated byte
                mov     ah, al                              ; AX is 2 of the fill bytes
                shr     cx, 1                               ; raster_size / 2

                cld                                                                                     ; increment DI
                rep     stosw                               ; faster than stosb but must be even size 

                popf
                pop bp
            }
        }

    }

}

std::ostream& operator<< (std::ostream& os, const gfx::bmp::bitmap_t& bmp) {
        os << bmp.width << ',' << bmp.height << ',' << (int)bmp.bit_depth << ',' << (int)bmp.colour_type << '\n'
                << std::hex << (uint32_t)bmp.raster_data << '\n'
                << std::dec << bmp.raster_size << '\n'
                << std::hex << (uint32_t)bmp.palette_data << '\n'
                << std::dec << bmp.palette_size;
        return os;
}
