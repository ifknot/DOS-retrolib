/**
 *
 *  @brief     Bulk memory block management using DOS memory allocation and deallocation.
 *  Memory aquired via DOS, divvied out and then freed all at once when no longer needed.
 *  @note *By design* unable to free individual allocated memory blocks *only* the whole backing memory block arena 
 *  @details   Memory Arena the area where dynamic runtime memory is stored. 
 *  The memory arena consists of the heap and unused memory. 
 *  The heap is where all user-allocated memory is located. 
 *  The heap grows up from a lower memory address to a higher memory address.
 *  synonyms: region, zone, arena, area, or memory context.
 *  @url https://www.youtube.com/watch?v=3IAlJSIjvH0&t=4s
 *  @author    Jeremy Thornton
 *  @date      18.05.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef MEM_DOS_ARENA_H
#define MEM_DOS_ARENA_H

#include "../DOS/dos.h"

#include "mem_arena.h"
#include "mem_contstants.h"

namespace mem {

	arena_t make_arena_using_DOS(size_t bytes = MEM_MAX_ARENA_BYTES) {
		size_t paragraphs = bytes / PARAGRAPH_SIZE;
		if (bytes & 0xF != 0) {	// if mod 16 then need another paragraph for the remainder
			paragraphs++;
		}
		dos::address_t addr(dos::allocate_memory_blocks(paragraphs), 0);
		mem::arena_t arena;
		arena.memory = (uint32_t)addr.address;
		arena.alloc_position = arena.memory;
		arena.capacity = bytes;
		arena.size = arena.capacity;
	}

}

#endif