#ifndef TEST_RND_H
#define TEST_RND_H

#include <cassert>
#include <iostream>

#include "../DEBUG/debug_macros.h"

#include "rnd_splitmix64.h"

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