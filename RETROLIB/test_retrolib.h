/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_RETROLIB_H
#define TEST_RETROLIB_H

#include <iostream>


#include "RETROLIB/TEST/debug_macros.h"
 // 000
#include "RETROLIB/TEST/test_debug_macros.h"
// 001
#include "RETROLIB/DOS/test_dos.h"
// 002
#include "RETROLIB/MEM/test_mem.h"

namespace test_retrolib {

	void run() {

		std::cout << "test functions..." << std::endl;
		//if (YESNO("* 000\ttest debug ?")) test_debug_macros::run();
		//if (YESNO("* 001\ttest DOS ?")) test_dos::run();
		if (YESNO("* 002\ttest MEM ?")) test_lib_mem::run();

	}

}

#endif