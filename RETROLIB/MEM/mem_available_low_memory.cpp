/**
 *
 *  @file      mem_available_low_memory.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      22.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_available_low_memory.h"

#include <cassert>

namespace mem {

	uint32_t available_low_memory_bytes() {
        uint16_t paragraphs, err_code = 0;
        uint32_t convert = 16;  // 16 bytes per paragraph
        __asm {
            .8086
            mov     bx, 0FFFFh                      ; deliberate over sized request
            mov     ah, 48h                         ; allocate memory
            int     21h                             ; INT 21h, 48h allocate memory service 
            mov     err_code, ax                    ; CF set, and AX = 08 (Not Enough Mem)
            mov     paragraphs, bx                  ; size in paras of the largest block of memory available
        }
        assert(err_code == 8); 
        return convert * paragraphs;
	}

}