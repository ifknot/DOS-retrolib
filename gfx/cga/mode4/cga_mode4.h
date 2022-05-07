/**
 *
 *  @file      cga_mode4.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE4_H
#define CGA_MODE4_H

#include <iostream>

#include "../../../bios/bios_services.h"

namespace cga {

	namespace mode4 {

		bios::video_mode_t original_mode;

		void enter() {
			original_mode = bios::get_video_state().mode;
			bios::set_video_mode(bios::GRAPHICS_4_COLOUR_320x200);
		}

		void exit(bios::video_mode_t mode = original_mode) {
			bios::set_video_mode(mode);
		}

		void palette_cyan_red_white() {
			__asm {
				.8086
				mov		ah, 0		; Interrupt 10H Service 0 : Set Video Mode
				mov		al, 5		; 320x200 4-colour mode, colour burst disabled 
				int		10h
			}
		}

		void palette_cyan_magenta_white() {
			__asm {
				.8086
				mov		ah, 0		; Interrupt 10H Service 0 : Set Video Mode
				mov		al, 4		; 320x200 4-colour mode, colour burst enabled 
				int		10h

				mov		ah, 0Bh		; Interrupt 10H Service 11 : Set Color Palette
				mov		bh, 1		; If BH = 1 (Palette Color ID) then selects the palette for 320 x 200 graphics modes
				mov		bl, 1		; 1 for cyan-magenta-white
				int		10h
			}
		}

		void palette_green_red_yellow() {
			__asm {
				.8086
				mov		ah, 0		; Interrupt 10H Service 0 : Set Video Mode
				mov		al, 4		; 320x200 4-colour mode, colour burst enabled 
				int		10h

				mov		ah, 0Bh		; Interrupt 10H Service 11 : Set Color Palette
				mov		bh, 1		; If BH = 1 (Palette Color ID) then selects the palette for 320 x 200 graphics modes
				mov		bl, 0		; 0 for green-red-yellow
				int		10h
			}
		}

		void print_mode_info() {
			std::cout << "mode " << bios::video_mode_names[bios::get_video_state().mode] << '\n';
		}

		void print_adapter_info() {
			std::cout << bios::video_adapter_names[bios::detect_video_adapter_type()] << '\n';
		}

	}
}

#endif
