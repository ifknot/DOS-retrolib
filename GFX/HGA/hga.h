/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HERCULES_GRAPHICS_ADAPTER_H
#define HERCULES_GRAPHICS_ADAPTER_H

 // TODO: gfx::herc
 //  [x] card type primitives
 //  [x] graphics_mode
 //  [x] swap_buffers
 //  [x] cls
 //  [x] write_glyph
 //  [ ] glyphmap
 //  [ ] write_glyphmap
 //  [x] default font ascii 0-255
 //  [x] bitmap_union
 //  [x] load_bitmap
 //  [ ] save_bitmap

#include "hga_cls.h"
#include "hga_constants.h"
#include "hga_default_font_8x8.h"
#include "hga_environment.h"
#include "hga_monospaced_font_t.h"
#include "hga_read_light_pen_registers.h"
#include "hga_swap_buffers.h"
#include "hga_video_mode.h"
#include "hga_vram_tile_8x8.h"
#include "hga_vram_tile_block.h"
#include "hga_vram_word_write_bitmap.h"
#include "hga_vsync.h"

/**
 *  @namespace hga
 *  @brief     
 */
namespace hga {

}

#endif