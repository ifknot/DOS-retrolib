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

#include "../../FILESYS/file_extension.h"
#include "../../DOS/dos_error_messages.h"
#include "../../TEST/debug_macros.h"

#include "pbm_types.h"

namespace pbm {

	namespace P4 {

		dos::error::codes read_bitmap(std::string file_path, bitmap* img) {
			// perform sanity checks before attempting to load
			if (filesys::extension(file_path) != VALID_PBM_EXT) { // 1. is it a valid extension?
				return dos::error::INVALID_HANDLE;
			}
			std::ifstream* f(new std::ifstream(file_path.c_str()));
			if (!f->is_open()) { // 2. is it a valid file path?
				delete f;
				return dos::error::FILE_NOT_FOUND;
			}
			char line[256];
			f->getline(line, 1);
			if (f->eof()) { // 3. is there at least 1 line in the file?
				f->close();
				delete f;
				return dos::error::INVALID_DATA;
			}
			LOG_AS(*(uint16_t*)line, std::hex);

			return dos::error::SUCCESS;
		}



	}

}

#endif