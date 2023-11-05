/**
 *
 *  @file      gfx_detect_adapter.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "gfx_detect_adapter.h"

#include "gfx_constants.h"

#include "HGA/hga_detect_adapter.h"
#include "CGA/cga_detect_adapter.h"

namespace gfx {

	uint8_t detect_monochrome_adapter() {
		return hga::detect_adapter();
	}

	uint8_t detect_colour_adapter() {
		if (cga::detect_adapter()) {
			return VIDEO_ADAPTER_CGA;
		}

	}

}