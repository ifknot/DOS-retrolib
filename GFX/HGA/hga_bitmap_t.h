/**
 *
 *  @brief     An HGA memory layout matching bitmap for fast blit to HGA VRAM
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.04.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_BITMAP_T_H
#define HGA_BITMAP_T_H

#include <assert.h>

#include "../../GFX/gfx_bitmap_t.h"

namespace hga {

 /**
  *  @struct bitmap_t
  *  @brief  A very simple interleaved data structure for storing HGA bitmap data.
  *  @details HGA VRAM has an unusual layout of 4 interleaved scan lines, packed pixel.
  *	 The 32K VRAM of each display page is divided into 4 x 8K blocks.
  *     +         Block 1 divisible by 4 then + 0 (0, 4, 8, 12..)
  *     +         Block 2 divisible by 4 then + 1 (1, 5, 9, 13..)
  *     +         Block 3 divisible by 4 then + 2 (2, 6, 10, 14..)
  *     +         Block 4 divisible by 4 then + 3 (3, 7, 11, 15..)
  *
  *   Each scan line is 90-bytes long and there are 348 scan lines (2 lines unused in each block).
  *   Each byte contains 8 pixels ie 31,320 total pixel bytes.
  */
	struct bitmap_t {
		uint16_t width;			// image pixel width
		uint16_t byte_width;	// number of bytes per image line (calculated fomr width and height)
		uint16_t height;		// image pixel height
		uint16_t size;			// total number of image data bytes
		char* data;				// pointer to the image data bytes
	};

 /**
  *  @brief Initialise a bitmap_t
  *  @note Offers convenient zero size image defaults
  *  @param bmp    - pointer to an extant hga::bitmap_t
  *  @param width  - image pixel width
  *  @param height - image pixel height
  *  @param data   - pointer to HGA interleaved image data bytes sufficient to satisfy calculated size as per width and height
  */
	void init_bitmap(hga::bitmap_t* bmp, uint16_t width = 0, uint16_t height = 0, char* data = NULL) {
		if (bmp) {
			bmp->width = width;
			bmp->byte_width = (width >> 3) + (width % 8 == 0) ? 0 : 1;	// width/8 + 1 byte if pixel width not evenly divisible by 8
			bmp->height = height;
			bmp->size = bmp->byte_width * bmp->height;
			bmp->data = data;
		}
	}

 /**
  *  @brief  create 8 step shifted HGA interleaved bitmaps from a DIB gfx::simple_bitmap_t
  *  @param  bmp - pointer to an extant gfx::simple_bitmap_t
  *  @retval     - pointer to the first bitmap newly created array of 8 hga::bitmap_t 
  */
	hga::bitmap_t* create_bitmap(gfx::simple_bitmap_t* bmp) { // TODO:

	}

 /**
  *  @brief  create a byte aligned HGA interleaved bitmap composed of 8x8 pixel tiles from a DIB gfx::simple_bitmap_t
  *  @param  bmp - pointer to an extant gfx::simple_bitmap_t
  *  @retval     - pointer to the byte aligned HGA interleaved bitmap composed of 8x8 pixel tiles
  */
	hga::bitmap_t* create_tilemap(gfx::simple_bitmap_t* bmp) { // TODO:

	}

 /**
  *  @brief Free any malloc'd memory used by an HGA bitmap.
  *  @note  The bitmap structure itself is *not* deleted.
  *  @param bmp - pointer to an extant hga::bitmap_t
  */
	void free_bitmap(hga::bitmap_t* bmp) {
		if (bmp && bmp->data) free(bmp->data);
	}

}

#endif