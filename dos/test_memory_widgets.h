/**
 *
 *  @file      test_memory_widgets.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.03.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_MEMORY_WIDGETS_H
#define TEST_MEMORY_WIDGETS_H

#include <iostream>
#include <cassert>

#include "dos_segmented_memory_block.h"

namespace test_memory_widgets {

	void run() {
		std::cout << "test_memory_widgets... ";
		// test segmented_memory_block
		{
			dos::segmented_memory_block<uint8_t> m(1);
			assert(m.size == 16);
			m.debug();
			m.clear();
			for (int i = 0; i < m.size; ++i) { assert(m[i] == 0); }
			m.clear('B');
			for (int i = 0; i < m.size; ++i) { assert(m[i] == 'B'); }
			m[8] = 'A';
			assert(m[8] == 'A');
		}
		std::cout << "success!\n";
	}

}

#endif