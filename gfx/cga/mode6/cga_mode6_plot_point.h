/**
 *
 *  @file       cga_mode6_plot_point.h
 *  @brief      Plot a point in CGA "High Resolution" mode
 *  @details    CGA Hi-res pixel-addressable graphics mode (video mode 06H)
 *  Resolution	640x200 
 *  Colours		4-color 
 *  Palette     
 *  VRAM		16K
 *	Pixel Ratio 1:1.2 on a standard 4:3 display.
 *  Segment     B800
 *  Layout      Interleaved scan lines, packed-pixel.  
 *  Even-numbered scan lines begin at b800:0, and odd-numbered lines begin at b800:2000.
 *
 *          Each scan line is 80-bytes long and there are 200 scan lines
 *          (regen size=8000 bytes * 2 regions).  Each byte contains 8 pixels
 *          (16,000 total pixel bytes):
 *          ╓7┬6┬5┬4┬3┬2┬1┬0╖
 *          ║ │ │ │ │ │ │ │ ║
 *          ╙╥┴╥┴╥┴╥┴╥┴╥┴╥┴╥╜  bits mask
 *           ║ ║ ║ ║ ║ ║ ║ ╚══► 0:  01H  eighth pixel in byte
 *           ║ ║ ║ ║ ║ ║ ╚════► 1:  02H  seventh pixel in byte
 *           ║ ║ ║ ║ ║ ╚══════► 2:  04H  sixth pixel in byte
 *           ║ ║ ║ ║ ╚════════► 3:  08H  fifth pixel in byte
 *           ║ ║ ║ ╚══════════► 4:  10H  fourth pixel in byte
 *           ║ ║ ╚════════════► 5:  20H  third pixel in byte
 *           ║ ╚══════════════► 6:  40H  second pixel in byte
 *           ╚════════════════► 7:  80H  first pixel in byte
 *                                       0=black; 1=white*
 *
 *          Each 1-bit field selects black (0) or 'white'(selected foreground colour) (1).
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE6_PLOT_POINT_H
#define CGA_MODE6_PLOT_POINT_H

#include <stdint.h>

#include "../cga_constants.h"
#include "cga_mode6_constants.h"

//#define NOSNOW
//#define SYNCHRONISED

namespace cga {

        namespace mode6 {

                namespace screen_bound {

                    /**
                    *  @brief  Plot a point clipping to fit within the screen bounds
                    *
                    * Fast bit manipulation calculate row byte y/2 * 80 bytes per row thusly:
                    *               = y * 40
                    *               = y * 0x28
                    *               = y * 101000
                    *  i.e. 3 shl, add, 2 shl, add
                    *
                    *  @param x - x coordinate, (0,0) top-left 
			        *  @param y - y coordinate, (319,199) bottom-right 
			        *  @param colour - background 0 foreground 1
			        */
                    void plot_point(size_type x, size_type y, colour_t colour) {
                            __asm {
                                .8086

                                mov             ax, CGA_EVEN_VRAM_SEGMENT ; assume even lines segment
                                mov             bx, y                   ; load y into bx then perform screen clipping
                                cmp             bx, SCREEN_Y_MAX        ; compare bx with y maximum boundry
                                jge             END                     ; nothing to plot
                                test            bx, 1h                  ; is the in bounds y even ?
                                jz              EVEN                    ; yes skip
                                mov             ax, CGA_ODD_VRAM_SEGMENT  ; otherwise load odd lines segment
                EVEN:           mov             es, ax                          ; transer segment into es
                                mov             dx, x                           ; load x into dx and clip to torus bounds
                                cmp             dx, SCREEN_X_MAX        ; compare dx with x maximum boundry
                                jge             END                     ; nothing to plot
                                mov             cx, dx                  ; copy of x in cx
                                and             cx, 7h                  ; mask off 0111 lower bits i.e.mod 8 (thanks powers of 2)
                                mov             al, 01111111b           ; load al with pixel mask
                                ror		        al, cl                  ; roll mask around by x mod 8
                                mov             ah, colour              ; load ah with a single pixel at msb (e.g. white 10000000)
                                shr             ah, cl                  ; shift single bit along by x mod 8
                                shr             dx, 1                   ; calculate column byte x / 8
                                shr             dx, 1                   ; 8086 limited to single step shifts
                                shr             dx, 1                   ;
                                and             bx, 0FFFEh              ; mask out even / odd row bit from y
                                shl             bx, 1                   ; 8086 shift left 3 time
                                shl             bx, 1                   ; as per binary simplification of y/2 * 80 above
                                shl             bx, 1                   ;
                                mov             cx, bx                  ; temp result in cx
                                shl             cx, 1                   ; 8086 shift left twice
                                shl             cx, 1                   ;
                                add             bx, cx                  ; add back into bx
                                add             bx, dx                  ; add in column byte
#ifdef NO_SNOW
                                mov             dx, CGA_STATUS_REG      ; load CGA status register
                HSNOW:          in              al, dx                  ; read register
                                test            al, 1                   ; is bit 0 a 1?
                                jne             HSNOW                   ; wait until it is and then enough time to move 2 bytes into VRAM
#endif // NO_SNOW
#ifdef SYNCHRONISED	// will need al so cost an extra mov reg, reg to copy into cl
					            mov		cl, al			; copy mask byte
					            mov     dx, CGA_STATUS_REG  ; CGA status reg
				L0:             in      al, dx          ; read status
					            test    al, 1000b       ; is bit 3 set ? (in a vertical retrace interval)
					            jnz     L0              ; yes, keep waiting
				L1:             in      al, dx          ; read status
					            test    al, 1000b       ; is bit 3 set ? (just started a vertical retrace interval)
					            jnz     L1              ; no, keep waiting

					            and		es:[bx], cl		; mask out the pixel bits
#else
					            and		es:[bx], al		; mask out the pixel bits
#endif					
					            or		es:[bx], ah		; plot point
                END:
                    }
                    }

                }

                namespace torus_bound {

                   /**
                    *  @brief  Perform torus boundry clipping for classical Asteroids behaviour.
                    *
                    * Fast bit manipulation calculate row byte y/2 * 80 bytes per row thusly:
                    *               = y * 40
                    *               = y * 0x28
                    *               = y * 101000
                    *  i.e. 3 shl, add, 2 shl, add
                    *
                    *  @param x - x coordinate, where (0,0) top-left and (639,199) bottom-right
                    *  @param y - y coordinate
                    */
                    void plot_point(size_type x, size_type y, colour_t colour) {
                            __asm {
                                .8086

                                mov             ax, CGA_EVEN_VRAM_SEGMENT ; assume even lines segment
                                mov             bx, y                   ; load y into bx then perform torus clipping for Asteroids
                                cmp             bx, SCREEN_Y_MIN        ; compare bx with y minimum boundry
                                jge             Y1                      ; if within boundry then skip to next boundry test
                                add             bx, SCREEN_Y_MAX        ; otherwise add y max to return bx to torus bounds
                Y1:             cmp             bx, SCREEN_Y_MAX        ; compare bx with y maximum boundry
                                jl              Y2                      ; if within boundry then skip
                                sub             bx, SCREEN_Y_MAX ; otherwise subtract y max to return bx to torus bounds
                Y2:             test            bx, 1h                  ; is the in bounds y even ?
                                jz              EVEN                    ; yes skip
                                mov             ax, CGA_ODD_VRAM_SEGMENT  ; otherwise load odd lines segment
                EVEN:           mov             es, ax                  ; transer segment into es
                                mov             dx, x                   ; load x into dx and clip to torus bounds
                                cmp             dx, SCREEN_X_MIN        ; compare dx with x minimum boundry
                                jge             X1                      ; if within boundry then skip to next boundry test
                                add             dx, SCREEN_X_MAX        ; otherwise add x max to return ax to torus bounds
                X1:             cmp             dx, SCREEN_X_MAX        ; compare ax with x maximum boundry
                                jl              X2                      ; if within boundry then skip
                                sub             dx, SCREEN_X_MAX        ; otherwise subtract x max to return ax to torus bounds
                X2:             mov             cx, dx                  ; copy of x in cx
                                and             cx, 7h                  ; mask off 0111 lower bits i.e.mod 8 (thanks powers of 2)
                                mov             al, 01111111b           ; load al with pixel mask
                                ror		        al, cl                  ; roll mask around by x mod 8
                                mov             ah, colour              ; load dl with a single pixel at msb 10000000
                                shr             ah, cl                  ; shift single bit along by x mod 8
                                shr             dx, 1                   ; calculate column byte x / 8
                                shr             dx, 1                   ; 8086 limited to single step shifts
                                shr             dx, 1                   ;
                                and             bx, 0FFFEh              ; mask out even / odd row bit from y
                                shl             bx, 1                   ; 8086 shift left 3 time
                                shl             bx, 1                   ; as per binary simplification of y/2 * 80 above
                                shl             bx, 1                   ;
                                mov             cx, bx                  ; temp result in cx
                                shl             cx, 1                   ; 8086 shift left twice
                                shl             cx, 1                   ;
                                add             bx, cx                  ; add back into bx
                                add             bx, dx                  ; add in column byte
#ifdef NO_SNOW
                                mov             dx, CGA_STATUS_REG      ; load CGA status register
                HSNOW:          in              al, dx                  ; read register
                                test            al, 1                   ; is bit 0 a 1?
                                jne             HSNOW                   ; wait until it is and then enough time to move 2 bytes into VRAM
#endif // NO_SNOW
#ifdef SYNCHRONISED	// will need al so cost an extra mov reg, reg to copy into cl
					    mov		cl, al			; copy mask byte
					    mov     dx, CGA_STATUS_REG  ; CGA status reg
				    L0: in      al, dx          ; read status
					    test    al, 1000b       ; is bit 3 set ? (in a vertical retrace interval)
					    jnz     L0              ; yes, keep waiting
				    L1: in      al, dx          ; read status
					    test    al, 1000b       ; is bit 3 set ? (just started a vertical retrace interval)
					    jnz     L1              ; no, keep waiting

					    and		es:[bx], cl		; mask out the pixel bits
#else
					    and		es:[bx], al		; mask out the pixel bits
#endif					
					    or		es:[bx], ah		; plot point

                        }
                    }

                }

        }

}

#endif