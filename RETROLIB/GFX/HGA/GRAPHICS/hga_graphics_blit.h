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

namespace hga {

	namespace graphics {

		/**
		* @brief blit contiguous 720x348 raster image into banked HGA VRAM
		* @details 
		* @note No sanity checking! Expects raster_data & vram_segment to be valid.
		*/
		void blit_full_screen(char* raster_data, uint16_t vram_segment = HGA_BUFFER_0);

	}

}


#endif