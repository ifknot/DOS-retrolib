/**
 *
 *  @file      hga_graphics_toolbox.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_graphics_toolbox.h"

namespace hga {

	namespace graphics {

		void cls(uint16_t vram_segment, uint8_t byte_pattern) {
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

		void select_buffer(uint8_t select) {
			__asm {
				.8086
				push	bp
				pushf 

				mov     dx, HGA_CONTROL_REGISTER
				mov		al, select 
				and		al, 00000001b
				jz      J0                          
				mov     al, 10001010b               ; screen on buffer 1 second display page buffer B000 : 800
				jmp     J1
		J0:     mov     al, 00001010b               ; screen on buffer 0 default display page buffer B000 : 000
		J1:     out     dx, al
    
				popf
				pop		bp

			}
		}

	}

}
