/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_BLIT_H
#define	HGA_BLIT_H

#include <stdint.h>

namespace hga {

	void test_blit(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w, uint16_t h);

	/**
	* @brief fast raster bit block transfer 31320 bytes from bitmap memory to the 4 banks of a VRAM buffer
	* @details used for e.g. painting entire background image
	* @note BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data);

	/**
	* @brief fast rectangular block (x,y,w,h) transfer raster bytes from bitmap memory to the same location in 4 banks of a VRAM buffer
	* @details used for e.g. patching background bitmap
	* copies a bitmap rectangle(x,y,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. x and w values are truncated to the enclosing byte boundry
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	/**
	* @brief fast rectangular block (a,b,w,h) transfer raster bytes from bitmap memory to new location (x,y,w,h) in 4 banks of a VRAM buffer
	* @details used for e.g. animation
	* copies a bitmap rectangle(a,b,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. a, x and w values are truncated to the enclosing byte boundry
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w,  uint16_t h);

}


#endif
