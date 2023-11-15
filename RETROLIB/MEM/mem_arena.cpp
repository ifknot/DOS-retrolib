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

		struct arena_t {

			char* top;
			address_t mcb;
			mem_size_t size;
			mem_size_t capacity;

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
			arena_t* p = new(arena_t);
			p->top = NULL_PTR;
			p->size = p->capacity = 0;
			mem_size_t paragraphs = byte_count / PARAGRAPH_SIZE;
			if (byte_count % PARAGRAPH_SIZE) {	// if mod 16 then need another paragraph for the remainder
				paragraphs++;
			}
			p->mcb.segoff.segment = dos::allocate_memory_blocks(paragraphs);
			p->mcb.segoff.offset = 0;
			p->top = (char*)p->mcb.memloc;
			if (p->top) {
				p->capacity = paragraphs * PARAGRAPH_SIZE;
				p->size = p->capacity;
			}
			return p;
		}

		void delete_dos_arena(arena_t* arena) {
			dos::free_allocated_memory_blocks(arena->mcb.segoff.segment);
			arena->top = NULL_PTR;
			arena->mcb.memloc = arena->size = arena->capacity = 0;
		}

		char* raw_alloc(arena_t* arena, mem_size_t byte_request) {
			char* p = NULL_PTR;
			if (byte_request <= arena->size) {
				arena->size -= byte_request;
				p = arena->top;
				arena->top += byte_request;
			}
#ifndef NDEBUG
			else {
				std::cout << "mem::arena::error\tInsufficient memory\nlargest block of memory available = " << std::dec << arena->size << " bytes" << std::endl;
			}
#endif			
			return p;
		}

		mem_size_t size(arena_t* arena) { 
			return arena->size; 
		}

		mem_size_t capacity(arena_t* arena) { 
			return arena->capacity; 
		}

	}

}

std::ostream& operator<< (std::ostream& os, const mem::arena::arena_t& arena) {
	os << std::hex << (uint32_t)arena.top << ','
		<< std::dec << arena.size << ','
		<< arena.capacity;
	return os;
}