#ifndef POPCNT_H
#define POPCNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm { // 8086 advanced bit manipulation 

    /**
     * Counts the number of 1 bits (population count) in a 64-bit unsigned integer.
     * 
     * @param   ptr_value - the 64-bit unsigned integer for which we want the population count.
     * @return  the number of 1 bits in the quad word of memory pointed to.
     */
    uint8_t popcnt64(uint64_t* ptr_value) {
        uint8_t cnt;
        __asm {
            .8086
            sub     bx, bx              ; zero BX bit count
            lds     si, ptr_value       ; DS:SI points to 64bit quad word value
            mov     cx, BITS_PER_WORD   ; set up the loop counter
            cld                         ; clear direction flag to increment DS:SI chain instructions
            
    WORD0:  lodsw                       ; load AX the first word of the qword value
            cmp     ax, 0xFFFF          
            jne     SHIFT0
            mov     bx, 16              ; it's all 1s
            jmp     WORD1               ; fast path the full word
    SHIFT0: shr     ax, 1               ; shift lsb into the carry flag
            jnc     NCF0                ; 0
            inc     bx                  ; 1 - increment bit count
    NCF0:   jz      WORD1               ; no more set bits to count fast path to next word
            loop    SHIFT0              ; count the remaining set bits

    END:    mov     cnt, bx

        }
        return cnt;
    }

}

#endif
