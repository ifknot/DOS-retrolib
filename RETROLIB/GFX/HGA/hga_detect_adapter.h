/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef HGA_DETECT_ADAPTER_H
#define HGA_DETECT_ADAPTER_H

#include <stdint.h>

#include "../gfx_constants.h"
#include "../gfx_detect_crtc.h"

#include "hga_constants.h"

namespace hga {

    /**
    * If an MDA card is detected, however, you can also distinguish between an MDA card and the Hercules cards.
    * To do this, the vertical sync bit is sampled and then for a certain time interval, is continually and frequently re-sampled.
    * + if no change is observed, the video card is assumed to be an MDA card.
    * + if the vertical sync bit changes, the video card is one of the Hercules graphics cards.
    * The specific card is identified by examining bits 4-6 of the status port:
    * + a pattern of 001 indicates a Hercules Graphics Card Plus
    * + a pattern of 101 indicates a Hercules In-Color Card
    * + any other pattern is a Hercules Graphics Card.
    *
    * Reading from port 03BAh returns vertical sync in bit 7, and a card ID in bits 6-4:
    * 000: Hercules
    * 001: Hercules Plus
    * 101: Hercules InColor
    * 111: Unknown clone
    *
    * @note Only trust this ID once you've checked that there's a vertical sync present; if bit 7 is the same for 32768 reads in succession, then there isn't.
    * @note Some Hercules cards support a light pen. Bit 1 of port 3BAh returns the lightpen sensor status; any write to port 3BBh resets the light pen status.
    *
    * return:
    * 0 Unknown
    * 2 Hercules
    * 3 Hercules Plus
    * 4 Hercules InColor
    * 5 Hercules Clone
    */
	uint8_t detect_adapter() {
        uint8_t adapter = VIDEO_ADAPTER_UKNOWN;
        if (gfx::detect_CRTC_at_port(gfx::crtc_port_MDA)) {
            __asm {
                .8086
                push    bp
                pushf

                mov     dx, HGA_CRTC_STATUS_PORT            ; DX: = 3BAh(MDA/Hercules status port)
                in      al, dx                              ; read status port
                and     al, 80h                             ; mask off only bit 7
                mov     ah, al                              ; copy al into ah = bit 7 (vertical sync on HGC)

                mov     cx, 8000h                           ; 32768 samples - deemed adequate in the literature
        L1:     in      al, dx                              ; read status port
                and     al, 80h                             ; isolate bit 7
                cmp     ah, al                              ; has the vertical sync bit changed?
                loope   L1                                  ; no sample again yes leave loop

                jne     HGA                                 ; bit 7 changed, it's a Hercules
                mov     adapter, VIDEO_ADAPTER_MDA          ; MDA
                jmp     EXIT

        HGA:    in      al, dx                              ; read status port again
                and     al, 70h                             ; isolate bits 4-6

                cmp     al, 70h                             ; Unknown clone bit pattern 111
                jne     L2
                mov     adapter, VIDEO_ADAPTER_HGC_CLONE    ; Unknown clone
                jmp     EXIT

        L2:     cmp     al, 50h                             ; Hercules InColor bit pattern 101
                jne     L3
                mov     adapter, VIDEO_ADAPTER_HGC_INCOLOR  ; HGC_INCOLOR
                jmp     EXIT

        L3:     cmp     al, 10h                             ; Hercules Plus bit pattern 100
                jne     L4
                mov     adapter, VIDEO_ADAPTER_HGC_PLUS     ; HGC_PLUS
                jmp     EXIT

        L4:     mov     adapter, VIDEO_ADAPTER_HGC          ; HGC only bit pattern left ie 000

        EXIT:   popf 
                pop     bp

            }
        }
        return adapter;
    }

}

#endif