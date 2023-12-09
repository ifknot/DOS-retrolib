/**
 *
 *  @brief     The memory arena paradigm - one lifetime to bind them all.
 *  @details   Untangling lifetimes with absurdly simple linear allocator, lightning fast allocation and 
 *  deallocation, eliminating lifetime soup of per-allocation freeing/stack fragility/garbage collection requirements.
 *  Memory Arena the area where dynamic runtime memory is stored. 
 *  The memory arena consists of the heap and unused memory. 
 *  The heap is where all user-allocated memory is located. 
 *  The heap grows up from a lower memory address to a higher memory address.
 *  synonyms: region, zone, arena, area, or memory context.
 *  @note *By design* unable to free individual allocated memory blocks *only* the whole backing memory block arena 
 *  @url https://www.youtube.com/watch?v=3IAlJSIjvH0&t=4s
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_ARENA_H
#define MEM_ARENA_H

#include "mem_constants.h"

#include <iostream>

namespace mem {

	namespace arena {

		struct arena_t;

		arena_t* new_dos_arena(mem_size_t byte_count);

		mem_size_t delete_dos_arena(arena_t* arena);

		mem_size_t size(arena_t* arena);

		mem_size_t capacity(arena_t* arena);

		char* raw_alloc(arena_t* arena, mem_size_t byte_request);

		char* raw_dealloc(arena_t* arena, mem_size_t byte_request);

		template<typename T>
		T* alloc(arena_t* arena, mem_size_t type_count) {
			return (T*)raw_alloc(arena, sizeof(T) * type_count); 
		}

		template<typename T>
		T* dealloc(arena_t* arena, mem_size_t type_count) {
			return (T*)raw_dealloc(arena, sizeof(T) * type_count);
		}

	}

}

std::ostream& operator<< (std::ostream& os, const mem::arena::arena_t& arena);

#endif