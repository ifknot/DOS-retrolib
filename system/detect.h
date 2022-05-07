/**
 *
 *  @file      detect.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef DETECT_H
#define DETECT_H

#include <stdint.h>

namespace system {

	bool detect_8087() {
        uint16_t status = 0xFF;
        __asm {
            .8086
            .8087
            push	cx

            fninit				; no wait initialise the NPX(if there is one)
            mov		cx, 64h		; idle in an empty loop whilst fninit loads the status word
    L1:		loop	L1
            fnstsw	status		; save the status word which will reset the lower byte to 0
            mov		cx, 64h		; idle in an empty loop whilst fnstsw stores the status word
	L2:		loop	L2

            pop		cx
        }
        return status == 0;
	}

    bool detect_crtc() {
		uint8_t found = 1;
		__asm {
			.8086
			push	ax
			push	cx
			push	dx

			mov		dx, 3DAh
			mov     al, 0Fh
			out     dx, al		; select 6845 reg 0Fh(Cursor Low)
			inc     dx
			in      al, dx		; AL: = current Cursor Low value
			mov     ah, al		; preserve in AH
			mov     al, 66h		; AL: = arbitrary value
			out     dx, al		; try to write to 6845
			mov     cx, 100h
	WAIT:	loop    WAIT		; wait for 6845 to respond
			in      al, dx
			xchg    ah, al
			out     dx, al		; restore original value
			cmp     ah, 66h		; test whether 6845 responded
			je      YES			; jump if it did(cf is reset)
			mov 	found, 0	; clear the found flag

	YES:	pop		dx
			pop		cx
			pop		ax

		}
		return (bool)found;
    }


}

#endif