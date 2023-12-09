/**
 *
 *  @file      file_extension.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "file_toolbox.h"

#include <string.h>

#include "file_constants.h"

#include "../DOS/dos_services_files.h"
#include "../DOS/dos_services_files_types.h"

namespace file {

	const char* get_extension(const char* pfile_path) {
		const char* p = strrchr(pfile_path, file::EXTENSION_DELIM);
		if (!p || p == pfile_path) {
			return 0;
		}
		else {
			return ++p;
		}
	}

	file_size_t get_size(const char* file_path) {
		dos::file::handle_t fhandle = dos::open_file_using_handle(file_path, dos::file::ACCESS_READ_ONLY);
		dos::file::position_t fpos = dos::move_file_pointer_using_handle(fhandle, dos::file::FSEEK_END, 0);
		dos::close_file_using_handle(fhandle);
		return (file_size_t)fpos;
	}

	file_size_t get_size(const dos::file::handle_t fhandle) {
		dos::file::position_t fpos = dos::move_file_pointer_using_handle(fhandle, dos::file::FSEEK_END);
		dos::move_file_pointer_using_handle(fhandle, dos::file::FSEEK_SET);
		return (file_size_t)fpos;
	}

	file_size_t skip_white_space(const dos::file::handle_t handle, const char* whitespaces) {
		// TODO:
		return file_size_t();
	}

	file_size_t skip_line(const dos::file::handle_t handle) {
		// TODO
		return file_size_t();
	}

}