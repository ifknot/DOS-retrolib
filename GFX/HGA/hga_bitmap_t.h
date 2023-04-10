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

#define HGA_BITMAP_DATA_BLOCKS 8
#define HGA_BITMAP_MAX_IMG_SIZE 8192
#define HGA_BITMAP_INTERLEAVE 4

#define LOOP if (--cx != 0) goto 

#define JCXZ if(cx == 0) goto 

#define JZ(r) if(r == 0) goto 

#define DUMP	std::cout << std::hex << "src = " << (uint32_t)src << ' ' << "dst = " << (uint32_t)dst << '\n'; \
				std::cout << std::dec << "bx = " << bx << " dx = " << dx << " bp = " << bp << " step = " << step << " cx = " << cx << '\n'

namespace hga {

 /**
  *  @struct bitmap_t
  *  @brief  An HGA prepared bitmap optimized for fast blitting to VRAM.
  *  @details HGA VRAM has an unusual layout of 4 interleaved scan lines, packed pixel.
  *	 The 32K VRAM of each display page is divided into 4 x 8K blocks.
  *     +         Block 1 divisible by 4 then + 0 (0, 4, 8, 12..)
  *     +         Block 2 divisible by 4 then + 1 (1, 5, 9, 13..)
  *     +         Block 3 divisible by 4 then + 2 (2, 6, 10, 14..)
  *     +         Block 4 divisible by 4 then + 3 (3, 7, 11, 15..)
  *
  *   Each scan line is 90-bytes long and there are 348 scan lines (2 lines unused in each block).
  *   Each byte contains 8 pixels ie 31,320 total pixel bytes.
  *   Thus, the HGA bitmap has its data laid out in the same interleaved pattern.
  *   Further, the data block has a further 7 blocks, each of which is bit shifted right by one pixel from its prior block.
  *   In this way the bitmap has a preshifted bitmap for each x loctaion 0..7 lower 3 bits ready for fast blitting
  *   @note This has the consequence that the *maximum* original image size is 8K (8192 bytes) as the total 8 shifted copies must fit inside an 8086 64K segment
  */
	struct bitmap_t {
		uint16_t width;			// image pixel width
		uint16_t byte_width;	// number of bytes per image line (calculated fomr width and height)
		uint16_t height;		// image pixel height
		uint16_t img_size;		// single image number of data bytes (max 8192 bytes)
		uint16_t size;			// total number of bytes for all 8 shifted images (max 64K)
		char* data;				// pointer to the image data bytes 8 blocks of shifted duplicates offset by img_size bytes
	};

 /**
  *  @brief Initialise a bitmap_t
  *  @note Offers convenient zero size image defaults
  *  @param bmp    - pointer to an extant hga::bitmap_t
  *  @param width  - image pixel width
  *  @param height - image pixel height
  *  @param data   - pointer to HGA interleaved image data bytes sufficient to satisfy calculated size as per width and height
  */
	void init_bitmap(hga::bitmap_t* hmp, uint16_t width = 0, uint16_t height = 0, char* data = NULL) {
		if (hmp) {
			hmp->width = width;
			hmp->byte_width = (width >> 3);				// width / 8
			hmp->byte_width += (width & 7) == 0 ?0 :1;	// extra byte if pixel width not evenly divisible by 8
			hmp->byte_width++;							// finally add extra byte to right shift into for x 0..7
			hmp->height = height;
			hmp->img_size = hmp->byte_width * hmp->height;
			assert(hmp->img_size < HGA_BITMAP_MAX_IMG_SIZE);
			hmp->size = hmp->img_size; // *HGA_BITMAP_DATA_BLOCKS;
			hmp->data = data;
		}
	}

	void interleave(char* src, char* dst, uint16_t byte_width, uint16_t height) {

		uint32_t stack = (uint32_t)src;		// push SI

		--byte_width;				// drop the spare rotate into byte
		uint16_t bx = byte_width;	// BX is number of bytes per row
		
		uint16_t step = byte_width; // source memory stride = (w * 4) - w 
		step <<= 2;					// * 4				
		step -= byte_width;			// compensate for the rep instructions auto increment

		uint16_t dx = height;		// DX is the number of rows
		uint16_t bp = 0;			// BP is the interleaved bytes count
			
		uint16_t cx = dx;			// row counter
	ROWS:
		dx = cx;					// push counter

		bp = dx;					// calculate the number of interleaved steps
		--bp;						// zero base the height
		bp >>= 2;					// divide by 4 interleaved VRAM lines

		src = (char*)stack;			// pop SI

		cx = bx;					// interleave counter
	REP0:	
		*dst++ = *src++;			// REP MOVSB
		LOOP REP0;	
		*dst++ = 0xF0;				// STOSB into spare byte
		stack = (uint32_t)src;		// push SI

		if (bp == 0) goto SKIP;		// more interleaved lines?
		--bp;
		src += step;				// SI + stride

		cx = bx;
	REP1:
		*dst++ = *src++;
		LOOP REP1;
		*dst++ = 0xF1;
		if (bp == 0) goto SKIP;
		--bp;
		src += step;

		cx = bx;
	REP2:
		*dst++ = *src++;
		LOOP REP2;
		*dst++ = 0xF2;
		if (bp == 0) goto SKIP;
		--bp;
		src += step;

		cx = bx;
	REP3:
		*dst++ = *src++;
		LOOP REP3;
		*dst++ = 0xF3;
		if (bp == 0) goto SKIP;
		--bp;
		src += step;
	
	SKIP:
		cx = dx;
		LOOP ROWS;

	}

 /**
  *  @brief  create 8 step shifted HGA interleaved bitmaps from a DIB gfx::simple_bitmap_t
  *  @param  bmp - pointer to an extant gfx::simple_bitmap_t
  *  @retval     - pointer to the first bitmap newly created array of 8 hga::bitmap_t 
  */
	hga::bitmap_t* create_bitmap(gfx::simple_bitmap_t* bmp) { 
		// compatible bitmap?
		assert(bmp->ihdr.bit_depth == 1);
		// create hga bitmap and sanity check
		hga::bitmap_t* hmp = new hga::bitmap_t;
		assert(hmp);
		init_bitmap(hmp, bmp->ihdr.width, bmp->ihdr.height);
		hmp->data = (char*)calloc(sizeof(char), hmp->size);

		interleave(bmp->idat.data, hmp->data, hmp->byte_width, hmp->height);
		
		return hmp;
	}

 /**
  *  @brief Free any malloc'd memory used by an HGA bitmap.
  *  @note  The bitmap structure itself is *not* deleted.
  *  @param bmp - pointer to an extant hga::bitmap_t
  */
	void free_bitmap(hga::bitmap_t* hmp) {
		if (hmp && hmp->data) free(hmp->data);
	}

}

std::ostream& operator<<(std::ostream& os, const hga::bitmap_t& hmp) {
	os << std::dec << hmp.width << 'x' << hmp.height << ' '
		<< hmp.byte_width << ' ' << hmp.img_size << ' ' << hmp.size << '\n';
	if (hmp.data) {
		os << std::hex << std::setfill('0');
		for (uint16_t i = 0; i < hmp.size; ++i) {
			if ((i & 0xF) == 0) os << '\n';
			os << std::setw(2) << (int)(*(hmp.data + i)) << ' ';
		}
	}
	return os;
}

#endif