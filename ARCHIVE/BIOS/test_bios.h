#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "bios_clock_services.h"
#include "bios_memory_services.h"

// TODO:
// [?] AT time bios functions
// [ ] printEBDA()

//#define ENABLE_EBDA

namespace test_bios {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test clock services\nWAIT...");
			LOG(bios::read_system_clock_counter());
			LOG(bios::is_24_hours_since_reset());
			bios::set_system_clock_counter(0);
			uint32_t t = bios::read_system_clock_counter();
			ASSERT( t == 0, t, 0);
			LOG(bios::read_system_clock_counter());
			INFO("PASS!\n");
		}
		{
			INFO("test clock memory services\nWAIT...");
			LOG(bios::get_low_memory_size());
			std::cout << std::hex;
			LOG(bios::get_ram_segment_top());
			//LOG(bios::get_ebda_segment());
			//LOG(bios::get_ebda_size());
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif 