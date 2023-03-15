/**
 *
 *  @brief     fast path for 8x8 bitmaps and monospaced fonts
 *  @details   90x43.5 glyph tiles per screen
 *  @author    Jeremy Thornton
 *  @date      6.03.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_WRITE_GLYPH_8x8_H 
#define HGA_WRITE_GLYPH_8x8_H

#include "hga_constants.h"
#include "hga_environment.h"

namespace hga {

	/**
    * An 8x8 font is small but readable as 90 characters per line but unfortunately the vertical 
    * screen size of 348 is not evenly divisible by 8 (320/8 = 43.5 vertical char positions)
    * @note uses partial x,y values to take advantage of cancel out shl and shr 
    * for convert up to pixel location and then down to memory location
    */
	void write_glyph_8x8(uint16_t x, uint16_t y, const char* bytes, uint8_t buffer = GLOBAL::active_buffer) {
        __asm {
		    .8086
   
            shl     y, 1                    ; convert y glyph row to partial (x2) pixel location
		    lds     si, bytes		        ; ds:[si] points to list of 8 glyph data bytes to write

		    mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1               ; which buffer ?
            jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
            add     ax, HGA_PAGE_2_OFFSET   ; B000:8000 - B000 : FFFF   Second Page
    J0:     mov     es, ax			        ; es points to screen segment
 
		    mov     ax, y                   ; load y into ax then perform screen clipping
		    cmp     ax, SCREEN_Y_MAX / 4    ; compare ax with partial y maximum boundry / 4
            jge     END                     ; nothing to plot   
           
            mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate(y / 4) * 90 nb 133 cycles 
		        
		    mov     di, x                   ; load x into di and clip to screen bounds
            cmp     di, SCREEN_X_MAX / 8    ; compare di with partial x maximum boundry / 8
            jge     END                     ; nothing to plot
            add     di, ax                  ; + (y / 4) * 90

#ifdef SYNCHRONISED                    
            mov     dx, HGA_STATUS_REG      ; HGA status reg 
    S0:     in      al, dx                  ; read status
            test    al, 1000b               ; is bit 3 set ? (in a vertical retrace interval)
            jnz     S0                      ; yes, keep waiting
    S1:     in      al, dx                  ; read status
            test    al, 1000b               ; is bit 3 set ? (just started a vertical retrace interval)
            jnz     S1                      ; no, keep waiting              
#endif
            lodsb                           ; load 8 pixels strip glyph row 0 into al
            mov     es:[di], al             ; store row 0 bank 0 as guaranteed bank zero start in glyph space coords
            lodsb                           ; load 8 pixels strip glyph row 1 into al
            mov     es:[di + 2000h], al     ; store row 1 bank 1
            lodsb                           ; load 8 pixels strip glyph row 2 into al
            mov     es:[di + 4000h], al     ; store row 2 bank 2
            lodsb                           ; load 8 pixels strip glyph row 3 into al
            mov     es:[di + 6000h], al     ; store row 3 bank 3

            add     di, 90                  ; add 90 bytes next line for all 4 banks

            lodsb                           ; load 8 pixels strip glyph row 4 into al
            mov     es : [di] , al          ; store row 4 bank 0
            lodsb                           ; load 8 pixels strip glyph row 5 into al
            mov     es : [di + 2000h], al   ; store row 5 bank 1
            lodsb                           ; load 8 pixels strip glyph row 6 into al
            mov     es : [di + 4000h], al   ; store row 6 bank 2
            lodsb                           ; load 8 pixels strip glyph row 7 into al
            mov     es : [di + 6000h], al   ; store row 7 bank 3

		    END:
		}
	}

}

#endif