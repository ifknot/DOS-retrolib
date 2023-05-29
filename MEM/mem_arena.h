/**
 *  @brief Bulk memory block management using memory allocation and deallocation.
 *  Memory aquired via C, divvied out and then freed all at once when no longer needed.
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
#ifndef MEM_ARENA_H
#define MEM_ARENA_H

#include "mem_contstants.h"
#include "mem_types.h"

#include "../DOS/dos.h"

#define MDOS_TAG 0x534F444D		// "MDOS" ascii hex NB little endian
#define CMEM_TAG 0x4D454D43		// "CMEM" ie using C malloc and free
#define VOID_TAG 0x44494F56		// "VOID"	

namespace mem {

	struct arena_t {

		char* ptr;
		size_t pos;
		uint32_t capacity;
		uint32_t size;
		uint32_t type;

	};

	template<typename T>
	T* arena_alloc(arena_t* arena, uint32_t capacity) {
		assert(arena->type != VOID_TAG && "Invalid arena type, uninitialized!");
		assert(capacity > 0 && "Invalid request, capacity = 0!");
		uint32_t byte_count = sizeof(T) * capacity;
		assert(byte_count <= arena->size && "Arena not enough space for request!");
		T* p = (T*)(arena->ptr + arena->pos);
		arena->pos += byte_count;
		arena->size -= byte_count;
		return p;
	}

	arena_t new_arena(uint32_t byte_count = MEM_MAX_ARENA_BYTES) {
		
		return mem::arena_t();
	}

	void free_arena(arena_t& arena) {
		assert(arena.ptr);
		
	}

	void init_arena(
		arena_t* arena,
		// arena default values 
		char* ptr = NULL,
		size_t pos = 0,
		uint32_t capacity = 0,
		uint32_t size = 0,
		uint32_t type = VOID_TAG
	) {
		assert(arena);
		arena->ptr = ptr;
		arena->pos = pos;
		arena->capacity = capacity;
		arena->size = size;
		arena->type = type;
	}

	/**
	* Bulk memory block management using DOS memory allocation and deallocation.
	*/
	arena_t* new_arena_using_DOS (uint32_t byte_count = MEM_MAX_ARENA_BYTES) {
		assert(byte_count <= MEM_MAX_ARENA_BYTES && "DOS memory managed arena limited to 64K bytes!");
		size_t paragraphs = byte_count / PARAGRAPH_SIZE;
		if (byte_count & 0xF != 0) {	// if mod 16 then need another paragraph for the remainder
			paragraphs++;
		}
		dos::address_t addr(dos::allocate_memory_blocks(paragraphs), 0);
		arena_t* arena = new arena_t;
		assert(arena);
		init_arena(arena, (char*)addr.ptr, 0, byte_count, byte_count, MDOS_TAG);
		return arena;
	}

	void free_arena_using_DOS(arena_t* arena) {
		assert(arena->ptr && "Void memory arena ptr!");
		assert(arena->type == MDOS_TAG && "Invalid arena type, not created with DOS!");
		dos::address_t addr(arena->ptr);
		bool success = dos::free_allocated_memory_blocks(addr.memloc.segment);
		assert(success && "DOS failed to free memory block!");
		arena->ptr = NULL;
		arena->pos = 0;
		arena->capacity = arena->size = 0;
		arena->type = VOID_TAG;
	}

}

std::ostream& operator<< (std::ostream& os, const mem::arena_t& arena) {
	dos::address_t addr(arena.ptr);
	os << "start ptr\t" << addr << '\n'
		<< "alloc pos\t" << arena.pos << '\n'
		<< "capacity\t" << arena.capacity << '\n'
		<< "size    \t" << arena.size << '\n';
	char* name = (char*)&arena.type;
	os << "type    \t" << name[0] << name[1] << name[2] << name[3] << '\n';
	return os;
}



#endif