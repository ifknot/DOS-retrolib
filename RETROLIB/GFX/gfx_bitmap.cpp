/**
 *
 *  @file      gfx_bitmap.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.12.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "gfx_bitmap.h"

#include <iostream>
#include <string.h>

#include "../FILE/file.h"
#include "../STR/str_toolbox.h"
#include "../DOS/dos_services_files.h"
#include "../MEM/mem.h"

#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		void load_file_pbm(const char* file_path, bitmap_t* bmp, mem::arena::arena_t* pool, bool auto_invert) {			
			const char* raw_ext = file::get_extension(file_path);
			char pbm_ext[] = "   ";
			str::copy_convert_to_upper(raw_ext, pbm_ext);
			if (strcmp(pbm_ext, PBM_EXT) != 0) {	
#ifndef NDEBUG
				std::cout << "Error load_file_pbm incorrect file extension - expected .PBM - found " << raw_ext << std::endl;
#endif
				return;
			}			
			dos::file::handle_t fhandle = dos::open_file_using_handle(file_path, dos::file::ACCESS_READ_ONLY);
			if (!fhandle) {		
				return;
			}			
			if (file::get_size(fhandle) > mem::arena::capacity(pool)) {	
#ifndef NDEBUG
				std::cout << "Error load_file_pbm file too large for arena memory pool!" << std::endl;
#endif
				return;
			}
			

			dos::close_file_using_handle(fhandle);
		}

	}

}

/*

// 5. is it a valid P4 file ?
			uint16_t magic;
			dos::read_file_using_handle(fhandle, (char*)&magic, 2);
			if (magic != PBM_MAGIC) {
				std::cout << "Error load_file_pbm invalid magic number - expected 3450h - found " << std::hex << magic << 'h' << std::endl;
				return;
			}

*/
