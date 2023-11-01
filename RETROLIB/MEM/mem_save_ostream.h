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
	* @brief save (unformatted) contents of memory to output stream
	*
	* @return size_t - the actual number of bytes saved
	*/
	//dos::file::size_t save_ostream(char* path_name, , const address_t start, const uint32_t bytes);

	/**
	* @brief saves (unformatted) *upto* a page (64K bytes or 4096 paragraphs) of memory to ostream
	*/
	dos::file::size_t save_page_ostream(std::ostream& os, const address_t start, const uint16_t bytes);

}

#endif