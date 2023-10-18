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

#include "bios_keyboard_services.h"

namespace test_keyboard {

	void run() {
		std::cout << "\ntest keyboard - 'Q' to quit...\n";
		{
			uint8_t k = 0;
			while (k != 'Q') {
				k = bios::wait_key_ascii();
				std::cout << k << std::endl;
			}
		}
		std::cout << "success!\n";
	}

}

#endif