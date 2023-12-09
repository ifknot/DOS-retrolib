/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_GFX_H
#define TEST_GFX_H

#include "../TEST/debug_macros.h"

#include "gfx.h"
#include "../MEM/mem.h"

#include "HGA/test_hga.h"

namespace test_gfx {

	void run() {
		INFO("* testing lib graphics services...");
		if (YESNO("* 410\ttest detect CRTC MDA/HGA & CGA ?")) {
			LOG(gfx::detect_CRTC_at_port(gfx::crtc_port_MDA));
			LOG(gfx::detect_CRTC_at_port(gfx::crtc_port_CGA));
		}
		if (YESNO("* 420\ttest detect video adapter ?")) {
			LOG((int)gfx::detect_monochrome_adapter());
			INFO(gfx::video_adapter_names[gfx::detect_monochrome_adapter()]);
			LOG((int) gfx::detect_colour_adapter());
			INFO(gfx::video_adapter_names[gfx::detect_colour_adapter()]);
			LOG((int)gfx::detect_adapter());
			INFO(gfx::video_adapter_names[gfx::detect_adapter()]);
		}
		if (YESNO("* 430\ttest HGA functions ?")) {
			test_hga::run();
		}
		if (YESNO("* 440\ttest bitmap load functions ?")) {
			char fpath[13] = "";
			mem::arena::arena_t* pool = mem::arena::new_dos_arena(65536);
			LOG(*pool);
			gfx::bmp::bitmap_t bmp;

			while (YESNO("test file?")) {
				INFO("enter file name : ");
				if (scanf("%s", fpath)) {
					gfx::bmp::load_file_pbm(fpath, &bmp, pool);
					LOG(*pool);
				}
				LOG(bmp);
			}

			mem::arena::delete_dos_arena(pool);
		}
	}

}

#endif