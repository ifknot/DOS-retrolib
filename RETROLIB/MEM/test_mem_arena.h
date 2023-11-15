/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_MEM_ARENA_H
#define TEST_MEM_ARENA_H

#include "../TEST/debug_macros.h"

#include "mem_arena.h"

namespace test_mem_arena {

	void run() {
		INFO("* testing memory arena services...");
		mem::arena::dos_arena_t* p = mem::arena::new_dos_arena(1024);
		LOG(mem::arena::available(p));
		LOG(mem::arena::total(p));
		delete p;
	}

}

#endif