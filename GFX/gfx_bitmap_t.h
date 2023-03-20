/**
 *
 *  @brief     Device Independent Bitmap 
 *  @details   Based on the PNG container format with critical and optional "chunks" the critical chunks are
 *				+ IHDR - image header *must* appear first
 *				+ IDAT - image data as a rectangular pixel array, left-to-right pixels per line and top-to-bottom lines
 *			   The optional chunks are (as of 20.03.2023)
 *				+ PLTE - palette of 1 to 256 indexed entries of 3 byte RGB tuples 
 *  @note	   Unlike the 4 bytes used by PNG chunks the retrolib chunks omit the CRC and have 2 byte lenght as a memory sapce compromise
 *  @url http://www.libpng.org/pub/png/spec/1.2/PNG-DataRep.html#DR.Image-layout
 *  @author    Jeremy Thornton
 *  @date      20.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "gfx_constants.h"

namespace gfx {

	 /**
	  *  @struct ihdr
	  *  @brief  always the first chunk contains image metrics
	  *  @details 
	  *  + width (2 bytes)
	  *  + height (2 bytes)
	  *  + bit depth (1 byte, values 1, 2, 4, 8, or 16)
	  *  + color type (1 byte, values 0, 2, 3, 4, or 6)
	  */
	struct ihdr {
		uint16_t length;
		char type[4];

	};

}

#endif