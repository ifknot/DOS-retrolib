/**
 *
 *  @file      cga_mode6.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE6_H
#define CGA_MODE6_H

#include <iostream>

#include "../../../bios/bios_services.h"
#include "cga_mode6_constants.h"

namespace cga {

	namespace mode6 {

		bios::video_mode_t original_mode;

		void enter() {
			original_mode = bios::get_video_state().mode;
			bios::set_video_mode(bios::GRAPHICS_MONOCHROME_640X200);
		}

		void exit(bios::video_mode_t mode = original_mode) {
			bios::set_video_mode(mode);
		}

		void ink_colour(colour_t colour) {
			__asm {
				.8086
				mov		ah, 0Bh		; Interrupt 10H Service 11 : Set Color Palette
				mov		bh, 0		; Sub-function 0 - sets foreground color for 640 x 200 graphics modes
				mov		bl, colour
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
