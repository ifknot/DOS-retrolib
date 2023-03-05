/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      6.06.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_READ_LIGHTPEN_REGISTERS_H
#define HGA_READ_LIGHTPEN_REGISTERS_H

#include <stdint.h>

#include "hga_constants.h"

namespace hga {

	    /**
        *  @brief  the 6845 CRTC's Light Pen High and Low registers (10h and 11h) in the high and low bytes
        *  @retval  - High and Low registers
        */
        inline uint16_t read_light_pen_registers() {
            uint16_t pen_regs = 0;
            __asm {
                .8086
#ifdef STACKING
                push dx
                push ax
#endif
                mov     dx, CRTC_LIGHT_PEN_RESET        ; reset the CRTC light pen latch
                out     dx, al                          ; writing anything to this port resets the light pen

                mov     dx, CRTC_STATUS_PORT            ; wait for start of vertical retrace
L1:             in      al, dx                          ; read status port
                test    al, 80h                         ; is horizontal retrace active?
                jnz     L1                              ; retrace still active

L2:             in      al, dx                          ; read status port again
                test    al, 80h                         ; is horizontal retrace active?
                jz      L2                              ; not yet

                cli                                     ; disable interupts
L3:             in      al, dx                          ; read status port again
                test    al, 80h                         ; is horizontal retrace active ?
                jnz             L3                      ; wait for it to to finish

                mov     dx, CRTC_LIGHT_PEN_LATCH        ; latch the light pen register counter
                out     dx, al                          ; writing anything captures
                sti                                                                     ; re-enable interupts

                mov     dx, CRTC_ADDRESS_PORT
                mov     al, 10h                         ; Light Pen high register number
                out     dx, al                          ; latch high register

                mov     dx, CRTC_DATA_PORT
                in      al, dx                          ; high reg in al
                mov     ah, al                          ; copy to ah

                mov     dx, CRTC_ADDRESS_PORT
                mov     al, 11h                         ; Light Pen low register number
                out             dx, al                  ; latch low register

                mov     dx, CRTC_DATA_PORT
                in      al, dx                          ; low reg in al

                mov     pen_regs, ax
#ifdef STACKING
                pop     ax
                pop     dx
#endif
            }
            return pen_regs;
        }
 
}

#endif