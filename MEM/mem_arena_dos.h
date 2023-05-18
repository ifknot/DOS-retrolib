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
#ifndef MEM_ARENA_DOS_H
#define MEM_ARENA_DOS_H

#include "mem_constants.h"
#include "mem_types.h"

namespace mem {

	template<typename T>
	T* arena_alloc_dos(arena* m, uint16_ size) {

	}

}

#endif