#ifndef TEST_HERC_H
#define TEST_HERC_H

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"

#include "../../BIOS/bios_video_services.h"
#include "../../BIOS/bios_clock_services.h"

#include "hga.h"
#include "../gfx_bitmap_t.h"

using namespace hga;


/*
void fill_screen() {
	monospaced_font_t<8> f((char(*)[8])default_font_data);
	int i = 0;
	for (int y = 0; y < 43; ++y) { //58 or 43
		for (int x = 0; x < 90; ++x) {
			write_tile_8x8(x, y, f.data[i++ % 256]);
		}
	}
}
*/

namespace test_herc {

	int run() {
		INFO(__FUNCTION__);
		{
			char img[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};// { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 };	// U+0041 (A)
			gfx::rgb_t rgb[1] = { {128,127,12} };

			gfx::simple_bitmap_t bmp;
			gfx::init_simple_bitmap(&bmp, 8, 8, 1, 0, rgb, 1, img, 8);
			std::cout << bmp << std::endl;
			std::cout << "make hmp from bmp\n";
			hga::bitmap_t* hmp = hga::create_bitmap(&bmp);
			std::cout << "HGA bitmap " << *hmp << std::endl;
			hga::free_bitmap(hmp);
		}
		/* {
			INFO("test Hercules graphics mode\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(read_light_pen_registers());
				//fill_screen();
				//std::cout << GLOBAL::default_font.name.c_str() << std::endl;
				
				bios::tick_count_t t, t1, t2;
				bios::set_system_clock_counter(0);
				if (YESNO("graphics mode? ")) {
					graphics_full_mode();
					cls();
					t = bios::read_system_clock_counter();
					fill_screen();
					t1 = bios::read_system_clock_counter() - t;
					//bounds check 
					write_tile_8x8(20, 20, f.data[250]);
					write_tile_8x8(88, 20, f.data[250]);
					write_tile_8x8(89, 20, f.data[250]);
					write_tile_8x8(90, 20, f.data[250]);
					write_tile_8x8(20, 41, f.data[250]);
					write_tile_8x8(20, 42, f.data[250]);
					write_tile_8x8(20, 43, f.data[250]);
					
				}
				if (YESNO("swap buffers? ")) {
					swap_buffers();
					cls();
					t = bios::read_system_clock_counter();
					fill_screen();
					t2 = bios::read_system_clock_counter() - t;
					//write_tile_8x8(20, 20, f.data[250]);
				}
				
				if (YESNO("text mode? ")) {
					text_half_mode();
				}
				
				std::cout << "perf = " << t1 << ' ' << t2 << '\n';

			}
		}*/
		return 0;
	}

}

#endif