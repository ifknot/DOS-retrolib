/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.06.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_TYPES_H
#define MEM_TYPES_H

#include <stdint.h>

#include "mem_segoff.h"
#include "mem_address.h"

namespace mem {

        typedef int8_t byte_t; // char

        union word_t {

                int16_t word;
                byte_t bytes[2];

        };

        union dword_t {

                int32_t dword;
                int16_t words[2];

        }; 

}

#endif