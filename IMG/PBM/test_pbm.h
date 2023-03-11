/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_PBM
#define TEST_PBM

#include <cassert>
#include <iostream>

#include "../../TEST/debug_macros.h"
#include "pbm.h"

namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test Hercules graphics mode\n");
			pbm::bitmap bmp("CHESS/WSQ1.pbm");
			
			
			std::cout << bmp;
		}
		return 0;
	}

}

#endif