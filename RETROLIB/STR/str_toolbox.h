/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      3.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef STR_TOOLBOX_H
#define STR_TOOLBOX_H

namespace str {

	const char WHITE_SPACE_TOKENS[] = " \t\r";

	int ignore_token(const char* cstr, char delim, int pos = 0);

	inline int ignore_line(const char* cstr, int pos = 0) {
		return ignore_token(cstr, '\n', pos);
	}

	int skip_chars(const char* cstr, const char* chars, int pos = 0);

	inline int skip_white_space(const char* cstr, int pos = 0) {
		return skip_chars(cstr, WHITE_SPACE_TOKENS, pos);
	}

	//int copy_token(const char* src, char* dst, char delim, int pos = 0);

	int in_place_to_upper(char* cstr, int begin = 0, int end = 0);

	int in_place_to_lower(char* cstr, int begin = 0, int end = 0);

	int copy_convert_to_upper(const char* src, char* dst, int begin = 0, int end = 0);

	int copy_convert_to_lower(const char* src, char* dst, int begin = 0, int end = 0);

}

#endif