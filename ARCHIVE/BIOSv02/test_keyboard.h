/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_KEYBOARD_H
#define TEST_KEYBOARD_H

#include <iostream>

#include "../TEST/debug_macros.h"

#include "bios_keyboard_services.h"

namespace test_keyboard {

	void run() {
		{
			INFO("\ntest keyboard press each key 3 times - 'Q' to quit...\n");
			uint16_t s = 0;
			while ((s & 0xFF) != 'Q') {
				s= bios::wait_key();
				char k1 = s;
				uint16_t s1 = s >> 8;
				std::cout << k1 << ' ' << s1 << std::endl;
				char k2 = bios::wait_key_ascii();
				std::cout << k2 << std::endl;
				ASSERT(k1 == k2, k2, k1);
				uint16_t s2 = bios::wait_key_scan_code();
				std::cout << s2 << std::endl;
				ASSERT(s1 == s2, s2, s1);
			}
		}
	}

}

#endif