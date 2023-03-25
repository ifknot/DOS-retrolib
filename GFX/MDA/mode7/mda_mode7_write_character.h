/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.08.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_WRITE_CHARACTER_H 
#define MDA_MODE7_WRITE_CHARACTER_H

#include "mda_mode7_constants.h"

namespace mda {

	namespace mode7 {

		namespace screen_bound {

			void write_character(size_type x, size_type y, char ascii) {
				_asm {
					.8086

					mov		ax, MDA_VIDEO_RAM_SEGMENT
					mov		es, ax					; ES:DI will point to x,y screen byte 
					mov		bx, x					; load x into bx then perform screen clipping
					cmp     bx, SCREEN_X_MAX        ; compare bx with x maximum boundry
					jge     END						; nothing to plot
					mov		ax, y					; load y into ax then perform screen clipping
					cmp     ax, SCREEN_Y_MAX        ; compare ax with y maximum boundry
					jge     END                     ; nothing to plot
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
					mov		al, ascii
					mov		es:[di], al
					
END:
				}
			}

		}

		namespace torus_bound {

		}

	}

}

#endif