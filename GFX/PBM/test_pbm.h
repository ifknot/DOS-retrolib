/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_PBM
#define TEST_PBM

#include "../../TEST/debug_macros.h"
#include "../../FSYS/fsys_read_dsv.h"
#include "../../BIOS/bios_video_services.h"
#include "../HGA/hga.h"
#include "../gfx.h"

#include "pbm.h"



namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);

		gfx::simple_bitmap_t bmp;
		gfx::simple_bitmap_t* p = new gfx::simple_bitmap_t;

		std::cout << bmp.ihdr << std::endl;
		std::cout << p->ihdr << std::endl;

		gfx::rgb_t rgb[1] = { {128,127,126} };

		gfx::init_simple_bitmap(&bmp, 4, 4, 1, 0, rgb, 1);
		std::cout << bmp << std::endl;
		p = gfx::create_simple_bitmap();
		std::cout << *p<< std::endl;
		
		return 0;
	}

}

#endif

/*

		void fill_screen(pbm::bitmap_t bmp[20]) {
			int i = 0;
			for (int x = 0; x < 20; ++x) {
				hga::write_tile_8x8(10 + x, 10, bmp[i++ % 20].data);
			}

		}
		
		{
			INFO("test Portable Bit Map\n");

			const int n = 20;

			const char data_path[] = "CHESS/FILES.csv";
			char fpaths[20][MAX_LINE_SIZE];
			if (fsys::read_csv(data_path, fpaths, n) == STDIO_FAIL) {
				LOG(data_path);
				LOG(strerror(errno));
			}

			pbm::bitmap_t bmp[n];
			for (int i = 0; i < n; ++i) {
				if (pbm::load_bitmap(fpaths[i], &bmp[i]) == STDIO_FAIL) {
					std::cout << strerror(errno) << std::endl;
					exit(EXIT_FAILURE);
				}
			}

			pbm::bitmap_t testbmp; //"CHESS/LEFTNUM.pbm" "WDINGS/CIRCLE24.pbm" "CHESS/TOPALPHA.pbm" "CHESS/E4MOVE.pbm"
			if (pbm::load_bitmap("CHESS/SPRITES0.pbm", &testbmp) == STDIO_FAIL) {
				std::cout << strerror(errno) << std::endl;
				exit(EXIT_FAILURE);
			}

			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(hga::read_light_pen_registers());
				//fill_screen();
				//std::cout << GLOBAL::default_font.name.c_str() << std::endl;

				std::cout << "bytes = " << testbmp.header->bytes << '\n';

				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::cls();
					fill_screen(bmp);
					uint16_t step = testbmp.header->width >> 3;

					hga::write_tile_block(20,20, &testbmp);

				}
				if (YESNO("swap buffers? ")) {
					hga::swap_buffers();
					hga::cls();
					fill_screen(bmp);
					uint16_t step = testbmp.header->width >> 3;

					hga::write_tile_block(20, 20, &testbmp);

				}

				if (YESNO("text mode? ")) {
					hga::text_half_mode();
				}

			}
			for (int i = 0; i < n; ++i) {
				pbm::free_bitmap(&bmp[i]);
			}
			pbm::free_bitmap(&testbmp);
		}*/