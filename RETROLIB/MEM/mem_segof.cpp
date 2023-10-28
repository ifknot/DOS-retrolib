/**
 *
 *  @file      mem_segof.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_segoff.h"

namespace mem {

}

std::ostream& operator<< (std::ostream& os, const mem::segoff_t& memloc) {
    os << std::hex << std::setfill('0')
        << std::setw(4) << memloc.segment << ':' << std::setw(4) << memloc.offset
        << std::dec;
    return os;
}