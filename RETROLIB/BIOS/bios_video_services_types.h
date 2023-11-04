/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef	BIOS_VIDEO_SERVICES_TYPES
#define BIOS_VIDEO_SERVICES_TYPES

#include <stdint.h>

#include "bios_video_services_constants.h"

namespace bios {

	/**
	 * Video BIOS get video mode return structure.
	 */
	struct video_state_t {
		uint8_t			columns;
		uint8_t			mode;
		uint8_t			page;
	};

}

#endif