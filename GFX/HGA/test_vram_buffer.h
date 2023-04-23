#ifndef TEST_VRAM_BUFFER_H
#define TEST_VRAM_BUFFER_H

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"

#include "../../BIOS/bios_video_services.h"
#include "../../BIOS/bios_clock_services.h"

#include "hga.h"
#include "../gfx_bitmap_t.h"

// TODO:
// [ ] load splash.pbm 
// [ ] vram splash
// [ ] correctly vram splash
// [ ] time 100 displays 1. XT timings 2. AT timings
// [ ] vsync vram splash
// [ ] time 100 displays 1. XT timings 2. AT timings
// [ ] timings on real hardware XT V20 AT ALT286 ALT386

namespace test_herc {

	int run() {
		{
			INFO("test HGA VRAM write buffer to screen\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(hga::read_light_pen_registers());
				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::cls();
					ANYKEY("");
					hga::swap_buffers();
					hga::cls();
					ANYKEY("");
					hga::text_half_mode();
				}
			}
		}
		return EXIT_SUCCESS;
	}

}
#endif // !TEST_VRAM_BUFFER_H

