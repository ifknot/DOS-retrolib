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

	int in_place_to_upper(char* cstr, int begin = 0, int end = 0);

	int in_place_to_lower(char* s, int begin = 0, int end = 0);

	int copy_convert_to_upper(const char* lower, char* upper, int begin = 0, int end = 0);

	int copy_convert_to_lower(const char* upper, char* lower, int begin = 0, int end = 0);

}

#endif