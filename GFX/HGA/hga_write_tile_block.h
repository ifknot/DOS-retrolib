/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_WRITE_TILE_BLOCK_H
#define HGA_WRITE_TILE_BLOCK_H

#include "hga_constants.h"
#include "hga_environment.h"

#include "../../IMG/PBM/pbm_bitmap.h"

namespace hga {
    
    void write_tile_block(uint16_t x, uint16_t y, const pbm::bitmap_t* bmp, uint8_t buffer = GLOBAL::active_buffer) {
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

            sub     bx, bx                      ; zero column count

            mov     cx, w                       ; load CX bitmap width in pixels
            shr     cx, 1                       ; convert to width in tiles
            shr     cx, 1                       ; pixels height / 8
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




/*
void write_tile_strip(uint16_t x, uint16_t y, uint16_t w, uint16_t h, const char* bytes, uint16_t tile_offset = 0, uint8_t buffer = GLOBAL::active_buffer) {
    __asm {
        .8086
        pushf

        mov     bx, x                           ; BX will hold x to save exec cycles

        //mov     cx, h
//ROW:        push    cx                              ; store row count on stack

           // mov     cx, w
//COL:        push    cx                              ; store column count on stack

            //call    VRAM                            ; calculate source DS:[SI] and destination ES:[DI]


            mov     ax, y                           ; load y into ax then perform screen clipping
            shl     ax, 1                           ; convert y tile row to partial(x2) pixel location
            cmp     ax, SCREEN_Y_MAX / 4            ; compare ax with partial y maximum boundry / 4
            jge     END                             ; nothing to plot

            mov     cx, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1                       ; which buffer ?
            jz      J0                              ; B000:0000 - B000 : 7FFF   First Page
            add     bx, HGA_PAGE_2_OFFSET           ; B000:8000 - B000 : FFFF   Second Page
J0:         mov     es, cx                          ; es points to screen segment

            lds     si, bytes                       ; DS: [SI] points to list of 8 tile data bytes to write
            add 	si, tile_offset                 ; DS: [sI] points to the specific list of 8 tile bytes
            mov 	dx, w                           ; the width in *tiles* of the bitmap will step to correct column byte
            dec 	dx                              ; compensate for MOVSB auto increment

            mov     di, bx                          ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_X_MAX / 8            ; compare di with partial x maximum boundry / 8
            jge     END                             ; nothing to plot

            mov     cl, BYTES_PER_LINE
            mul     cl                              ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                          ; +(y / 4) * 90

            lodsb                                   ; load 8 pixels strip tile row 0 into al
            mov     es:[di] , al                    ; store row 0 bank 0 as guaranteed bank zero start in tile space coords
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 1 into al
            mov     es:[di + 2000h] , al            ; store row 1 bank 1
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 2 into al
            mov     es:[di + 4000h] , al            ; store row 2 bank 2
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 3 into al
            mov     es:[di + 6000h] , al            ; store row 3 bank 3
            add     di, 90                          ; add 90 bytes next line for all 4 banks
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 4 into al
            mov     es:[di] , al                    ; store row 4 bank 0
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 5 into al
            mov     es:[di + 2000h] , al            ; store row 5 bank 1
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 6 into al
            mov     es:[di + 4000h] , al            ; store row 6 bank 2
            add     si, dx
            lodsb                                   ; load 8 pixels strip tile row 7 into al
            mov     es:[di + 6000h] , al            ; store row 7 bank 3

            //inc     bx                              ; next column
            //inc     tile_offset
            //pop     cx                              ; retrieve COL count
            //loop    COL

            //pop     cx
            jmp     END

VRAM:       mov     ax, y                           ; load y into ax then perform screen clipping
            shl     ax, 1                           ; convert y tile row to partial(x2) pixel location
            cmp     ax, SCREEN_Y_MAX / 4            ; compare ax with partial y maximum boundry / 4
            jge     END                             ; nothing to plot

            mov     cx, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1                       ; which buffer ?
            jz      J0                              ; B000:0000 - B000 : 7FFF   First Page
            add     bx, HGA_PAGE_2_OFFSET           ; B000:8000 - B000 : FFFF   Second Page
J0:         mov     es, cx                          ; es points to screen segment

            lds     si, bytes                       ; DS: [SI] points to list of 8 tile data bytes to write
            add 	si, tile_offset                 ; DS: [sI] points to the specific list of 8 tile bytes
            mov 	dx, w                           ; the width in *tiles* of the bitmap will step to correct column byte
            dec 	dx                              ; compensate for MOVSB auto increment

            mov     di, bx                          ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_X_MAX / 8            ; compare di with partial x maximum boundry / 8
            jge     END                             ; nothing to plot

            mov     cl, BYTES_PER_LINE
            mul     cl                              ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                          ; +(y / 4) * 90
            ret

END:        popf
        }
    }*/