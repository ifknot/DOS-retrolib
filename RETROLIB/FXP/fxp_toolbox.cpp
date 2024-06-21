/**
 *
 *  @file      fxp_toolbox.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#include "fxp_toolbox.h"
#include "fxp_constants.h"
#include "fxp_types.h"
#include "fxp_errors.h"

#include <math.h>
#include <assert.h>

#include "../TEST/debug_macros.h"

namespace fxp {

	void as_ufixed_t(ufixed_t* x, float f) {
		uint16_t i = (uint16_t)f;
		assert(i < FXP_INTEGER_UNSIGNED_MAX);
		*x = i;
		*x <<= FXP_FRACTION_BITS;					// shift the integer part left into integral bits
		f -= i;										// remove the integer part
		i = (uint16_t)round(f * FXP_DENOMINATOR);	// convert to a fraction of the denominator
		assert(i);
		*x |= i;									// OR in the lower fractional rounded part
	}

	void as_float(float* f, ufixed_t x) {
		*f = (x & FXP_DENOMINATOR);					// mask off integer part
		*f /= FXP_DENOMINATOR;						// convert to fraction
		*f += (x >> FXP_FRACTION_BITS);				// add integral part
	}

}