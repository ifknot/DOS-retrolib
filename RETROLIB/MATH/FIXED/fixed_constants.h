/*!
 *  @file fixed_constants.h
 *  @brief Declares the fixed constants.
 *  @details ~
 *  @author Jeremy Thornton
 *  @date 2024-07-27
 *  @copyright © Jeremy Thornton. All right reserved.
 *  
 */
#ifndef FIXED_CONSTANTS_H
#define FIXED_CONSTANTS_H

#define Q_INTEGRAL_BITS		10
#define Q_FRACTIONAL_BITS	6
#define Q_FRACTIONAL_MASK	0x3F		// 0000000000.111111
#define UQ_INFINITY			0xFFFF		// 1111111111.111111
#define Q_INFINITY			0x7FFF		// 0111111111.111111
#define Q_NINFINITY			0x8000		// 1000000000.000000
#define UQ_MAXINT			1023
#define Q_MAXINT			511
#define Q_MININT			-512
#define Q_FRACTIONAL_MIN	0.015873	// 0000000000.000001


#endif
