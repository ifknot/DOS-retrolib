#ifndef TEST_ABM_H
#define TEST_ABM_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "abm_popcnt.h"



namespace test_abm {

	int run() {
		INFO(__FUNCTION__);
		{/*
			INFO("test hamming_wegner_64\nWAIT...");
			uint64_t b = 0;// 0xFFFFEEEEDDDD0000;
			while (b != 0xFF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t hw = abm::hamming_wilkes_wheeler_gill(b);
				std::cout << b << ' ' << hw << '\n';
				ASSERT(abm::hamming_wegner_64(&b) == hw, abm::hamming_wegner_64(&b));
				b++;
			}
			std::cout << "PASS!\n";
		*/}
		{
			INFO("test hamming_lookup_64\nWAIT...");
			uint64_t b = 0xA0A0A0A0A0A0A0A0;
			while (b <= 0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(b);
				uint16_t obs = abm::hamming_lookup_64(&b);
				//std::cout << obs << ' ' << exp << '\n';
				ASSERT( obs == exp, abm::hamming_lookup_64(&b), abm::hamming_wilkes_wheeler_gill(b));
				b++;
			}
			std::cout << "PASS!\n";
		}
		
		return 0;
	}

}

#endif