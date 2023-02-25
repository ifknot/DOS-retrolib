/*****************************************************************//**
 * \file   abm_trailing_zeros_count.h
 * \brief  8086 implemention of advanced bit manipulation - trailing zeros count
 * \note   In the abscence of dedicated instruction bs ron 368 and above processors.
 * Counting zeros starting at the LSB until a 1-bit is encountered
 * \url	   en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef TRAILING_ZEROS_COUNT_H
#define TRAILING_ZEROS_COUNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm {

	uint8_t tzcnt_lookup_64(uint64_t* ptr_value) {
		static char tztable[256] = {
			8,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			7,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			6,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,
			5,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0,4,0,1,0,2,0,1,0,3,0,1,0,2,0,1,0
		};
		uint8_t zeros;
		__asm {
			lea     bx, tztable     ; setup lookup table DS:[BX]
            mov     cx, WORDS_PER_QWORD
            sub     dl, dl          ; zero the count in DL
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS:SI chain instructions
	WLOOP:  lodsw                   ; load AX next word of the quadword value
            xlatb                   ; lookup the lo byte number of bits 
			cmp		al, 8			; found lsbit?
			jne		LSB				; yes
            add     dl, 8			; update zero bit count	
            xchg    al, ah          ; swap hi byte into AL 
            xlatb                   ; lookup the hi byte number of bits 
			cmp		al, 8			; found lsbit ?
			jne		LSB				; yes
            add     dl, 8			; update set bit count
			loop    WLOOP
			jmp		END				; 64bits zero

	LSB:    add		dl, al
	END:	mov     zeros, dl
		}
		return zeros;
	}

	uint8_t trailing_zeroes(uint64_t n) {
		uint8_t zeros = 0;
		if (n == 0) return 64;
		while (n >= 0 && !(n & 01)) {
			++zeros;
			if (n != 0) n >>= 1;
			else break;
		}
		return zeros;
	}

}

#endif