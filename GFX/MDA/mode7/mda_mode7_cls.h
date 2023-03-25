/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      23.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_CLS_H
#define MDA_MODE7_CLS_H

#include "mda_mode7_constants.h"

namespace mda {

    namespace mode7 {

        void cls(colour_t col, attribute_t attrib = attribute::normal) {
            __asm {
                .8086

                mov             ax, MDA_VIDEO_RAM_SEGMENT
                mov             es, ax                                  ; ES:DI will point to x,y screen byte
                xor             di, di
                mov             ah, attrib                              ; 'normal' attribute
                mov             al, col                                 ; default 'black'
                mov             cx, CHARS_PER_SCREEN    ; 80 columns x 25 rows
                cld                                                     ; increment mode
                rep             stosw                                   ; fill screen
            }
        }

        void cls_attributes(attribute_t attrib = attribute::normal) {
            __asm {
                .8086

                mov             ax, MDA_VIDEO_RAM_SEGMENT
                mov             es, ax                                  ; ES:DI will point to x,y screen byte
                xor             di, di
                mov             al, attrib
                mov             cx, CHARS_PER_SCREEN    ; 80 columns x 25 rows
                cld                                                     ; increment mode
L0:             inc             di                                      ; skip ascii byte
                stosb                                                   ; reset attribute byte
                loop    L0                                              ; whole screen
            }
        }

        void cls_characters(char ascii = 0) {
            __asm {
                .8086

                mov             ax, MDA_VIDEO_RAM_SEGMENT
                mov             es, ax                                  ; ES:DI will point to x,y screen byte
                xor             di, di
                mov             al, ascii
                mov             cx, CHARS_PER_SCREEN    ; 80 columns x 25 rows
                cld                                                     ; increment mode
L0:             stosb                                                   ; reset ascii byte
                inc             di                                      ; skip attribute byte
                loop    L0                                              ; whole screen
            }
        }

    }

}

#endif