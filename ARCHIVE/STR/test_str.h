/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_STR_H
#define TEST_STR_H

#include "../TEST/debug_macros.h"
#include "str.h"

namespace test_str {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test my string functions\n");
			char binalpha[64];
			str::bits_to_binary(0xF5, binalpha);
			std::cout << binalpha;

		}
		return 0;
	}

}

#endif