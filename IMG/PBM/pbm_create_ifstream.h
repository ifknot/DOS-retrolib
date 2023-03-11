/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      11.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_CREATE_IFSTREAM_H
#define PBM_CREATE_IFSTREAM_H

#include <string>
#include <fstream>

#include "../../FILESYS/filesys.h"
#include "../../DOS/dos_error_messages.h"

#include "pbm_types.h"

namespace pbm {

	std::ifstream* create_ifstream(std::string& file_path) {
		std::string ext = filesys::extension(file_path);
		if (ext != VALID_PBM_EXT) { // 1. is it a valid extension?
			file_path += ext + dos::error::messages[dos::error::INVALID_FORMAT];
			return 0;
		}
		std::ifstream* f(new std::ifstream(file_path.c_str()));
		if (!f->is_open()) { // 2. is it a valid file path?
			file_path += dos::error::messages[dos::error::FILE_NOT_FOUND];
			delete f;
			return 0;
		}
		return f;
	}

}

#endif