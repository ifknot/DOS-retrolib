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
	* @brief dump contents of memory to screen - defaults to 256 bytes 
	* @note mimics the DOS DEBUG program layout
	* 
	* @return address_t - the end address of the paragraph 
	*/
	address_t dump_ostream(std::ostream& os, const address_t start, const uint16_t bytes = 256);

	/**
	* @brief dumps a paragraph (16 bytes) of memory to the ostream as hex, ascii combo
	* @note mimics the DOS DEBUG program layout
	* 
	* @return address_t - the end address of the paragraph 
	*/
	address_t dump_paragraph_ostream(std::ostream& os, const address_t start);

}

#endif