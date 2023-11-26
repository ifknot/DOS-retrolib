/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      25.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_HGA_H
#define TEST_HGA_H

#include "../../TEST/debug_macros.h"

#include "hga.h"

namespace test_hga {

	void run() {
		INFO("* testing HGA functions...");		
		if (YESNO("* 431\ttest set HGA graphics mode ?")) {
			hga::graphics_mode();
			hga::graphics::cls(0xAA);
		}
		if (YESNO("* 432\ttest set HGA text mode ?")) {
			hga::text_mode();
			hga::cls('X', hga::BLACK_ON_GREEN);
		}
	}

}

#endif