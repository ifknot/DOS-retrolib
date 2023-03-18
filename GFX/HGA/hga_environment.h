/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright � Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_ENVIRONMENT_H
#define HGA_ENVIRONMENT_H

#include <stdint.h>
#include "hga_default_font_8x8.h"
#include "hga_monospaced_font_t.h"

/**
 *  @def   TILE_WIDTH
 *  @brief HGA resolution of 720x348 using an 8x8 tile gives as screen 90 tiles wide
 */
#define TILE_WIDTH 8;
/**
 *  @def   TILE_HEIGHT
 *  @brief however, HGA resolution of 720x348 using an 8x8 tile gives a screen 43.5 tiles high
 */
#define TILE_HEIGHT 8;

namespace hga {

	namespace GLOBAL {

		static uint8_t active_buffer = 0;	// 0 = default B000:000 1 = B000:8000 second display page buffer

		
	}

}

#endif