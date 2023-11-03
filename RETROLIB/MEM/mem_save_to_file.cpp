/**
 *
 *  @file      mem_dump_file.cpp
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      31.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_save_to_file.h"

#include "../DOS/dos_services_files.h"

namespace mem {

    dos::file::size_t save_to_file(const char * path_name, address_t start, uint16_t nbytes) {
        dos::file::size_t bytes_saved = 0;
        dos::file::handle_t fhandle = dos::open_file_using_handle(path_name, dos::file::ACCESS_WRITE_ONLY);
        if (fhandle) {
            bytes_saved = dos::write_file_using_handle(fhandle, (char*)start.void_ptr, nbytes);
            dos::close_file_using_handle(fhandle);
        }
        return bytes_saved;
    }

}