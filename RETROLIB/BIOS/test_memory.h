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

namespace test_memory {

	void  run() {
		{
			INFO("test memory services\nWAIT...");
			LOG(bios::get_low_memory_size());
			LOG(bios::read_data_area<int16_t>(BIOS_DATA_AREA_MEMORY));
			LOG_AS(bios::get_ram_segment_top(), std::hex);
			//LOG(bios::get_ebda_segment());
			//LOG(bios::get_ebda_size());
			INFO("PASS!\n");
		}
	}

}

#endif