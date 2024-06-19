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

	void test_blit(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w, uint16_t h) {
		__asm {
			.8086								
			pushf								; preserve flags on entry (direction flag used)

			// 1. setup RAM source pointer DS:SI = (b * 90) + (a div 8)
			lds		si, raster_data
			mov		ax, b
			mov		cx, HGA_BYTES_PER_LINE		; CX = 90
			mul		cx							; AX = (b * 90)
			mov		bx, a						; BX = (a div 8)
			shr		bx, 1						;	.
			shr		bx, 1						;	.
			shr		bx, 1						;	.
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
			add		ax, bx						; AX = (y div 4) * 90) + (x div 8)
			mov		di, ax						; ES:DI point to VRAM destination
			// 3. set up the registers and select execution path
			// 3.1 clear the direction flag so that SI and DI will be incremented by chain instructions
			cld
			// 3.2 DX = height i.e. number of raster lines
			mov		dx, h
			// 3.3 CX = y mod 3 to select the start VRAM bank
			mov		cx, y
			and		cx, 3						; mask y lower 3 bits i.e. 0..3
			// 3.4 BX = (w div 8) because HGA bit depth is 8 pixels per byte
			mov		bx, w
			shr		bx, 1
			shr		bx, 1
			shr		bx, 1
			// 3.5 AX = next line offset HGA_BYTES_PER_LINE - (w div 8)
			mov		ax, HGA_BYTES_PER_LINE		; 90
			sub		ax, bx						; 90 - (w div 8)
			// 3.6 test if width is even?
			test	bx, 1
			jz		EVEN
			// 3a.7 BX = (w div 16) to count the words to MOVSW
			shr		bx, 1
			// 4a. jump to the correct starting bank 
	ACASE3: cmp		cx, 3						; select starting bankand initial DI offset
			jne		ACASE2
			add		di, HGA_BANK_OFFSET * 3		; 4th bank offset
			jmp		ABANK3						; start on 4th bank
	ACASE2: cmp		cx, 2
			jne		ACASE1
			add		di, HGA_BANK_OFFSET * 2		; 3rd bank offset
			jmp		ABANK2						; start on 3rd bank
	ACASE1: cmp		cx, 1
			jne		ACASE0
			add		di, HGA_BANK_OFFSET			; 2nd bank offset
			jmp		ABANK1						; start on 2nd bank
	ACASE0:										; fall through to zero offset 1st bank
			// 5a. The width is an odd number of bytes extra MOVSB adds 18 clocks to each raster line copy
			// the wider the bitmap the smaller the influence of the MOVSB worst case 3 byte raster line 63 vs 63 + 18 (22% slower)
			// TODO: wait for vertical blank interval
			// 5a.1 bank 0																	[       cycles        ]
	ABANK0: movsb								; copy single byte bank 0						18
			mov		cx, bx						; copy(w div 16) into CX						 2
			rep		movsw						; copy source rect line to vram line bank 0		(2 + 18) * CX
			dec		dx							; dec line count								 2
			jz		BREAK						; DX = 0 all done								 4 (not taken)
			add		si, ax						; RAM source next line							 3
			add		di, ax						; VRAM next line								 3
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)	 9
			// 5a.2 bank 1
	ABANK1:	movsb								; copy single byte bank 1
			mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 1
			dec		dx							; dec line count
			jz		BREAK						; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 5a.3 bank 2
	ABANK2:	movsb								; copy single byte bank 2
			mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 2
			dec		dx							; dec line count
			jz		BREAK						; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 5a.4 bank 3
	ABANK3:	movsb								; copy single byte bank 3 
			mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 3
			dec		dx							; dec line count
			jz		BREAK						; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h
			// 6a. until all raster lines done i.e. height(h)
			jmp		ABANK0						; loop around until all lines drawn
			// 8. restore registers
	BREAK:	jmp		END

	EVEN:	// 3b.7 BX = (w div 16) to count the words to MOVSW
			shr		bx, 1
			// 4b. jump to the correct starting bank 
	CASE3:  cmp		cx, 3						; select starting bankand initial DI offset
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
			// 5b. move the raster data in 2 byte blocks 
			// TODO: wait for vertical blank interval
			// 5b.1 bank 0
	BANK0:  mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 0
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 5b.2 bank 1
	BANK1:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 1
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 5b.3 bank 2
	BANK2:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 2
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 5b.4 bank 3
	BANK3:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 3
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h
			// 6b. until all raster lines done i.e. height(h)
			jmp		BANK0						; loop around until all lines drawn
	END:
			popf								; restore flags on exit
		}

	}


	// word blit fullscreen bitmap to VRAM
	void word_blit_byte_aligned_vram_bmp(uint16_t vram_segment, char* raster_data) {
		__asm {
			.8086
			pushf								; preserve flags on entry (direction flag used)

			// 1. setup RAM source pointer DS:SI
			lds		si, raster_data; DS:SI point to pixel data source
			// 2. setup HGA quad bank VRAM destination pointer ES:DI
			xor		di, di						; top left screen(0, 0)
			mov		ax, vram_segment
			mov		es, ax						; ES:DI point to VRAM destination
			// 3. set up the lines per bank counter CX and persitent copy BX
			mov		cx, HGA_SCREEN_Y_MAX / 4	; HGA uses 4 banks of memory
	LINES:	mov		bx, cx						; copy of lines per bank count
			// 4. move the raster data in 2 byte blocks  
			// TODO: wait for vertical blank interval - for each bank? 
			// 4.0 clear the direction flag so that SI and DI will be incremented by chain instructions
			cld
			// 4.1 bank 0
	BANK0:	mov		cx, HGA_WORDS_PER_LINE		; 45 16it words per line
			rep		movsw						; copy source rect line to vram line bank 0
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 4.2 bank 1
	BANK1:	mov		cx, HGA_WORDS_PER_LINE
			rep		movsw						; copy source rect line to vram line bank 1
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 2 = DI + (2000h - 90)
			// 4.3 bank 2
	BANK2:	mov		cx, HGA_WORDS_PER_LINE
			rep		movsw						; copy source rect line to vram line bank 2
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 3 = DI + (2000h - 90)
			// 4.4 bank 3
	BANK3:	mov		cx, HGA_WORDS_PER_LINE		
			rep		movsw						; copy source rect line to vram line bank 3
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h
			// 5. load CX with lines per bank counter and loop until done
			mov		cx, bx						; restore lines per bank loop counter
			loop	LINES

			popf								; restore flags on exit
		}
	}

	// byte blit fullscreen bitmap rectangle(x,y,w,h) to VRAM rectangle(x,y,w,h)
	void byte_blit_byte_aligned_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
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

	// word blit fullscreen bitmap rectangle(a,b,w,h) to VRAM rectangle(x,y,w,h)
	void word_blit_byte_aligned_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w, uint16_t h) {
		__asm {
			.8086
			pushf								; preserve flags on entry (direction flag used)

			// 1. setup RAM source pointer DS:SI = (b * 90) + (a div 8)
			lds		si, raster_data
			mov		ax, b
			mov		cx, HGA_BYTES_PER_LINE		; CX = 90
			mul		cx							; AX = (b * 90)
			mov		bx, a						; BX = (a div 8)
			shr		bx, 1						;	.
			shr		bx, 1						;	.
			shr		bx, 1						;	.
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
			add		ax, bx						; AX = (y div 4) * 90) + (x div 8)
			mov		di, ax						; ES:DI point to VRAM destination
			// 3. reserved for 8bit strip select
			
			// 4. set up the registers
			// 4.0 clear the direction flag so that SI and DI will be incremented by chain instructions
			cld
			// 4.1 BX = (w div 8) because HGA bit depth is 8 pixels per byte
			mov		bx, w
			shr		bx, 1
			shr		bx, 1
			shr		bx, 1
			// 4.2 AX = next line offset HGA_BYTES_PER_LINE - (w div 8)
			mov		ax, HGA_BYTES_PER_LINE		; 90
			sub		ax, bx						; 90 - (w div 8)
			// 4.3 BX = (w div 16) to count the words to MOVSW
			shr		bx, 1
			// 4.4 CX = y mod 3 to select the start VRAM bank
			mov		cx, y
			and		cx, 3						; mask y lower 3 bits i.e. 0..3
			// 4.5 DX = height i.e. number of raster lines
			mov		dx, h
			// 5. jump to the correct starting bank 
	CASE3:  cmp		cx, 3						; select starting bankand initial DI offset
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
			// TODO: wait for vertical blank interval
			// 6.1 bank 0
	BANK0:  mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 0
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 6.2 bank 1
	BANK1:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 0
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 6.3 bank 2
	BANK2:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 0
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			add		di, HGA_BANK_OFFSET - HGA_BYTES_PER_LINE	; bank 1 = DI + (2000h - 90)
			// 6.4 bank 3
	BANK3:	mov		cx, bx						; copy(w div 16) into CX
			rep		movsw						; copy source rect line to vram line bank 0
			dec		dx							; dec line count
			jz		END							; DX = 0 all done
			add		si, ax						; RAM source next line
			add		di, ax						; VRAM next line
			sub		di, HGA_BANK_OFFSET * 3		; bank 0 next line = DI - 6000h
			// 7. until all raster lines done i.e. height(h)
			jmp		BANK0						; loop around until all lines drawn
			// 8. break out of loop
	END:

			popf								; restore flags on exit
		}
	}

}

