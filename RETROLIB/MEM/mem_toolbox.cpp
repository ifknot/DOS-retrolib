/**
 *
 *  @file      mem_toolbox.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_toolbox.h"

#include <cassert>
#include <iostream>
#include <stdint.h>

#include "../DOS/dos_services_files.h"

#include "mem_constants.h"
#include "mem_types.h"

namespace mem {

    uint32_t available_low_memory_bytes() {
        uint16_t paragraphs, err_code = 0;
        uint32_t convert = 16;  // 16 bytes per paragraph
        __asm {
            .8086
            mov     bx, 0FFFFh; deliberate over sized request
            mov     ah, 48h; allocate memory
            int     21h; INT 21h, 48h allocate memory service
            mov     err_code, ax; CF set, and AX = 08 (Not Enough Mem)
            mov     paragraphs, bx; size in paras of the largest block of memory available
        }
        assert(err_code == 8);
        return convert * paragraphs;
    }

    address_t dump(const address_t start, uint32_t nbytes) {
        return dump_ostream(std::cout, start, nbytes);
    }

    address_t dump_ostream(std::ostream& os, address_t start, uint16_t nbytes) {
        address_t next = start;
        uint16_t paras = (nbytes % PARAGRAPH_SIZE) ? (nbytes >> 4) + 1 : nbytes >> 4; // convert size to paragraphs
        for (int i = 0; i < paras; ++i) {
            next = dump_paragraph_ostream(os, next);
        }
        return next;
    }

    address_t dump_paragraph_ostream(std::ostream& os, address_t start) {
        os << start.segoff << ' ';
        const char* pbyte = (char*)start.memloc;                     // extract char* from address_t
        const char* pchar = pbyte;                                                                            // duplicate
        int i = 0;
        for (; i < PARAGRAPH_SIZE / 2; ++i) {                           // first 8 bytes as hex
            os << ' ' << std::setw(2) << std::hex << (int)*pbyte++;
        }
        os << '-' << std::setw(2) << std::hex << (int)*pbyte++;         // 9th byte as hex w dash spacer as per DOS DEBUG
        for (; i < PARAGRAPH_SIZE - 1; ++i) {                           // remaining bytes of the paragraph of memory
            os << ' ' << std::setw(2) << std::hex << (int)*pbyte++;
        }
        os << "   ";
        for (i = 0; i < PARAGRAPH_SIZE; ++i) {                          // 16 bytes as hex replace with '.' if not standard alphabet
            os << ((*pchar >= ' ' & *pchar <= '~') ? *pchar : '.');
            pchar++;
        }
        os << std::endl;
        address_t next;
        next.memloc = (uint32_t)pbyte;
        return next;
    }

    dos::file::size_t load_from_file(const char* path_name, address_t start, uint16_t nbytes) {
        dos::file::size_t bytes_loaded = 0;
        dos::file::handle_t fhandle = dos::open_file_using_handle(path_name, dos::file::ACCESS_READ_ONLY);
        if (fhandle) {
            bytes_loaded = dos::read_file_using_handle(fhandle, (char*)start.memloc, nbytes);
            dos::close_file_using_handle(fhandle);
        }
        return bytes_loaded;
    }

    dos::file::size_t save_to_file(const char* path_name, address_t start, uint16_t nbytes) {
        dos::file::size_t bytes_saved = 0;
        dos::file::handle_t fhandle = dos::open_file_using_handle(path_name, dos::file::ACCESS_WRITE_ONLY);
        if (fhandle) {
            bytes_saved = dos::write_file_using_handle(fhandle, (char*)start.memloc, nbytes);
            dos::close_file_using_handle(fhandle);
        }
        return bytes_saved;
    }

    dos::file::size_t write_ostream(std::ostream& os, address_t start, uint16_t bytes) {
        char* pchar = (char*)start.memloc;
        int i;
        for (i = 0; i < bytes; ++i) {
            os << *pchar++;
        }
        return i;
    }

}