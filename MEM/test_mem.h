#ifndef TEST_MEM_H
#define TETS_MEM_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "mem.h"

namespace test_mem {

	int run() {
		{
			INFO("0. test arena");
			mem::arena_t a1;
			std::cout << a1;
			mem::arena_t a2 = mem::make_arena_using_DOS();
			std::cout << a2;
			mem::free_arena_using_DOS(a2);
		}

		return EXIT_SUCCESS;
	}

}

#endif // !TEST_MEM_H
