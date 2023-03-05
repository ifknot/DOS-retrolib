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

namespace hga {

    void cls(uint8_t buffer = 0) {
        __asm {
            .8086
            pushf
            mov     ax, HGA_VIDEO_RAM_SEGMENT
            test    buffer, 1                   ; which buffer ?
            jz      J0
            add     ax, 800h                    ; second buffer
J0:         mov     es, ax
            xor     di, di
            mov     cx, 4000h                   ; 16K words VRAM buffer 32K bytes
            xor     ax, ax                      ; zero ax
            cld                                 ; increment mode
            rep     stosw                       ; clear VRAM buffer
            popf
        }
    }

}

#endif