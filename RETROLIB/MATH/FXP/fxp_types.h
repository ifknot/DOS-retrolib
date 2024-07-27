/**
 *
 *  @brief     Fixed point mathematics designed for DOS gaming upto and including XGA
 *  @details   Screen dimenisions likely in DOS games:
 *  + CGA4		320 x 200
 *  + CGA6		600 x 200 
 *  + HGA		720 x 348
 *  + VGA		640 x 480
 *  + SVGA		800 x 600
 *	+ XGA		1024 x 768
 *  For comparison "High Definition" HD is defined as:
 *  + HD720		1280 x 720
 *  + HD		1920 x 1080
 *  Choosing fixed point layout of 10:6 i.e. 10 bit integral and 6 bit fractional parts would give:
 *  ufixed (0 < n < 1023.63)
 *  fixed (-512.63 < n < 511.63)
 *  A fractional part of of 6 bits gives 1/63 resolution:
 *  + x range 0..1023 ie XGA 
 *  + 0.0159 of a pixel
 *  + PI rounded to 3dp 3.142
 *  + sin of 1 degree to 3dp 0.017
 *  @author    Jeremy Thornton
 *  @date      21.06.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef FXP_TYPES_H
#define FXP_TYPES_H

#include <stdint.h>

namespace fxp {

	typedef uint16_t ufixed_t;
	typedef int16_t fixed_t;

}

#endif