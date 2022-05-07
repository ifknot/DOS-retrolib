/**
 *
 *  @file               hga_plot_point.h
 *  @brief              Plot a point in Hecules Graphics Mode
 *  @details    HGA Graphics Mode pixel-addressable graphics mode at 720x348 (two rows of pixels are lost since the dimensions must be divisible by four for technical reasons).
 *      VRAM:           64K
 *      Pixel Ratio 1:1.55 on a standard 4:3 display.
 *  Segments:   B000:0000 - B000:7FFF   First Page
 *              B000:8000 - B000:FFFF   Second Page
 *  The HGA has 64K of Video RAM and each display page is 32K, having the capacity to host a 4K text page and a graphics page.
 *  @note The display page is (once enabled) selectable
 *  Layout:     An unusual layout of 4 interleaved scan lines, packed pixel.
 *  The 32K VRAM of each display page is divided into 4 x 8K blocks.
 *              Block 1 divisible by 4 then + 0 (0, 4, 8, 12..)
 *              Block 2 divisible by 4 then + 1 (1, 5, 9, 13..)
 *              Block 3 divisible by 4 then + 2 (2, 6, 10, 14..)
 *              Block 4 divisible by 4 then + 3 (3, 7, 11, 15..)
 *
 *              Each scan line is 90-bytes long and there are 348 scan lines (2 lines unused in each block)
 *      Each byte contains 8 pixels
 *          (31,320 total pixel bytes):
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
 *  @author    Jeremy Thornton
 *  @date      28.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef HGA_PLOT_POINT_H
#define HGA_PLOT_POINT_H

#include "hga_constants.h"

//#define ENABLE_MUL

namespace hga {

        namespace screen_bound {

                /**
                *  @brief plot to default display page 0, clipping to fit within the screen bounds
                *  @param x      - screen x coordinate, (0,0) top-left
                *  @param y      - screen y coordinate, (719,347) bottom right
                *  @param colour - background 0 foreground 1
                */
                void plot_point(size_type x, size_type y, colour_t colour) {
                        __asm {
                            .8086

                            mov     ax, HGA_VIDEO_RAM_SEGMENT
                            mov     es, ax

                            mov     ax, y           ; load y into bx then perform screen clipping
                            mov     dx, ax          ; copy y
                            cmp     ax, SCREEN_Y_MAX ; compare bx with y maximum boundry
                            jge     END             ; nothing to plot
                            

#ifdef ENABLE_MUL           
                            shr     ax, 1       ; calculate y / 4
                            shr     ax, 1       ; 8086 limited to single step shifts
                            mov     cl, BYTES_PER_LINE
                            mul     cl          ; calculate(y / 4) * 90
#else
                            // bit shifting * 90
                            and     ax, 0FFFCh  ; mask out bank selection bits
                            mov     bx, ax      ; copy y                   
                            //shr     ax, 1       ; calculate y / 4
                            //shr     ax, 1       ; 8086 limited to single step shifts
                            
                            // (y / 4) * 80
                            // simplifies to y * 20
                            //shl     ax, 1       ; 8086 shift left 4 times
                            //shl     ax, 1       ; y * 16
                            shl     ax, 1
                            shl     ax, 1
                            mov     cx, ax      ; copy y 
                            shl     ax, 1       ; 8086 shift left 2 times
                            shl     ax, 1       ; 
                            add     ax, cx      ; 
                            // (y / 4) * 10
                            // simplifies to (y / 2) * 4
                            //shr     bx, 1       ; calculate y / 4
                            shr     bx, 1       ; 8086 limited to single step shifts
                            //shl     bx, 1       
                            mov     cx, bx      ; copy y 
                            shl     bx, 1       ; 8086 shift left 2 times
                            shl     bx, 1       ; 
                            add     ax, cx      ; + (y / 2)
                            add     ax, bx      ; + (y * 4)
#endif                      
                            and     dx, 00000011b           ; mask off only the bank select bits (0..4)
                            ror     dx, 1                   ; calculate 16-bit bank# * 2000h
                            ror     dx, 1                   ; 8086 limited to single step shifts
                            ror     dx, 1                   ; (y mod 4) * 2000h

                            mov     di, x                   ; load x into di and clip to screen bounds
                            cmp     di, SCREEN_X_MAX        ; compare di with x maximum boundry
                            jge     END                     ; nothing to plot

                            mov     cx, di                  ; copy of x in cx
                                
                            shr     di, 1                   ; calculate column byte x / 8
                            shr     di, 1                   ; 8086 limited to single step shifts
                            shr     di, 1                   ; x / 8

                            add     di, ax                  ; + (y / 4) * 90
                            add     di, dx                  ; + (y mod 4) * 2000h

                            and     cx, 7h                  ; mask off 0111 lower bits i.e.mod 8 (thanks powers of 2)
                            mov     al, 01111111b           ; load al with pixel mask
                            mov     ah, colour              ; load ah with a single pixel at msb (e.g. white 10000000)
                            ror		al, cl			        ; roll mask around by x mod 8
                            shr     ah, cl                  ; shift single bit along by x mod 8

#ifdef SYNCHRONISED	// will need al so cost an extra mov reg, reg to copy into cl
					        mov		cl, al			; copy mask byte
					        mov     dx, CGA_STATUS_REG  ; CGA status reg
				        L0: in      al, dx          ; read status
					        test    al, 1000b       ; is bit 3 set ? (in a vertical retrace interval)
					        jnz     L0              ; yes, keep waiting
				        L1: in      al, dx          ; read status
					        test    al, 1000b       ; is bit 3 set ? (just started a vertical retrace interval)
					        jnz     L1              ; no, keep waiting

					        and		es:[di], cl		; mask out the pixel bits
#else
					        and		es:[di], al		; mask out the pixel bits
#endif					
					        or		es:[di], ah		; plot point
                               
                END:
                        }
                }

                /**
                *  @brief plot to selected display page, clipping to fit within the screen bounds
                *  @param x      - x coordinate, where (0,0) top-left and (639,199) bottom-right
                *  @param y      -
                *  @param colour - background 0 foreground 1
                *  @param page   - display page 0 or 1
                */
                void plot_point(size_type x, size_type y, colour_t colour, uint8_t page) {
                }

        }

}

#endif