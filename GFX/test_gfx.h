/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef	TEST_GFX_H
#define TEST_GFX_H

#include "../TEST/debug_macros.h"

#include "gfx.h"

namespace test_gfx {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test bitmap_t\n");
			
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif