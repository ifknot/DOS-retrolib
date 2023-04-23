/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VRAM_TILE_BLOCK_H
#define HGA_VRAM_TILE_BLOCK_H

#include "hga_constants.h"
#include "hga_environment.h"

#include "../gfx_bitmap_t.h"

namespace hga {

    /**
     *  @brief writes a block of 8x8 tiles to VRAM using byte aligned (x) and bank aligned (y) Cartesian coordinates a.k.a. "tile space"
     *  @param x           - screen tile column position 0..89
     *  @param y           - screen tile row position 0..42
     *  @param bytes       - the bitmap data
     *  @param buffer - the VRAM buffer to write to
     */
    void vram_tile_block(uint16_t x, uint16_t y, const gfx::simple_bitmap_t* bmp, uint16_t buffer = GLOBAL::active_buffer) {
        uint16_t w, h, step;
        w = step = bmp->ihdr.width;
        h = bmp->ihdr.height;
        const char* bytes = bmp->idat.data;
        __asm {
            .8086

            mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; es points to screen segment

            sub     bx, bx                      ; zero column count

            mov     cx, w                       ; load CX bitmap width in pixels
            shr     cx, 1                       ; convert to width in tiles
            shr     cx, 1                       ; pixels width / 8
            shr     cx, 1                       ; 8086 limited to 1 shift at a time
            sub     step, cx                    ; compensate the step for the next tile inc
            mov     w, cx                       ; store back in w

            mov     cx, h                       ; load CX bitmap height in pixels
            shr     cx, 1                       ; convert to height in tiles
            shr     cx, 1                       ; pixels height / 8
            shr     cx, 1                       ; 8086 limited to 1 shift at a time
ROWS:       push    cx                          ; save rows loop counter

            mov     dx, x                       ; use a reg better performance
            
            mov     cx, w 
COLS:       push    cx                          ; save columns loop counter
            
            call    TILE                        ; write source to destination

            inc     dx                          ; next column
            inc     bx                          ; next tile (compensate for this)
            pop     cx                          ; retrieve columns loop counter
            loop    COLS

            inc     y                           ; next row
            add     bx, step
            pop     cx                          ; retrieve rows loop counter
            loop    ROWS

            jmp     END

TILE:       mov     ax, y                       ; load y into AX then perform screen clipping
            cmp     ax, SCREEN_TILE_HEIGHT
            jge     END                         ; no more rows to plot

            mov     di, dx                      ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_TILE_WIDTH
            jge     TEND                        ; no more columns on this row to plot

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

TEND:       ret

END:       

        }
    }

}

#endif