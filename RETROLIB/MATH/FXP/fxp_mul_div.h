/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      26.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef FXP_MUL_DIV_H
#define FXP_MUL_DIV_H

#include "fxp_types.h"

namespace fxp {

	void umul(ufixed_t* x, ufixed_t y);

	void mul(fixed_t* x, fixed_t y);

	void udiv(ufixed_t* x, ufixed_t y);

	void div(fixed_t* x, fixed_t y);


}

#endif