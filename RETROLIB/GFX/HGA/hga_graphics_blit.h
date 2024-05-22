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
		
	/**
	* @brief paint the VRAM buffer with a repeating byte 
	*/
	//void blit_vram_byte(uint16_t vram_segment, char byte);

	/**
	* @brief paint the VRAM buffer with a repeating word
	*/
	//void blit_vram_byte(uint16_t vram_segment, uint16_t word);

	/**
	* @brief fast raster bit block transfer 32768 bytes from bitmap memory to the 4 banks of a VRAM buffer 
	* @note hard coded HGA screen rectangle (0,0,720,480)
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data);

	//void blit_vram_byte(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	/**
	* @brief fast rectangular block (x,y,w,h) transfer raster bytes from bitmap memory to the same location in 4 banks of a VRAM buffer
	* @note x and w values are rounded to the enclosing byte boundry 
	*/
	void blit_vram_bmp(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	/**
	* @brief fast rectangular block (x,y,w,h) transfer raster bytes from source bitmap memory to destination bitmap memory at position (xx,yy)
	* @note expects an xshifted bitmap with pre-rendered offsets for mod 7 x values
	*/
	void blit_bmp_bmp(char* raster_destination, char* raster_source, uint16_t xx, uint16_t yy, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	//void blit_bmp_bmp(char* raster_destination, char* raster_source, char* raster_mask, uint16_t x, uint16_t y, uint16_t ox, uint16_t oy, uint16_t ow, uint16_t oh);

}


#endif
