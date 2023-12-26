/**
 *
 *  @file      hga_graphics_blit.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
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
				rep		movsw						; copy source rect line to vram line bank 0

		BANK1:	add		di, 1FA6h					; bank 1 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw						; copy source rect line to vram line bank 1

		BANK2:	add		di, 1FA6h					; bank 2 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE
				rep		movsw						; copy source rect line to vram line bank 2

		BANK3:	add		di, 1FA6h					; bank 3 = DI + (2000h - 90)
				mov		cx, HGA_WORDS_PER_LINE		
				rep		movsw						; copy source rect line to vram line bank 3

				sub		di, 6000h					; bank 0 next line = DI - 6000h

				mov		cx, bx						; restore lines per bank loop counter
				loop	LINES

				popf
				pop		bp
			}
		}

		void blit(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
			__asm {
				.8086								; NB clock cycle comments refer to 8086
				push	bp
				pushf

				// setup VRAM destination pointer ES:DI
				mov		ax, vram_segment
				mov		es, ax
				mov		ax, y
				shr		ax, 1						; y div 4 (4 banks of VRAM)
				shr		ax, 1						; 8086 single shifts only
				mov		cx, HGA_BYTES_PER_LINE
				mul		cx							; AX = (y div 4) * 90
				mov		di, ax						; ES:DI point to VRAM destination

				// setup RAM source pointer DS:SI 
				lds		si, raster_data
				mov		ax, y
				mul		cx							; AX = y * 90
				add		si, ax						; DS:SI point to pixel data source
				
				// calculate w = w div 8 and increment if mod 8 != 0 
				mov		bx, w						
				mov		ax, bx						; copy w (2 clocks)
				shr		bx, 1						; BX = (w div 8)
				shr		bx, 1
				shr		bx, 1						; 8086 single shifts only
				//and	ax, 7						; mod 8 != 0? (4 clocks vs test w, 7 mem,imm 11 clocks)
				//jz		SKIP					; zero so no remainder
				//inc		bx						; increment byte width for partial byte overlap
		SKIP:	mov		w, bx						; w = (w div 8) 'rect byte width'

				//select movsb (odd rect byte width) or movsw (even rect byte width) blit routine
				// test		bx, 1
				// jz		EVEN					; even width jmp to faster movsw version 

				// calculate (x div 8)
				mov		ax, x
				shr		ax, 1						; AX = (x div 8)
				shr		ax, 1
				shr		ax, 1	

				// calculate y = 2000h - (w div 8) - (x div 8) offset for next line VRAM bank		
				mov		dx, HGA_BANK_OFFSET			; 2000h	
				sub		dx, bx						; - (w div 8)
				sub		dx, ax						; - (x div 8)
				mov		cx, y						; copy y
				mov		y, dx						; x = 2000h - (w div 8) - (x div 8) 'next bank offset'
				
										

				// calculate 
				mov		ax, HGA_BYTES_PER_LINE		; AX = SI increment
				sub		ax, bx						; 90 - rect_byte_width - (x div 8)

				// setup rect line count putting h into DX enables loop dec reg(3 clocks x 3 per loop ) vs dec mem(15 clocks x 3 per loop !)
				mov		dx, h

				// use CX mod 3 to select the start VRAM bank						
				and		cx, 3						; mask y lower 3 bits i.e. 0..3
		CASE3:  cmp		cx, 3						; select starting bank and initial DI offset
				jne		CASE2 
				add		di, HGA_BANK_OFFSET * 3		; 4th bank offset
				jmp		BANK3						; start on 4th bank 
		CASE2:  cmp		cx, 2
				jne		CASE1 
				add		di, HGA_BANK_OFFSET * 2		; 3rd bank offset
				jmp		BANK2						; start on 3rd bank
		CASE1:  cmp		cx, 1
				jne		CASE0
				add		di, HGA_BANK_OFFSET			; 2nd bank offset
				jmp		BANK1						; start on 2nd bank 
		CASE0:										; fall through to zero offset 1st bank

		BANK0:	mov		cx, w						; width counter (use 8 clock reg,mem releases BX to use in faster 3 clock reg,reg sums)
				rep		movsb						; copy source rect line to vram line bank 0
				dec		dx							; dec line count (3 clocks)
				jz		END							; DX = 0 all done
				add		si, ax						; advance source to next line
				add		di, y						; next bank (use a 9 clock reg,mem to save 3 reg,reg 3 clocks each)
			
		BANK1:	mov		cx, w						; rectangle byte width
				rep		movsb						; copy source rect line to vram line bank 1	
				dec		dx							; dec line count (3 clocks)
				jz		END							; DX = 0 all lines copied to VRAM
				add		si, ax						; advance source to next line
				add		di, y						; next bank

		BANK2:	mov		cx, w						; rectangle byte width
				rep		movsb						; copy source rect line to vram line bank 2	
				dec		dx							; dec line count (3 clocks)
				jz		END							; DX = 0 all lines copied to VRAM
				add		si, ax						; advance source to next line
				add		di, y						; next bank

		BANK3:	mov		cx, w						; rectangle byte width
				rep		movsb						; copy source rect line to vram line bank 3	
				dec		dx							; dec line count (3 clocks)
				jz		END							; DX = 0 all lines copied to VRAM
				add		si, ax						; advance source to next line
				sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h
				add		di, ax						// (use a 9 clock reg,mem to save 3 reg,reg 3 clocks each)  

				jmp		BANK0

		END:	popf
				pop		bp
			}
		}

	}

}