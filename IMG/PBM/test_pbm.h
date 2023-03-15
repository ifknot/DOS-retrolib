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
#include "../../FSYS/fsys_read_dsv.h"
#include "pbm.h"

namespace test_pbm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test Portable Bit Map\n");

			const int n = 20; 

			const char data_path[] = "CHESS/FILES.csv";
			char fpaths[20][MAX_LINE_SIZE];
			if (fsys::read_csv(data_path, fpaths, n) == STDIO_FAIL) {
				LOG(data_path);
				LOG(strerror(errno));
			}

			pbm::bitmap_t bmp[n];
			for (int i = 0; i < n; ++i) {
				if (pbm::load_bitmap(fpaths[i], &bmp[i]) == STDIO_FAIL) {
					std::cout << strerror(errno) << std::endl;
					exit(EXIT_FAILURE);
				}
			}
			for (int i = 0; i < n; ++i) {
				std::cout << bmp[i];
				getchar();
			}
			for (int i = 0; i < n; ++i) {
				pbm::free_bitmap(&bmp[i]);
			}
		}
		return 0;
	}

}

#endif