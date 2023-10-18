/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DEBUG_MACROS_H
#define TEST_DEBUG_MACROS_H

#include "debug_macros.h"

namespace test_debug_macros {

	void run() {
		int n = 0xDEADBEEF;
		INFO("info message");
		LOG(n);
		LOG_AS(n, std::hex);
#define VERBOSE
		ASSERT(true, false, true);
		if (YESNO("yes or no?")) {
			std::cout << "YES :)\n";
		}
		else {
			std::cout << "NO :(\n";
		}
		std::cout << ANYKEY("choose a letter...");
		PRESSENTER("do a thing and");
	}

}

#endif