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
     * \brief Uses the Wegner[1] algorithm to count the number of 1 bits (population count aka Hamming Weight) in a 64-bit unsigned integer.
     * Wegner[1] algorithm bitset cardinality algorithm optimised for the 8086 using fast paths for all 1s or as soon as all the 1s have been counted.
     * As well as being competitive when the population count is relatively low it offers a fast path for the Wegner worst case of all 1s.
     * Further, it proves not only faster than a naive function checking the values of each bit (ROR or LSR) but also
     * + C implementation of the naive tree-of-adder approach and the
     * + Wilkes-Wheeler-Gill function in C - due to the overhead of multiplication
     * \note if 64K of system memory can be sacrificed then a Hamming Weight lookup table is faster.
     * [1] Wegner, P. (1960) A technique for counting ones in a binary computer. Commun. ACM, 3, 322–.
     * [2] https://en.wikipedia.org/wiki/Hamming_weight
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint16_t hamming_wegner_64(uint64_t* ptr_value) {
        uint16_t hamming_weight;
        __asm {
            //.8086
            sub     bx, bx          ; zero BX bit count
            sub     cx, cx
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS : SI chain instructions

    WORD0:  lodsb                   ; load AX the first word of the qword value
            //cmp     ax, 0xFFFF
            //jne     EMPTY
            //mov     bl, 16          ; it's all 1s
            //jmp     WORD1           ; fast path the full bitset
    EMPTY:  mov     cl, al          ; fast path the empty bitset
    LOOP0:  jcxz    WORD1           ; while not 0
            mov     al, cl          ; Wegner algorithm
            dec     al              ; subtract 1
            and     cl, al          ; mask off
            inc     bl              ; count bit
            jmp     LOOP0

    WORD1:

    END:    mov     hamming_weight, bx

        }
        return hamming_weight;
    }

    /**
     * \brief Uses a 64K lookup table to count the number of 1 bits (population count aka Hamming Weight) in a 64-bit unsigned integer.
     * \url https://en.wikipedia.org/wiki/Hamming_weight
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint16_t hamming_lookup_64(uint64_t* ptr_value) {
        uint16_t hamming_weight;
        __asm {
            //.8086
        }
        return hamming_weight;
    }

}

#endif