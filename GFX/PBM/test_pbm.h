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

void fill_screen(gfx::simple_bitmap_t* bmp[20]) {
	int i = 0;
	for (int x = 0; x < 20; ++x) {
		hga::vram_tile_8x8(10 + x, 10, bmp[i++ % 20]->idat.data);
	}
}

namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test gfx::simple_bitmap\n");

			gfx::rgb_t rgb[1] = { {128,127,12} };

			char img[8] = { 0x30, 0x78, 0xcc, 0xcc, 0xfc, 0xcc, 0xcc, 0x00 };	// U+0041 (A)

			gfx::simple_bitmap_t bmp(8, 8, 1, 0, 1, rgb, 8, img);
			gfx::simple_bitmap_t* p = new gfx::simple_bitmap_t(8, 8, 1, 0, 1, rgb, 8, img);

			std::cout << bmp << std::endl;
			std::cout << *p << std::endl;

			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					//hga::swap_buffers();
					hga::cls();
					hga::vram_tile_8x8(10, 11, p->idat.data);
					hga::vram_tile_block(10, 20, &bmp);
					
					ANYKEY("");					
					hga::swap_buffers();
					hga::cls();
					hga::vram_tile_8x8(10, 12, bmp.idat.data);
					hga::vram_tile_block(21, 12, &bmp);

					for (int i = 0; i < 5; ++i) {
						ANYKEY("");
						hga::swap_buffers();
					}
					
					ANYKEY("");
					hga::text_half_mode();
					
				}
			}
	
		}
		/*
		{
			INFO("test Portable Bit Map\n");
			const int n = 20;
			const char data_path[] = "TEST/CHESS/FILES.csv";
			char fpaths[20][MAX_LINE_SIZE];
			if (fsys::read_csv(data_path, fpaths, n) == STDIO_FAIL) {
				LOG(data_path);
				LOG(strerror(errno));
			}
			INFO("Loading image files...");
			gfx::simple_bitmap_t* bmp[n];
			for (int i = 0; i < n; ++i) {
				bmp[i] = pbm::create_simple_bitmap(fpaths[i]);
			}

			gfx::simple_bitmap_t* testbmp; //"CHESS/LEFTNUM.pbm" "WDINGS/CIRCLE24.pbm" "CHESS/TOPALPHA.pbm" "CHESS/E4MOVE.pbm" "CHESS/SPRITES0.pbm"
			testbmp = pbm::create_simple_bitmap("TEST/CHESS/16x16set.pbm");

			bios::video_adapter_t adapter = bios::detect_video_adapter_type();
			LOG(bios::video_adapter_names[adapter]);
			LOG(bios::detect_CRTC_at_port(bios::MDA_crtc_port));
			if (adapter == bios::HGC || adapter == bios::UNKNOWN) {
				LOG(hga::read_light_pen_registers());
				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::cls();
					fill_screen(bmp);

					hga::vram_tile_block(20, 20, testbmp);

					if (YESNO("swap buffers? ")) {
						hga::cls(0x800);						
						hga::vram_tile_block(20, 20, testbmp, 0x800);
						hga::swap_buffers();
					}

					if (YESNO("text mode? ")) {
						
						hga::text_half_mode();
					}
				}		
			}
			for (int i = 0; i < n; ++i) {
				gfx::free_simple_bitmap(bmp[i]);
				delete bmp[i];
			}
			gfx::free_simple_bitmap(testbmp);
			delete testbmp;
		}*/
		return 0;
	}

}

#endif

/*

		void fill_screen(gfx::simple_bitmap_t bmp[20]) {
			int i = 0;
			for (int x = 0; x < 20; ++x) {
				hga::vram_tile_8x8(10 + x, 10, bmp[i++ % 20].data);
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

					hga::vram_tile_block(20,20, &testbmp);

				}
				if (YESNO("swap buffers? ")) {
					hga::swap_buffers();
					hga::cls();
					fill_screen(bmp);
					uint16_t step = testbmp.header->width >> 3;

					hga::vram_tile_block(20, 20, &testbmp);

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