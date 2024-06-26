/**
 *
 *  @file      fxp_conversions.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.06.2024
 *  @copyright � Jeremy Thornton, 2024. All right reserved.
 *
 */
#include "fxp_conversions.h"
#include "fxp_constants.h"
#include "fxp_types.h"

#include <math.h>
#include <assert.h>

namespace fxp {

	void round_to_ufixed_t(ufixed_t* x, float f) {
		uint16_t i = (uint16_t)f;
		assert(i <= FXP_INTEGER_UNSIGNED_MAX);
		*x = i;
		*x <<= FXP_FRACTIONAL_BITS;					// shift the integral part left into integral bits
		f -= i;										// remove the integral part
		if (f) assert(f >= FXP_FRACTIONAL_MIN);		// conversion fails
		*x |= (uint16_t)round(f * FXP_DENOMINATOR); // OR in the lower 5 bit fractional part as rounded 
	}

	void uconvert_to_float(float* f, ufixed_t x) {
		*f = (x & FXP_DENOMINATOR);					// mask off integer part
		*f /= FXP_DENOMINATOR;						// convert to fraction
		*f += (x >> FXP_FRACTIONAL_BITS);			// add integral part
	}

	void truncate_to_uint16_t(uint16_t* i, ufixed_t x) {
		*i = x >> FXP_FRACTIONAL_BITS;
	}

	void round_to_uint16_t(uint16_t* i, ufixed_t x) {
		*i = x >> FXP_FRACTIONAL_BITS;
		x &= FXP_DENOMINATOR;
		if (x > 31) *i += 1;
	}


	void round_to_fixed_t(fixed_t* x, float f) {
		int16_t i = (int16_t)f;
		assert(FXP_INTEGER_SIGNED_MIN <= i);
		assert(i <= FXP_INTEGER_SIGNED_MAX);
		*x = i;
		*x <<= FXP_FRACTIONAL_BITS;					// shift the integral part left into integral bits
		f -= i;										// remove the integral part
		i = (int16_t)round(f * FXP_DENOMINATOR);	// fraction of denominator
		*x += i;									// add in the lower 5 bit fractional part as rounded 
	}

	void convert_to_float(float* f, fixed_t x) {
		*f = (x & FXP_DENOMINATOR);					// mask off integer part
		*f /= FXP_DENOMINATOR;						// convert to fraction
		*f += (x >> FXP_FRACTIONAL_BITS);			// add integral part
	}

	void truncate_to_int16_t(int16_t* i, fixed_t x) {
		*i = x >> FXP_FRACTIONAL_BITS;
	}

	void round_to_int16_t(int16_t* i, fixed_t x) {
		*i = x >> FXP_FRACTIONAL_BITS;
		x &= FXP_DENOMINATOR;
		if (x > 31) *i += 1;
	}

}

