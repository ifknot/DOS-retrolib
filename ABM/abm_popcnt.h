/*****************************************************************//**
 * \file   abm_popcnt.h
 * \brief  
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef POPCNT_H
#define POPCNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm { // 8086 advanced bit manipulation 

    /**
     * \brief Counts the number of 1 bits (population count) in a 64-bit unsigned integer.
     * Wegner algorithm bitset cardinality algorithm optimised for the 8086 using fast paths for all 1s or as soon as all the 1s have been counted.
     * As well as being ompetitive when the population count is relatively low (e.g., less than 4 one bit per 64-bit word) it offers fast path for the Wegner worst case all 1s.
     * Further, it proves not only faster than a naive function checking the values of each bits but also
     * + C implementation of the naive tree-of-adder approach and the 
     * + Wilkes-Wheeler-Gill function in C - due to the overhead of multiplication
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint16_t popcnt64(uint64_t* ptr_value) {
        uint16_t cnt;
        __asm {
            .8086
            sub     bx, bx              ; zero BX bit count
            lds     si, ptr_value       ; DS:SI points to 64bit quad word value
            mov     cx, BITS_PER_WORD   ; set up the loop counter
            cld                         ; clear direction flag to increment DS:SI chain instructions
            
    WORD0:  lodsw                       ; load AX the first word of the qword value
            cmp     ax, 0xFFFF          
            jne     SHIFT0
            mov     bl, 16              ; it's all 1s
            jmp     WORD1               ; fast path the full word
    SHIFT0: shr     ax, 1               ; shift lsb into the carry flag
            jnc     NCF0                ; 0
            inc     bl                  ; 1  increment bit count
    NCF0:   jz      WORD1               ; no more set bits to count fast path to next word
            loop    SHIFT0              ; count the remaining set bits

    WORD1:  lodsw                       ; load AX the next word of the qword value
            cmp     ax, 0xFFFF          
            jne     SHIFT1
            add     bl, 16              ; it's all 1s
            jmp     WORD2               ; fast path the full word
    SHIFT1: shr     ax, 1               ; shift lsb into the carry flag
            jnc     NCF1                ; 0
            inc     bl                  ; 1  increment bit count
    NCF1:   jz      WORD2               ; no more set bits to count fast path to next word
            loop    SHIFT1              ; count the remaining set bits

    WORD2:  lodsw                       ; load AX the next word of the qword value
            cmp     ax, 0xFFFF          
            jne     SHIFT2
            add     bl, 16              ; it's all 1s
            jmp     WORD3               ; fast path the full word
    SHIFT2: shr     ax, 1               ; shift lsb into the carry flag
            jnc     NCF2                ; 0
            inc     bl                  ; 1  increment bit count
    NCF2:   jz      WORD3               ; no more set bits to count fast path to next word
            loop    SHIFT2              ; count the remaining set bits

    WORD3:  lodsw                       ; load AX the next word of the qword value
            cmp     ax, 0xFFFF          
            jne     SHIFT3
            add     bl, 16              ; it's all 1s
            jmp     END                 ; fast path the full word
    SHIFT3: shr     ax, 1               ; shift lsb into the carry flag
            jnc     NCF3                ; 0
            inc     bl                  ; 1  increment bit count
    NCF3:   jz      END                 ; no more set bits to count fast path to next word
            loop    SHIFT3              ; count the remaining set bits

    END:    mov     cnt, bx

        }
        return cnt;
    }

}

#endif
