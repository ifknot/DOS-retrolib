/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef HGA_PIXEL_H
#define HGA_PIXEL_H

#include "hga_types.h"

namespace hga {

	void plot_pixel(uint16_t vram_segment, uint16_t x, uint16_t y, colour_t c);

	void hsync_plot_pixel(uint16_t vram_segment, uint16_t x, uint16_t y, colour_t c);

	colour_t read_pixel(uint16_t vram_segment, uint16_t x, uint16_t y);

}

#endif