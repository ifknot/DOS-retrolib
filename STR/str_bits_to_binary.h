/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef STR_BITS_TO_BINARY_H
#define STR_BITS_TO_BINARY__H

#include <iostream>

#include "str_constants.h"
#include "str_types.h"

namespace str {

	errno_t bits_to_binary(uint64_t value, char string[], int bits = 64) {
		for (int i = 0; i < bits; ++i) {
			string[bits - 1 - i] = ((value & 1) == 1) ? '1' : '0';
			value >>= 1;
		}
		string[bits] = '\0';
		return 0;
	}

}

#endif