/**
 *
 *  @file      str_to_upper.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      3.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "str_to_upper.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

namespace str {

	void in_place_to_upper(char* s) {
		size_t len = strlen(s);
		for(int i = 0; i < len; ++i) {
			s[i] = toupper(s[i]);
		}
	}

	void copy_convert_to_upper(const char* lower, char* upper) {
		size_t len = strlen(lower);
		assert(len <= strlen(upper));
		for (int i = 0; i < len; ++i) {
			upper[i] = toupper(lower[i]);
		}
	}

}