/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_VERTICAL_CAPPED_LINE_H
#define	MDA_MODE7_VERTICAL_CAPPED_LINE_H

#include "mda_mode7_constants.h"

namespace mda {

	namespace mode7 {

		namespace screen_bound {

			void draw_vertical_capped_line(size_type x1, size_type y1, size_type x2, size_type y2, char block = FULL_BLOCK, char topcap = LOWER_HALF_BLOCK, char basecap = UPPER_HALF_BLOCK) {
				__asm {
					.8086
					
					mov		ax, x1
					cmp		ax, x2					; it has to be a vertical line
					jne		END						; nothing to draw

					mov		ax, y2
					cmp		ax, y1					; of at least 1 unit size
					jle		END						; nothing to draw

					mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					; ES:DI will point to x,y screen byte 
					mov		bx, x1					; load x into bx then perform screen clipping
					cmp     bx, SCREEN_X_MAX        ; compare bx with x maximum boundry
					jge     END						; nothing to draw
					mov		ax, y1					; load y into ax then perform screen clipping
					cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
					jge     END                     ; nothing to draw

					mov		cx, y2					; x1,y1 is onscreen x1 = x2 so clip y2
					cmp		cx, SCREEN_Y_MAX		; compare with boundry
					jl		J0						; within screen width
					sub		cx, SCREEN_Y_MAX		; clip to screen
					sub		y2, cx					; store clipped y2
J0:					sub		y2, ax					; y2 - y1 is now line length

#ifdef ENABLE_MUL
					mov     cl, BYTES_PER_LINE
					mul     cl						; calculate y * 80 i.e. AX * 160 bytes
					mov		di, ax
#else		
					shl		ax, 1					; on 8086 this bitwise multiplication is faster than mul 
					shl		ax, 1					; y * 80 = (y * 16) + (y * 64)
					shl		ax, 1					; 8086 limited to single step shifts
					shl		ax, 1					; y * 16
					mov		di, ax					; copy result
					shl		ax, 1
					shl		ax, 1					; y * 64
					add		di, ax					; di = y * 80
#endif				
					shl		bx, 1					; x * 2 as 2 bytes per character cell
					add		di, bx					; di = (y * 80 ) + x

					mov		al, topcap				; load the top cap character
					mov		es:[di], al				; upper endcap
					add		di, BYTES_PER_LINE		; next screen line

					mov		al, block				; load block semigrpahic
					mov		cx, y2					; load y2
					cmp		cx, 1					; just one pixel?
					je		END						; done
					cmp		cx, 2					; just two pixels?
					je		J1						; lower endcap

					sub		cx, 2					; decrement for 2 endcaps
L0:					mov		es:[di], al				; plot semigraphics 'point'
					add		di, BYTES_PER_LINE		; next screen line
					loop	L0

J1:					mov		al, basecap				; load the top cap character
					mov		es:[di], al				; lower endcap					

END:
				}
			}

		}

	}

}

#endif