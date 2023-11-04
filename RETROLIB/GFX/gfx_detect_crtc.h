/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef GFX_DETECT_CRTC_H
#define GFX_DETECT_CRTC_H

#include <stdint.h>

#include "gfx_constants.h"

namespace gfx {

    /**
    * @brief Detects whether or not a given I/O address is that of a 6845 CRT Controller
    * @details The Cursor Location Low register of the alleged CRTC is written with an arbitrary value
    * [1] Wilton, Richard, Programmer's Guide to PC and PS/2 Video Systems.
    * Wait an arbitrary period of time then check if the value is retained?
    * In which case the CRTC is *probably* detected
    */
    bool detect_CRTC_at_port(uint16_t port_number);

}

#endif