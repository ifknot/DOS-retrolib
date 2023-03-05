/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_ENVIRONMENT_H
#define HGA_GRAPHICS_ENVIRONMENT_H

#include <stdint.h>

namespace hga {

	namespace GLOBAL {

		uint8_t active_buffer = 0;	// 0 = default B000:000 1 = B000:8000 second display page buffer

	}

}

#endif