/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      13.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_FSYS_H
#define TEST_FSYS_H

#include <string.h>
#include <stdlib.h>

#include "fsys_read_dsv.h"

namespace test_fsys {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test read_csv\n");
			const char data_path[] = "CHESS/FILES.csv";
			char fpaths[19][MAX_LINE_SIZE];
			if (fsys::read_csv(data_path, fpaths, 19) == STDIO_FAIL) {
				LOG(data_path);
				LOG(strerror(errno));
			}
			for (int i = 0; i < 19; ++i) {
				std::cout << fpaths[i] << '\n';
			}
			free(fpaths);
		}
		return 0;
	}

}

#endif