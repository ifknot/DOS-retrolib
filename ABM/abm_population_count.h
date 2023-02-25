/*****************************************************************//**
 * \file   abm_population_count.h
 * \brief  8086 implemention of advanced bit manipulation - population count 
 * \note   In the abscence of dedicated instruction popcnt on x64 processors.
 * The Hamming weight of a string is the number of symbols that are different from the zero-symbol of the alphabet used. 
 * It is thus equivalent to the Hamming distance from the all-zero string of the same length. For the most typical case, 
 * a string of bits, this is the number of 1's in the string, or the digit sum of the binary representation of a given number. 
 * In this binary case, it is also called the population count, popcount, sideways sum, or bit summation.
 * \url    en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef POPULATION_COUNT_H
#define POPULATION_COUNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm {

    /**
     * \brief Uses the Wegner[1] algorithm to count the number of 1 bits (population count aka Hamming Weight) in a 64-bit unsigned integer.
     * Wegner[1] algorithm bitset cardinality algorithm optimised for the 8086 using fast paths for each of the 4 words 
     * such that when all 1s or as soon as all the 1s have been counted.
     * As well as being competitive when the population count is relatively low it offers a fast path for the Wegner worst cases of all 1s.
     * Importantly, the all 1s fast path occurs for each of the 4 words in the quadword and so it is triggered with high frequency at least once.
     * Further, it proves not only faster than a naive function checking the values of each bit (ROR or LSR) but also
     * + C implementation of the naive tree-of-adder approach and the
     * + Wilkes-Wheeler-Gill function in C - due to the overhead of multiplication
     * \note if 64K of system memory can be sacrificed then a Hamming Weight lookup table is faster.
     * [1] Wegner, P. (1960) A technique for counting ones in a binary computer. Commun. ACM, 3, 322–.
     * [2] https://en.wikipedia.org/wiki/Hamming_weight
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint8_t hamming_wegner_64(uint64_t* ptr_value) {
        uint8_t hamming_weight;
        __asm {
            .8086
            sub     bl, bl          ; zero BX bit count
            sub     cx, cx          ; zero CX intermediate result
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS:SI chain instructions
                                    
    WORD0:  lodsw                   ; load AX the first word of the quadword value
            cmp     ax, 0xFFFF      ; is it all 1s ?
            jne     EMPTY0          ; no skip
            mov     bl, BITS_PER_WORD       
            jmp     WORD1           ; fast path the full bitset
    EMPTY0: mov     cx, ax          ; fast path the empty bitset
    LOOP0:  jcxz    WORD1           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP0
                                    
    WORD1:  lodsw                   ; load AX the next word of the quadword value
            cmp     ax, 0xFFFF
            jne     EMPTY1
            add     bl, BITS_PER_WORD
            jmp     WORD2           ; fast path the full bitset
    EMPTY1: mov     cx, ax          ; fast path the empty bitset
    LOOP1:  jcxz    WORD2           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP1

    WORD2:  lodsw                   ; load AX the next word of the quadword value
            cmp     ax, 0xFFFF
            jne     EMPTY2
            add     bl, BITS_PER_WORD
            jmp     WORD3           ; fast path the full bitset
    EMPTY2: mov     cx, ax          ; fast path the empty bitset
    LOOP2:  jcxz    WORD3           ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP2

    WORD3:  lodsw                   ; load AX the next word of the quadword value
            cmp     ax, 0xFFFF
            jne     EMPTY3
            add     bl, BITS_PER_WORD
            jmp     END             ; fast path the full bitset
    EMPTY3: mov     cx, ax          ; fast path the empty bitset
    LOOP3:  jcxz    END             ; while not 0
            mov     ax, cx          ; Wegner algorithm
            dec     ax              ; subtract 1
            and     cx, ax          ; mask off
            inc     bl              ; count bit
            jmp     LOOP3

    END:    mov     hamming_weight, bl

        }
        return hamming_weight;
    }

    /**
     * \brief Uses a 256 byte lookup table to count the number of 1 bits (population count aka Hamming Weight) in a 64-bit unsigned integer.
     * Alternative to sacrificing 64K for 16 bit lookup table instead uses 256 byte table for byte address 256 byte lookup
     * \url https://en.wikipedia.org/wiki/Hamming_weight
     * \param ptr_value - the 64-bit unsigned integer for which we want the population count.
     * \return - the number of 1 bits in the quad word of memory pointed to.
     */
    uint8_t hamming_lookup_64(uint64_t* ptr_value) {
        static char table[256] = {
            0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
            1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
            1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
            2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
            1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
            2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
            2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
            3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8
        };
        uint8_t hamming_weight;
        __asm {
            .8086
            lea     bx, table       ; setup lookup table DS:[BX]
            mov     cx, WORDS_PER_QWORD
            sub     dl, dl          ; zero the set bit count in DL
            lds     si, ptr_value   ; DS:SI points to 64bit quad word value
            cld                     ; clear direction flag to increment DS:SI chain instructions
      
    WLOOP:  lodsw                   ; load AX next word of the quadword value
            xlatb                   ; lookup the lo byte number of bits 
            add     dl, al          ; update set bit count
            xchg    al, ah          ; swap hi byte into AL 
            xlatb                   ; lookup the hi byte number of bits 
            add     dl, al          ; update set bit count
            loop    WLOOP

            mov     hamming_weight, dl
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
    uint8_t hamming_wilkes_wheeler_gill(uint64_t x) {
        x -= (x >> 1) & c1;
        x = ((x >> 2) & c2) + (x & c2);
        x = (x + (x >> 4)) & c4;
        x *= 0x0101010101010101;
        return x >> 56;
    }

}

#endif