/**

    @file      gfx_bitmap_file_tools.cpp
    @brief     
    @details   ~
    @author    Jeremy Thornton
    @date      13.05.2024
    @copyright © Jeremy Thornton, 2024. All right reserved.

**/
#include "gfx_bitmap_file_tools.h"

#include <iostream>

#include "../FILE/file.h"
#include "../STR/str_toolbox.h"
#include "../DOS/dos_services_files.h"
#include "../MEM/mem.h"

namespace gfx {

    namespace bmp {

        namespace pbm {

			void load_file(mem::arena::arena_t* pool, bitmap_t* bmp, const char* file_path) {
				mem::address_t file_data;

				const char* raw_ext = file::get_extension_ptr(file_path);
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

				file::file_size_t fsize = file::get_size(fhandle);
				if (fsize > mem::arena::size(pool)) {									// is there enough avaiable memory in the pool?
#ifndef NDEBUG
					std::cout << "Error load_file_pbm file too large for arena memory pool! - file size = " << fsize << " arena pool size = " << mem::arena::size(pool) << std::endl;
#endif
					return;																// nope, return															
				}

				file_data.memloc = (uint32_t)mem::arena::raw_alloc(pool, fsize);		// allocate pool memory for whole file
				mem::load_from_file_using_handle(fhandle, file_data, fsize);			// load file into memory

				if (PBM_MAGIC_RAW != *(uint16_t*)file_data.memloc) {					// check if a valid PBM data
					mem::arena::raw_dealloc(pool, fsize);								// nope then release pool memory
					dos::close_file_using_handle(fhandle);								// close the file
#ifndef NDEBUG
					std::cout << "Error load_file_pbm incorrect magic number not P4 portable bitmap format RAW" << std::endl;
#endif
					return;																// return
				}

				uint32_t mem_start = file_data.memloc;
				file_data.memloc += str::ignore_line((char*)file_data.memloc);			// skip the magic 
				while ('#' == *(char*)file_data.memloc) {								// skip any subsequent comments  
					file_data.memloc += str::ignore_line((char*)file_data.memloc);
				}
				bmp->width = atoi((const char*)file_data.memloc);						// extract the width
				file_data.memloc += str::ignore_token((char*)file_data.memloc, ' ');	// skip the width token
				bmp->height = atoi((const char*)file_data.memloc);						// extract the height
				file_data.memloc += str::ignore_line((char*)file_data.memloc);			// skip line to start raw pixel data
				bmp->raster_data = (char*)file_data.memloc;								// file_data.memloc points to start of raster date
				bmp->raster_size = fsize - (file_data.memloc - mem_start);				// calculate raster size
				bmp->bit_depth = 1;														// 1 bits per pixel
				bmp->colour_type = GREYSCALE;											// greyscale
				bmp->palette_data = NULL_PTR;											// no palette data
				bmp->palette_size = 0;

				dos::close_file_using_handle(fhandle);
			}

        }

    }

}