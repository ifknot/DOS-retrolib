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
#define Q_INTEGER_UMAX		1023
#define Q_INTEGER_MAX		511
#define Q_INTEGER_MIN		-512
#define Q_FRACTIONAL_MIN	0.015873

#define UQ_SATURATE   0xFFFF
#define Q_SATURATE    0x7FFF
#define Q_MAX         0x7FFF
#define Q_MIN         0x8000

#endif
