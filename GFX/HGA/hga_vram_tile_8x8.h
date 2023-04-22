/**
 *
 *  @brief     fast path for 8x8 bitmaps and monospaced fonts
 *  @details   90x43.5 tile sper screen
 *             An 8x8 tile or font is small but readable as 90 characters per line but unfortunately the vertical 
 *             screen size of 348 is not evenly divisible by 8 (320/8 = 43.5 vertical char positions)
 *  @author    Jeremy Thornton
 *  @date      6.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VRAM_TILE_8x8_H 
#define HGA_VRAM_TILE_8x8_H

#include "hga_constants.h"
#include "hga_environment.h"

namespace hga {

    /**
    *  @brief writes a single tile to VRAM suing bank aligned and byte aligned Cartesian coordinates a.k.a. "tile space"
    *  @note special case (14% faster on XT compared to write_tile_block) for 8x8 source bitmap data 
    *  @param x           - screen tile column position 0..89
    *  @param y           - screen tile row position 0..42
    *  @param bytes       - the bitmap data
    *  @param buffer      - the buffer to write to
    */
	void vram_tile_8x8(uint16_t x, uint16_t y, const char* bytes, uint16_t buffer = GLOBAL::active_buffer) {
        __asm {
		    .8086    

            mov     ax, y                   ; load y into AX then perform screen clipping        
            cmp     ax, SCREEN_TILE_HEIGHT
            jge     END                     ; nothing to plot   

            mov     di, x                   ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_TILE_WIDTH
            jge     END                     ; nothing to plot
            
            shl     ax, 1                   ; convert y tile row to partial(x2) pixel location
            mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                  ; +(y / 4) * 90

		    mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer              ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax			        ; ES points to screen segment

            lds     si, bytes               ; DS: [SI] points to list of 8 tile data bytes to write

            movsb 				            ; movsb row 0 bank 0 as guaranteed bank 0 start in tile space coords
            add     di, 1FFFh			    ; DI and SI auto inc by 1 so bank 1 is DI + 2000h - 1
            movsb 				            ; tile pixel row 1 to bank 1
            add 	di, 1FFFh			    ; DI and SI auto inc by 1 so bank 2 is DI + 2000h - 1
            movsb 				            ; tile pixel row 2 to bank 2
            add 	di, 1FFFh			    ; DI and SI auto inc by 1 so bank 3 is DI + 2000h - 1
            movsb 				            ; tile pxiel row 3 to bank 3
            
            sub 	di, 5FA7h			    ; 6000h - 89 to get DI back to next bank

            movsb 				            ; tile pixel row 4 to bank 0
            add 	di, 1FFFh			    ; DI and SI auto inc by 1 so bank 1 is DI + 2000h - 1
            movsb 				            ; tile pixel row 5 to bank 1
            add 	di, 1FFFh			    ; DI and SI auto inc by 1 so bank 2 is DI + 2000h - 1
            movsb 				            ; tile pixel row 6 to bank 2
            add 	di, 1FFFh			    ; DI and SI auto inc by 1 so bank 3 is DI + 2000h - 1
            movsb 				            ; tile pxiel row 7 to bank 3

		    END:
		}
	}

    /**
    *  @brief writes a single tile *from a buffer* to VRAM using bank aligned and byte aligned Cartesian coordinates a.k.a. "tile space"
    *  @note special case (14% faster on XT compared to write_tile_block) for 8x8 source bitmap data 
    *  @brief writes a single tile within the bitmap data to vram 
    *  @note special case (14% x faster on XT) for 8x8 source bitmap data 
    *  @param x           - screen tile column position 0..89
    *  @param y           - screen tile row position 0..42
    *  @param bytes       - the bitmap data
    *  @param step        - the offset in the data of tile bytes
    *  @param buffer      - the buffer to write to
    */
	void vram_tile_8x8_from_buffer(uint16_t x, uint16_t y, const char* bytes, uint16_t step, uint8_t buffer = GLOBAL::active_buffer) {
        __asm {
		    .8086    

            mov     ax, y                   ; load y into AX then perform screen clipping        
            cmp     ax, SCREEN_TILE_HEIGHT
            jge     END                     ; nothing to plot   

            mov     di, x                   ; load x into DI and clip to screen bounds
            cmp     di, SCREEN_TILE_WIDTH
            jge     END                     ; nothing to plot
            
            shl     ax, 1                   ; convert y tile row to partial(x2) pixel location
            mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate(y / 4) * 90 nb 133 cycles
            add     di, ax                  ; +(y / 4) * 90

		    mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1               ; which buffer ?
            jz      J0                      ; B000:0000 - B000 : 7FFF   First Page
            add     ax, HGA_PAGE_2_OFFSET   ; B000:8000 - B000 : FFFF   Second Page
    J0:     mov     es, ax			        ; ES points to screen segment

            lds     si, bytes               ; DS: [SI] points to list of 8 tile data bytes to write
            mov     cx, step
            dec     cx                      ; compensate for MOVSB auto increment

            movsb 				            ; movsb row 0 bank 0 as guaranteed bank 0 start in tile space coords
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 1 is DI + 2000h - 1
            movsb 				            ; tile pixel row 1 to bank 1
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 2 is DI + 2000h - 1
            movsb 				            ; tile pixel row 2 to bank 2
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 3 is DI + 2000h - 1
            movsb 				            ; tile pxiel row 3 to bank 3
            add       si, cx

            sub 	  di, 5FA7h			    ; 6000h - 89 to get DI back to next bank

            movsb 				            ; tile pixel row 4 to bank 0
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 1 is DI + 2000h - 1
            movsb 				            ; tile pixel row 5 to bank 1
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 2 is DI + 2000h - 1
            movsb 				            ; tile pixel row 6 to bank 2
            add       si, cx
            add 	  di, 1FFFh			    ; DI and SI auto inc by 1 so bank 3 is DI + 2000h - 1
            movsb 				            ; tile pxiel row 7 to bank 3

		    END:
		}
	}

}

#endif