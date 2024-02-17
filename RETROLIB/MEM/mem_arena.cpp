/**
 *
 *  @file      mem_arean.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_arena.h"

#include <stdint.h>

#include "../DOS/dos.h"

#include "../TEST/debug_macros.h"

namespace mem {

	namespace arena {

		struct arena_t {	// 128 bytes

			char* pfree;				// pointer to the start of free memory pool
			mem_size_t size;			// current amount of free memory (bytes) pool 	

			address_t pool;				// base address of the DOS memory block used by the arena pool
			mem_size_t capacity;		// starting size of the memory (bytes) pool

		};

		/**
		* The DOS INT 21,48 - Allocate Memory function takes a 16 bit word size request in paragraphs (16 bytes)
		* and returns a memory segment address as a 16 bit value.
		* Because the request is a 16 bit word the, *theoretical*, maximum number of paragraphs requestable to
		* allocate is 65535 paragraphs or 65535 x 16 = 1048560 bytes.
		* Which is 16 bytes, one paragraph, less than 1 Mebibyte (MiB)
		* @note 1MiB Max the original 8086/8088 microprocessors' 20-bit address bus can address 1,048,576 bytes.
		* However, the actual amount of allocatable RAM is restricted 640K or less (+ possible upper memory area)
		* and will depend on installed RAM.
		*/
		arena_t* new_dos_arena(mem_size_t byte_count) {
			arena_t* arena = new(arena_t);
			arena->pfree = NULL_PTR;								// setup default values...
			arena->pool.memloc = arena->size = arena->capacity = 0;
			mem_size_t paragraphs = byte_count / PARAGRAPH_SIZE;	// calculate the number of paragraphs to request fron DOS
			if (byte_count % PARAGRAPH_SIZE) {		// if mod 16 then need another paragraph for the remainder
				paragraphs++;
			}
			arena->pool.segoff.segment = dos::allocate_memory_blocks(paragraphs);	// ask DOS for the memory 
			if (arena->pool.segoff.segment) {						// success DOS could fulfill the memory request				
				arena->pfree = (char*)arena->pool.memloc;			// initialize values...
				arena->size = arena->capacity = paragraphs * PARAGRAPH_SIZE;
			}

#ifndef NDEBUG

			else {
				std::cout << "ERROR memory request too large for DOS to provide!";
			}

#endif
			return arena;
		}

		mem_size_t delete_dos_arena(arena_t* arena) {
			mem_size_t sz = arena->capacity;						// capture the capacity of the arena
			dos::free_allocated_memory_blocks(arena->pool.segoff.segment);	// ask DOS to free the memory block
			delete arena;											// free up arena_t memory
			return sz;												// return amount freed up
		}

		mem_size_t size(arena_t* arena) {
			return arena->size;
		}

		mem_size_t capacity(arena_t* arena) {
			return arena->capacity;
		}

		char* raw_alloc(arena_t* arena, mem_size_t byte_request) {
			char* p = NULL_PTR;						// default return to null
			if (byte_request <= arena->size) {		// can fulfill request 
				arena->size -= byte_request;		// shrink pool size
				p = arena->pfree;					// initialize return value points to requested block
				arena->pfree += byte_request;		// now point to the start of remaining free memory 
			}
#ifndef NDEBUG
			else {
				std::cout << "ERROR memory request too large for ARENA to ALLOC!\nLargest block of memory available = " << std::dec << arena->size << " bytes." << std::endl;
			}
#endif			
			return p;
		}

		char* raw_dealloc(arena_t* arena, mem_size_t byte_request) {
			char* p = NULL_PTR;						// default return to null
			if (byte_request <= arena->capacity) {	// can fulfill request 
				arena->size += byte_request;		// grow pool size
				arena->pfree -= byte_request;		// now point to the start of enlarged free memory
				p = arena->pfree;					// initialize return value points to resized pool 
			}
#ifndef NDEBUG
			else {
				std::cout << "ERROR memory request too large for ARENA to DEALLOC!\nLargest block of memory available = " << std::dec << arena->capacity << " bytes." << std::endl;
			}
#endif			
			return p;
		}

	}

}

std::ostream& operator<< (std::ostream& os, const mem::arena::arena_t& arena) {
	os << std::hex << (uint32_t)arena.pfree << ','
		<< std::dec << arena.size << ','
		<< arena.capacity;
	return os;
}