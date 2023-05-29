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

	/**
	* @brief calculate the size, in bytes, of a stream.
	* @note 1. assumes stream is open in binary mode.
	*/
	long stream_size(FILE* fptr) {
		long pos, size = STDIO_FAIL;
		if (fptr) {
			pos = ftell(fptr);		// copy the current position in the stream
			if (pos != STDIO_FAIL	// found the current position
				&& fseek(fptr, 0L, SEEK_END) == 0 // seek from begin (0L offset) to end of stream
				) {					// binary streams are not required to support SEEK_END, in particular if additional null bytes are output
				size = ftell(fptr); // position now the end stream
				assert(size != STDIO_FAIL);
				assert(fseek(fptr, pos, SEEK_SET) != STDIO_FAIL); // restore stream position
			}
		}
		return size;
	}

	/**
	* @brief calculate the remaining bytes in a stream.
	* @note 1. assumes stream is open in binary mode.
	*/
	long stream_bytes_remaining(FILE* fptr) {
		long pos, size = STDIO_FAIL;		
		if (fptr) {
			pos = ftell(fptr);		// copy the current position in the stream
			if (pos != STDIO_FAIL	// found the current position
				&& fseek(fptr, pos, SEEK_END) == 0 // seek from current offset to end of stream
				) {					// binary streams are not required to support SEEK_END, in particular if additional null bytes are output
				size = ftell(fptr); // position now the end stream
				assert(size != STDIO_FAIL);
				assert(fseek(fptr, pos, SEEK_SET) != STDIO_FAIL); // restore stream position
			}
		}
		return size; 
	}

}

#endif