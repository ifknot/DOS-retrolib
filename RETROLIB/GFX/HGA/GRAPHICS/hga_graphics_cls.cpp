/**
 *
 *  @file      hga_graphics_cls.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_graphics_cls.h"

namespace hga {

	namespace graphics {

		void cls(uint8_t byte_pattern, uint16_t vram_segment) {
			__asm {
				.8086
				push	bp
				pushf

				mov     ax, vram_segment
				mov     es, ax                      ; ES:DI will point to x, y screen word
				xor     di, di	

				cld									; increment ES:DI
				mov		al, byte_pattern
				mov		ah, al						; duplicate byte pattern into AX word
				mov		cx, HGA_WORDS_PER_SCREEN	; set counter to full screen
				rep		stosw						; chain store byte pattern word to VRAM

				popf 
				pop		bp
			}
		}

	}

}