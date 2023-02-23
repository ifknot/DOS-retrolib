#ifndef TEST_RND_H
#define TEST_RND_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

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
			for(int i = 0; i < 5; ++i) LOG(prng());
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif