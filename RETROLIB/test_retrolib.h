/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      27.10.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_RETROLIB_H
#define TEST_RETROLIB_H

#include <iostream>
		
//#include "TEST/test_debug_macros.h"				// 000
//#include "DOS/test_dos.h"							// 100
//#include "MEM/test_mem.h"							// 200
//#include "BIOS/test_bios.h"						// 300
//#include "GFX/test_gfx.h"							// 400
//#include "FILE/test_file.h"						// 500
//#include "STR/test_toolbox.h"						// 600
//#include "GFX/HGA/test_hga.h"						// 700
//#include "GFX/MDA/test_mda.h"						// 800
//#include "KBD/test_kbd.h"							// 900
#include "MATH/FIXED/test_fixed.h"

namespace test_retrolib {

	void run() {

		std::cout << "test functions..." << std::endl;
		//if (YESNO("* 000\ttest debug ?")) test_debug_macros::run();
		//if (YESNO("* 100\ttest DOS ?")) test_dos::run();
		//if (YESNO("* 200\ttest MEM ?")) test_mem::run();
		//if (YESNO("* 300\ttest BIOS ?")) test_bios::run();
		//if (YESNO("* 400\ttest GFX ?")) test_gfx::run();
		//if (YESNO("* 500\ttest FILE ?")) test_file::run();
		//if (YESNO("* 600\ttest STR ?")) test_toolbox::run();
		//if (YESNO("* 700\ttest HGA ?")) test_hga::run();
		//if (YESNO("* 800\ttest MDA ?")) test_mda::run();
		//if (YESNO("* 900\ttest KBD ?")) test_kbd::run();
		if (YESNO("* 800\ttest FXP ?")) test_fixed::run();

	}

}

#endif