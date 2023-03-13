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

#include "../../TEST/debug_macros.h"
#include "pbm.h"

namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test Portable Bit Map\n");

			const char pieces[6][80] = {
				"CHESS/BNR.pbm",
				"CHESS/BR.pbm",
				"CHESS/BSQ.pbm",
				"CHESS/WSQ.pbm",
				"CHESS/WSQ1.pbm",
				"CHESS/WSQ2.pbm",
			};

			pbm::bitmap_t bmp[6];
			for (int i = 0; i < 6; ++i) {
				if (pbm::load_bitmap(pieces[i], &bmp[i]) == STDIO_FAIL) {
					std::cout << strerror(errno) << std::endl;
					exit(EXIT_FAILURE);
				}
			}
			for (int i = 0; i < 6; ++i) {
				std::cout << bmp[i];
				getchar();
			}
			for (int i = 0; i < 6; ++i) {
				pbm::free_bitmap(&bmp[i]);
			}
		}
		return 0;
	}

}

#endif