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
			char** raster_data,
			uint32_t raster_size,
			char* palette_data,
			uint32_t palette_size
		) {
			bitmap_t* bmp = (bitmap_t * )mem::arena::raw_alloc(pool, sizeof(bitmap_t));
			bmp->width = width;
			bmp->height = height;
			bmp->bit_depth = bit_depth;
			bmp->colour_type = colour_type;
			bmp->raster_size = raster_size;
			new_raster_data(bmp, pool, width, height, raster_data);
			bmp->palette_data = palette_data;
			bmp->palette_size = palette_size;
			return bmp;
		}

		void new_raster_data(bitmap_t* bmp, mem::arena::arena_t* pool, uint16_t width, uint16_t height, char* raster_data[]) {
			if(width and height) { // caller wants to use passed width and height arguements and extant bit_depth to calculate a new raster_size 
				switch (bmp->bit_depth) {
				case 1:	// fall through
				case 2: // .
				case 4: // .
				case 8: // .
					bmp->raster_size = ((uint32_t)width * (uint32_t)height) / (8 / bmp->bit_depth);
					break;
				case 16:
					bmp->raster_size = width * height * 2;
					break;
	#ifndef NDEBUG
				default:
					std::cout << "ERROR new_bitmap ILLEGAL bit depth " << bmp->bit_depth << std::endl;
	#endif
				}
			}
			if (raster_data) { // copy the passed raster_data array arguement
				bmp->raster_data[0] = raster_data[0];
				bmp->raster_data[1] = raster_data[1];
				bmp->raster_data[2] = raster_data[2];
				bmp->raster_data[3] = raster_data[3];
				bmp->raster_data[4] = raster_data[4];
				bmp->raster_data[5] = raster_data[5];
				bmp->raster_data[6] = raster_data[6];
				bmp->raster_data[7] = raster_data[7];
			}
			else if(bmp->raster_size) { // caller wants to reserve space for raster data in passed memory pool and assign same to every pointer in the array
				bmp->raster_data[0] =
					bmp->raster_data[1] =
					bmp->raster_data[2] =
					bmp->raster_data[3] =
					bmp->raster_data[4] =
					bmp->raster_data[5] =
					bmp->raster_data[6] =
					bmp->raster_data[7] = mem::arena::raw_alloc(pool, bmp->raster_size);
			}
			else { // all null pointers in the array 
				bmp->raster_data[0] =
					bmp->raster_data[1] =
					bmp->raster_data[2] =
					bmp->raster_data[3] =
					bmp->raster_data[4] =
					bmp->raster_data[5] =
					bmp->raster_data[6] =
					bmp->raster_data[7] = NULL_PTR;
			}
		}

		void fill(gfx::bmp::bitmap_t* bmp, gfx::colours::high_colour_t colour) {
			__asm {
				.8086
				push bp
				pushf

				lds		si, bmp
				les		di, [si + OFFSET_RASTER_DATA]
				mov		cx, [si+ OFFSET_RASTER_SIZE]
				mov		ax, colour
				cld
				rep		stosw

				popf
				pop bp
			}
		}

		namespace pbm {

			void load_file(mem::arena::arena_t* pool, bitmap_t* bmp, const char* file_path) {
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
		<< std::hex << std::setfill('0') << std::setw(8) 
		<< (uint32_t)bmp.raster_data[0] << '\n'
		<< (uint32_t)bmp.raster_data[1] << '\n'
		<< (uint32_t)bmp.raster_data[2] << '\n'
		<< (uint32_t)bmp.raster_data[3] << '\n'
		<< (uint32_t)bmp.raster_data[4] << '\n'
		<< (uint32_t)bmp.raster_data[5] << '\n'
		<< (uint32_t)bmp.raster_data[6] << '\n'
		<< (uint32_t)bmp.raster_data[7] << '\n'
		<< std::dec << bmp.raster_size << '\n'
		<< std::hex << std::setfill('0') << std::setw(8) << (uint32_t)bmp.palette_data << '\n'
		<< std::dec << bmp.palette_size;
	return os;
}
