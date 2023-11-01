/**
 *
 *  @file      mem_save_ostream.cpp
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_save_ostream.h"

#include "../DOS/dos_services_files_types.h"

namespace mem {

        dos::file::size_t save_page_ostream(std::ostream& os, const address_t start, const uint16_t bytes) {
                char* pchar = (char*)start.void_ptr;
                int i;
                for (i = 0; i < bytes; ++i) {
                        os << *pchar++;
                }
                return i;
        }

}