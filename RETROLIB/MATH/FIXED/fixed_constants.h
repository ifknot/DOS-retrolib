/*!
 *  @file fixed_constants.h
 *  @brief Declares the fixed constants.
 *  @details ~
 *  @author Jeremy Thornton
 *  @date 2024-07-27
 *  @copyright © Jeremy Thornton. All right reserved.
 *  
 */
#ifndef FIXED_CONSTANTS_H
#define FIXED_CONSTANTS_H

#include "fixed_types.h"

#define FIXED_INTEGRAL_BITS			10
#define FIXED_FRACTIONAL_BITS		6
#define FIXED_DENOMINATOR			0x3F
#define FIXED_INTEGER_UNSIGNED_MAX	1023
#define FIXED_INTEGER_SIGNED_MAX	511
#define FIXED_INTEGER_SIGNED_MIN	-512
#define FIXED_FRACTIONAL_MIN		0.015873

namespace math {

	namespace fixed {

		const Q10_6_t PI = 201; // this is 3.14 as 10:6 fixed point notation

	}

}

#endif