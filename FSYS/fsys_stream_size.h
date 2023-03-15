/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      11.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS_STREAM_SIZE_H
#define FSYS_FSTREAM_SIZE_H

#include "fsys_constants.h"

namespace fsys {

	long stream_size(FILE* fptr) {
		long pos, size = 0;
		if (fptr) {
			pos = ftell(fptr);
			if (pos != STDIO_FAIL && fseek(fptr, 0L, SEEK_END) == 0) {
				size = ftell(fptr);
				assert(size != STDIO_FAIL);
				assert(fseek(fptr, pos, SEEK_SET) != STDIO_FAIL);
			}
		}
		return size; 
	}

}

#endif