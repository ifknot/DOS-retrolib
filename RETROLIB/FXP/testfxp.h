/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef TEST_FXP_H
#define TEST_FXP_H

#include "../TEST/debug_macros.h"

#include "fxp.h"

#include <stdio.h>

namespace test_fxp {

	void run() {
		INFO("* testing lib HGA graphics routines");
		if (YESNO("* 110\t Test fixed point maths ?")) {
			fxp::ufixed_t x;
			float f;
			while (YESNO("convert a float?")) {
				scanf("%f", &f);
				LOG(x);
				fxp::as_float(&f, x);
				LOG(f);
			}
		}
	}

}

#endif