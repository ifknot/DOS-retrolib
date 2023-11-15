/**
 *
 *  @file      mem_address.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_address.h"

namespace mem {

}

std::ostream& operator<< (std::ostream& os, const mem::address_t& addr) {
    os << std::hex << std::setfill('0')
        << std::setw(8) << (uint32_t)addr.memloc
        << std::dec;
    return os;
}