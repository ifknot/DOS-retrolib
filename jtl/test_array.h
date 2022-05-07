/**
 *
 *  @file      test_array.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      29.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_ARRAY_H
#define TEST_ARRAY_H

#include <iostream>
#include <cassert>

#include "array.h"

namespace test_array {

	void run() {
		std::cout << "test_array... ";
		{
			// test Implicitly-defined member functions
			{
				jtl::array<int, 3> a = { 1,2,3 };
				for (int i = 0; i < a.size(); ++i) assert(a[i] == i + 1);
			}
			// test element access
			{
				// operator[]
				jtl::array<int, 4> numbers = { 2, 4, 6, 8 };
				assert(numbers[1] == 4);
				numbers[0] = 5;
				assert(numbers[0] == 5);
				// front
				jtl::array<char, 6> letters = { 'a', 'b', 'c', 'd', 'e', 'f' };
				assert(letters.front() == 'a');
				letters.front() = 'A';
				assert(letters.front() == 'A');
				// back
				assert(letters.back() == 'f');
				letters.back() = 'F';
				assert(letters.back() == 'F');
				// data
				assert(*letters.data() == 'A');
				assert(*(letters.data() + 3) == 'd');
			}
			// capacity
			{
				// empty
				jtl::array<int, 4> numbers = { 3, 1, 4, 1 };
				jtl::array<int, 0> no_numbers;
				assert(!numbers.empty());
				assert(no_numbers.empty());
				// size
				assert(numbers.size() == 4);
				assert(no_numbers.size() == 0);
			}
			// operations
			{
				// fill
				typedef jtl::array<unsigned char, 8> Cell;
				jtl::array<Cell, 4> board;
				Cell row = { 0xDC,0xDF,0xDC,0xDF,0xDC,0xDF,0xDC,0xDF };
				board.fill(row);

				std::cout << '\n';
				for (jtl::size_t i = 0; i < board.size(); ++i) {
					for (jtl::size_t j = 0; j < board.front().size(); ++j) {
						std::cout << board[i][j];
					}
					std::cout << '\n';
				}
				// swap
				jtl::array<int, 3> a = { 1,2,3 };
				jtl::array<int, 3> b = { 4,5,6 };
				a.swap(b);
				a.dump();
				b.dump();
				//for (int i = 0; i < a.size(); ++i) assert(a[i] == i + 4);
				//for (int i = 0; i < b.size(); ++i) assert(a[i] == i + 1);

			}
		}
		std::cout << "success!\n";
	}

}

#endif