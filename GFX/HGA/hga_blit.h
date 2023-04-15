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

 /**
  *  @brief If the bitmap is already interleaved and shifted then can treat the VRAM is if contiguous memory - which is faster
  *  @param x          - 
  *  @param y          - 
  *  @param byte_width - 
  *  @param height     - 
  *  @param bytes      - 
  *  @param buffer     - 
  */
	void blit_copy(uint16_t x, uint16_t y, uint16_t byte_width, uint16_t height, const char* bytes, uint16_t buffer = GLOBAL::active_buffer) {
		__asm {
			.8086

			// 1. sanity check screen coordinates and dimensions
			mov     ax, y                   ; load y into AX and sanity check       
            cmp     ax, SCREEN_Y_MAX		; below the screen?
            jge     END                     ; nothing to plot   

            mov     di, x                   ; load x into DI and sanity check
            cmp     di, SCREEN_X_MAX		; to the right of the screen?
            jge     END                     ; nothing to plot

			mov		cx, byte_width			; zero width?
			jcxz	END						; nothing to plot

			mov		cx, height				; zero height?
			jcxz	END						; nothing to plot

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
			mov		dx, di					; copy line byte index (see 3.)
            add     di, ax                  ; (x / 8) + ((y / 4) * 90)
            add     di, bx                  ; (x / 8) + ((y / 4) * 90) + ((y mod 4) * 2000h)
            
			// 3. clip the bitmap width to fit on screen
			mov		bx, byte_width			; BX width of bitmap in bytes
			add		dx, bx					; DX = x byte + byte_width
			cmp		dx, BYTES_PER_LINE		; fit on screen?
			jle		J0						; less or equal no clip, otherwise...
			sub		dx, BYTES_PER_LINE		; calculate the bytes overhang
			sub		bx, dx					; subtract overhang from byte width
			mov		byte_width, bx

	J0:		// 4. clip the bitmap height to fit on screen
			mov		dx, height				; DX height of bitmap in pixels
			mov     ax, y                   ; load y into AX then perform screen clipping 
			add		ax, dx					; AX = y + height
			cmp		ax, SCREEN_Y_MAX		; fit on screen?
			jle		J1						; less or equal no clip, otherwise...
			sub		ax, SCREEN_Y_MAX		; calculate the vertical pixel overhang
			sub		dx, ax					; subtract vertical overhang from height
			mov		height, dx

	J1:		// 5. finalse ES:[DI] to address destination bytes in chosen VRAM buffer
			mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer              ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax			        ; ES:[DI] points to first VRAM byte 

			// 6. set up DS:[SI] to point to the bitmap data
			//lds     si, bytes               ; DS:[SI] points to first bitmap byte 
			
			// 7. calculate row jump in DX (90 - byte width)
			mov		dx, BYTES_PER_LINE
			sub		dx, byte_width

			mov		ax, 0BDh
			
			mov		cx, byte_width			; load byte width counter 
			rep		stosb					; copy bitmap row to VRAM

			add		di, BYTES_PER_LINE
			sub		di, byte_width

			pop		cx						; load height counter
			loop	L0		

	END:
		}
	}

}

#endif