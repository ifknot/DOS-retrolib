/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef	HGA_BLIT_H
#define HGA_BLIT_H

#include <assert.h>

#include "hga_constants.h"
#include "hga_environment.h"


namespace hga {

	void blit_copy_h4() {}

	void blit_copy_h8() {}

 /**
  *  @brief If the bitmap is already interleaved and shifted then can treat the VRAM is if contiguous memory - which is faster
  *  @note bitmap height *must* be a multiple of 4
  *  @param x          - 
  *  @param y          - 
  *  @param byte_width - 
  *  @param height     - 
  *  @param bytes      - 
  *  @param buffer     - 
  */
	void blit_copy(uint16_t x, uint16_t y, uint16_t byte_width, uint16_t height, const char* bytes, uint16_t buffer = GLOBAL::active_buffer) {
		assert(x < SCREEN_X_MAX);
		assert(y < SCREEN_Y_MAX);
		assert(byte_width > 0);
		assert(height > 0);
		//assert((height & 3) == 0);
		uint16_t row, bank_height;
		__asm {
			.8086
			// calculate row byte index	x / 8
			mov		ax, x					; AX = x
            shr     ax, 1                   ; calculate column byte (x / 8) 
            shr     ax, 1                   ; 8086 limited to single step shifts
            shr     ax, 1                   ; AX = (x / 8)
			mov		x, ax					; x >>= 3
			// clip the bitmap width to fit on screen
			add		ax, byte_width			; AX = (x / 8) + byte_width
			cmp		ax, BYTES_PER_LINE		; fit on screen?
			jle		J0						; less or equal no clip, otherwise...
			sub		ax, BYTES_PER_LINE		; calculate the bytes overhang
			sub		byte_width, ax			; subtract overhang from byte width to adjust
	J0:		// clip the bitmap height to fit on screen
			mov		ax, y
			add 	ax, height				; AX = y + height
			cmp		ax, SCREEN_Y_MAX		; fit on screen?
			jle		J1						; less or equal no clip, otherwise...
			sub		ax, SCREEN_Y_MAX		; calculate the vertical pixel overhang
			sub		height, ax				; subtract vertical overhang from height
	J1:		// ES chosen VRAM buffer
			mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer              ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax			        ; ES:[DI] points to first VRAM byte 
			// set up DS:[SI] to point to the bitmap data
			lds     si, bytes               ; DS:[SI] points to first bitmap byte 
			// caluclate bytes to add for next row
			mov		ax, BYTES_PER_LINE
			sub		ax, byte_width
			mov		row, ax
			// calculate number of rows to copy into each bank in height and dx
			mov		ax, height				; load height into AX
			mov		dx, ax	
			dec		ax						; zero base height
			shr		ax, 1					; height / 4
            shr     ax, 1                   ; 8086 limited to single step shifts
			mov		bank_height, ax				; bank height ie height / 4	
			and		dx, 3					;  
			inc		dx

			mov		cx, height
	L0:		call	BANK
			inc		y
			loop	L0

			jmp		END
			// ----------------------------------------- //
	BANK:
			push	cx
			// calculate row offset
			mov		ax, y					; AX = y
			mov		bx, ax					; BX will be the bank offset
			shr		ax, 1					; (y / 4)
            shr     ax, 1                   ; 8086 limitediloveyou to single step shifts
			mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate AX = ((y / 4) * 90)  
			// calculate bank offset
			and     bx, 00000011b           ; mask off only the bank select bits (y mod 4)
			ror     bx, 1                   ; calculate 16-bit bank * 2000h (with that one clever rotate right trick)
            ror     bx, 1                   ; 8086 limited to single step shifts
            ror     bx, 1                   ; BX = ((y mod 4) * 2000h)
			// DI = (x / 8) + ((y / 4) * 90) + ((y % 4) * 2000h)
			mov		di, x					; (x / 8)
			add		di, ax					; + ((y / 4) * 90)
			add		di, bx					; +((y % 4) * 2000h)

			// test
			mov		al, 0F1h

			mov		cx, bank_height			; bank height
			jcxz	Z0						; loop counter zero
	B0:		push	cx						; copy bank height rows in bank 0 
			mov		cx, byte_width
			rep		stosb
			add		di, row
			pop		cx
			loop	B0
	Z0:		mov		cx, dx
			jcxz	DONE
			mov		cx, byte_width
			rep		stosb
			dec		dx

	DONE:	pop		cx
			ret
			
			
	END:
		}
	}

}

#endif