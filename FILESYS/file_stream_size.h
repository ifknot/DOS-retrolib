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

namespace filesys {

	int istream_size(std::istream* f) {
		f->seekg(0, f->end);		// seek to the end
		int size = f->tellg();		// position of the current character ie the end character
		f->seekg(0, f->beg);		// return to the beginning
		return size;
	}

}

#endif