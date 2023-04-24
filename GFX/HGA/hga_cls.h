/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_CLS_H
#define HGA_CLS_H

#include <stdint.h>

#include "hga_constants.h"
#include "hga_environment.h"

namespace hga {

    /**
     *  @brief Clear the current active page Hercules VRAM starts at B000:0000
     *  @note When switching back to text mode use mda::text_cls to ensure that the attribute bytes are set to visible text 
     *  @details The Hercules display adapter displays in both text mode and graphics mode,
     *  with a graphics resolution of 720x348 pixels, and contains enough RAM for 2 page displays.
     *  Each display page is 32K, having the capacity to host a 4K text page and a graphics page.
     *  B000:0000 - B000:7FFF   First Page
     *  B000:8000 - B000:FFFF   Second Page
     *  @param buffer - select the offset of the current active page 
     */
    void cls(uint16_t buffer = GLOBAL::active_buffer) {
        __asm {
            .8086
            pushf
            mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; es points to screen segment

            xor     di, di
            mov     cx, WORDS_PER_PAGE          ; 16K words VRAM buffer 32K bytes
            xor     ax, ax                      ; zero ax
            cld                                 ; increment mode
            rep     stosw                       ; clear VRAM buffer
            popf
        }
    }

    /**
     *  @brief Waits for the vertival sync before clearing the screen
     *  @param buffer - 
     */
    void sync_cls(uint16_t buffer = GLOBAL::active_buffer) {
        __asm {
            .8086
            pushf
            mov     ax, HGA_VIDEO_RAM_SEGMENT
            add     ax, buffer                  ; 0000h or 0B000h for first or second VRAM buffer
            mov     es, ax                      ; es points to screen segment

            xor     di, di
            mov     cx, WORDS_PER_PAGE          ; 16K words VRAM buffer 32K bytes
            xor     ax, ax                      ; zero ax
            cld                                 ; increment mode

            mov     dx, CRTC_STATUS_PORT        ; read port 3BAh
vWAIT0:     in      al, dx                      ; read status
            test    al, 10000000b               ; is bit 7 clear ? (in a vertical retrace interval)
            jz      VWAIT0                      ; yes, keep waiting
VWAIT1:     in      al, dx                      ; read status again
            test    al, 10000000b               ; is bit 7 clear ? (just started a vertical retrace interval)
            jz      VWAIT1                      ; no, keep waiting

            rep     stosw                       ; clear VRAM buffer
            popf
        }
    }

}

#endif

