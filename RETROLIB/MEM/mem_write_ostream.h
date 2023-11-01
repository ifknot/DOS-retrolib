/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_SAVE_OSTREAM_H
#define	MEM_SAVE_OSTREAM_H

#include <iostream>
#include <stdint.h>

#include "mem_types.h"

#include "../DOS/dos_services_files_types.h"

namespace mem {

	/**
	* @brief write contents of memory to output stream
	* @note the ostream will interpret control characters
	*
	* @return size_t - the actual number of bytes written
	*/
	// TODO
	//dos::file::size_t write_ostream(std::ostream& os, const address_t start, const uint32_t bytes);

	/**
	* @brief write *upto* a page (64K bytes or 4096 paragraphs) of memory to ostream
	* @note the ostream will interpret control characters
	* 
	* @return size_t - the actual number of bytes written
	*/
	dos::file::size_t write_page_ostream(std::ostream& os, const address_t start, const uint16_t bytes);

}

#endif