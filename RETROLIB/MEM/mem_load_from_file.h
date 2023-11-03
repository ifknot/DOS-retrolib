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
	* @brief use DOS to load contents of a file to memory
	* @note loads raw bytes
	*
	* @return file::size_t - the actual byte count loaded
	*/
	// TODO
	//dos::file::size_t load_large_from_file(const char* path_name, address_t start, uint32_t bytes);

	//dos::file::size_t load_page_from_file(const char* path_name, address_t start);

	/**
	* @brief loads unformatted *upto* a page (64K bytes or 4096 paragraphs) of from file to memory
	* @note loads raw bytes
	*
	* @return file::size_t - the actual byte count loaded
	*/
	dos::file::size_t load_from_file(const char* path_name, address_t start, uint16_t nbytes);
}

#endif