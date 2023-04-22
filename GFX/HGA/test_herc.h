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
			
			INFO("test Hercules graphics mode\n");
			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(read_light_pen_registers());
				if (YESNO("graphics mode? ")) {
					graphics_full_mode();
					cls();
					int x = 0;
					hga::blit_copy(100, 0, 4, 1, 0);
					hga::blit_copy(150, 0, 4, 2, 0);
					hga::blit_copy(200, 0, 4, 3, 0);
					hga::blit_copy(250, 0, 4, 4, 0);
					hga::blit_copy(300, 0, 4, 5, 0);
					hga::blit_copy(350, 0, 4, 6, 0);
					hga::blit_copy(400, 0, 4, 7, 0);
					hga::blit_copy(450, 0, 4, 8, 0);

					hga::blit_copy(100, 150, 4, 1, 0);
					hga::blit_copy(150, 150, 4, 2, 0);
					hga::blit_copy(200, 150, 4, 3, 0);
					hga::blit_copy(250, 150, 4, 4, 0);
					hga::blit_copy(300, 150, 4, 5, 0);
					//for (int y = 0; y < SCREEN_Y_MAX; ++y) {
						//for (x = 0; x < SCREEN_X_MAX; ++x) {
							//hga::blit_copy(x++, y, 1, 1, 0);
						//}
					//}	
				}
				if (YESNO("swap buffers? ")) {
					swap_buffers();
					cls();
					hga::blit_copy(100, 0, 4, 1, 0);
					hga::blit_copy(150, 0, 4, 2, 0);
					hga::blit_copy(200, 0, 4, 3, 0);
					hga::blit_copy(250, 0, 4, 4, 0);
					hga::blit_copy(300, 0, 4, 5, 0);

					hga::blit_copy(100, 150, 4, 8, 0);
					hga::blit_copy(150, 150, 4, 16, 0);
					hga::blit_copy(200, 150, 4, 24, 0);
					hga::blit_copy(250, 150, 4, 32, 0);
					hga::blit_copy(300, 150, 4, 33, 0);
				}
				if (YESNO("text mode? ")) {
					text_half_mode();
				}
			}
		}
		/* {
			char img[16] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};// { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 };	// U+0041 (A)
			gfx::rgb_t rgb[1] = { {128,127,12} };

			gfx::simple_bitmap_t bmp;
			gfx::init_simple_bitmap(&bmp, 16, 8, 1, 0, rgb, 1, img, 16);
			std::cout << bmp << std::endl;
			std::cout << "make hmp from bmp\n";
			hga::bitmap_t* hmp = hga::create_bitmap(&bmp);
			std::cout << "HGA bitmap " << *hmp << std::endl;
			hga::free_bitmap(hmp);
		}*/
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