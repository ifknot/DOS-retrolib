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
		if (YESNO("* 110\t Test fixed point maths ?")) {
			fxp::ufixed_t a, b;
			fxp::fixed_t x, y;
			float f, g;
			uint16_t i;
			int16_t j;
			while (YESNO("unsigned multiply?")) {
				printf("? ");
				scanf("%f", &f);
				printf("? ");
				scanf("%f", &g);
				fxp::round_to_ufixed_t(&a, f);
				fxp::round_to_ufixed_t(&b, g);
				LOG(a);
				LOG(b);
				fxp::umul(&a, b);
				LOG(a);
				fxp::uconvert_to_float(&f, a);
				LOG(f);
			}
			while (YESNO("signed multiply?")) {
				printf("? ");
				scanf("%f", &f);
				printf("? ");
				scanf("%f", &g);
				fxp::round_to_fixed_t(&x, f);
				fxp::round_to_fixed_t(&y, g);
				LOG(x);
				LOG(y);
				fxp::mul(&x, y);
				LOG(x);
				fxp::convert_to_float(&f, x);
				LOG(f);
			}
		}
		if (YESNO("* 110\t Test fixed point conversions ?")) {
			fxp::ufixed_t a, b;
			fxp::fixed_t x, y;
			float f, g;
			uint16_t i;
			int16_t j;
			while (YESNO("unsigned convert a float?")) {
				scanf("%f", &f);
				fxp::round_to_ufixed_t(&a, f);
				LOG(a);
				fxp::uconvert_to_float(&f, a);
				LOG(f);
				fxp::truncate_to_uint16_t(&i, a);
				LOG(i);
				fxp::round_to_uint16_t(&i, a);
				LOG(i);
			}
			while (YESNO("signed convert a float?")) {
				scanf("%f", &f);
				fxp::round_to_fixed_t(&x, f);
				LOG(x);
				fxp::convert_to_float(&f, x);
				LOG(f);
				fxp::truncate_to_int16_t(&j, x);
				LOG(j);
				fxp::round_to_int16_t(&j, x);
				LOG(j);
			}
		}
	}

}

#endif