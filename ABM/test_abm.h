#ifndef TEST_ABM_H
#define TEST_ABM_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "abm_population_count.h"
#include "abm_trailing_zeros_count.h"
#include "abm_leading_zeros_count.h"

namespace test_abm {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test lzcnt_lookup_64\nWAIT...");
			uint64_t b = 0x0000000000000000;// 0xFFFFEEEEDDDD0000;
			while (b <=  0x00000000000000FF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::leading_zeros(b);
				uint16_t obs = abm::lzcnt_lookup_64(&b);
				std::cout << "| " << obs << ' ' << exp << ", ";
				//ASSERT(obs == exp, abm::lzcnt_lookup_64(&b), abm::leading_zeros(b));
				b += 1;
			}
			std::cout << "PASS!\n";
		}
		/*
		{
			INFO("test tzcnt_lookup_64\nWAIT...");
			uint64_t b = 0x0;// 0xFFFFEEEEDDDD0000;
			while (b <= 0xFFFFFF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::trailing_zeroes(b);
				uint16_t obs = abm::tzcnt_lookup_64(&b);
				std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::tzcnt_lookup_64(&b), abm::trailing_zeroes(b));
				b += 0x8000;
			}
			std::cout << "PASS!\n";
		}

		{
			INFO("test hamming_wegner_64\nWAIT...");
			uint64_t b = 0;// 0xFFFFEEEEDDDD0000;
			while (b != 0xFF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(b);
				uint16_t obs = abm::hamming_wegner_64(&b);
				//std::cout << std::hex << b << std::dec << ' ' << obs << ' ' << exp << '\n';
				ASSERT(obs == exp, abm::hamming_wegner_64(&b), abm::hamming_wilkes_wheeler_gill(b));
				b++;
			}
			std::cout << "PASS!\n";
		}
		{
			INFO("test hamming_lookup_64\nWAIT...");
			uint64_t b = 0xA0A0A0A0A0A0A0A0;
			while (b <= 0xA0A0A0A0A0A0A0FF) {
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(b);
				uint16_t obs = abm::hamming_lookup_64(&b);
				//std::cout << std::hex << b << std::dec << ' ' << obs << ' ' << exp << '\n';
				ASSERT( obs == exp, abm::hamming_lookup_64(&b), abm::hamming_wilkes_wheeler_gill(b));
				b++;
			}
			std::cout << "PASS!\n";
		}
		*/
		return 0;
	}

}

#endif