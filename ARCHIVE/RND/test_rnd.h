#ifndef TEST_RND_H
#define TEST_RND_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "rnd_splitmix64.h"

// TODO:
// [x] splitmix64 https://rosettacode.org/wiki/Pseudo-random_numbers/Splitmix64
// [ ] xorshift32 (asm) https://en.wikipedia.org/wiki/Xorshift
// [?] xorshift64 https://stackoverflow.com/questions/53886131/how-does-xorshift32-works
// [?] rnd::crypto::xorshift128

namespace test_rnd {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test splitmix64\nWAIT...");
			rnd::splitmix64<1234567> prng;
			uint64_t exp[5] = { // expected first five integers generated using the seed 1234567
				6457827717110365317,
				3203168211198807973,
				9817491932198370423,
				4593380528125082431,
				16408922859458223821
			};
			for (int i = 0; i < 5; ++i) {
				uint64_t r = prng();
				ASSERT(r == exp[i], r, exp[i]);
				LOG(r);
			}
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif