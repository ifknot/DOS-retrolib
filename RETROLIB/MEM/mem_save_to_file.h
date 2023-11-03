/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_SAVE_TO_FILE_H
#define MEM_SAVE_TO_FILE_H

#include <stdint.h>

#include "mem_types.h"

#include "../DOS/dos_services_files_types.h"

namespace mem {

	/**
	* @brief use DOS to save contents of memory to file 
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	// TODO
	//dos::file::size_t save_large_to_file(const char* path_name, address_t start, uint32_t bytes);

	//dos::file::size_t save_page_to_file(const char* path_name, address_t start);

	/**
	* @brief saves unformatted *upto* a page (64K bytes or 4096 paragraphs) of memory to file
	* @note saves raw bytes
	*
	* @return file::size_t - the actual byte count saved
	*/
	dos::file::size_t save_to_file(const char * path_name, address_t start, uint16_t nbytes);

}

#endif