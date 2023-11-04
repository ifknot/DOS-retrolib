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
#include "HGA/hga.h"

namespace test_gfx {

	void run() {
		INFO("* testing lib graphics services...");
		if (YESNO("* 410\ttest detect CRTC MDA/HGA & CGA ?")) {
			LOG(gfx::detect_CRTC_at_port(gfx::crtc_port_MDA));
			LOG(gfx::detect_CRTC_at_port(gfx::crtc_port_CGA));
			LOG((int)hga::detect_adapter());
			INFO(gfx::video_adapter_names[hga::detect_adapter()]);
		}
	}

}

#endif