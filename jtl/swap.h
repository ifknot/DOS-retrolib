/**
 *
 *  @file      swap.h
 *  @brief     Exchange values of two objects
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      13.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef SWAP_H
#define SWAP_H

namespace jtl {

	/**
	*  @brief  Exchanges the values of a and b.
	*  @tparam T 
	*  @param  a 
	*  @param  b 
	*/
	template <typename T> 
	void swap(T& a, T& b) {
		T temp = a;
		a = b;
		b = temp;
	}

}

#endif