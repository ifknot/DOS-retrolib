/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef	HGA_BLIT_BITMAP_H
#define HGA_BLIT_BITMAP_H

#include <assert.h>

#include "hga_constants.h"
#include "hga_environment.h"

#include "../gfx_bitmap_t.h"

namespace hga {

 /**
  *  @brief copy the HGA sized bitmap to the VRAM
  *  @note no sanity checks unless debug mode
  *  @param bmp    - screen sized bitmap
  *  @param buffer - the vram buffer 
  */
	void blit_bitmap(const gfx::simple_bitmap_t* bmp, uint16_t buffer = GLOBAL::active_buffer) {

	}

}

#endif