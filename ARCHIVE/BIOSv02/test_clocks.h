/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      16.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_CLOCKS_H
#define TEST_CLOCKS_H

#include "../TEST/debug_macros.h"

#include "bios_data_area_services.h"
#include "bios_clock_services.h"

namespace test_clocks {

	void run() {
		if (YESNO("XT clocks?")) {
			INFO("test XT clock services\nWAIT...");
			LOG(bios::read_system_clock_counter());
			assert(bios::read_system_clock_counter() == bios::read_BDA<int32_t>(BDA_DAILY_TIMER));
			LOG(bios::is_24_hours_since_reset());
			bios::set_system_clock_counter(1);
			INFO("bios::set_system_clock_counter(1)");
			uint32_t t = bios::read_system_clock_counter();
			ASSERT(t == 1, t, 0);
			assert(bios::read_system_clock_counter() == bios::read_BDA<int32_t>(BDA_DAILY_TIMER));
			INFO("PASS!\n");
		}
		if (YESNO("AT clocks?")) {
			INFO("test AT clock services\nWAIT...");
			ASSERT(bios::is_rtc_working(), bios::is_rtc_working(), 1);
			char time[9] = "  -  -  ";
			std::cout << time << '\n';
			bios::bcd_time_t t;
			bios::read_rtc_time(&t);
			INFO("bios::read_rtc_clock(&t)");
			LOG_AS(t.time, std::hex);

			bios::convert_bcd_time_to_string(&t, time);
			INFO("bios::convert_bcd_time_to_string(&t, time)");
			LOG(time);
			std::cout << time << '\n';
			std::cout << (int)t.hmsd[3] << '\n';	// daylight savings time?

			bios::convert_string_to_bcd_time("10:12:20", &t);
			INFO("bios::convert_string_to_bcd_time(\"10:12:20\", &t)");
			if (YESNO("Enter a new time?")) {
				std::cin >> t;
			}
			LOG_AS(t.time, std::hex);
			bios::set_rtc_time(&t);
			INFO("bios::set_rtc_clock(&t)");

			bios::read_rtc_time(&t);
			INFO("bios::read_rtc_clock(&t)");
			LOG_AS(t.time, std::hex);
			bios::convert_bcd_time_to_string(&t, time);
			INFO("bios::convert_bcd_time_to_string(&t, time)");
			LOG(time);

			INFO("PASS!\n");
		}
		if (YESNO("AT DATES?")) {
			INFO("test AT date services\nWAIT...");
			char date[9] = "  -  -  ";
			bios::bcd_date_t d;
			bios::read_rtc_date(&d);
			INFO("bios::read_rtc_date(&d)");
			LOG_AS(d.date, std::hex);

			bios::convert_bcd_date_to_string(&d, date);
			INFO("bios::convert_bcd_date_to_string(&d, date)");
			LOG(date);
			std::cout << date << '\n';

			bios::convert_string_to_bcd_date("01/02/86", &d);
			INFO("bios::convert_string_to_bcd_date(\"11/02/86\", &d);");
			if (YESNO("Enter a new date?")) {
				std::cin >> d;
			}
			LOG_AS(d.date, std::hex);
			//bios::set_rtc_date(&d);
			INFO("bios::set_rtc_date(&d);");

			INFO("PASS!\n");
		}
	}

}

#endif