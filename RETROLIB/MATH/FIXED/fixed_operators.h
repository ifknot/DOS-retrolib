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
	UQ10_6_t result;
	__asm {
		mov 	ax, lhs
		add 	ax, rhs 
		bcc 	END
		mov 	ax, UQ_SATURATE
END:		mov 	result, ax
	}
	return result;
}

/*!
* overflow flag is set, if carry_flag != sign_flag for addends of the same sign. 
* ie addition/subtraction of two negative numbers can be interpreted positive or adding two positive numbers can be interpreted as negative. 
* For addends of different sign (3) + (-2) overflow doesn't happen.
*/
Q10_6_t operator + (Q10_6_t lhs, Q10_6_t rhs) {
	Q10_6_t result;
	char flags;
	FZ = FX = FN = FO = 0;
	__asm {
		mov 	ax, lhs
		add 	ax, rhs 
		//jno 	END
		lahf  
		mov 	flags, AH
END:		mov 	result, ax
	}
	LOG(((int)flags);
	return result;
}

UQ10_6_t operator - (UQ10_6_t lhs, UQ10_6_t rhs) {
	return lhs - rhs;
}

#endif
