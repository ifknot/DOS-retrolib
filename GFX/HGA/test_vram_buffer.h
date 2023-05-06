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

	static int n = 100;

	int run() {
		{
			INFO("0. test HGA primitives\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			LOG(hga::read_light_pen_registers());
		}
		{
			INFO("\n1. test & time vram_write_buffer(bmp)\n");
			gfx::simple_bitmap_t* bmp = pbm::create_simple_bitmap("TEST/SPLASH.PBM");	
			//bmp->ihdr.height /= 2;
			if (YESNO("graphics mode? ")) {
				hga::graphics_full_mode();
				hga::sync::cls();
				hga::vram_write_buffer(0, bmp);
				ANYKEY("");
				hga::swap_buffers();
				hga::cls();
				bios::set_system_clock_counter(0);
				for (int i = 0; i < n; ++i) {
					hga::vram_write_buffer(0, bmp);
				}
				
				//ANYKEY("");
				hga::text_half_mode();
				float t = 1;
				std::cout << bios::read_system_clock_counter();
				//std::cout << t << " ticks ";
				//t = (t / n) / TICKS_PER_SECOND;
				//std::cout << t << "Hz " << t << "fps\n";
			}
		}
		return EXIT_SUCCESS;
	}

}
#endif // !TEST_VRAM_BUFFER_H

