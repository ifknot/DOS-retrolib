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

	void video_mode(const uint8_t* presets, uint8_t flags_config, uint8_t flags_ctrl) {
		__asm {
			.8086
			pushf											; preserve flags on entry(direction flag used)

            // 1. configure the Hercules control register 
            mov     dx, HGA_CONFIG_REGISTER
            mov     al, flags_config
            out     dx, al
            // 2. set the Hercules control register 
            mov     dx, HGA_CONTROL_REGISTER
            mov     al, flags_ctrl                   
            out     dx, al
            // 3. program the CRTC registers w presets data 
            lds     si, presets
            cld												; increment mode
            mov     cx, 16									; 16 registers of the 6845
            mov     dx, HGA_CRTC_ADDRESS_PORT
			// 3.1 write out the values to the registers
    L0:     lodsw                                           ; al = register ah = data
            out     dx, ax                                  ; write data to 6845 register
            loop    L0
            // 4. screen on
            mov     dx, HGA_CONTROL_REGISTER
            mov     al, flags_ctrl
            or      al, 00001000b                           ; bit 3 = 0 screen on
            out     dx, al

			popf											; restore flags on exit
		}
	}

    void fill_vram_buffer(uint16_t vram_segment, uint8_t byte_pattern) {
		__asm {
			.8086
			pushf								; preserve flags on entry(direction flag used)

			// 1. setup HGA quad bank VRAM destination pointer ES:DI
			xor		di, di						; top left screen(0, 0)
			mov		ax, vram_segment
			mov		es, ax						; ES:DI point to VRAM destination
			// 2. set up the registers
			cld									; increment ES:DI
			mov		al, byte_pattern
			mov		ah, al						; duplicate byte pattern into AX word
			mov		cx, HGA_WORDS_PER_SCREEN	; set counter to full screen
			// 3. move the byte:byte pattern to VRAM
			rep		stosw						; chain store byte pattern word to VRAM

			popf								; restore flags on exit
		}
	}

	void select_display_buffer(uint8_t select) {
		__asm {
			.8086

			mov     dx, HGA_CONTROL_REGISTER
			mov		al, select 
			and		al, 00000001b				; only bit 0 selects buffer 
			jz      J0                         
			mov     al, 10001010b               ; screen on buffer 1 second display page buffer B000 : 800
			jmp     J1
	J0:     mov     al, 00001010b               ; screen on buffer 0 default display page buffer B000 : 000
	J1:     out     dx, al

		}
	}

}