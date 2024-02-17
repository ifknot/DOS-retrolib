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
#include <stdlib.h>

#include "../FILE/file.h"
#include "../STR/str_toolbox.h"
#include "../DOS/dos_services_files.h"
#include "../MEM/mem.h"

#include "../TEST/debug_macros.h"

namespace gfx {

	namespace bmp {

		struct bitmap_t {	// 50 bytes

			uint16_t    width;          // max 65535 x 65535 image
			uint16_t    height;         // raster rectangle dimensions
			uint8_t     bit_depth;      // bits per pixel (1, 2, 4, 8 , 16) or palette index
			uint8_t     colour_type;    // Greyscale 0, Truecolour 2, Indexed colour 3, Greyscale alpha 4, Truecolour alpha 6
			char*		raster_data[8]; // ptr to pixel data raster image and any pre x-shifted optimisations for bit depths 1,2, and 4
			uint32_t    raster_size;    // size of the pixel data
			char*		palette_data;   // ptr to palette data - 24-bit values for the RGB color space, 16,777,216 color variations
			uint32_t    palette_size;   // size of the palette data

		};

		bitmap_t* new_bitmap(mem::arena::arena_t* pool, uint16_t width, uint16_t height, uint8_t bit_depth, uint8_t colour_type) {
			bitmap_t* bmp = (bitmap_t * )mem::arena::raw_alloc(pool, sizeof(bitmap_t));
			bmp->width = width;
			bmp->height = height;
			bmp->bit_depth = bit_depth;
			bmp->colour_type = colour_type;
			bmp->raster_data[0] = NULL_PTR;
			bmp->raster_data[1] = NULL_PTR;
			bmp->raster_data[2] = NULL_PTR;
			bmp->raster_data[3] = NULL_PTR;
			bmp->raster_data[4] = NULL_PTR;
			bmp->raster_data[5] = NULL_PTR;
			bmp->raster_data[6] = NULL_PTR;
			bmp->raster_data[7] = NULL_PTR;
			bmp->raster_size = 0;
			bmp->palette_data = NULL_PTR;
			bmp->palette_size = 0;
			return bmp;
		}

		namespace pbm {

			void load_file(mem::arena::arena_t* pool, const char* file_path, bitmap_t* bmp) {
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
				bmp->raster_data[0] = (char*)data.memloc;						// data.memloc now points to start of raster date
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
	os << bmp.width << ',' << bmp.height << ',' << (int)bmp.bit_depth << ',' << (int)bmp.colour_type << '\n' 
		<< std::hex << (uint32_t)bmp.raster_data[0] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[1] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[2] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[3] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[4] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[5] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[6] << '\n'
		<< std::hex << (uint32_t)bmp.raster_data[7] << '\n'
		<< std::dec << bmp.raster_size << '\n'
		<< std::hex << (uint32_t)bmp.palette_data << '\n' 
		<< std::dec << bmp.palette_size;
	return os;
}
