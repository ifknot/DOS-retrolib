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

				xor		di, di						; top left screen(0, 0)
				mov		ax, vram_segment
				mov		es, ax						; ES:DI point to VRAM destination
				lds		si, raster_data				; DS:SI point to pixel data source

				mov		cx, HGA_SCREEN_Y_MAX / 4	; HGA uses 4 banks of memory
		LINES: mov		bx, cx						; copy of lines per bank count

		BANK0: mov		cx, HGA_WORDS_PER_LINE		; 45 16it words per line
				rep		movsw						; copy raster line to vram line bank 0

		BANK1:	add		di, 1FA6h					; bank 1 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw						; copy raster line to vram line bank 1

		BANK2:	add		di, 1FA6h					; bank 2 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw						; copy raster line to vram line bank 2

		BANK3:	add		di, 1FA6h					; bank 3 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE		
				rep		movsw						; copy raster line to vram line bank 3

				sub		di, 6000h					; bank 0 next line = DI - 6000h

				mov		cx, bx						; restore lines per bank loop counter
				loop	LINES

				popf
				pop		bp
			}
		}

		void blit(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
			__asm {
				.8086
				push	bp
				pushf

				mov		ax, y 
				shr		ax,	1						; y div 4 (4 banks of VRAM)
				shr		ax, 1						; 8086 single shifts only
				mov		cl, HGA_BYTES_PER_LINE		; 
				mul		cl							; AX = (y div 4) * 90
				mov		di, ax

				mov		ax, vram_segment
				mov		es, ax						; ES:DI point to VRAM destination

				lds		si, raster_data				; DS:SI point to pixel data source
									
				mov		ax, w
				shr		ax, 1						; AX = w div 8
				shr		ax, 1
				shr		ax, 1						; 8086 single shifts only
				//test	w, 7						; mod 7
				//jz		SKIP						; zero so no remainder
				//inc		ax							; AX = (w div 8) + overlap byte
		SKIP:	mov		dx, HGA_BYTES_PER_LINE		
				//sub		dx, ax						; DX = screen byte width - rectangle byte width

				mov		cx, h						; CX = rectangle height counter
				*mov ax,cx
				shr,1 etc
				*** something w SI + (h/8)
				

				mov		ax, y						; select starting bank
				and		ax, 3						; mask only lower 3 bits i.e. 0..3
		CASE3:  cmp		ax, 3
				jne		CASE2 
				add		di, 6000h					; 4th bank offset 
				jmp		BANK3						; start on 4th bank 
		CASE2:  cmp		ax, 2
				jne		CASE1 
				add		di, 4000h					; 3rd bank offset 
				jmp		BANK2						; start on 3rd bank
		CASE1:  cmp		ax, 2
				jne		CASE0
				add		di, 2000h					; 2nd bank offset 
				jmp		BANK1						; start on 2nd bank 
		CASE0:										; fall through to zero offset 1st bank

		BANK0:	mov		bx, cx						; update copy of lines per bank count
				mov		cx, dx						; rectangle byte width
				rep		movsb						; copy raster line to vram line bank 0
				dec		bx							; dec line count 
				jz		END							; BX = 0 all done

		BANK1:	add		di, 2000h				;TODO use AX as pre sum
				sub		di, dx						; bank 1 = DI + (2000h - rectangle byte width)
				mov		cx, dx						; rectangle byte width
				rep		movsb						; copy raster line to vram line bank 1	
				dec		bx							; dec line count 
				jz		END							; BX = 0 all done

		BANK2:	add		di, 2000h
				sub		di, dx						; bank 2 = DI + (2000h - rectangle byte width)
				mov		cx, dx						; rectangle byte width
				rep		movsb						; copy raster line to vram line bank 2	
				dec		bx							; dec line count 
				jz		END							; BX = 0 all done

		BANK3:	add		di, 2000h
				sub		di, dx						; bank 3 = DI + (2000h - rectangle byte width)
				mov		cx, dx						; rectangle byte width
				rep		movsb						; copy raster line to vram line bank 3	
				dec		bx							; dec line count 
				jz		END							; BX = 0 all done

				sub		di, 6000h					; bank 0 next line = DI - 6000h

				mov		cx, bx						; restore lines per bank loop counter
				loop	BANK0

		END:	popf
				pop		bp
			}
		}

	}

}