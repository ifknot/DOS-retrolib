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
			INFO("test hamming_wegner_64");
			uint64_t b = 0;// 0xFFFFEEEEDDDD0000;
			while (b != 0xFF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t hw = abm::hamming_wilkes_wheeler_gill(b);
				std::cout << hw << ", ";
				//td::cout << b << ' ' << hw << '\n';
				//ASSERT(abm::hamming_wegner_64(&b) == hw, abm::hamming_wegner_64(&b));
				b++;
			}
		}
		{
			INFO("test hamming_lookup_64");
			uint64_t b = 0x0;
			while (b <= 0xFF) {
				uint16_t hw = abm::hamming_wilkes_wheeler_gill(b);
				std::cout << b << ' ' << hw << '\n';
				ASSERT(abm::hamming_lookup_64(&b) == hw, abm::hamming_lookup_64(&b));
				b++;
			}
		}
		return 0;
	}

}

#endif