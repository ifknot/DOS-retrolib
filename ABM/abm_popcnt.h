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
            .8086
            sub     bx, bx          ; zero BX bit count
            sub     cx, cx
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS : SI chain instructions

    WORD0:  lodsw                   ; load AX the first word of the qword value
            cmp     ax, 0xFFFF
            jne     EMPTY0
            mov     bl, 16          ; it's all 1s
            jmp     WORD1           ; fast path the full bitset
    EMPTY0: mov     cx, ax          ; fast path the empty bitset
    LOOP0:  jcxz    WORD1           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP0

    WORD1:  lodsw                   ; load AX the next word of the qword value
            cmp     ax, 0xFFFF
            jne     EMPTY1
            add     bl, 16          ; it's all 1s
            jmp     WORD2           ; fast path the full bitset
    EMPTY1: mov     cx, ax          ; fast path the empty bitset
    LOOP1:  jcxz    WORD2           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP1

    WORD2:  lodsw                   ; load AX the next word of the qword value
            cmp     ax, 0xFFFF
            jne     EMPTY2
            add     bl, 16          ; it's all 1s
            jmp     WORD3           ; fast path the full bitset
    EMPTY2: mov     cx, ax          ; fast path the empty bitset
    LOOP2:  jcxz    WORD3           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP2

    WORD3:  lodsw                   ; load AX the next word of the qword value
            cmp     ax, 0xFFFF
            jne     EMPTY3
            add     bl, 16          ; it's all 1s
            jmp     END             ; fast path the full bitset
    EMPTY3: mov     cx, ax          ; fast path the empty bitset
    LOOP3:  jcxz    END             ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP3

    END:    mov     hamming_weight, bx

        }
        return hamming_weight;
    }

    /**
     * \brief Uses a 256 byte lookup table to count the number of 1 bits (population count aka Hamming Weight) in a 64-bit unsigned integer.
     * Alternative to sacrificing 64K for 16 bit lookup table instead use 256 byte table for byte by byte lookup
     * \url https://en.wikipedia.org/wiki/Hamming_weight
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint16_t hamming_lookup_64(uint64_t* ptr_value) {
        static char table[2] = { 10,1 };
        uint16_t hamming_weight;
        __asm {
            .8086
            lea     bx, table;
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS : SI chain instructions
                
            lodsw                   ; load AX the first word of the qword value
            xlatb                   ; lookup the number of bits 

            mov     hamming_weight, ax
        }
        return hamming_weight;
    }

    uint64_t c1 = 0x5555555555555555;
    uint64_t c2 = 0x3333333333333333;
    uint64_t c4 = 0x0F0F0F0F0F0F0F0F;

    /**
     * A fast and widely used tree-of-adder function to compute the population count.
     * Attributed by Knuth [1] to a 1957 textbook by Wilkes, Wheeler and Gill [2].
     * [1] Knuth, D. E. (2009) Bitwise Tricks & Techniques, The Art of Computer Programming.
     * [2] Wilkes, M. V., Wheeler, D. J., and Gill, S. (1957) The Preparation of Programs for an Electronic Digital Computer, second edition.
     * \param x
     * \return 
     */
    uint16_t hamming_wilkes_wheeler_gill(uint64_t x) {
        x -= (x >> 1) & c1;
        x = ((x >> 2) & c2) + (x & c2);
        x = (x + (x >> 4)) & c4;
        x *= 0x0101010101010101;
        return x >> 56;
    }

}

#endif