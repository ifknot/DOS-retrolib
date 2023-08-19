/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_TYPES_STREAM_OPERATORS_H
#define MEM_TYPES_STREAM_OPERATORS_H

#include <iostream>

#include "mem_types.h"

std::ostream& operator<< (std::ostream& os, const retro::segoff_t& memloc);

std::ostream& operator<< (std::ostream& os, const retro::address_t& addr);

#endif