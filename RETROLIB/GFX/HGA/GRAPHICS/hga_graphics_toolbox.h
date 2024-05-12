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

namespace hga {

	namespace graphics {

		/**
		* @brief Fast fill the specified HGA VRAM buffer with an 8 bit byte pattern
		* @details 
		* @note No sanity checking! Expects vram_segment to be valid.
		*/
		void fill_vram_buffer(uint16_t vram_segment, uint8_t byte_pattern);

		/**
		* @brief clear the specified HGA VRAM buffer to black
		* @note defaults to buffer 0
		*/
		inline void cls(uint16_t vram_segment = HGA_BUFFER_0) {
			fill_vram_buffer(vram_segment, 0);
		}

		/**
		* @brief select which of the 2 HGA adapter VRAM buffers ( 0 or 1 ) to be displayed on screen 
		* @note No sanity checking! Expects 0 or 1.
		*/
		void select_display_buffer(uint8_t select);

	}

}

#endif