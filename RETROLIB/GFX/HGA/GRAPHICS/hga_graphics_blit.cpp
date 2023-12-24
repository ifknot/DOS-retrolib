/**
 *
 *  @file      hga_graphics_blit.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_graphics_blit.h"

#include "../hga_constants.h"

namespace hga {

	namespace graphics {

		void blit(uint16_t vram_segment, char* raster_data) {
			__asm {
				.8086
				push	bp
				pushf

				xor di, di; top left screen(0, 0)
				mov		ax, vram_segment
				mov		es, ax; ES:DI point to VRAM destination
				lds		si, raster_data; DS:SI point to pixel data source

				mov		cx, HGA_SCREEN_Y_MAX / 4; HGA uses 4 banks of memory
				LINES : mov		bx, cx; copy of lines per bank count

				BANK0 : mov		cx, HGA_WORDS_PER_LINE; 45 16it words per line
				rep		movsw; copy raster line to vram line bank 0

				BANK1:		add		di, 1FA6h; bank 1 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw; copy raster line to vram line bank 1

				BANK2:		add		di, 1FA6h; bank 2 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw; copy raster line to vram line bank 2

				BANK3:		add		di, 1FA6h; bank 3 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE		
				rep		movsw						; copy raster line to vram line bank 3

				sub		di, 6000h					; bank 0 next line = DI - 6000h

				mov		cx, bx						; restore lines per bank loop counter
				loop	LINES

				popf
				pop		bp
			}
		}

	}

}