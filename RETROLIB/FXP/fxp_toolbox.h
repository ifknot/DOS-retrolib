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

	/**
	* Convert a float to an unsigned fixed
	* @note fractional part precision is lost below minimum granularity i.e. (0.0159 / 2)
	*/
	void as_ufixed_t(ufixed_t* x, float f);

	/**
	* Convert an unsigned fixed to a float 
	*/
	void as_float(float* f, ufixed_t x);

}

#endif