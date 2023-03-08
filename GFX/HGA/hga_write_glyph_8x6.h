/**
 *
 *  @brief     fast path for 8x6 aspect ratio correct bitmaps and monospaced fonts
 *  @details   90x58 glyph tiles per screen
 *  @author    Jeremy Thornton
 *  @date      6.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_WRITE_GLYPH_8x6_H
#define HGA_WRITE_GLYPH_8x6_H

#include "hga_constants.h"
#include "hga_environment.h"

#include <iostream>

namespace hga {

    /**
    * An 8x6 bitmap/font whilst a vertical size of 6 pixels is evenly divisible into HGA's 348 vertical lines 
    * and a width of 8 pixels is evenly divisible into the 720 HGA width - it does not leave much room
    * for a legible font or resolvable bitmap.
    * However, it does serve as the smallest full byte screen ratio glyph that is fully tileable across the HGA screen.
    * 90x58 glyph screen can, therefore, be used as component tiles for larger glyphs
    */
    void write_glyph_8x6(uint16_t x, uint16_t y, const uint8_t* bytes, uint8_t buffer = GLOBAL::active_buffer) {
        __asm {
            .8086 

            // can likely optimise away * 8
            shl     x, 1            ; convert x glyph column to pixel location x*8
            shl     x, 1            ; 8086 limited to single step shifts, but...
            shl     x, 1            ; 3 x mem with 1 shift is 3 x 15 = 45 clock cycles, MUL 16 bit mem is 139 clock cycles(!)

            // can likely optimise away * 4
            shl     y, 1            ; convert y glyph row to pixel location y*6 which is y*4 + y*2
            mov     ax, y           ; copy of y*2
            shl     y, 1            ; y*4 
            add     y, ax           ; y*4 + y*2 which is 15 + 10 + 15 + 16 = 51 clock cycles vs 2x139 = 278 or 45 + 51 / 278 = 34% the time for 2 MULS

            lds     si, bytes       ; ds: [si] points to list of 8 glyph data bytes to write

            mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1               ; which buffer ?
            jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
            add     ax, HGA_PAGE_2_OFFSET   ; B000:8000 - B000 : FFFF   Second Page
    J0:     mov     es, ax			        ; es points to screen segment

        }
        
    }


}

#endif