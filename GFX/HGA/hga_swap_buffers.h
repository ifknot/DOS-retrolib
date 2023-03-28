/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_GRAPHICS_SWAP_BUFFERS_H
#define HGA_GRAPHICS_SWAP_BUFFERS_H

#include <stdint.h>

#include "hga_constants.h"
#include "hga_environment.h"

namespace hga {

    inline void swap_buffers() {
        using namespace GLOBAL;
        __asm {
            .8086
            xor     active_buffer, HGA_PAGE_2_OFFSET    ; flip to other page  using xor 0 -> 800h and 800h -> 0
            mov     dx, HGA_CONTROL_REGISTER
            mov     ax, active_buffer
            or      ah, ah
            jns     L0                          ; because Bh is 80b ie signed hence 800h is signed
            mov     al, 00001010b               ; screen on buffer 0 default display page buffer B000:000
            out     dx, al
            jmp     END
    L0:     mov     al, 10001010b               ; screen on buffer 1 second display page buffer B000:8000
            out     dx, al
    END:

        }
    }

    void vsync_swap_buffers() {
         using namespace GLOBAL;
        __asm {
            .8086
            xor     active_buffer, HGA_PAGE_2_OFFSET    ; xor other page  using xor 0 -> 800h and 800h -> 0
            mov     ax, active_buffer
            or      ah, ah
            jns     L0                          ; because Bh is 80b ie signed hence 800h is signed

            mov     dx, CRTC_STATUS_PORT        ; read port 3BAh
    V0a:    in      al, dx                      ; read status
            test    al, 10000000b               ; is bit 7 clear ? (in a vertical retrace interval)
            jz      V0a                         ; yes, keep waiting
    V0b:    in      al, dx                      ; read status again
            test    al, 10000000b               ; is bit 7 clear ? (just started a vertical retrace interval)
            jz      V0b                         ; no, keep waiting

            mov     dx, HGA_CONTROL_REGISTER
            mov     al, 00001010b               ; screen on buffer 0 default display page buffer B000:000
            out     dx, al                      ; swap 
            
            jmp     END

    L0:     mov     dx, CRTC_STATUS_PORT        ; read port 3BAh
    V1a:    in      al, dx                      ; read status
            test    al, 10000000b               ; is bit 7 clear ? (in a vertical retrace interval)
            jz      V1a                         ; yes, keep waiting
    V1b:    in      al, dx                      ; read status again
            test    al, 10000000b               ; is bit 7 clear ? (just started a vertical retrace interval)
            jz      V1b                         ; no, keep waiting

            mov     dx, HGA_CONTROL_REGISTER
            mov     al, 10001010b               ; screen on buffer 1 second display page buffer B000:8000
            out     dx, al                      ; swap
    END:
        }
    }


}

#endif

/*

                                mov     dx, CRTC_STATUS_PORT  ; CGA status reg
                L0:             in      al, dx          ; read status
                                test    al, 1000b       ; is bit 3 set ? (in a vertical retrace interval)
                                jnz     L0              ; yes, keep waiting
                L1:             in      al, dx          ; read status
                                test    al, 1000b       ; is bit 3 set ? (just started a vertical retrace interval)
                                jnz     L1              ; no, keep waiting

*/