/**
 *
 *  @file      mem_types_stream_operators.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      19.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_types_stream_operators.h"

#include <iomanip>

std::ostream& operator<< (std::ostream& os, const retro::segoff_t& memloc) {
	os << std::hex << std::setfill('0')
		<< std::setw(4) << memloc.segment << ':' << std::setw(4) << memloc.offset
		<< std::dec;
	return os;
}

std::ostream& operator<< (std::ostream& os, const retro::address_t& addr) {
	os << std::hex << std::setfill('0')
		<< std::setw(8) << (uint32_t)addr.ptr
		<< std::dec;
	return os;
}
