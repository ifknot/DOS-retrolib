/*!
 *  @file fixed_types.h
 *  @brief Fixed point mathematics designed for DOS gaming upto and including XGA
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
 *  @author Jeremy Thornton
 *  @date 2024-07-27
 *  @copyright © Jeremy Thornton. All right reserved.
 */
#ifndef FIXED_TYPES_H
#define FIXED_TYPES_H

#include <stdint.h>

namespace math {

	/*!
	 * The Q notation consists of the letter Q followed by a pair of numbers m.n
	 * where m is the number of bits used for the integer part of the value, and n is the number of fraction bits.
	 * By default, the notation describes signed binary fixed point format, with the unscaled integer being stored in two's complement format, used in most binary processors.
	 * The first bit always gives the sign of the value(1 = negative, 0 = non-negative), and it is not counted in the m parameter. Thus, the total number w of bits used is 1 + m + n.
	 */
	namespace fixed {

		typedef uint16_t UQ10_6_t;
		typedef int16_t Q10_6_t;

	}

}

TODO:
// << and >> 

#endif // !FIXED_TYPES_H
