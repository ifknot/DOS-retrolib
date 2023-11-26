/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      25.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_VIDEO_MODE_H
#define HGA_VIDEO_MODE_H

#include <stdint.h>

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

}

#endif