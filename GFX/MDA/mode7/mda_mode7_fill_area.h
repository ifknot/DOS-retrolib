/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_FILL_AREA_H
#define MDA_MODE7_FILL_AREA_H

#include "mda_mode7_constants.h"

namespace mda {

	namespace mode7 {

		namespace screen_bound {

			void fill_area(size_type x, size_type y, size_type w, size_type h, colour_t colour) {
				__asm {
					.8086
					
					mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					; ES:DI will point to x,y screen byte 
					mov		bx, x					; load x into bx then perform screen clipping
					cmp     bx, SCREEN_X_MAX        ; compare bx with x maximum boundry
					jge     END						; nothing to fill
					mov		ax, y					; load y into ax then perform screen clipping
					cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
					jge     END                     ; nothing to fill

					mov		cx, w					; x,y is onscreen so load width 
					add		cx, x					; add x 
					cmp		cx, SCREEN_X_MAX		; compare with boundry
					jl		J0						; within screen width
					sub		cx, SCREEN_X_MAX		; clip to screen
					sub		w, cx					; clip width

J0:					mov		cx, h					; load height
					add		cx, y					; add y	
					cmp		cx, SCREEN_Y_MAX		; compare with boundry
					jl		J1						; within screen height
					sub		cx, SCREEN_Y_MAX		; clip to screen
					sub		h, cx					; clip height
J1:

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
					mov		al, colour
		
					cld								; clear direction flag (increment)
					mov		bx, w					; BX is register copy of width
					mov		dx, BYTES_PER_LINE		; DX calculate 160 - (width * 2) 
					sub		dx, bx					; to use as the additive to DI to point to
					sub		dx, bx					; the next line 

					mov		cx, h					; load the height
L0:					mov 	si, cx					; store the height counter
					mov		cx, bx					; load (clipped) width into counter		

L1:					stosb							; store attrib
					inc		di						; skip attribute byte
					loop	L1						; whole row						; store attrib:ascii row
					
					add		di, dx					; next line
					mov		cx, si					; recover the height counter
					loop	L0

END:
				}
			}

			void fill_area_attribute(size_type x, size_type y, size_type w, size_type h, attribute_t attrib) {
				__asm {
					.8086
					
					mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					; ES:DI will point to x,y screen byte 
					mov		bx, x					; load x into bx then perform screen clipping
					cmp     bx, SCREEN_X_MAX        ; compare bx with x maximum boundry
					jge     END						; nothing to fill
					mov		ax, y					; load y into ax then perform screen clipping
					cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
					jge     END                     ; nothing to fill

					mov		cx, w					; x,y is onscreen so load width 
					add		cx, x					; add x 
					cmp		cx, SCREEN_X_MAX		; compare with boundry
					jl		J0						; within screen width
					sub		cx, SCREEN_X_MAX		; clip to screen
					sub		w, cx					; clip width

J0:					mov		cx, h					; load height
					add		cx, y					; add y	
					cmp		cx, SCREEN_Y_MAX		; compare with boundry
					jl		J1						; within screen height
					sub		cx, SCREEN_Y_MAX		; clip to screen
					sub		h, cx					; clip height
J1:

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
					
					mov		al, attrib				; AX now has atrrib:ascii

					cld								; clear direction flag (increment)
					mov		bx, w					; BX is register copy of width
					mov		dx, BYTES_PER_LINE		; DX calculate 160 - (width * 2) 
					sub		dx, bx					; to use as the additive to DI to point to
					sub		dx, bx					; the next line 

					mov		cx, h					; load the height
L0:					mov 	si, cx					; store the height counter
					mov		cx, bx					; load (clipped) width into counter	

L1:					inc		di						; point to attribute byte
					stosb							; store attrib
					loop	L1						; whole row

					add		di, dx					; next line
					mov		cx, si					; recover the height counter
					loop	L0

END:
				}
			}

		}

	}

}

#endif