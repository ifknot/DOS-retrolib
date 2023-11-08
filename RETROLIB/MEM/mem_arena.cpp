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

namespace mem {

	struct dos_arena_t {

		char* ptr;
		mem_size_t top;
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
		uint16_t paragraphs = byte_count / PARAGRAPH_SIZE;
		if (byte_count & 0xF != 0) {	// if mod 16 then need another paragraph for the remainder
			paragraphs++;
		}
		//dos::address_t addr(dos::allocate_memory_blocks(paragraphs), 0);
		//arena_t* arena = new arena_t;
		//assert(arena);
		//init_arena(arena, (char*)addr.ptr, 0, byte_count, byte_count, MDOS_TAG);
		//return arena;
		//return 0;
	}

	namespace arena {

		mem_size_t available(dos_arena_t* arena) { return arena->available; }

		mem_size_t total(dos_arena_t* arena) { return arena->total; }

	}

}

//assert(byte_request <= available(arena) && "Arena not enough space for request!");