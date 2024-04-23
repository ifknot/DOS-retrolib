/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FILE_EXTENSION_H
#define	FILE_EXTENSION_H

#include "file_types.h"
#include "../DOS/dos_services_files_types.h"

namespace file {

	/**
	*  @brief	Retrieve position of file extension (if there is one) in file path 
	*  @param	const char* file_path, ptr to extant file path C string
	*  @retval  const char* position of start of extension in file_path
	*/
	const char* get_extension_ptr(const char* file_path);

	/**
	*  @brief	Retrieve file size
	*  @param	const char* file_path
	*  @retval  file_size_t or 0 if not found
	*/
	file_size_t get_size(const char* file_path);

	file_size_t get_size(const dos::file::handle_t handle);

	file_size_t skip_white_space(const dos::file::handle_t handle, const char* whitespaces);

	file_size_t skip_line(const dos::file::handle_t handle);

}

#endif