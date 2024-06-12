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

/* TEST *****************************************************************************************/

	//hga::wallpaper16(HGA_BUFFER_1, bmp.raster_data, 0, 10, 0, 10, 16, 320);
	//source must be same dimensions as screen (faster) 
	void wallpaper16(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w,  uint16_t h);
		
/******************************************************************************************/

	/**
	* @brief fast raster bit block transfer 32768 bytes from bitmap memory to the 4 banks of a VRAM buffer 
	* @note hard coded HGA screen rectangle (0,0,720,480)
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data);

	/**
	* @brief fast rectangular block (x,y,w,h) transfer raster bytes from bitmap memory to the same location in 4 banks of a VRAM buffer
	* @note x and w values are truncated to the enclosing byte boundry 
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);
}


#endif
