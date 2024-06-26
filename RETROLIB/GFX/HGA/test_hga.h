/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_HGA_GRAPHICS_H
#define TEST_HGA_GRAPHICS_H

#include "../../TEST/debug_macros.h"

#include "hga.h"
#include "../gfx.h"
#include "../../MEM/mem.h"

namespace test_hga {

	void run() {
		INFO("* testing lib HGA graphics routines");
		uint8_t hga = hga::detect_adapter();
		if (hga) {
			INFO(hga::video_adapter_names[hga]);
			/*
			if (YESNO("* 710\tswitch to HGA graphics mode and clear screen ?")) {
				hga::graphics_mode();
				hga::cls();
				if (YESNO("switch buffer ?")) {
					hga::select_display_buffer(1);
					hga::fill_vram_buffer(HGA_BUFFER_1, 1);

				}
				if (YESNO("switch back ?")) {
					hga::select_display_buffer(0);
					hga::fill_vram_buffer(HGA_BUFFER_0, 0xEE);
				}

				if (YESNO("")) {
					hga::text_mode();
				}
			}


			if (YESNO("* 720 load fullscreen bitmap ?")) {
				char fpath[13] = "";
				mem::arena::arena_t* pool = mem::arena::new_dos_arena(65536);
				LOG(*pool);
				gfx::bmp::bitmap_t bmp;

				INFO("enter file name : ");
				if (scanf("%s", fpath)) {
					gfx::bmp::pbm::load_file(pool, &bmp, fpath);
					LOG(*pool);
				}
				LOG(bmp);
				if (YESNO("* 721\tswitch to HGA graphics mode and buffer fullscreen rect (0,0,720,348) to VRAM rect fullscreen ?")) {
					hga::graphics_mode();
					hga::select_display_buffer(1);

					hga::cls(HGA_BUFFER_1);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data);

					if (YESNO("")) {
						hga::text_mode();
					}
				}
				if (YESNO("* 722\tswitch to HGA graphics mode blt buffer rect (x,y,w,h) to corresponding VRAM rect (x,y,w,h) ?")) {
					hga::graphics_mode();
					hga::select_display_buffer(1);

					hga::cls(HGA_BUFFER_1);
					hga::cls(HGA_BUFFER_1);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 0, 40, 32);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 0, 32, 32);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 0, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 150, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 150, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 150, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 348 - 48, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 348 - 48, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 348 - 48, 64, 48);

					if (YESNO("")) {
						hga::text_mode();
					}
				}
				if (YESNO("* 722\tswitch to HGA graphics mode and blt buffer rect (a,b,w,h) to VRAM rect (x,y,w,h) ?")) {
					hga::graphics_mode();
					hga::select_display_buffer(1);

					hga::cls(HGA_BUFFER_1);
					hga::cls(HGA_BUFFER_1);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 0, 0, 32, 40, 32);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 0, 0, 32, 32, 32);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 0, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 150, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 150, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 150, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 0, 348 - 48, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 328, 348 - 48, 102, 90, 64, 48);
					hga::vblt(HGA_BUFFER_1, bmp.raster_data, 720 - 64, 348 - 48, 102, 90, 64, 48);

					if (YESNO("")) {
						hga::text_mode();
					}
				}
				mem::arena::delete_dos_arena(pool);
			}
			if (YESNO("* 730\ttest blit fill ?")) {
				mem::arena::arena_t* pool = mem::arena::new_dos_arena(65536 * 2);
				gfx::bmp::bitmap_t* bmp;
				LOG(*pool);
				if (YESNO("* 731\tcreate & blit screen buffer bmp ?")) {
					bmp = gfx::bmp::new_bitmap(pool, 720, 348, 1, gfx::bmp::GREYSCALE);
					LOG(*bmp);
					LOG(*pool);
				}
				if (YESNO("* 732\tclear & blit screen buffer bmp ?")) {
					hga::graphics_mode();
					hga::select_display_buffer(1);

					gfx::bmp::fill(bmp, hga::BRIGHT);
					hga::vblt(HGA_BUFFER_1, bmp->raster_data);

					if (YESNO("")) {
						hga::text_mode();
						LOG(sizeof(*bmp));
					}
				}
				mem::arena::delete_dos_arena(pool);
			}
			*/
			if (YESNO("* 740\ttest pixel functions ?")) {
				hga::graphics_mode();
				hga::select_display_buffer(1);

				hga::cls(HGA_BUFFER_1);
				uint16_t x, y;
				x = y = 0;
				for (int i = 0; i < 200; ++i) {
					//for (int j = 0; j < 348; ++j) {
						hga::plot_pixel(HGA_BUFFER_1, x++, y++, hga::WHITE);
					//}
				}
				

				if (YESNO("")) {
					hga::text_mode();
				}
			}
		}
		else {
			INFO("No compatible Hercules Graphics Adapter found!");
		}
	}

}

#endif