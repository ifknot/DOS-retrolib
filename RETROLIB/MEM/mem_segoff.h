/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_SEGOFF_H
#define MEM_SEGOFF_H

#include <stdint.h>
#include <iostream>
#include <iomanip>

namespace mem {

    /**
     * Intel 16 bit segment:offset memory type
     */
    struct segoff_t {

        uint16_t offset;
        uint16_t segment;       // reverse order as Intel is little-endian

    };

}

std::ostream& operator<< (std::ostream& os, const mem::segoff_t& memloc);

#endif
