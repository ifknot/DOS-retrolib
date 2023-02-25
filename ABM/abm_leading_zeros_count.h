/*****************************************************************//**
 * \file   abm_leading_zeros_count.h
 * \brief  8086 implemention of advanced bit manipulation - leading zeros count
 * \note   In the abscence of dedicated instruction bsf on 368 and above processors.
 * In computer software and hardware, find first set (ffs) or find first one is a bit operation that, given an unsigned machine word,
 * designates the index or position of the least significant bit set to one in the word counting from the least significant bit position.
 * \url	   en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef LEADING_ZEROS_COUNT_H
#define LEADING_ZEROS_COUNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm {

	uint8_t lzcnt_lookup_64(uint64_t* ptr_value) {
		static char lztable[256] = {
			8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
			2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
		};
		uint8_t zeros;
		__asm {
			pushf					; preserve flags
			lea     bx, lztable     ; setup lookup table DS:[BX]
            mov     cx, WORDS_PER_QWORD
            sub     dl, dl          ; zero the count in DL
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
			add		si, 6			; start at the hi word
            std                     ; set direction flag to decrement DS:SI chain instructions
			
	WLOOP:  lodsw                   ; load AX next word of the quadword value
            xchg	al, ah			; start with hi byte (x86 is little-endian)
			xlatb                   ; lookup the hi byte number of bits 
			cmp		al, 8			; found msbit?
			jne		MSB				; yes
            add     dl, 8			; update zero bit count	
            xchg    al, ah          ; swap lo byte into AL 
            xlatb                   ; lookup the lo byte number of bits 
			cmp		al, 8			; found msbit ?
			jne		MSB				; yes
            add     dl, 8			; update set bit count
			loop    WLOOP
			jmp		END				; 64bits zero

	MSB:    add		dl, al
	END:	mov     zeros, dl
			popf					; restore flags
		}
		return zeros;
	}

	uint16_t leading_zeros(uint64_t n) {
		uint64_t msb = 0x8000000000000000;
		uint16_t zeros = 0;
		for (uint16_t i = 0; i < 64; ++i) {
			if ((n << i) & msb) break; // leading set bit found	
			++zeros;
		}
		return zeros;
	}

}

#endif