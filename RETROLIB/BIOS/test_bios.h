#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "bios_clock_services.h"
#include "bios_memory_services.h"

// TODO:
// [?] AT time bios functions
// [ ] printEBDA()

//#define ENABLE_EBDA

namespace test_bios {

	int run() {
		INFO(__FUNCTION__);
		{
			INFO("test XT clock services\nWAIT...");
			LOG(bios::read_system_clock_counter());
			LOG(bios::is_24_hours_since_reset());
			bios::set_system_clock_counter(1);
			INFO("bios::set_system_clock_counter(1)");
			uint32_t t = bios::read_system_clock_counter();
			ASSERT( t == 1, t, 0);
			LOG(bios::read_system_clock_counter());
			INFO("PASS!\n");
		}
		{
			INFO("test AT clock services\nWAIT...");
			ASSERT(bios::is_rtc_working(), bios::is_rtc_working(), 1);
			char time[9] = "  -  -  ";
			bios::bcd_time_t t;		
			bios::read_rtc_clock(&t);
			INFO("bios::read_rtc_clock(&t)");
			LOG_AS(t.time, std::hex);		
			bios::convert_bcd_time_to_string(&t, time);
			INFO("bios::convert_bcd_time_to_string(&t, time)");
			LOG(time);
			std::cout << (int)t.hmsd[3] << '\n';
			bios::convert_string_to_bcd_time("10:12:20", 0, &t);
			INFO("bios::convert_string_to_bcd_time(\"10:12:20\", false, &t)");
			LOG_AS(t.time, std::hex);
			bios::set_rtc_clock(&t);
			INFO("bios::set_rtc_clock(&t)");
			bios::read_rtc_clock(&t);
			INFO("bios::read_rtc_clock(&t)");
			LOG_AS(t.time, std::hex);
			bios::convert_bcd_time_to_string(&t, time);
			INFO("bios::convert_bcd_time_to_string(&t, time)");
			LOG(time);
			INFO("PASS!\n");
		}
		{
			INFO("test memory services\nWAIT...");
			LOG(bios::get_low_memory_size());
			std::cout << std::hex;
			LOG(bios::get_ram_segment_top());
			//LOG(bios::get_ebda_segment());
			//LOG(bios::get_ebda_size());
			INFO("PASS!\n");
		}
		return 0;
	}

}

#endif 