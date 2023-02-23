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

			dos::segmented_memory_block<uint8_t> cells8(16);
			cells8.fill('A');
			cells8.dump();
			std::cout << "capacity " << cells8.capacity() << '\n'
				<< "bytes " << cells8.bytes() << '\n'
				<< "paragraphs " << cells8.paragraphs() << '\n';

			dos::segmented_memory_block<uint16_t> cells16(16);
			cells16.fill(0x4142);
			cells16.dump();
			std::cout << std::hex << cells16[15] << '\n';
			std::cout << "capacity " << cells16.capacity() << '\n'
				<< "bytes " << cells16.bytes() << '\n'
				<< "paragraphs " << cells16.paragraphs() << '\n';

			dos::segmented_memory_block<uint32_t> cells32(16);
			cells32.fill(0x41424344);
			cells32[15] = 0x44434241;
			cells32.dump();
			std::cout << std::hex << cells32[15] << '\n';
			std::cout << "capacity " << cells32.capacity() << '\n'
				<< "bytes " << cells32.bytes() << '\n'
				<< "paragraphs " << cells32.paragraphs() << '\n';
		}
		std::cout << "success!\n";
	}

}

#endif