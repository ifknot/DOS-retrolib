/**
 *
 *  @file      hga_detect_adapter.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "hga_detect_adapter.h"

#include "../gfx_constants.h"
#include "../gfx_detect_crtc.h"

#include "hga_constants.h"

namespace hga {

	uint8_t detect_adapter() {
        uint8_t adapter = VIDEO_ADAPTER_UKNOWN;
        if (gfx::detect_CRTC_at_port(gfx::crtc_port_HGA)) {
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

                cmp     al, 70h                             ; Hercules unknown clone bit pattern 111
                jne     L2
                mov     adapter, VIDEO_ADAPTER_HGA_CLONE    
                jmp     EXIT

        L2:     cmp     al, 50h                             ; Hercules InColor bit pattern 101
                jne     L3
                mov     adapter, VIDEO_ADAPTER_HGA_INCOLOR  
                jmp     EXIT

        L3:     cmp     al, 10h                             ; Hercules Plus bit pattern 100
                jne     L4
                mov     adapter, VIDEO_ADAPTER_HGA_PLUS     
                jmp     EXIT

        L4:     mov     adapter, VIDEO_ADAPTER_HGA          ; Original Hercules only bit pattern left ie 000

        EXIT:   popf 
                pop     bp

            }
        }
        return adapter;
    }

}