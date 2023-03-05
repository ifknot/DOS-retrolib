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
#include "hga_default_font_8x8.h"

using namespace hga;

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
				if (YESNO("graphics mode? ")) {
					graphics_full_mode();
				}
				uint8_t a[8] = { // letter A
					0, 0x38, 0x44, 0x44, 0x44, 0x7C, 0x44, 0x44
				};
				cls();
				draw_glyph_8x8(10, 10, a);
				if (YESNO("swap buffers? ")) {
					swap_buffers();
				}
				draw_glyph_8x8(11, 10, a);
				if (YESNO("text mode? ")) {
					text_half_mode();
				}
			}
		}
		return 0;
	}

}

#endif