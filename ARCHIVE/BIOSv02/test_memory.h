/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      16.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_MEMORY_H
#define TEST_MEMORY_H

#include "../TEST/debug_macros.h"

#include "bios_memory_services.h"

namespace test_memory {

	void  run() {
		{
			INFO("test memory services\nWAIT...");
			LOG(bios::get_low_memory_size());
			LOG(bios::read_BDA<int16_t>(BDA_LOW_MEMORY_SIZE));
			LOG_AS(bios::get_ram_top_segment(), std::hex);
			LOG(bios::get_ebda_segment());
			LOG(bios::read_BDA<int16_t>(BDA_IO_LPT4));
			LOG(bios::get_ebda_size());
			INFO("PASS!\n");
		}
	}

}

#endif