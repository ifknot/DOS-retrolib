/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.05.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VRAM_TILE_16x16_H
#define HGA_VRAM_TILE_16x16_H

#include "hga_constants.h"
#include "hga_environment.h"

namespace hga {

	void vram_tile_16x16(uint16_t x, uint16_t y, const char* bytes, uint16_t buffer = GLOBAL::active_buffer) {
		__asm {
			.8086
			pushf
			cld								    ; increment mode

			mov     ax, y                       ; load y into AX then perform screen clipping        
            cmp     ax, SCREEN_TILE_HEIGHT - 1  ; enough room for height of tiles?
            jge     END                         ; nothing to plot        

            mov     di, x                       ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_TILE_WIDTH - 1   ; enough room for width of tiles
            jge     END                         ; nothing to plot
            
            shl     ax, 1                       ; convert y tile row to partial(x2) pixel location
            mov     cl, BYTES_PER_LINE
            mul     cl                          ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                      ; +(y / 4) * 90

		    mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax			            ; ES points to screen segment

            lds     si, bytes                   ; DS: [SI] points to list of 8 tile data bytes to write
                                                // TODO: unroll to save final wasted sub 
            mov     cx, 4                       ; 4 lots of 4 banks for 16 pixel height
    L0:     movsw                               ; move 2 bytes to bank 0 (guaranteed bank 0 start in tile space coords)
            add     di, HGA_BANK_OFFSET - 2     ; next bank is offset - byte width
            movsw                               ; next 16x16 tile pixel row to bank 1
            add     di, HGA_BANK_OFFSET - 2     ; next bank is offset - byte width
            movsw                               ; next 16x16 tile pixel row to bank 2
            add     di, HGA_BANK_OFFSET - 2     ; next bank is offset - byte width
            movsw                               ; next 16x16 tile pixel row to bank 3
            
            sub     di, 6000h - 88              ; DI = ((bank offset * 3) - bytes per line - width) to get back to the next line in bank 0
            
            loop L0

    END:    popf
		}
	}

}

#endif