/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      13.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS_READ_CSV_H
#define FSYS_READ_CSV_H

#include "fsys_constants.h"

namespace fsys {

	uint16_t read_csv(const char* file_path, char strings[], uint16_t count) {
		FILE* fptr = fopen(file_path, "r");
		if (!fptr) return STDIO_FAIL;
	}

}

#endif