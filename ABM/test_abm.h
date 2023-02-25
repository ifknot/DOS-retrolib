#ifndef TEST_ABM_H
#define TEST_ABM_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "../RND/rnd_splitmix64.h"

#include "../BIOS/bios_clock_services.h"

#include "abm_population_count.h"
#include "abm_trailing_zeros_count.h"
#include "abm_leading_zeros_count.h"

#define TIMINGS

namespace test_abm {

	int run() {
		rnd::splitmix64<1234567> prng;
		INFO(__FUNCTION__);
		{
			INFO("test lzcnt_lookup_64\nWAIT...");
			uint64_t b = 0x0000000000000000;// 0xFFFFEEEEDDDD0000;
			while (b <=  0x000000000000000F) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::leading_zeros(b);
				uint16_t obs = abm::lzcnt_lookup_64(&b);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::lzcnt_lookup_64(&b), abm::leading_zeros(b));
				b += 1;
			}
			for (int i = 0; i < 500; ++i) {
				uint64_t r = prng();
				uint16_t exp = abm::leading_zeros(r);
				uint16_t obs = abm::lzcnt_lookup_64(&r);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::lzcnt_lookup_64(&b), abm::leading_zeros(b));
			}
			std::cout << "PASS!\n";
		}
#ifdef TIMINGS
		{
			INFO("time abm::leading_zeros... ");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 500; ++i) {
				uint16_t exp = abm::leading_zeros(i);
			}
			LOG(bios::read_system_clock_counter());
			INFO("time abm::lzcnt_lookup_64...");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 500; ++i) {
				uint16_t exp = abm::lzcnt_lookup_64(&i);
			}
			LOG(bios::read_system_clock_counter());
		}
#endif
		{
			INFO("test tzcnt_lookup_64\nWAIT...");
			uint64_t b = 0x0;// 0xFFFFEEEEDDDD0000;
			while (b <= 0xFFFFFF) { //0xFFFFFFFFFFFFFFFF) {
				uint16_t exp = abm::trailing_zeros(b);
				uint16_t obs = abm::tzcnt_lookup_64(&b);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::tzcnt_lookup_64(&b), abm::trailing_zeros(b));
				b += 0x8000;
			}
			for (int i = 0; i < 500; ++i) {
				uint64_t r = prng();
				uint16_t exp = abm::trailing_zeros(r);
				uint16_t obs = abm::tzcnt_lookup_64(&r);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::tzcnt_lookup_64(&b), abm::trailing_zeros(b));
			}
			std::cout << "PASS!\n";
		}
#ifdef TIMINGS
		{
			INFO("time abm::trailing_zeros... ");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				uint16_t exp = abm::trailing_zeros(i);
			}
			LOG(bios::read_system_clock_counter());
			INFO("time abm::tzcnt_lookup_64...");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				uint16_t exp = abm::tzcnt_lookup_64(&i);
			}
			LOG(bios::read_system_clock_counter());
		}
#endif
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
			for (int i = 0; i < 500; ++i) {
				uint64_t r = prng();
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(r);
				uint16_t obs = abm::hamming_wegner_64(&r);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::hamming_wegner_64(&b), abm::hamming_wilkes_wheeler_gill(b));
			}
			std::cout << "PASS!\n";
		}
#ifdef TIMINGS
		{
			INFO("time abm::hamming_wilkes_wheeler_gill... ");
			uint64_t r;
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				r = prng();
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(r);
			}
			LOG(bios::read_system_clock_counter());
			INFO("time abm::hamming_wegner_64...");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				r = prng();
				uint16_t exp = abm::hamming_wegner_64(&r);
			}
			LOG(bios::read_system_clock_counter());
		}
#endif
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
			for (int i = 0; i < 500; ++i) {
				uint64_t r = prng();
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(r);
				uint16_t obs = abm::hamming_lookup_64(&r);
				//std::cout << "| " << obs << ' ' << exp << ", ";
				ASSERT(obs == exp, abm::hamming_lookup_64(&b), abm::hamming_wilkes_wheeler_gill(b));
			}
			std::cout << "PASS!\n";
		}
#ifdef TIMINGS
		{
			INFO("time abm::hamming_wilkes_wheeler_gill... ");
			uint64_t r;
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				r = prng();
				uint16_t exp = abm::hamming_wilkes_wheeler_gill(r);
			}
			LOG(bios::read_system_clock_counter());
			INFO("time abm::hamming_lookup_64...");
			bios::set_system_clock_counter(0);
			for (uint64_t i = 0; i < 1000; ++i) {
				r = prng();
				uint16_t exp = abm::hamming_lookup_64(&r);
			}
			LOG(bios::read_system_clock_counter());
		}
#endif
		return 0;
	}

}

#endif