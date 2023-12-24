/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_GRPAHICS_BLIT_H
#define	HGA_GRPAHICS_BLIT_H

#include <stdint.h>

namespace hga {

	namespace graphics {
		
		void blit(uint16_t vram_segment, char* raster_data);

	}

}


#endif