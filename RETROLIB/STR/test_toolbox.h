/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      5.12.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_TOOLBOX_H
#define TEST_TOOLBOX_H

#include <stdint.h>

#include "../TEST/debug_macros.h"
#include "../MEM/mem.h"

#include "str_toolbox.h"

namespace test_toolbox {

	void run() {
		INFO("* testing string toolbox...");
		char src[] = { "P4\n# Created by GIMP version 2.10.34 PNM plug - in\n720 348\n" };
		char dst[64] = {"                                                               "};
		mem::address_t addr_src, addr_dst;
		addr_src.memloc = (uint32_t)&src;
		addr_dst.memloc = (uint32_t)&dst;
		if (YESNO("* 610\tcopy convert upper ?")) {
			LOG(str::copy_convert_to_upper(src, dst, 5, 11));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
			std::cout << std::endl;
			LOG(str::copy_convert_to_upper(src, dst));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
		}
		if (YESNO("* 620\tcopy convert lower ?")) {
			LOG(str::copy_convert_to_lower(src, dst, 16, 19));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
			std::cout << std::endl;
			LOG(str::copy_convert_to_lower(src, dst));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
		}
		if (YESNO("* 630\tin place upper ?")) {
			LOG(str::in_place_to_upper(dst, 5, 11));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
			std::cout << std::endl;
			LOG(str::in_place_to_upper(dst));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
		}
		if (YESNO("* 640\tin place lower  ?")) {
			LOG(str::in_place_to_lower(dst, 16, 19));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
			std::cout << std::endl;
			LOG(str::in_place_to_lower(dst));
			mem::dump_ostream(std::cout, addr_dst, sizeof(dst));
		}
		if (YESNO("* 650\tskip line  ?")) {
			int pos = str::ignore_line(src, str::ignore_line(src));
			LOG(src[pos]);
		}
		if (YESNO("* 660\tskip white space  ?")) {
			LOG(str::skip_white_space(dst));
			LOG(str::skip_white_space(dst, 4));
		}
	}

}

#endif