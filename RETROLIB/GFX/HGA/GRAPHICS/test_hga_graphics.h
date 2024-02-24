/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_HGA_GRAPHICS_H
#define TEST_HGA_GRAPHICS_H

#include "../../../TEST/debug_macros.h"

#include "../hga.h"
#include "../../gfx.h"
#include "../../../MEM/mem.h"

namespace test_hga_graphics {

	void run() {
		INFO("* testing lib HGA graphics routines");
		uint8_t hga = hga::detect_adapter();
		if(hga) {
			INFO(hga::video_adapter_names[hga]);
			/*
			if (YESNO("* 710\tswitch to HGA graphics mode and clear screen ?")) {
				hga::graphics_mode();
				hga::graphics::cls(HGA_BUFFER_0, 0xAA);
				if (YESNO("switch buffer ?")) {
					hga::graphics::select_buffer(1);
					hga::graphics::cls(HGA_BUFFER_1, 1);

				}
				if (YESNO("switch back ?")) {
					hga::graphics::select_buffer(0);
					hga::graphics::cls(HGA_BUFFER_0, 0xEE);
				}
				
				if (YESNO("")) {
					hga::text_mode();
					hga::cls();
				}
			}
			*/
			/*
			if (YESNO("* 720 load fullscreen bitmap ?")) {
				char fpath[13] = "";
				mem::arena::arena_t* pool = mem::arena::new_dos_arena(65536);
				LOG(*pool);
				gfx::bmp::bitmap_t bmp;

				INFO("enter file name : ");
				if (scanf("%s", fpath)) {
					gfx::bmp::pbm::load_file(fpath, &bmp, pool);
					LOG(*pool);
				}
				LOG(bmp);
				if (YESNO("* 721\tswitch to HGA graphics mode and display bitmap?")) {
					hga::graphics_mode();
					hga::graphics::select_buffer(1);
					
					hga::graphics::cls(HGA_BUFFER_1, 0);
					hga::graphics::blit_vram_bmp(HGA_BUFFER_1, bmp.raster_data[0]);

					if (YESNO("")) {
						hga::text_mode();
						hga::cls();
					}
				}
				if (YESNO("* 722\tswitch to HGA graphics mode and letterbox bitmap?")) {
					hga::graphics_mode();
					hga::graphics::select_buffer(1);

					for (int i = 10; i < 20; i += 1) {
						hga::graphics::cls(HGA_BUFFER_1, 0);
						hga::graphics::blit_vram_bmp(HGA_BUFFER_1, bmp.raster_data[0], i, i, 360, 88);
						YESNO("");
					}

					if (YESNO("")) {
						hga::text_mode();
						hga::cls();
					}
				}
				mem::arena::delete_dos_arena(pool);
			}*/
			if (YESNO("* 730\ttest blit bmp->bmp blit bmp->vram ?")) {
				mem::arena::arena_t* pool = mem::arena::new_dos_arena(65536 * 2);
				LOG(*pool);
				if (YESNO("* 731\tcreate & blit screen buffer bmp ?")) {
					gfx::bmp::bitmap_t* bmp = gfx::bmp::new_bitmap(pool, 720, 348, 1, 0);
					LOG(*bmp);
					LOG(*pool);
				}
				if (YESNO("* 732\tclear & blit screen buffer bmp ?")) {
					gfx::bmp::bitmap_t* bmp = gfx::bmp::new_bitmap(pool, 720, 348, 1, 0);
					LOG(*bmp);
					LOG(*pool);
					hga::graphics_mode();
					hga::graphics::select_buffer(1);
					
						hga::graphics::cls(HGA_BUFFER_1, 0xAA);
						hga::graphics::blit_vram_bmp(HGA_BUFFER_1, bmp->raster_data[0]);

					if (YESNO("")) {
						hga::text_mode();
					}
				}
				if (YESNO("* 733\tload sprite bmp ?")) {
				}
				if (YESNO("* 734\tblit sprite to buffer & blit screen buffer bmp ?")) {
				}
				mem::arena::delete_dos_arena(pool);
			}
		}
		else {
			INFO("No compatible Hercules Graphics Adapter found!");
		}
	}

}

#endif