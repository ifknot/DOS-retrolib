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
			ASSERT(abm::hamming_wegner_64(&b) == 0, abm::hamming_wegner_64(&b));
			b = 0xF;
			ASSERT(abm::hamming_wegner_64(&b) == 4, abm::hamming_wegner_64(&b));
			b = 0xFF;
			ASSERT(abm::hamming_wegner_64(&b) == 8, abm::hamming_wegner_64(&b));
			b = 0xFFFF;
			ASSERT(abm::hamming_wegner_64(&b) == 16, abm::hamming_wegner_64(&b));
			b = 0xFFFFFFFF;
			ASSERT(abm::hamming_wegner_64(&b) == 32, abm::hamming_wegner_64(&b));
			b = 0xFFFFFFFFFFFFFFFF;
			ASSERT(abm::hamming_wegner_64(&b) == 64, abm::hamming_wegner_64(&b));
			b = 0xA;
			ASSERT(abm::hamming_wegner_64(&b) == 2, abm::hamming_wegner_64(&b));
			b = 0xAA;
			ASSERT(abm::hamming_wegner_64(&b) == 4, abm::hamming_wegner_64(&b));
			b = 0xAAAA;
			ASSERT(abm::hamming_wegner_64(&b) == 8, abm::hamming_wegner_64(&b));
			b = 0xAAAAAAAA;
			ASSERT(abm::hamming_wegner_64(&b) == 16, abm::hamming_wegner_64(&b));
			b = 0xAAAAAAAAAAAAAAAA;
			ASSERT(abm::hamming_wegner_64(&b) == 32, abm::hamming_wegner_64(&b));
			
		}
		return 0;
	}

}

#endif