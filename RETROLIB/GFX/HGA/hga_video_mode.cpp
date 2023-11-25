/**
 *
 *  @file      hga_video_mode.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      25.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_video_mode.h"

#include "hga_constants.h"

namespace hga {



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