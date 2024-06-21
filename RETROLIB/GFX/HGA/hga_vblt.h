/**
 *
 *  @brief     Suite of fast block transfer functions to copy raster data from system RAM to video screen RAM
 *  @details   Bridges the linear system RAM and the 4 banks of Hercules video RAM
 *  + Enables the offscreen buffer pattern where faster linear memory or "bitmap" functions are used cut, mask, paste, etc. the 
 *  buffered graphics before the affected areas or "dirty rectangles" are updated in optimal sized rectangular chunks to the video RAM
 *  + Enables fast updating of the screen from an offscreen buffer
 *  + Is byte aligned and most efficient when update rectangle is even ie divisible by 2 bytes ie a word hence MOVSW
 *  + Not designed to mask but simply replace update aka "dirty" rectangles from a back buffer to the screen
 *  @note there is no boundry checking or clipping else face undefined behaviour
 *  @author    Jeremy Thornton
 *  @date      19.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VBLT_H
#define	HGA_VBLT_H

#include <stdint.h>

namespace hga {

	/**
	* @brief fast raster *byte aligned* bit block transfer 31320 bytes from bitmap memory to the 4 banks of a VRAM buffer
	* @details used for updating the entire screen from the offscreen buffer
	* @note BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	*/
	void vblt(uint16_t vram_segment, char* raster_data);

	/**
	* @brief fast *byte aligned* rectangular block (x,y,w,h) transfer raster bytes from bitmap memory to the same location in 4 banks of a VRAM buffer
	* @details used for updating corresponding rectangles between screen and offscreen buffer
	* copies a bitmap rectangle(x,y,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. x and w values are truncated to the enclosing byte boundry
	*/
	void vblt(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t w, uint16_t h);

	/**
	* @brief fast *byte aligned* rectangular block (a,b,w,h) transfer raster bytes from bitmap memory to new location (x,y,w,h) in 4 banks of a VRAM buffer
	* @details used for updating different rectangles between screen and offscreen buffer 
	* copies a bitmap rectangle(a,b,w,h) to VRAM rectangle(x,y,w,h)
	* @note 1. BOTH source bitmap and HGA screen rectangle (0,0,720,348) hardcoded ie 31,320 bytes each
	* @note 2. a, x and w values are truncated to the enclosing byte boundry
	*/
	void vblt(uint16_t vram_segment, char* raster_data, uint16_t x, uint16_t y, uint16_t a, uint16_t b, uint16_t w,  uint16_t h);

}

#endif
