/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_ADDRESS_H
#define MEM_ADDRESS_H

#include <stdint.h>

#include "mem_segoff.h"

namespace mem {

    /**
     * Intel 32 bit address breakdown as a union
     */
    union address_t {

        uint32_t memloc;
        segoff_t segoff;
        uint16_t words[2];
        uint8_t bytes[4];
        void* ptr;

    };

}

std::ostream& operator<< (std::ostream& os, const mem::address_t& addr);

#endif