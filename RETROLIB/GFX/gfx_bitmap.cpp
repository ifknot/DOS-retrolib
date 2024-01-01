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
#include <stdlib.h>

#include "../FILE/file.h"
#include "../STR/str_toolbox.h"
#include "../DOS/dos_services_files.h"
#include "../MEM/mem.h"

#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		namespace pbm {

			void load_file(const char* file_path, bitmap_t* bmp, mem::arena::arena_t* pool) {
				const char* raw_ext = file::get_extension(file_path);
				char pbm_ext[] = "   ";
				mem::address_t data;

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

				file::file_size_t fsize = file::get_size(fhandle);
				if (fsize > mem::arena::size(pool)) {
#ifndef NDEBUG
					std::cout << "Error load_file_pbm file too large for arena memory pool! - file size = " << fsize << " arena pool size = " << mem::arena::size(pool) << std::endl;
#endif
					return;
				}

				data.memloc = (uint32_t)mem::arena::raw_alloc(pool, fsize);		// allocate memory for whole file
				mem::load_from_file_using_handle(fhandle, data, fsize);			// load file into memory

				if (PBM_MAGIC_RAW != *(uint16_t*)data.memloc) {					// check if a valid 
					mem::arena::raw_dealloc(pool, fsize);
					dos::close_file_using_handle(fhandle);
#ifndef NDEBUG
					std::cout << "Error load_file_pbm incorrect magic number not P4 portable bitmap format RAW" << std::endl;
#endif
					return;
				}

				uint32_t mem_start = data.memloc;
				data.memloc += str::ignore_line((char*)data.memloc);			// skip the magic 
				while ('#' == *(char*)data.memloc) {							// skip any subsequent comments  
					data.memloc += str::ignore_line((char*)data.memloc);
				}
				bmp->width = atoi((const char*)data.memloc);					// extract the width
				data.memloc += str::ignore_token((char*)data.memloc, ' ');		// skip the width token
				bmp->height = atoi((const char*)data.memloc);					// extract the height
				data.memloc += str::ignore_line((char*)data.memloc);			// skip line to start raw pixel data
				bmp->raster_data[0] = (char*)data.memloc;							// data.memloc now points to start of raster date
				bmp->raster_size = fsize - (data.memloc - mem_start);			// calculate raster size
				bmp->bit_depth = 1;												// 1 bits per pixel
				bmp->colour_type = GREYSCALE;									// greyscale
				bmp->palette_data = NULL_PTR;									// no palette data
				bmp->palette_size = 0;

				dos::close_file_using_handle(fhandle);
			}

		}

	}

}

std::ostream& operator<< (std::ostream& os, const gfx::bmp::bitmap_t& bmp) {
	os << bmp.width << ',' << bmp.height << ',' << (int)bmp.bit_depth << ',' << (int)bmp.colour_type
		<< ',' << std::hex << (uint32_t)bmp.raster_data << ',' << std::dec << bmp.raster_size
		<< ',' << std::hex << (uint32_t)bmp.palette_data << ',' << std::dec << bmp.palette_size;
	return os;
}
