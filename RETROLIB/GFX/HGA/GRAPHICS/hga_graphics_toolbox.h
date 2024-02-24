/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_GRPAHICS_TOOLBOX_H
#define HGA_GRPAHICS_TOOLBOX_H

#include <stdint.h>

#include "hga_graphics_palette.h"

#include "../hga_constants.h"

#include "../../gfx_bitmap.h"

namespace hga {

	namespace graphics {

		/**
		* @brief Fast fill the specified HGA VRAM buffer with an 8 bit byte pattern - defaults to 0 (black)
		* @details
		* @note No sanity checking! Expects vram_segment to be valid.
		*/
		void cls(uint16_t vram_segment = HGA_BUFFER_0, uint8_t byte_pattern = 0);

		/**
		* @brief select which of the 2 HGA adapter VRAM buffers ( 0 or 1 ) to be displayed on screen 
		* @note No sanity checking! Expects 0 or 1.
		*/
		void select_buffer(uint8_t select);

	}

}

#endif