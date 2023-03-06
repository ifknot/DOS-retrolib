/**
 *
 *  @brief Hercules VRAM starts at B000:0000
 *  @details The Hercules display adapter displays in both text mode and graphics mode,
 *  with a graphics resolution of 720x348 pixels, and contains enough RAM for 2 page displays.
 *  B000:0000 - B000:7FFF   First Page
 *  B000:8000 - B000:FFFF   Second Page
 *  Each display page is 32K, having the capacity to host a 4K text page and a graphics page.
 *  @note However, the 32K per buffer is not contiguous but rather split into 4 banks of 8K VRAM each
 *  that map to 4 consecutive screen lines before the 5th line starts back in bank 0 but 90 bytes in.
 *  So each group of 4 lines is separated by 2000h bytes.
 * 
 *  For "glyphs" the idea is to divide up the screen into tiles of size width x height 
 *  where (ideally) 720 is evenly divisible by glyph width (eg multiples of 4)
 *  and 348 is evenly divisible by glyph height (eg multiple of 6)
 *
 *  @author    Jeremy Thornton
 *  @date      12.06.2022 v2 03/05/2023
 *  @copyright Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GLYPH_H
#define HGA_GLYPH_H

#include "hga_constants.h"
#include "hga_environment.h"

#include "hga_write_glyph_8x8.h"
#include "hga_write_glyph_8x6.h"

// TODO:
// [x] fast 8x8 glyph 
// [ ] fast 8x6 glyph
// [ ] fast 4x4 glyph
// [ ] slower general purpose width x height glyphs

namespace hga {

	void write_glyph(uint16_t width, uint16_t height, uint16_t x, uint16_t y, const uint8_t* bytes, uint8_t buffer = GLOBAL::active_buffer) {
	
	}

}

#endif