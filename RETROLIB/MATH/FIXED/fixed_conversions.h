/*!
 *  @file fixed_conversions.h
 *  @brief Declares the fixed conversions.
 *  @details ~
 *  @author Jeremy Thornton
 *  @date 2024-07-27
 *  @copyright © Jeremy Thornton. All right reserved.
 *  
 */
#ifndef FIXED_CONVERSIONS_H
#define FIXED_CONVERSIONS_H

#include <stdint.h>

#include "fixed_types.h"
#include "fixed_constants.h"

namespace math {

	namespace fixed {

		Q10_6_t saturate(int32_t n);

		UQ10_6_t saturate(uint32_t n);

		int16_t truncate(Q10_6_t n);

		uint16_t truncate(UQ10_6_t n);

		float convert_to_float(Q10_6_t n);

		float convert_to_float(UQ10_6_t n);

		Q10_6_t round_to_Q10_6_t(float f);

		UQ10_6_t round_to_UQ10_6_t(float f);

	}

}

#endif