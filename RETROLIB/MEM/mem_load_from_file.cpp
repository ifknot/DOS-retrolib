/**
 *
 *  @file      mem_load_from_file.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_load_from_file.h"

#include "../DOS/dos_services_files.h"

namespace mem {

	dos::file::size_t load_from_file(const char* path_name, address_t start, uint16_t nbytes) {
        dos::file::size_t bytes_loaded = 0;
        dos::file::handle_t fhandle = dos::open_file_using_handle(path_name, dos::file::ACCESS_READ_ONLY);
        if (fhandle) {
            bytes_loaded = dos::read_file_using_handle(fhandle, (char*)start.void_ptr, nbytes);
            dos::close_file_using_handle(fhandle);
        }
        return bytes_loaded;
	}

}