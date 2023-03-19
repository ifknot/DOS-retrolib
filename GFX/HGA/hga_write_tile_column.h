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
        const char* bytes = bmp->data + 56;
        uint16_t h = bmp->header->height;
        __asm {
		    .8086    

            mov     ax, x                   ; load x into AX and test screen bounds
            cmp     ax, SCREEN_TILE_WIDTH
            jge     END                     ; nothing to plot

            mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1               ; which buffer ?
            jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
            add     ax, HGA_PAGE_2_OFFSET   ; B000:8000 - B000 : FFFF   Second Page
    J0:     mov     es, ax			        ; ES points to screen segment

            mov     cx, h
            shr     cx, 1                   ; convert to height in tiles
            shr     cx, 1                   ; pixels height / 8
            shr     cx, 1                   ; 8086 limited to 1 shift at a time
ROW:        push    cx

            mov     ax, y                   ; load y into AX then perform screen clipping        
            cmp     ax, SCREEN_TILE_HEIGHT
            jge     END                     ; nothing to plot   

            mov     di, x                   ; load x into DI and clip to screen bounds
            
            shl     ax, 1                   ; convert y tile row to partial(x2) pixel location
            mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                  ; +(y / 4) * 90

		    
            lds     si, bytes               ; DS: [SI] points to list of 8 tile data bytes to write

            lodsb                           ; load 8 pixels strip tile row 0 into al
            mov     es:[di], al             ; store row 0 bank 0 as guaranteed bank zero start in tile space coords
            lodsb                           ; load 8 pixels strip tile row 1 into al
            mov     es:[di + 2000h], al     ; store row 1 bank 1
            lodsb                           ; load 8 pixels strip tile row 2 into al
            mov     es:[di + 4000h], al     ; store row 2 bank 2
            lodsb                           ; load 8 pixels strip tile row 3 into al
            mov     es:[di + 6000h], al     ; store row 3 bank 3

            add     di, 90                  ; add 90 bytes next line for all 4 banks

            lodsb                           ; load 8 pixels strip tile row 4 into al
            mov     es : [di] , al          ; store row 4 bank 0
            lodsb                           ; load 8 pixels strip tile row 5 into al
            mov     es : [di + 2000h], al   ; store row 5 bank 1
            lodsb                           ; load 8 pixels strip tile row 6 into al
            mov     es : [di + 4000h], al   ; store row 6 bank 2
            lodsb                           ; load 8 pixels strip tile row 7 into al
            mov     es : [di + 6000h], al   ; store row 7 bank 3

            inc     y

            pop     cx
            loop    ROW

		    END:
		}

    }

}

#endif