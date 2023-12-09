/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_MEM_ARENA_H
#define TEST_MEM_ARENA_H

#include "../TEST/debug_macros.h"

#include "mem_arena.h"

namespace test_mem_arena {

	void run() {
		INFO("* testing memory arena services...");
		mem::arena::arena_t* arena;
		if (YESNO("* 221\tmake 1K arena ?")) {
			INFO("arena = mem::arena::new_dos_arena(1024)");
			arena = mem::arena::new_dos_arena(1024);
			LOG(*arena);
			LOG(mem::arena::size(arena));
			LOG(mem::arena::capacity(arena));
			ASSERT(mem::arena::delete_dos_arena(arena),==,1024,"Memory Leak!");
		}

		if (YESNO("* 221\tmake 64K arena ?")) {
			INFO("arena = mem::arena::new_dos_arena(65535)");
			arena = mem::arena::new_dos_arena(65535);
			LOG(*arena);
			LOG(mem::arena::delete_dos_arena(arena));
		}

		if (YESNO("* 222\t request too large DOS")) {
			arena = mem::arena::new_dos_arena(655350);
			LOG(*arena);
			LOG(mem::arena::delete_dos_arena(arena));
		}

		if (YESNO("* 223\t request too large ARENA ?")) {
			INFO("arena = mem::arena::new_dos_arena(1026)");
			arena = mem::arena::new_dos_arena(1026);
			LOG(*arena);
			LOG_AS((uint32_t)mem::arena::raw_alloc(arena, 1024), std::hex);
			LOG(*arena);
			INFO("* request too large ARENA using template function");
			LOG_AS((uint32_t)mem::arena::alloc<mem::address_t>(arena, 40), std::hex);
			LOG(*arena);
			LOG(mem::arena::delete_dos_arena(arena));
		}

		if (YESNO("* 224\t dealloc mem in ARENA ?")) {
			INFO("arena = mem::arena::new_dos_arena(1024)");
			arena = mem::arena::new_dos_arena(1024);
			LOG(*arena);
			LOG_AS((uint32_t)mem::arena::raw_alloc(arena, 500), std::hex);
			LOG(*arena);
			LOG_AS((uint32_t)mem::arena::raw_dealloc(arena, 250), std::hex);
			LOG(*arena);
			LOG_AS((uint32_t)mem::arena::raw_alloc(arena, 50), std::hex);
			LOG(*arena);
			LOG(mem::arena::delete_dos_arena(arena));
		}

		INFO("* Mop up any mistakes...");
		ASSERT(mem::arena::delete_dos_arena(arena),==,0,"Memory Leak!");
	}

}

#endif