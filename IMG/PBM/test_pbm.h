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
#include "../../GFX/HGA/hga.h"

#include "pbm.h"

void fill_screen(pbm::bitmap_t bmp[20]) {
	int i = 0;
	for (int x = 0; x < 20; ++x) {
		hga::write_glyph_8x8(10 + x, 10, bmp[i++ % 20].data);
	}

}

namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);
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
			
			pbm::bitmap_t skull;
			if (pbm::load_bitmap("WDINGS/SKULL2.pbm", &skull) == STDIO_FAIL) {
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

				if (YESNO("graphics mode? ")) {
					hga::graphics_full_mode();
					hga::cls();
					fill_screen(bmp);
					hga::write_glyph(20, 20, &skull);
				}
				if (YESNO("swap buffers? ")) {
					hga::swap_buffers();
					hga::cls();
					fill_screen(bmp);
					hga::write_glyph(20, 20, &skull);
				}

				if (YESNO("text mode? ")) {
					hga::text_half_mode();
				}
			}
			for (int i = 0; i < n; ++i) {
				pbm::free_bitmap(&bmp[i]);
			}
			pbm::free_bitmap(&skull);
		}
		return 0;
	}

}

#endif