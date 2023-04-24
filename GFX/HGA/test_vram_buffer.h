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

				gfx::simple_bitmap_t* bmp = pbm::create_simple_bitmap("TEST/SPLASH.PBM");

				LOG(hga::read_light_pen_registers());
				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::cls();
					hga::vram_tile_block(0, 0, bmp);
					//hga::vram_write_screen_buffer(bmp->idat.data);
					//hga::vram_tile_block(0, 0, bmp, hga::GLOBAL::back_buffer);
					ANYKEY("");
					hga::swap_buffers();
					hga::cls();
					//hga::vram_tile_block(0, 0, bmp);
					hga::sync_vram_write_screen_buffer(bmp);
					ANYKEY("");
					hga::text_half_mode();
				}
			}
		}
		return EXIT_SUCCESS;
	}

}
#endif // !TEST_VRAM_BUFFER_H

