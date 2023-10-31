/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_DUMP_FILE_H
#define MEM_DUMP_FILE_H

#include "../DOS/dos_services_files.h"

namespace mem {

	/**
	* @brief dump contents of memory to file - defaults to 256 bytes
	* @note mimics the DOS DEBUG program layout
	*
	* @return size_t - the end address of the paragraph
	*/
	//dos::file::size_t dump_file(char* path_name, , const address_t start, const uint32_t bytes = 256);

	/**
	* @brief dumps a page (64K bytes or 4096 paragraphs) of memory to file
	*/
	//dos::file::size_t dump_page_file(dos::file::handle_t fhandle, const address_t start);

	/**
	* @brief dumps a paragraph (16 bytes) of memory to file
	*/
	dos::file::size_t dump_paragraph_file(dos::file::handle_t fhandle, const address_t start);

}

#endif