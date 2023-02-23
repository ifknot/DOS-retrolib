#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "bios_clock_services.h"

namespace test_bios {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test clock services\nWAIT...");
			std::cout << bios::read_system_clock_counter() << '\n';
			bios::set_system_clock_counter(0);
			std::cout << bios::read_system_clock_counter() << '\n';
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif 