/**
 *
 *  @file      fxp_mul_div.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#include "fxp_mul_div.h"
#include "fxp_constants.h"
#include "fxp_types.h"

#include <math.h>
#include <assert.h>

namespace fxp {

	void umul(ufixed_t* x, ufixed_t y) {
		__asm {
			.8086 

			lds		si, x							; DS:[SI] points to x
			mov		ax, [si]						; AX = x
			mov		bx, y							; BX = y
			mul		bx								; DX:AX = AX * BX
			mov		cx, FXP_FRACTIONAL_BITS 
	_SHRD:	shr		dx, 1							; shift right DX:AX as 32 bits
			rcr		ax, 1	
			loop	_SHRD							; emulate the SHRD instruction 
			mov		[si], ax
			
		}
	}

	void mul(fixed_t* x, fixed_t y) {
		__asm {
			.8086 

			lds		si, x							; DS:[SI] points to x
			mov		ax, [si]						; AX = x
			mov		bx, y							; BX = y
			imul		bx							; DX:AX = AX * BX sign 
			mov		cx, FXP_FRACTIONAL_BITS 
	_SHRD:	sar		dx, 1							; shift right DX:AX as 32 bits
			rcr		ax, 1							; ...
			loop	_SHRD							; emulate the SHRD instruction 
			mov		[si], ax
			
		}
	}

	void udiv(ufixed_t* x, ufixed_t y) {
		__asm {
			.8086 

			lds		si, x							; DS:[SI] points to x
			mov		ax, [si]						; AX = x
			mov		bx, y							; BX = y
			xor		dx, dX							; DX = 0
			mov		cx, FXP_FRACTIONAL_BITS 
	_SHLD:	shl		ax, 1							; shift left DX:AX as 32 bits
			rcl		dx, 1							; ...			
			loop	_SHLD							; emulate the SHLD instruction 
			div		bx
			mov		[si], ax
			
		}
	}

	void div(fixed_t* x, fixed_t y) {
		__asm {
			.8086 

			lds		si, x							; DS:[SI] points to x
			mov		ax, [si]						; AX = x
			mov		bx, y							; BX = y
			xor		dx, dX							; DX = 0
			mov		cx, FXP_FRACTIONAL_BITS 
	_SHLD:	shl		ax, 1							; shift left DX:AX as 32 bits
			rcl		dx, 1							; ...			
			loop	_SHLD							; emulate the SHLD instruction 
			idiv	bx
			mov		[si], ax
			
		}
	}

}