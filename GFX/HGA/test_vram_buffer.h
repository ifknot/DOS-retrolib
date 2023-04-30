#ifndef TEST_VRAM_BUFFER_H
#define TEST_VRAM_BUFFER_H

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"

#include "../../BIOS/bios_video_services.h"
#include "../../BIOS/bios_clock_services.h"

#include "hga.h"
#include "../gfx_bitmap_t.h"
#include "../PBM/pbm.h"

// TODO:
// [x] load splash.pbm 
// [x] vram splash
// [x] correctly vram splash
// [ ] time 500 displays 1. XT = 592 ticks 2. AT timings
// [x] vsync vram splash 1. XT = 592 ticks 2. AT = 
// [ ] time 500 displays 1. XT timings 2. AT timings
// [ ] timings on real hardware XT V20 AT ALT286 ALT386
// 
// [ ] speed up tile block

namespace test_herc {

	uint32_t t;

	int run() {
		{
			INFO("test HGA VRAM write buffer to screen\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			//if (adapter == bios::HGC || adapter == bios::UNKNOWN) {

				gfx::simple_bitmap_t* bmp = pbm::create_simple_bitmap("TEST/SPLASH.PBM");

				LOG(hga::read_light_pen_registers());
				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::sync::cls();
					hga::vram_tile_block(0, 0, bmp);
					//hga::vram_write_screen_buffer(bmp->idat.data);
					//hga::vram_tile_block(0, 0, bmp, hga::GLOBAL::back_buffer);
					ANYKEY("");
					hga::swap_buffers();
					hga::cls();
					//hga::vram_tile_block(0, 0, bmp);
					bios::set_system_clock_counter(0);
					for (int i = 0; i < 100; ++i) {
						hga::sync::vram_write_buffer(bmp);
					}
					//ANYKEY("");
					hga::text_half_mode();
					std::cout << bios::read_system_clock_counter();
				}
			//}
		}
		return EXIT_SUCCESS;
	}

}
#endif // !TEST_VRAM_BUFFER_H

