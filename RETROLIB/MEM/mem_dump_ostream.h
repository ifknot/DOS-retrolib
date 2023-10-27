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

	void dump_ostream(std::ostream& os, const address_t start, const address_t end);

	/**
	* @brief dumps a paragraph (16 bytes) of memory to the ostream
	*/
	void dump_line_ostream(std::ostream& os, const address_t start);

}

#endif