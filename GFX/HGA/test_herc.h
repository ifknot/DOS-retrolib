#ifndef TEST_HERC_H
#define TEST_HERC_H

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"

#include "../../BIOS/bios_video_services.h"

#include "hga_read_light_pen_registers.h"
#include "hga_video_mode.h"
#include "hga_swap_buffers.h"

using namespace hga;

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
				}
				if (YESNO("swap buffers? ")) {
					swap_buffers();
				}
				if (YESNO("swap buffers? ")) {
					swap_buffers();
				}
				if (YESNO("text mode? ")) {
					text_half_mode();
				}
			}
		}
		return 0;
	}

}

#endif