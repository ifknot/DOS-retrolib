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
#include "str_toolbox.h"

#include <string.h>
#include <stdio.h>
#include <ctype.h>


namespace str {

	int ignore_token(const char* cstr, char delim, int pos) {
		while (cstr[pos] != '\0' && cstr[pos] != delim) {
			++pos;
		}
		return ++pos;
	}

	int skip_chars(const char* cstr, const char* chars, int pos) {
		while (cstr[pos] != '\0' && strchr(chars, cstr[pos])) {
			++pos;
		}
		return pos;
	}

	int in_place_to_upper(char* cstr, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for (int i = begin; i < end; ++i) {
			cstr[i] = toupper(cstr[i]);
		}
		return end - begin;
	}

	int in_place_to_lower(char* cstr, int begin, int end) {
		if (!end) {
			end = strlen(cstr);
		}
		for (int i = begin; i < end; ++i) {
			cstr[i] = tolower(cstr[i]);
		}
		return end - begin;
	}

	int copy_convert_to_upper(const char* src, char* dst, int begin, int end) {
		int len = strlen(src);
		if (!end) {
			end = len;
		}
		for (int i = 0; i < begin; ++i) {
			dst[i] = src[i];
		}
		for (int i = begin; i < end; ++i) {
			dst[i] = toupper(src[i]);
		}
		for (int i = end; i < len; ++i) {
			dst[i] = src[i];
		}
		return end - begin;
	}

	int copy_convert_to_lower(const char* src, char* dst, int begin, int end) {
		int len = strlen(src);
		if (!end) {
			end = len;
		}
		for (int i = 0; i < begin; ++i) {
			dst[i] = src[i];
		}
		for (int i = begin; i < end; ++i) {
			dst[i] = tolower(src[i]);
		}
		for (int i = end; i < len; ++i) {
			dst[i] = src[i];
		}
		return end - begin;
	}

}