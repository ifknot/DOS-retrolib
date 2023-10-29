/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DOS_MEMORY_H
#define TEST_DOS_MEMORY_H

#include <iostream>

#include "../TEST/debug_macros.h"

#include "../MEM/mem_dump_ostream.h"
#include "../MEM/mem_address.h"

#include "dos.h"

namespace test_dos_memory {

	void run() {
		uint16_t seg_mem_1K = 0;
		uint16_t seg_mem_2K = 0;
		
		INFO("* allocate 1K");
		seg_mem_1K = dos::allocate_memory_blocks(64); // 1024K bytes == 64 x paragraphs (16 bytes per paragraph)
		INFO("seg_mem_1K = dos::allocate_memory_blocks(64)");
		LOG_AS(seg_mem_1K, std::hex);
		ASSERT(seg_mem_1K != 0, seg_mem_1K, seg_mem_1K);

		mem::address_t mcb_1k; // set it up to point to the paragraph preceding the one returned
		mcb_1k.segoff.segment = seg_mem_1K - 1;
		mcb_1k.segoff.offset = 0;
		ASSERT(*(char*)mcb_1k.void_ptr == 'M', *(char*)mcb_1k.void_ptr, 'M');
		INFO("* MCB dump");
		mem::dump_ostream(std::cout, mcb_1k, 16);
		
		INFO("* allocate 2K");
		seg_mem_2K = dos::allocate_memory_blocks(128); // 2K
		INFO("seg_mem_2K = dos::allocate_memory_blocks(128)");
		LOG_AS(seg_mem_2K, std::hex);
		ASSERT(seg_mem_2K != 0, seg_mem_2K, seg_mem_2K);

		mem::address_t mcb_2k;
		mcb_2k.segoff.segment = seg_mem_2K - 1;
		mcb_2k.segoff.offset = 0;
		ASSERT(*(char*)mcb_2k.void_ptr == 'M', *(char*)mcb_2k.void_ptr, 'M');
		INFO("* MCB dump");
		mem::dump_ostream(std::cout, mcb_2k, 16);

		INFO("* free 2K");
		ASSERT(dos::free_allocated_memory_blocks(seg_mem_2K) == 0, 0, 0);
		LOG(dos::free_allocated_memory_blocks(seg_mem_2K));

		INFO("* free 1K");
		ASSERT(dos::free_allocated_memory_blocks(seg_mem_1K) == 0, 0, 0);
		LOG(dos::free_allocated_memory_blocks(seg_mem_1K));

		INFO("* allocate 2K at old 1K address");
		seg_mem_2K = dos::allocate_memory_blocks(128); // 2K
		INFO("seg_mem_2K = dos::allocate_memory_blocks(128)");
		LOG_AS(seg_mem_2K, std::hex);
		ASSERT(seg_mem_2K == seg_mem_1K, seg_mem_2K, seg_mem_2K);

		INFO("* try and free same 1K again");
		LOG(dos::free_allocated_memory_blocks(seg_mem_1K)); // should error out re-free freed

		INFO("* try free invalid MCB");
		LOG(dos::free_allocated_memory_blocks(seg_mem_1K + 1)); // should error out invalid MCB

		INFO("* try allocate too much");
		LOG(dos::allocate_memory_blocks(40960)); // All 640K - should error out

	}

}

#endif