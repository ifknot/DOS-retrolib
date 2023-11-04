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
    bool detect_CRTC_at_port(uint16_t port_number) {
        uint8_t found = 0;
        __asm {
            .8086
            push    bp
            pushf

            mov     ax, 0Fh             ; cursor low register
            mov     dx, port_number
            out     dx, al              ; select 6845 cursor low reg
            inc     dx
            in      al, dx              ; AL is old Cursor Low value
            mov     ah, al              ; preserve old value in AH
            mov     al, 66h             ; AL = arbitrary new value
            out     dx, al              ; try to write new value to 6845

            mov     cx, 100h            ; deemed adequate in the literature
    WAIT:   loop    WAIT                ; wait for 6845 to respond

            in      al, dx              ; read back value
            xchg    ah, al              ; AL becomes old Cursor Low value
            out     dx, al              ; restore old value

            cmp     ah, 66h             ; test whether 6845 responded with new value?
            jne     EXIT                ; jump if it did not, leaving found as 0

            mov     found, 1

    EXIT:   popf
            pop     bp
        }
        return static_cast<bool>(found);
    }

}

#endif