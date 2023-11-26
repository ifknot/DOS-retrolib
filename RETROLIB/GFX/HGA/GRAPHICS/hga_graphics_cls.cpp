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

#include "../hga_constants.h"

namespace hga {

	namespace graphics {

		void cls(uint8_t byte_pattern) {
			__asm {
				.8086
				push	bp
				pushf

				mov     ax, HGA_VIDEO_RAM_SEGMENT
				mov     es, ax                      ; ES:DI will point to x, y screen byte
				xor     di, di	

				cld 
				mov		al, byte_pattern
				mov		ah, al
				mov		cx, HGA_WORDS_PER_PAGE
				rep		stosw

				popf 
				pop		bp
			}
		}

	}

}