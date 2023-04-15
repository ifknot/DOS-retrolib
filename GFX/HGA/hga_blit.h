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
		__asm {
			.8086
			// 1. load args
			mov		ax, y
			mov		dx, ax					; copy y (see 4.)
			mov		di, x

			// 2. use plot point calculation ES:[DI] = (x / 8) + ((y /4 ) * 90) + ((y mod 4) * 2000h)
			mov     bx, ax                  ; copy y - BX is going to be the bank selector
            shr     ax, 1                   ; calculate (y / 4)
            shr     ax, 1                   ; 8086 limited to single step shifts
            mov     cl, BYTES_PER_LINE
            mul     cl                      ; calculate AX = ((y / 4) * 90)  

            and     bx, 00000011b           ; mask off only the bank select bits (y mod 4)
            ror     bx, 1                   ; calculate 16-bit bank * 2000h (with that one clever rotate right trick)
            ror     bx, 1                   ; 8086 limited to single step shifts
            ror     bx, 1                   ; BX = ((y mod 4) * 2000h)

            shr     di, 1                   ; calculate column byte (x / 8) 
            shr     di, 1                   ; 8086 limited to single step shifts
            shr     di, 1                   ; DI = (x / 8)
			mov		cx, di					; copy line byte index (see 3.)
            add     di, ax                  ; (x / 8) + ((y / 4) * 90)
            add     di, bx                  ; (x / 8) + ((y / 4) * 90) + ((y mod 4) * 2000h)
            
			// 3. clip the bitmap width to fit on screen
			mov		ax, cx					; AX = CX = line byte index
			add		ax, byte_width 			; AX = line byte index + byte_width
			cmp		ax, BYTES_PER_LINE		; fit on screen?
			jle		J0						; less or equal no clip, otherwise...
			sub		ax, BYTES_PER_LINE		; calculate the bytes overhang
			sub		byte_width, ax			; subtract overhang from byte width to adjust

	J0:		// 4. clip the bitmap height to fit on screen
			mov		ax, dx					; AX = DX = y
			mov		dx, height				; DX = height
			add		ax, dx					; AX = y + height
			cmp		ax, SCREEN_Y_MAX		; fit on screen?
			jle		J1						; less or equal no clip, otherwise...
			sub		ax, SCREEN_Y_MAX		; calculate the vertical pixel overhang
			sub		dx, ax					; subtract vertical overhang from height
			mov		height, dx

	J1:		

			// 5. finalse ES:[DI] to address destination bytes in chosen VRAM buffer
			mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer              ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax			        ; ES:[DI] points to first VRAM byte 

			// 6. set up DS:[SI] to point to the bitmap data
			lds     si, bytes               ; DS:[SI] points to first bitmap byte 
			
			// 7. calculate row jump in DX (90 - adjusted byte width)
			mov		bx, BYTES_PER_LINE
			sub		bx, byte_width
			
			mov		dx, height

			dec		dx						; zero base height
			shr		dx, 1					; calculate DX = (height - ) / 4 (i.e. rows per bank)
			shr		dx, 1					; 8086 limited to single step shifts
			inc		dx						; do while 

			// bank 0
			push	di
			mov		cx, dx
	B0:		push	cx

			mov		ax, 0F1h
			mov		cx, byte_width
			rep		stosb

			dec		height
			jz		END

			add		di, bx
			pop		cx
			loop	B0

			pop		di
			
			// bank 1				                 
			add		di, 2000h
			push	di
			mov		cx, dx
	B1:		push	cx

			mov		ax, 0F2h
			mov		cx, byte_width
			rep		stosb

			dec		height
			jz		END

			add		di, bx
			pop		cx
			loop	B1

			pop		di

			// bank 2				                 
			add		di, 2000h
			push	di
			mov		cx, dx
	B2:		push	cx

			mov		ax, 0F4h
			mov		cx, byte_width
			rep		stosb

			dec		height
			jz		END

			add		di, bx
			pop		cx
			loop	B2

			pop		di

			// bank 3				                 
			add		di, 2000h
			
			mov		cx, dx
	B3:		push	cx

			mov		ax, 0FFh
			mov		cx, byte_width
			rep		stosb

			dec		height
			jz		END

			add		di, bx
			pop		cx
			loop	B3

	END:
		}
	}

}

#endif