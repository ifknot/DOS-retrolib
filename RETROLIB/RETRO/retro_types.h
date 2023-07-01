/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.06.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef RETRO_TYPES_H
#define RETRO_TYPES_H

#include <stdint.h>
#include <iostream>
#include <iomanip>

namespace retro {

	typedef int8_t byte_t; // char

	union word_t {

		int16_t word;
		byte_t bytes[2];

	};

	union dword_t {

		int32_t dword;
		int16_t words[2];				

	};

	/**
	* Intel 16 bit segment:offset memory type
	*/
	struct segoff_t {

		uint16_t offset, segment;	// reverse order as Intel is little-endian

	};

	/**
	* Intel 32 bit address breakdown
	*/
	union address_t {

		void* ptr;
		segoff_t memloc;
		uint16_t words[2];
		uint8_t bytes[4];

	};

}

// ---- stream operators ----

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

#endif 