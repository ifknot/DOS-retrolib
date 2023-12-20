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

namespace test_hga_graphics {

	void run() {
		INFO("* testing lib HGA graphics routines");
		uint8_t hga = hga::detect_adapter();
		if(hga) {
			INFO(hga::video_adapter_names[hga]);
			if (YESNO("* 700\tswitch to HGA graphics mode and clear screen?")) {
				hga::graphics_mode();
				hga::graphics::cls(0xAA);
				uint16_t buffer = HGA_BUFFER_0;
				if (YESNO("switch buffer ?")) {
					hga::graphics::select_buffer(1);
					hga::graphics::cls(1, HGA_BUFFER_1);
				}
				if (YESNO("switch back ?")) {
					hga::graphics::select_buffer(0);
					hga::graphics::cls(0xEE, HGA_BUFFER_0);
				}
				
				if (YESNO("")) {
					hga::text_mode();
					hga::cls();
				}
			}
		}
		else {
			INFO("No compatible Hercules Graphics Adapter found!");
		}
	}

}

#endif