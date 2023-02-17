namespace abm16 { // 8086 advanced bit manipulation 
    uint16_t popcnt(int64_t bitboard) {
      uint16_t cnt;
        __asm {
             .8086
            sub     ax, ax
            mov     bx, bitboard
            mov     cx, 16

            cmp     bx, 0xFFFF
            jne     SHIFT
            mov     ax, 16
            jmp     END
    SHIFT:  shr     bx, 1
            jnc     CF0
            inc     ax
    CF0:    jz      END
            loop    SHIFT

    END:    mov     cnt, ax
          }
        return cnt
    }
}
