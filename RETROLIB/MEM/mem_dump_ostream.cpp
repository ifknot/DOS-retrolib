/**
 *
 *  @file      mem_dump_ostream.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */

#include <iostream>
#include <stdint.h>

#include "mem_dump_ostream.h"
#include "mem_constants.h"
#include "mem_types.h"


namespace mem {

	address_t dump_ostream(std::ostream& os, const address_t start, const uint16_t bytes) {
		address_t next = start;
		uint16_t paras = (bytes % PARAGRAPH_SIZE) ? (bytes >> 4) + 1 : bytes >> 4; // convert size to paragraphs
		for (int i = 0; i < paras; ++i) {
			next = dump_paragraph_ostream(os, next);
		}
		return next;
	}

	address_t dump_paragraph_ostream(std::ostream& os, const address_t start) {
		os << std::hex << start.segoff << "  ";				// memory address as segment:offset
		char* p = (char*) start.void_ptr;						// extract char* from address_t
		int i;												// going to resuse i
		for (i = 0; i < (PARAGRAPH_SIZE / 2) - 1; ++i) {	// first 7 bytes as hex
			os << std::setw(2) << std::hex << (int)*p++ << " ";
		}
		os << std::setw(2) << std::hex << (int)*p++ << "-"; // 8th byte as hex w dash spacer as per DOS DEBUG
		for (; i < PARAGRAPH_SIZE; ++i) {					// last 8 bytes of the paragraph of memory
			os << std::setw(2) << std::hex << (int)*p++ << " ";
		}
		os << "  ";
		char* c = p - PARAGRAPH_SIZE;						// reset char*
		while(c < p) {										// 16 bytes as hex replace with '.' if not standard alphabet
			if (*c >= ' ' & *c <= '~') {
				std::cout << *c;
			}
			else {
				std::cout << '.';
			}
			++c;
		}
		address_t next;
		next.void_ptr = (void*)p;
		return next;
	}

}
