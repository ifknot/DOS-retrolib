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
			uint64_t b = 0xFFFFEEEEDDDD0000;
			while (b++ <= 0xFFFFFFFFFFFFFFFF) {
				uint16_t hw = abm::hamming_wilkes_wheeler_gill(b);
				std::cout << b << ' ' << hw << '\n';
				ASSERT(abm::hamming_wegner_64(&b) == hw, abm::hamming_wegner_64(&b));
			}
		}
		return 0;
	}

}

#endif