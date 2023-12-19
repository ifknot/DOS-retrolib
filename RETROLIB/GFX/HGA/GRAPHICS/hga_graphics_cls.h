/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      25.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_CLS_H
#define HGA_GRAPHICS_CLS_H

#include <stdint.h>

#include "../hga_constants.h"

namespace hga {

	namespace graphics {

		/**
		* @brief Fast fill the specified HGA VRAM buffer with an 8 bit byte pattern - defaults to 0 (black)
		* @details 
		* @note No sanity checking! Expects vram_segment to be valid.
		*/
		void cls(uint8_t byte_pattern = 0, uint16_t vram_segment = HGA_BUFFER_0);

	}

}

#endif