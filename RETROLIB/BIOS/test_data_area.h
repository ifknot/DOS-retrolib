/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      16.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DATA_AREA_H
#define TEST_DATA_AREA_H

#include "../TEST/debug_macros.h"

#include "bios_data_area_services.h"

namespace test_data_area {

	void run() {
		{
			INFO("test data area services\nWAIT..");
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_COM1), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_COM2), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_COM3), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_COM4), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_LPT1), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_LPT2), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_LPT3), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_IO_LPT4), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_EBDA_ADDR), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_HARDWARE_FLAGS), std::hex);
			LOG_AS( bios::read_BDA<int16_t>(BDA_LOW_MEMORY_SIZE), std::dec);
			LOG_AS( bios::read_BDA<int8_t>(BDA_DISPLAY_MODE), std::dec);
			LOG_AS( bios::read_BDA<int16_t>(BDA_COLS_TEXT_MODE), std::dec);
			LOG_AS( bios::read_BDA<int8_t>(BDA_HARD_DISK_NUM), std::dec);
			LOG_AS( bios::read_BDA<int32_t>(BDA_DAILY_TIMER), std::dec);
			INFO("PASS!\n");
		}
	}

}

#endif