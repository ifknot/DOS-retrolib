/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_LOAD_FROM_FILE_H
#define MEM_LOAD_FROM_FILE_H

#include <stdint.h>

#include "mem_types.h"

#include "../DOS/dos_services_files_types.h"

namespace mem {

	/**
	* @brief use DOS (3.x+) to load raw contents of file to memory 
	*
	* @return file::size_t - the actual byte count loaded 
	*/
	// TODO
	//dos::file::size_t load_large_from_file(char* path_name, const address_t start, const uint32_t bytes);

	//dos::file::size_t load_page_from_file(char* path_name, const address_t start);

	/**
	* @brief loads *upto* a page (64K bytes or 4096 paragraphs) from file to memory
	*
	* @return file::size_t - the actual byte count loaded
	*/
	//dos::file::size_t save_to_file(char* path_name, const address_t start, const uint16_t nbytes) const;

}

#endif