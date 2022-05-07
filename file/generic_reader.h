/**
 *
 *  @file      generic_reader.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef GENERIC_READER_H
#define GENERIC_READER_H

#include <stdint.h>

namespace jtl {

	template< typename T>
	struct generic_reader {


		/**
		*  @brief	Attempts to read size number of type T into the specified data buffer.
		*  @warning No bounds checking!
		*  @note	maximum 64K types T 
		*  @note	
		*  @param  data<T>[]	destination buffer 
		*  @param  size			number of elements type T (max 64K)
		*  @retval				true on successful read, false on any fail
		*/
		virtual bool read(T* data, const uint16_t size) = 0;

		virtual ~reader() {}

	};

}

#endif