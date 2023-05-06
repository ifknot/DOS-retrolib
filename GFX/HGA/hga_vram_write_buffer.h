/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      22.04.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
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
	void vram_write_buffer(uint16_t y, const gfx::simple_bitmap_t* bmp, uint16_t buffer = GLOBAL::active_buffer) {
		assert(bmp->ihdr.width == SCREEN_X_MAX);
		uint16_t h = bmp->ihdr.height;
		const char* bytes = bmp->idat.data;
		// TODO: screen clip bmp.height
		__asm {
			.8086 
			pushf
			cld                                 ; increment mode

			mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; ES points to screen segment
			lds     si, bytes                   ; DS:[SI] points to list of 8 tile data bytes to write

			mov		ax, y						; load AX with pixel y
			shr		ax, 1						; AX = y / 4
			shr		ax, 1						; 8086 single shifts only 
			mov		bx, ax						; bx is a copy of y / number of vram banks
			mov     cl, BYTES_PER_LINE
            mul     cl							; calculate(y / 4) * 90 - nb 133 cycles
            mov     di, ax						; ES:[DI] = VRAM segment + (y / 4) * 90 

			mov		cx, h						; load CX with bmp height
			jcxz	END
	L0:		mov		bx, cx						; bx is a copy of h as the row count 

            mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 0
			dec		bx							; dec row count 
			jz		END

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 1 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 1
			dec		bx							; dec row count 
			jz		END

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 2 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 2
			dec		bx							; dec row count 
			jz		END

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 3 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line  to bank 0

			sub		di, 6000h 
			mov		cx, bx				
			loop	L0							; dec row count and loop

	END:	popf
		}
	}

	/**
	*  @brief fast writes screen width and height bitmap to VRAM assuming (0,0) coordinates
	*  @param bmp - a bitmap of 720 x 348 pixels i.e. HGA screen dimensions
	*  @param buffer - the VRAM buffer to write to
	*/
	void vram_write_buffer(const gfx::simple_bitmap_t* bmp, uint16_t buffer = GLOBAL::active_buffer) {
		assert(bmp->ihdr.width == SCREEN_X_MAX);
		assert(bmp->ihdr.height == SCREEN_Y_MAX);
		const char* bytes = bmp->idat.data;
		__asm {
			.8086 
			pushf
			cld                                 ; increment mode

            mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; ES points to screen segment
            xor     di, di						; ES:[DI] points to top left of screen
			lds     si, bytes                   ; DS:[SI] points to list of 8 tile data bytes to write

			mov		cx, SCREEN_Y_MAX / 4
	L0:		mov		bx, cx						; bx is a copy of y / number of vram banks

            mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 0

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 1 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 1

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 2 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line to bank 2 

			add     di, 1FA6h					; DI and SI auto inc by 2 so bank 3 is DI + 2000h - 90
			mov     cx, WORDS_PER_LINE          ; 45 words per line
            rep     movsw                       ; copy a screen line  to bank 0

			sub		di, 6000h 
			mov		cx, bx
			loop	L0
			
            popf                
		}

	}

	namespace sync {

		/**
		*  @brief Waits for the vertival sync beforefast writes screen width and height bitmap to VRAM assuming (0,0) coordinates
		*  @param bmp - a bitmap of 720 x 348 pixels i.e. HGA screen dimensions
		*  @param buffer - the VRAM buffer to write to
		*/
		void vram_write_buffer(const gfx::simple_bitmap_t* bmp, uint16_t buffer = GLOBAL::active_buffer) {
			//assert(bmp->ihdr.width == SCREEN_X_MAX);
			//assert(bmp->ihdr.height == SCREEN_Y_MAX);
			const char* bytes = bmp->idat.data;
			__asm {
				.8086
				pushf
				cld								; increment mode

				mov     ax, HGA_VIDEO_RAM_SEGMENT
				add     ax, buffer				; 0000h or 0B000h for first or second VRAM buffer
				mov     es, ax					; ES points to screen segment
				xor		di, di					; ES: [DI] points to top left of screen
				lds     si, bytes				; DS: [SI] points to list of 8 tile data bytes to write

				mov		cx, SCREEN_Y_MAX / 4

				mov     dx, CRTC_STATUS_PORT	; set DX port 3BAh
	vWAIT0:		in      al, dx					; read status
				test    al, 10000000b			; is bit 7 clear ? (in a vertical retrace interval)
				jz      VWAIT0					; yes, keep waiting
	VWAIT1:		in      al, dx					; read status again
				test    al, 10000000b			; is bit 7 clear ? (just started a vertical retrace interval)
				jz      VWAIT1					; no, keep waiting

	L0:			mov		bx, cx

				mov     cx, WORDS_PER_LINE		; 45 words per line
				rep     movsw					; copy a screen line to bank 0

				add     di, 1FA6h				; DI and SI auto inc by 2 so bank 1 is DI + 2000h - 90
				mov     cx, WORDS_PER_LINE		; 45 words per line
				rep     movsw					; copy a screen line to bank 1

				add     di, 1FA6h				; DI and SI auto inc by 2 so bank 2 is DI + 2000h - 90
				mov     cx, WORDS_PER_LINE		; 45 words per line
				rep     movsw					; copy a screen line to bank 2

				add     di, 1FA6h				; DIand SI auto inc by 2 so bank 3 is DI + 2000h - 90
				mov     cx, WORDS_PER_LINE		; 45 words per line
				rep     movsw					; copy a screen line  to bank 0

				sub		di, 6000h
				mov		cx, bx
				loop	L0

				popf
			}
		}

	}

}

#endif