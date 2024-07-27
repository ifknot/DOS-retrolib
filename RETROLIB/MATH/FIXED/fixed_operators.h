/*!
 *  @file fixed_operators.h
 *  @brief Declares the fixed operators.
 *  @details ~
 *  @author Jeremy Thornton
 *  @date 2024-07-27
 *  @copyright © Jeremy Thornton. All right reserved.
 *  
 */
#ifndef FIXED_OPERATORS_H
#define FIXED_OPERATORS_H

#include "fixed_types.h"

using namespace math::fixed;

UQ10_6_t operator + (UQ10_6_t lhs, UQ10_6_t rhs) {
	return lhs + rhs;
}

UQ10_6_t operator - (UQ10_6_t lhs, UQ10_6_t rhs) {
	return lhs - rhs;
}

#endif