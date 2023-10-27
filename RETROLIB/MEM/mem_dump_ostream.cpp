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

#include "mem_dump_ostream.h"
#include "mem_constants.h"
#include "mem_types.h"


namespace mem {

	void dump_ostream(std::ostream& os, const address_t start, const address_t end) {

	}

	void dump_line_ostream(std::ostream& os, const address_t start) {
		os << std::hex << start.memloc << "  ";
		char* p = (char*) start.ptr;
		for (int i = 0; i < PARAGRAPH_SIZE; ++i) {
			os << std::hex << (int)*p++ << " ";
		}
		os << std::dec << std::endl;
	}

}
