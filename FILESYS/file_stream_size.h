/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      11.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FILE_FSTREAM_SIZE_H
#define FILE_FSTREAM_SIZE_H

#include <istream>
#include <string>

namespace filesys {

	int file_size(std::string file_path) {
		int size = 0;
		std::ifstream* f(new std::ifstream(file_path.c_str()));
		if (!f->is_open()) {
			f->seekg(0, f->end);		// seek to the end
			size = f->tellg();		// position of the current character ie the end character
			f->seekg(0, f->beg);		// return to the beginning
			f->close();
		}
		delete f;
		return size;
	}

}

#endif