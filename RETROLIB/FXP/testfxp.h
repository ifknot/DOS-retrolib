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
			fxp::fixed_t y;
			float f;
			uint16_t i;
			int16_t j;
			while (YESNO("unsigned convert a float?")) {
				scanf("%f", &f);
				fxp::round_to_ufixed_t(&x, f);
				LOG(x);
				fxp::convert_to_float(&f, x);
				LOG(f);
				fxp::truncate_to_uint16_t(&i, x);
				LOG(i);
				fxp::round_to_uint16_t(&i, x);
				LOG(i);
			}
			while (YESNO("signed convert a float?")) {
				scanf("%f", &f);
				fxp::round_to_fixed_t(&y, f);
				LOG(y);
				fxp::convert_to_float(&f, y);
				LOG(f);
				fxp::truncate_to_int16_t(&j, y);
				LOG(j);
				INFO("**********");
				fxp::round_to_int16_t(&j, y);
				LOG(j);
			}
		}
	}

}

#endif