/**
 *
 *  @file      array.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      28.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>

#include "size_t.h"
#include "null_ptr_t.h"
#include "swap.h"

namespace jtl {

	template<typename T, size_t N>
	struct array {

		typedef T value_type;
		typedef size_t size_type;
		//typedef ptrdiff_t	difference_type
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		array& operator=(const array& other) {
			assert(size() == other.size());
            if (this != &other) { 
				for (size_type i = 0; i < size(); ++i) data_[i] = other.data_[i];
            }
            return *this;
		}

		inline reference operator[](size_type pos) {
			return data_[pos];
		}

		inline const_reference operator[](size_type pos) const {
			return data_[pos];
		}

		inline reference front() {
			return data_[0];
		}

		inline const_reference front() const {
			return data_[0];
		}

		inline reference back() {
			return data_[N - 1];
		}

		inline const_reference back() const {
			return data_[N - 1];
		}

		inline pointer data() {
			return data_;
		}

		inline size_type size() const {
			return N;
		}

		inline bool empty() const {
			return N == 0;
		}

		void clear() {
			for (size_type i = 0; i < size(); ++i) data_[i] = 0;
		}

		void fill(const value_type& value) {
			for (size_type i = 0; i < size(); ++i) data_[i] = value;
		}

		inline void swap(array& other) {
			array<T,N> temp = *this;
			*this = other;
			other = temp;
		}

		void dump() {
			for (size_type i = 0; i < size(); ++i) std::cout << data_[i] << ' ';
		}

	private:

		value_type data_[N];

	};

	template<typename T>
	struct array<T, 0> {

		typedef T value_type;
		typedef size_t size_type;
		//typedef ptrdiff_t	difference_type
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;

		inline size_type size() const {
			return 0;
		}

		inline bool empty() const {
			return true;
		}

		inline nullptr_t data() {
			return nullptr;
		}

		void dump() {
			std::cout << "the empty array";
		}

	};

}

#endif