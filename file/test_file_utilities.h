/**
 *
 *  @file      test_file_utilities.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_FILE_UTILITIES_H
#define TEST_FILE_UTILITIES_H

#include <cassert>

#include "file_utilities.h"

namespace test_file_utilities {

	void run() {
		std::cout << "test_file_utilities... ";
		//test filesystem::extension
		{
			assert(jtl::filesystem::extension("test.txt") == "txt");
		}
		std::cout << "success!\n";
	}

}

#endif