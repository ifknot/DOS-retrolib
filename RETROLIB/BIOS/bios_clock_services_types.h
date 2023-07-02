/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      17.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef BIOS_CLOCK_SERVICES_TYPES_H
#define BIOS_CLOCK_SERVICES_TYPES_H

#include <stdint.h>

namespace bios {

	typedef uint32_t tick_count_t;

	union bcd_time_t {

		uint32_t time;		// BCD hrs, mins, secs, daylight savings on/off
		uint8_t hmsd[4];	

	};

	union bcd_date_t {

		uint32_t date;		// BCD century, year, month, day
		uint8_t cymd[4];

	};

}

#endif