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
			pbm::bitmap bmp;
			bmp.header.file_path = "CHESS/WSQ12.pbm";
			std::ifstream* f = pbm::create_ifstream(bmp.header.file_path);
			if(!f) std::cout << bmp.header;
			//*f >> bmp.header;
			delete f;
			//LOG(dos::error::messages[pbm::P4::read_pbm_header("CHESS/WSQ1.pbm", &bmp)]);
			std::cout << bmp.header;
		}
		return 0;
	}

}

#endif