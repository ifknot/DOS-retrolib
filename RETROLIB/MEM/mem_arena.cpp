/**
 *
 *  @file      mem_arean.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "mem_arena.h"

#include <stdint.h>

#include "../DOS/dos.h"

#include "../TEST/debug_macros.h"

namespace mem {

	namespace arena {

		struct dos_arena_t {

			char* top_ptr;
			address_t mcb;
			mem_size_t available;
			mem_size_t total;

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
		dos_arena_t* new_dos_arena(mem_size_t byte_count) {
			dos_arena_t* p = new(dos_arena_t);
			p->top_ptr = NULL_PTR;
			p->available = p->total = 0;
			mem_size_t paragraphs = byte_count / PARAGRAPH_SIZE;
			LOG(byte_count);
			LOG(paragraphs);
			if (byte_count % PARAGRAPH_SIZE) {	// if mod 16 then need another paragraph for the remainder
				paragraphs++;
			}
			LOG(paragraphs);
			p->mcb.segoff.segment = dos::allocate_memory_blocks(paragraphs);
			p->mcb.segoff.offset = 0;
			p->top_ptr = (char*)p->mcb.memloc;
			LOG(p->mcb);
			LOG_AS((int)p->mcb.memloc, std::hex);
			LOG_AS((int)p->top_ptr, std::hex);
			if (p->top_ptr) {
				p->total = paragraphs * PARAGRAPH_SIZE;
				p->available = p->total;
			}
			return p;
		}

		void delete_dos_arena(dos_arena_t* p) {
			dos::free_allocated_memory_blocks(p->mcb.segoff.segment);
		}

		mem_size_t available(dos_arena_t* arena) { return arena->available; }

		mem_size_t total(dos_arena_t* arena) { return arena->total; }

	}

}
