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

namespace test_data_area {

	void run() {
		{
			INFO("test data area services\nWAIT..");
			LOG(bios::read_data_area<int32_t>(BIOS_DATA_AREA_TIMER));
			INFO("PASS!\n");
		}
	}

}

#endif