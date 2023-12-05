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
#include "str_toolbox.h"

namespace str {

	int in_place_to_upper(char* cstr, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for(int i = begin; i < end; ++i) {
			cstr[i] = toupper(cstr[i]);
		}
		return end - begin;
	}

	int in_place_to_lower(char* s, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for (int i = begin; i < end; ++i) {
			cstr[i] = tolower(cstr[i]);
		}
		return end - begin;
	}

	int copy_convert_to_upper(const char* source, char* destination, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for (int i = begin; i < end; ++i) {
			destination[i] = toupper(source[i]);
		}
		return end - begin;
	}

	int copy_convert_to_lower(const char* source, char* destination, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for (int i = begin; i < end; ++i) {
			destination[i] = tolower(source[i]);
		}
		return end - begin;
	}

}