/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      22.04.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VRAM_WRITE_BUFFER_H
#define HGA_VRAM_WRITE_BUFFER_H

#include "hga_constants.h"
#include "hga_environment.h"

#include "../gfx_bitmap_t.h"

namespace hga {


	/**
	*  @brief fast writes screen width bitmap data to VRAM using (assume x = 0) and bank aligned (y) Cartesian coordinates
	*  @param y - bank aligned row to start at (assume x = 0)
	*  @param bmp - a bitmap of width 720 pixels i.e. HGA screen x max and height multiples of 4 banks
	*  @param buffer - the VRAM buffer to write to
	*/
	void vram_write_buffer(uint16_t y, const char* data, uint16_t buffer = GLOBAL::active_buffer) {

	}

	/**
	*  @brief fast writes screen width and height bitmap data to VRAM assuming (0,0) coordinates
	*  @param bmp - a bitmap of 720 x 348 pixels i.e. HGA screen dimensions
	*  @param buffer - the VRAM buffer to write to
	*/
	void vram_write_screen_buffer(const char* data, uint16_t buffer = GLOBAL::active_buffer) {
		__asm {
			.8086 

			mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; es points to screen segment
			xor		di, di						; ES:[DI] points to the start of the chosen VRAM page

			lds		si, data					; DS:[SI] points to the start of 720x348 pixel data

			mov		cx, WORDS_PER_PAGE			; 16K words of data
			rep		movsw						

		}
	}

}

#endif