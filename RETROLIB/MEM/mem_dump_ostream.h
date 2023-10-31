/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_DUMP_OSTREAM_H
#define MEM_DUMP_OSTREAM_H

#include <iostream>
#include <stdint.h>

#include "mem_types.h"

namespace mem {

	/**
	* @brief convenience function dump memory to std::cout
	*/
	inline address_t dump(const address_t start, const uint32_t bytes = 256) {
		return dump_ostream(std::cout, start, bytes);
	}

	/**
	* @brief dump contents of memory to output stream - defaults to 256 bytes 
	* @note mimics the DOS DEBUG program layout
	* 
	* @return address_t - the end address of the paragraph 
	* 
	* @todo use a 32 bit byte count
	*/
	address_t dump_ostream(std::ostream& os, const address_t start, const uint16_t bytes = 256); 

	/**
	* @brief dumps a page (64K) of memory to file
	*/
	address_t dump_page_ostream(std::ostream& os, const address_t start, const uint16_t bytes = 256);

	/**
	* @brief dumps a paragraph (16 bytes) of memory to file
	*/
	address_t dump_paragraph_ostream(std::ostream& os, const address_t start);

}

#endif