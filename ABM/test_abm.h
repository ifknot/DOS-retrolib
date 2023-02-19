#ifndef TEST_ABM_H
#define TEST_ABM_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "abm_popcnt.h"

namespace test_abm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test popcnt64");
			uint64_t b = 0;
			ASSERT(abm::popcnt64(&b) == 0, abm::popcnt64(&b));
			b = 0xF;
			ASSERT(abm::popcnt64(&b) == 4, abm::popcnt64(&b));
			b = 0xFF;
			ASSERT(abm::popcnt64(&b) == 8, abm::popcnt64(&b));
			b = 0xFFFF;
			ASSERT(abm::popcnt64(&b) == 16, abm::popcnt64(&b));
			b = 0xFFFFFFFF;
			ASSERT(abm::popcnt64(&b) == 32, abm::popcnt64(&b));
			b = 0xFFFFFFFFFFFFFFFF;
			ASSERT(abm::popcnt64(&b) == 64, abm::popcnt64(&b));
			b = 0xA;
			ASSERT(abm::popcnt64(&b) == 2, abm::popcnt64(&b));
			b = 0xAA;
			ASSERT(abm::popcnt64(&b) == 4, abm::popcnt64(&b));
			b = 0xAAAA;
			ASSERT(abm::popcnt64(&b) == 8, abm::popcnt64(&b));
			b = 0xAAAAAAAA;
			ASSERT(abm::popcnt64(&b) == 16, abm::popcnt64(&b));
			b = 0xAAAAAAAAAAAAAAAA;
			ASSERT(abm::popcnt64(&b) == 32, abm::popcnt64(&b));
			
		}
		return 0;
	}

}

#endif