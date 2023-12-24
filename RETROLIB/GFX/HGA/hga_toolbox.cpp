/**
 *
 *  @file      hga_toolbox.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_toolbox.h"

namespace hga {

	void cls(char character, char attribute) {
		__asm {
			.8086
			push	bp
			pushf

			mov     ax, HGA_VIDEO_RAM_SEGMENT
			mov     es, ax; ES:DI will point to x, y screen byte
			xor di, di
			mov     ah, attribute
			mov     al, character
			mov     cx, HGA_CHARS_PER_SCREEN; 80 columns x 25 rows = 2000 characters per screen
			cld; increment mode
			rep     stosw; fill screen with atrribute : ascii word

			popf
			pop		bp
		}
	}

	void video_mode(const uint8_t* presets, uint8_t flags_config, uint8_t flags_ctrl) {
		__asm {
			.8086
			push	bp
			pushf

            // configure the Hercules control register 
            mov     dx, HGA_CONFIG_REGISTER
            mov     al, flags_config
            out     dx, al

            // set the Hercules control register 
            mov     dx, HGA_CONTROL_REGISTER
            mov     al, flags_ctrl                   
            out     dx, al

            // program the CRTC registers w presets data 
            lds     si, presets
            cld                                             ; increment mode
            mov     cx, 16                                  ; 16 registers of the 6845
            mov     dx, HGA_CRTC_ADDRESS_PORT

    L0:     lodsw                                           ; al = register ah = data
            out     dx, ax                                  ; write data to 6845 register
            loop    L0

            // screen on
            mov     dx, HGA_CONTROL_REGISTER
            mov     al, flags_ctrl
            or      al, 00001000b                           ; bit 3 = 0 screen on
            out     dx, al

			popf 
			pop		bp
		}
	}

}