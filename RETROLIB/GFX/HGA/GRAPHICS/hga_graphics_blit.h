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
		
		/**
		* @brief fast raster bit block transfer 32768 bytes from memory to the 4 banks of a VRAM buffer 
		* @note hard coded HGA screen rectangle (0,0,720,480)
		*/
		void blit(uint16_t vram_segment, char* raster_data);

		/**
		* @brief fast rectangular block (x,y,w,h) transfer raster bytes from memory to the same location in 4 banks of a VRAM buffer
		* @note x and w values are rounded to the enclosing byte boundry 
		*/
		void blit(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	}

}


#endif