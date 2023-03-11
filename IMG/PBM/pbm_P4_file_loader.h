/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_P4_FILE_LOADER_H
#define PBM_P4_FILE_LOADER_H

#include <string>
#include <fstream>

#include "../../FILESYS/filesys.h"
#include "../../DOS/dos_error_messages.h"
#include "../../TEST/debug_macros.h"

#include "pbm_types.h"

namespace pbm {

	namespace P4 {

		dos::error::codes read_pbm_header(std::string file_path, bitmap* img) {
			char line[MAX_LINE_SIZE];
			uint16_t width, height, offset;
			// perform sanity checks before attempting to load
			if (filesys::extension(file_path) != VALID_PBM_EXT) { // 1. is it a valid extension?
				return dos::error::INVALID_HANDLE;
			}
			std::ifstream* f(new std::ifstream(file_path.c_str()));
			if (!f->is_open()) { // 2. is it a valid file path?
				delete f;
				return dos::error::FILE_NOT_FOUND;
			}
			LOG(filesys::istream_size(f));
			f->getline(line, MAX_LINE_SIZE); 
			if (f->eof()) { // 3. is there at least 1 line in the file?
				f->close();
				delete f;
				return dos::error::INVALID_DATA;
			}
			if (*(uint16_t*)line != MAGIC_P4) { // 4. is it a valid magic number?
				f->close();
				delete f;
				return dos::error::INVALID_FORMAT;
			}
			// 5. get header data
			while (f->peek() == '#') f->getline(line, MAX_LINE_SIZE);	// skip any comments
			f->operator>>(width);				// read width
			f->operator>>(height);				// and height
			int bytes = (int)width / 8;			// convert width to bytes
			bytes += (width & 7) == 0 ? 0 : 1;	// need an extra byte for width remainder < 8?
			bytes *= height;					// this many bytes
			f->getline(line, MAX_LINE_SIZE);	// data should start on next line
			offset = f->tellg();				// data starts here
			if(offset + bytes != filesys::istream_size(f)) { // expected amount of data?
				f->close();
				delete f;
				return dos::error::INVALID_DATA;
			}
			// 6. populate the header
			img->header.magic_number = MAGIC_P4;
			img->header.width = width;
			img->header.height = height;
			img->header.size = bytes;
			img->header.offset = offset;
			f->close();
			delete f;

			return dos::error::SUCCESS;
		}



	}

}

#endif