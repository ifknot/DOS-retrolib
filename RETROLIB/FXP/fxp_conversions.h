/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef FXP_CONVERSION_H
#define FXP_CONVERSION_H

#include "fxp_types.h"

namespace fxp {

	void round_to_ufixed_t(ufixed_t* x, float f);

	void uconvert_to_float(float* f, ufixed_t x);

	void truncate_to_uint16_t(uint16_t* i, ufixed_t x);

	void round_to_uint16_t(uint16_t* i, ufixed_t x);


	void round_to_fixed_t(fixed_t* x, float f);

	void convert_to_float(float* f, fixed_t x);

	void truncate_to_int16_t(int16_t* i, fixed_t x);

	void round_to_int16_t(int16_t* i, fixed_t x);

}

#endif