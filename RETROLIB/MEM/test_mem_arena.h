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
		mem::arena::arena_t* p = mem::arena::new_dos_arena(1024);

		LOG(*p);
		LOG(mem::arena::size(p));
		LOG(mem::arena::capacity(p));
		mem::arena::delete_dos_arena(p);
		LOG(*p);

		p = mem::arena::new_dos_arena(65535);
		LOG(*p);
		mem::arena::delete_dos_arena(p);
		LOG(*p);

		p = mem::arena::new_dos_arena(655350);
		LOG(*p);
		mem::arena::delete_dos_arena(p);
		LOG(*p);

		INFO("p = mem::arena::new_dos_arena(1026)");
		p = mem::arena::new_dos_arena(1026);
		LOG(*p);
		LOG_AS((uint32_t)mem::arena::raw_alloc(p, 1024), std::hex);
		LOG(*p);
		LOG_AS((uint32_t)mem::arena::alloc<mem::address_t>(p, 40), std::hex);
		LOG(*p);

		mem::arena::delete_dos_arena(p);
		LOG(*p);

		delete p;
	}

}

#endif