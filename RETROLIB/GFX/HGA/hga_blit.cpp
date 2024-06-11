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
#include "hga_blit.h"

#include "hga_constants.h"

namespace hga {

/* TEST *****************************************************************************************/

	// MOVSW wallpaper
	void wallpaper16(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w, uint16_t h) {
		__asm {
			.8086
			push	bp
			pushf 

			// 1. setup RAM source pointer DS:SI = (y * 90) + (x div 8)
			lds		si, raster_data
			mov		ax, b
			mov		cx, HGA_BYTES_PER_LINE		; CX = 90
			mul		cx							; AX = (b * 90) 
			mov		bx, a						; BX = (a div 8)
			shr		bx, 1						;	.
			shr		bx, 1						;	.
			shr		bx, 1						;	.
			//push	bx							; save (a div 8) see section 4.5
			add		ax, bx						; AX = (b * 90) + (a div 8)
			add		si, ax						; DS:SI point to pixel data source

			// 2. setup HGA quad bank VRAM destination pointer ES:DI = ((y div 4) * 90) + (x div 8)
			mov		ax, vram_segment
			mov		es, ax
			mov		ax, y						; AX = (y div 4)
			shr		ax, 1						;	.
			shr		ax, 1						;	.	
			mul		cx							; AX = (y div 4) * 90
			mov		bx, x						; BX = (x div 8)
			shr		bx, 1						;	.
			shr		bx, 1						;	.
			shr		bx, 1						;	.

			//mov		bx,1

			add		ax, bx						; AX = (y div 4) * 90) + (x div 8)
			mov		di, ax						; ES:DI point to VRAM destination

			// 3. calculate (w div 8)
			mov		cx, w 
			shr		cx, 1
			shr		cx, 1
			shr		cx, 1

			// 4. set up the registers and (w div 16)
			// 4.1 AX = next VRAM line offset HGA_BYTES_PER_LINE - (w div 8) - (x div 8) 
			mov		ax, HGA_BYTES_PER_LINE		; 90
			sub		ax, cx						; 90 - (w div 8)
			sub		ax, bx						; 90 - (w div 8) - (x div 8)
			// 4.2 calculate (w div 16)
			shr		cx, 1
			mov		w, cx
			// 4.3 BX = next BMP line offset HGA_BYTES_PER_LINE - (w div 8) - (x div 8)  
			shr		bx, 1						; BX = (x div 16)
			// 4.4 CX = y mod 3 to select the start VRAM bank
			mov		cx, y
			and		cx, 3						; mask y lower 3 bits i.e. 0..3
			// 4.5 DX = height div 4, i.e. number of raster lines
			mov		dx, h
			// 4.6 BP = w (safe to use BP as all args using [BP + ] no longer needed to access)
			mov		bp, w

			// 5. jump to the correct starting bank 
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

			// 6. move the raster data in 2 byte blocks 
BANK0:		mov		cx, bp						; copy (w div 16) into CX
			rep movsw							; copy source rect line to vram line bank 0
			dec		dx							; dec line count 
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)

	BANK1:	mov		cx, bp						; copy (w div 16) into CX
			rep movsw							; copy source rect line to vram line bank 0
			dec		dx							; dec line count 
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
		
	BANK2:	mov		cx, bp						; copy (w div 16) into CX
			rep movsw							; copy source rect line to vram line bank 0
			dec		dx							; dec line count 
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			
	BANK3:	mov		cx, bp						; copy (w div 16) into CX
			rep movsw							; copy source rect line to vram line bank 0
			dec		dx							; dec line count 
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h

			jmp		BANK0						; loop around until all lines drawn

	END:

			popf
			pop		bp 
		}
	}

