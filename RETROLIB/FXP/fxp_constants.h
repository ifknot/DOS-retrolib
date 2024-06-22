/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef FXP_CONSTANTS_H
#define FXP_CONSTANTS_H

#include "fxp_types.h"

#define FXP_INTEGRAL_BITS	10
#define FXP_FRACTIONAL_BITS	6
#define FXP_DENOMINATOR		0x3F
#define FXP_INTEGER_UNSIGNED_MAX	1023
#define FXP_INTEGER_SIGNED_MAX		511
#define FXP_INTEGER_SIGNED_MIN		-512
#define FXP_FRACTIONAL_MIN			0.015873

namespace fxp {

	const ufixed_t PI = 201;		// this is 3.14 as 11:6 fixed point notation

}

#endif