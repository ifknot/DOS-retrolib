/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_WRITE_TILE_COLUMN_H
#define HGA_WRITE_TILE_COLUMN_H

#include "hga_constants.h"
#include "hga_environment.h"

#include "../../IMG/PBM/pbm_bitmap.h"

namespace hga {

    void write_tile_column(uint16_t x, uint16_t y, const pbm::bitmap_t* bmp, uint8_t buffer = GLOBAL::active_buffer) {
         uint16_t w, h, step;
        w = step = bmp->header->width;
        h = bmp->header->height;
        const char* bytes = bmp->data;
        __asm {
            .8086

            mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1                   ; which buffer ?
            jz      J0                          ; B000:0000 - B000 : 7FFF   First Page
            add     ax, HGA_PAGE_2_OFFSET       ; B000:8000 - B000 : FFFF   Second Page
J0:         mov     es, ax                      ; es points to screen segment

            mov     cx, h                       ; load CX bitmap height in pixels
            shr     cx, 1                       ; convert to height in tiles
            shr     cx, 1                       ; pixels height / 8
            shr     cx, 1                       ; 8086 limited to 1 shift at a time

ROWS:       push    cx                          ; save rows loop counter

            mov     dx, x                       ; use a reg better performance

            call    TILE                        ; write source to destination
                    
            pop     cx                          ; retrieve row count
            loop    ROWS

            jmp     END

TILE:       mov     ax, y                       ; load y into AX then perform screen clipping
            cmp     ax, SCREEN_TILE_HEIGHT
            jge     END                         ; no more rows to plot

            mov     di, dx                      ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_TILE_WIDTH
            jge     END                        ; no more columns on this row to plot

            shl     ax, 1                       ; convert y tile row to partial(x2) pixel location
            mov     cl, BYTES_PER_LINE
            mul     cl                          ; calculate (y / 4) * 90 nb 133 cycles
            add     di, ax                      ; + (y / 4) * 90

            lds     si, bytes                   ; DS:[SI] points to list of 8 tile data bytes to write
            add 	si, bx                      ; DS:[sI] points to the specific list of 8 tile bytes
            mov 	cx, w                       ; the width in *tiles* of the bitmap will step to correct column byte
            dec 	cx                          ; compensate for MOVSB auto increment

            lodsb                               ; load 8 pixels strip tile row 0 into AL
            mov     es:[di] , al                ; store row 0 bank 0 as guaranteed bank zero start in tile space coords

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 1 into AL
            mov     es:[di + 2000h] , al        ; store row 1 bank 1

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 2 into AL
            mov     es:[di + 4000h] , al        ; store row 2 bank 2

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 3 into AL
            mov     es:[di + 6000h] , al        ; store row 3 bank 3

            add     di, 90                      ; add 90 bytes next line for all 4 banks

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 4 into AL
            mov     es:[di] , al                ; store row 4 bank 0

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 5 into AL
            mov     es:[di + 2000h] , al        ; store row 5 bank 1

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 6 into AL
            mov     es:[di + 4000h] , al        ; store row 6 bank 2

            add     si, cx
            lodsb                               ; load 8 pixels strip tile row 7 into AL
            mov     es:[di + 6000h] , al        ; store row 7 bank 3

            ret

END:       
    }

}

#endif