/******************************************************************************************/

	// word blit fullscreen raster 32K to VRAM
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data) {
		__asm {
			.8086
			push	bp
			pushf

			xor		di, di						; top left screen(0, 0)
			mov		ax, vram_segment
			mov		es, ax						; ES:DI point to VRAM destination
			lds		si, raster_data				; DS:SI point to pixel data source

			mov		cx, HGA_SCREEN_Y_MAX / 4	; HGA uses 4 banks of memory
	LINES:	mov		bx, cx						; copy of lines per bank count

	BANK0:	mov		cx, HGA_WORDS_PER_LINE		; 45 16it words per line
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

	// byte blit rectangle x,y,w,h from fullscreen raster to VRAM 
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
		__asm {
			.8086								; NB clock cycle comments refer to 8086
			push	bp
			pushf

			// setup HGA quad bank VRAM destination pointer ES:DI = ((y div 4) * 90) + (x div 8)
			mov		ax, vram_segment
			mov		es, ax
			mov		ax, y						; AX = (y div 4)
			shr		ax, 1
			shr		ax, 1
			mov		cx, HGA_BYTES_PER_LINE		; CX = 90
			mul		cx							; AX = (y div 4) * 90
			mov		bx, x						; BX = (x div 8)
			shr		bx, 1
			shr		bx, 1
			shr		bx, 1
			add		ax, bx						; AX = (y div 4) * 90) + (x div 8)
			mov		di, ax						; ES:DI point to VRAM destination

			// setup RAM source pointer DS:SI = (y * 90) + (x div 8)
			lds		si, raster_data
			mov		ax, y
			mul		cx							; AX = (y * 90) (CX extant = 90)
			add		ax, bx						; AX = (y * 90) + (x div 8)
			add		si, ax						; DS:SI point to pixel data source

			// calculate w = (w div 8) + ((w mod 8) != 0 ? 1 : 0)
			mov		ax, w
			mov		cx, ax						; copy w(2 clocks)
			shr		ax, 1						; AX = (w div 8)
			shr		ax, 1
			shr		ax, 1
			and		cx, 7						; mod 8 != 0 ? (4 clocks vs test w, 7 mem, imm 11 clocks)
			jz		SKIP						; zero so no remainder
			inc		ax							; increment byte width - partial byte overlap
	SKIP:	mov		w, ax						; w = (w div 8)

			// calculate next line offset AX = 90 - (w div 8) - (x div 8)
			mov		cx, HGA_BYTES_PER_LINE		; 90
			sub		cx, ax						; 90 - (w div 8)
			sub		cx, bx						; 90 - (w div 8) - (x div 8)
			mov		ax, cx						; AX = 90 - (w div 8) - (x div 8)

			// using dec reg(3 clocks x 4 per loop = 12 clocks) vs dec mem(15 clocks x 4 per loop = 60 clocks!)
			mov		dx, h

			// use CX mod 3 to select the start VRAM bank	
			mov		cx, y
			// safe to use BP as all args using [BP + ] no longer needed to access		
			mov		bp, w						; last of all, with all args used, load BP width

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

	BANK0:	add		si, bx						; start offset RAM source  
			add		di, bx						; start offset VRAM destination
			mov		cx, bp						; width counter (mov reg, reg 2 clocks)
			rep		movsb						; copy source rect line to vram line bank 0
			dec		dx							; dec line count (3 clocks)
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			
	BANK1:	add		si, bx						; start offset RAM source  
			add		di, bx						; start offset VRAM destination	
			mov		cx, bp						; width counter(mov reg, reg 2 clocks)
			rep		movsb						; copy source rect line to vram line bank 1	
			dec		dx							; dec line count (3 clocks)
			jz		END							; DX = 0 all lines copied to VRAM
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 2 = DI + (2000h - 90)

	BANK2:	add		si, bx						; start offset RAM source  
			add		di, bx						; start offset VRAM destination
			mov		cx, bp						; width counter(mov reg, reg 2 clocks)
			rep		movsb						; copy source rect line to vram line bank 2	
			dec		dx							; dec line count (3 clocks)
			jz		END							; DX = 0 all lines copied to VRAM
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 3 = DI + (2000h - 90)

	BANK3:	add		si, bx						; start offset RAM source  
			add		di, bx						; start offset VRAM destination
			mov		cx, bp						; width counter(mov reg, reg 2 clocks)
			rep		movsb						; copy source rect line to vram line bank 3	
			dec		dx							; dec line count (3 clocks)
			jz		END							; DX = 0 all lines copied to VRAM
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h

			jmp		BANK0

	END:	popf
			pop		bp
		}
	}

}
