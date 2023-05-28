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
			LOG(a1);
			//int* p = mem::arena_alloc<int>(&a1, 20);
			//mem::free_arena_using_DOS(a1);
			//mem::arena_t a2 = mem::make_arena_using_DOS(MEM_MAX_ARENA_BYTES + 1);
			mem::arena_t a2 = mem::make_arena_using_DOS();
			LOG(a2);
			//char* p = mem::arena_alloc<char>(&a2, MEM_MAX_ARENA_BYTES + 1);
			//char* p = mem::arena_alloc<char>(&a2, 0);
			//char* p = mem::arena_alloc<char>(&a2, MEM_MAX_ARENA_BYTES);
			char* p = mem::arena_alloc<char>(&a2, 10);
			LOG_AS((uint32_t)p, std::hex);
			LOG(a2);
			p = mem::arena_alloc<char>(&a2, 10);
			LOG_AS((uint32_t)p, std::hex);
			LOG(a2);
			mem::arena_t* i = mem::arena_alloc<mem::arena_t>(&a2, 1);
			LOG_AS((uint32_t)i, std::hex);
			LOG(sizeof(mem::arena_t));
			LOG(a2);
			p = mem::arena_alloc<char>(&a2, 10);
			LOG_AS((uint32_t)p, std::hex);
			LOG(a2);
			mem::free_arena_using_DOS(a2);
			LOG(a2);
			//p = mem::arena_alloc<char>(&a2, 10);
		}

		return EXIT_SUCCESS;
	}

}

#endif // !TEST_MEM_H
