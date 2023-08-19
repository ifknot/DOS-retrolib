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

#endif 