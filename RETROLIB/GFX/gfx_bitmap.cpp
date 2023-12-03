/**
 *
 *  @file      gfx_bitmap.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "gfx_bitmap.h"

#include <iostream>
#include <string.h>

#include "../FILE/file.h"
#include "../STR/str_to_upper.h"
#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		void load_file_pbm(const char* file_path, bitmap_t* bmp, mem::arena::arena_t* pool, bool auto_invert) {
			const char* raw_ext = file::get_extension(file_path);
			char pbm_ext[] = "   ";
			str::copy_convert_to_upper(raw_ext, pbm_ext);
			file::file_size_t sz = file::get_size(file_path);
			if (sz && strcmp(pbm_ext, PBM_EXT) == 0) {
				
				LOG(sz);
			}

#ifndef NDEBUG

			else {
				std::cout << "Error load_file_pbm incorrect file extension - expected .PBM - found " << raw_ext << std::endl;
			}

#endif

		}

	}

}


