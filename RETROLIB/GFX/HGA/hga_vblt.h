/**
 *
 *  @brief     Suite of fast block transfer functions to copy raster data from system RAM to video screen RAM
 *  @details   Bridges the linear system RAM and the 4 banks of Hercules video RAM 
 *  + Enables fast updating of the screen from an offscreen buffer
 *  + Is byte aligned and most efficient when update rectangle is even ie divisible by 2 bytes ie a word hence MOVSW
 *  + Not designed to mask but simply replace update aka "dirty" rectangles from a back buffer to the screen
 *  @note there is no boundry checking or clipping else face undefined behaviour
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VBLT_H
#define	HGA_VBLT_H

#include <stdint.h>

namespace hga {

	/**
	* @brief fast raster *byte aligned* bit block transfer 31320 bytes from bitmap memory to the 4 banks of a VRAM buffer
	* @details used for updating the entire screen from the offscreen buffer
	* @note BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	*/
	void vblt(uint16_t vram_segment, char* raster_data);

	/**
	* @brief fast *byte aligned* rectangular block (x,y,w,h) transfer raster bytes from bitmap memory to the same location in 4 banks of a VRAM buffer
	* @details used for updating corresponding rectangles between screen and offscreen buffer
	* copies a bitmap rectangle(x,y,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. x and w values are truncated to the enclosing byte boundry
	*/
	void vblt(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	/**
	* @brief fast *byte aligned* rectangular block (a,b,w,h) transfer raster bytes from bitmap memory to new location (x,y,w,h) in 4 banks of a VRAM buffer
	* @details used for updating different rectangles between screen and offscreen buffer 
	* copies a bitmap rectangle(a,b,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. a, x and w values are truncated to the enclosing byte boundry
	*/
	void vblt(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w,  uint16_t h);

}

#endif

/*

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

*/
