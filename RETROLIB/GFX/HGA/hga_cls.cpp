/**
 *
 *  @file      hga_cls.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_cls.h"

#include "hga_constants.h"

namespace hga {

	/**
	* @brief HGA text mode clear screen and reset text attributes
	*/
	void cls(char character, char attribute) {
		__asm {
			.8086
			push	bp
			pushf

			mov     ax, HGA_VIDEO_RAM_SEGMENT
            mov     es, ax                      ; ES:DI will point to x, y screen byte
            xor     di, di
            mov     ah, attribute                    
            mov     al, character              
            mov     cx, HGA_CHARS_PER_SCREEN    ; 80 columns x 25 rows = 2000 characters per screen
            cld                                 ; increment mode
            rep     stosw                       ; fill screen with atrribute:ascii word

			popf
			pop		bp
		}
	}

}