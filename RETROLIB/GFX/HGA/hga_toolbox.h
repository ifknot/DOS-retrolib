/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_TOOLBOX_H
#define HGA_TOOLBOX_H

#include "hga_attributes.h"
#include "hga_constants.h"
#include "hga_video_mode_presets.h"

namespace hga {

    /**
    *  @brief  program CRTC for video mode as described by the CRTC presets data table
    *  @details Since the Hercules card(s) use the same CRTC 6845 processor as the IBM card(s), the internal
    *  registers of the 6845 and their meaning are identical to the IBM MDA.
    *  The index register and data register are also located at the same address and the preset values
    *  must be assigned to the various registers in the text and graphics modes respectively.
    * */
    void video_mode(const uint8_t* presets, uint8_t flags_config, uint8_t flags_ctrl);

    /**
    *  @brief  enter text "half" mode single display frame (mimic MDA)
    */
    inline void text_mode() {
        video_mode(hga::crtc_presets_text_mode, hga::text_config_default, hga::text_ctrl_default);
    }

    /**
    *  @brief  enter Hercules graphics "full" mode with 2 frame buffers
    */
    inline void graphics_mode() {
        video_mode(hga::crtc_presets_graphics_mode, hga::graphics_config_default, hga::graphics_ctrl_default);
    }

    /**
        * @brief Fast fill the specified HGA VRAM buffer with an 8 bit byte pattern
        * @details
        * @note No sanity checking! Expects vram_segment to be valid.
        */
    void fill_vram_buffer(uint16_t vram_segment, uint8_t byte_pattern);

    /**
    * @brief clear the specified HGA VRAM buffer to black
    * @note defaults to buffer 0
    */
    inline void cls(uint16_t vram_segment = HGA_BUFFER_0) {
        fill_vram_buffer(vram_segment, 0);
    }

    /**
    * @brief select which of the 2 HGA adapter VRAM buffers ( 0 or 1 ) to be displayed on screen
    * @note No sanity checking! Expects 0 or 1.
    */
    void select_display_buffer(uint8_t select);

}

#endif