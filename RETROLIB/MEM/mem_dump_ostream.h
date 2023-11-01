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

#include "../DOS/dos_services_files_types.h"

namespace mem {

	/**
	* @brief convenience function dump memory to std::cout
	*/
	address_t dump(address_t start, uint32_t nbytes);

	/**
	* @brief dump formatted contents of memory to output stream 
	* @note mimics the DOS DEBUG format of output
	* 
	* @return address_t - the end address of the dumped memory
	*/
	// TODO:
	//address_t dump_large_ostream(std::ostream& os, const address_t start, const uint32_t nbytes); 

	/**
	* @brief dump full 64K page of memory to ostream
	*/
	//address_t dump_page_ostream(std::ostream& os, const address_t start)

	/**
	* @brief debug formatted dumps *upto* a page (64K) of memory to ostream
	*/
	address_t dump_ostream(std::ostream& os, address_t start, uint16_t nbytes);

	/**
	* @brief debug fromatted dumps a paragraph (16 bytes) of memory to ostream
	*/
	address_t dump_paragraph_ostream(std::ostream& os, address_t start);

}

#endif