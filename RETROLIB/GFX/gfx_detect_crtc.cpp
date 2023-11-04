/**
 *
 *  @file      gfx_detect_crtc.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "gfx_detect_crtc.h"

namespace gfx {

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