/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef FXP_TOOLBOX_H
#define FXP_TOOLBOX_H

#include "fxp_types.h"

namespace fxp {

	void round_to_ufixed_t(ufixed_t* x, float f);

	void convert_to_float(float* f, ufixed_t x);

	void truncate_to_uint16_t(uint16_t* i, ufixed_t x);

	void round_to_uint16_t(uint16_t* i, ufixed_t x);

}

#endif