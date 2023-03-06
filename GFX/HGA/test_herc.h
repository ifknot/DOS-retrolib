#ifndef TEST_HERC_H
#define TEST_HERC_H

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"

#include "../../BIOS/bios_video_services.h"

#include "hga_read_light_pen_registers.h"
#include "hga_video_mode.h"
#include "hga_swap_buffers.h"
#include "hga_cls.h"
#include "hga_glyph.h"
#include "hga_environment.h"

using namespace hga;

void fill_screen() {
	monospaced_font_t<8> f((uint8_t(*)[8])default_font_data);
	int i = 0;
	for (int y = 0; y < 58; ++y) {
		for (int x = 0; x < 90; ++x) {
			write_glyph_8x6(x, y, f.data[i++ % 256]);
		}
		std::cout << '\n' << std::endl;
	}
}

namespace test_herc {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test Hercules graphics mode\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(read_light_pen_registers());
				fill_screen();
				//std::cout << GLOBAL::default_font.name.c_str() << std::endl;
				/*
				if (YESNO("graphics mode? ")) {
					graphics_full_mode();
					cls();
					fill_screen();
				}
				if (YESNO("swap buffers? ")) {
					swap_buffers();
					fill_screen();
				}
				
				if (YESNO("text mode? ")) {
					text_half_mode();
				}
				*/
			}
		}
		return 0;
	}

}

#endif