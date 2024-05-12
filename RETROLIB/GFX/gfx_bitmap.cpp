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

		bitmap_t* new_bitmap(
			mem::arena::arena_t* pool, 
			uint16_t width, 
			uint16_t height, 
			uint8_t bit_depth, 
			uint8_t colour_type,
			char* raster_data,
			uint32_t raster_size,
			char* palette_data,
			uint32_t palette_size
		) {
			if (sizeof(bitmap_t) > mem::arena::size(pool)) {						// is there enough avaiable memory in the pool?
#ifndef NDEBUG
				std::cout << "Error new_bitmap no room in arena memory pool for bitmap_t! - sizeof(bitmap_t) = " << sizeof(bitmap_t) << " arena pool size = " << mem::arena::size(pool) << std::endl;
#endif
				return NULL_PTR;																// nope, return															
			}
			bitmap_t* bmp = (bitmap_t*)mem::arena::raw_alloc(pool, sizeof(bitmap_t));
			bmp->width = width;
			bmp->height = height;
			bmp->bit_depth = bit_depth;
			bmp->colour_type = colour_type;
			bmp->raster_size = raster_size
			bmp->palette_data = palette_data;
			bmp->palette_size = palette_size;
			return bmp;
		}

		uint32_t calculate_raster_size(uint16_t width, uint16_t height, uint8_t bit_depth) {
			switch (bit_depth) {
			case 1:	// fall through
			case 2: // .
			case 4: // .
			case 8: // .
				return = ((uint32_t)width * (uint32_t)height) / (8 / bmp->bit_depth);
			case 16:
				return = width * height * 2;
#ifndef NDEBUG
			default:
				std::cout << "ERROR new_bitmap ILLEGAL bit depth " << bmp->bit_depth << std::endl;
#endif
			}
			if (raster_data) {
				bmp->raster_data = raster_data;
			}
			else {	// NULL_PTR (default) raster_data* will acquire raster_size bytes from pool
				bmp->raster_data = (char*)mem::arena::raw_alloc(pool, bmp->raster_size);
			}
		}

		void fill(gfx::bmp::bitmap_t* bmp, uint8_t fill_byte) {

			__asm {
				.8086
				push bp
				pushf

				lds		si, bmp								; DS:[SI] points to the bitmap_t metadata
				les		di, [si + OFFSET_RASTER_DATA]		; ES:[DI] points to raster data area
				mov		cx, [si + OFFSET_RASTER_SIZE]		; CX is the size of the raster data area
				mov		al, fill_byte						; AL is the repeated byte
				cld											; increment DI
				//rep		stosw								; chain store byte in AL into ES:[DI] update SI repeat CX times

				popf
				pop bp
			}
		}

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

std::ostream& operator<< (std::ostream& os, const gfx::bmp::bitmap_t& bmp) {
	os << bmp.width << ',' << bmp.height << ',' << (int)bmp.bit_depth << ',' << (int)bmp.colour_type << '\n' 
		<< std::hex << (uint32_t)bmp.raster_data << '\n'
		<< std::dec << bmp.raster_size << '\n'
		<< std::hex << (uint32_t)bmp.palette_data << '\n'
		<< std::dec << bmp.palette_size;
	return os;
}
