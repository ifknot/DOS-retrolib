/**
 *
 *  @file      timer_xt_tick_services.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TIMER_XT_TICK_SERVICES_H
#define TIMER_XT_TICK_SERVICES_H

#include <stdint.h>

#include "timer_constants.h"

namespace system {

	/**
	 * Read System Clock Counter
	 * INT 1A,0 - Read System Clock Counter
	 * AH = 00
	 * on return:
	 * AL = midnight flag, 1 if 24 hours passed since reset
	 * CX = high order word of tick count
	 * DX = low order word of tick count
	 * incremented approximately 18.206 times per second
	 * at midnight CX:DX is zero
	 * \return 
	 */
	uint32_t read_clock_counter() {
		uint16_t hi, lo;
		uint32_t ticks_since_midnight;
		__asm {
			push	ax
			push	cx
			push	dx

			mov		ah, READ_SYSTEM_CLOCK_COUNTER
			int		BIOS_RTC
			mov		hi, cx
			mov		lo, dx

			pop		dx
			pop		cx
			pop		ax
		}
		ticks_since_midnight = hi;
		ticks_since_midnight <<= 16;
		ticks_since_midnight |= lo;
		return ticks_since_midnight;
	}

	/**
	 * INT 1A,1 - Set System Clock Counter
	 * AH = 01
	 * CX = high order word of tick count
	 * DX = low order word of tick count
	 * \note There are approximately 1,573,040 (1800B0h) clock ticks per 24 hrs
	 * 
	 * \param ticks_since_midnight - should be set to the number of seconds past
	 * midnight multiplied by approximately 18.206
	 */
	void set_clock_counter(uint32_t ticks_since_midnight) {
		uint16_t hi, lo;
		lo = ticks_since_midnight;
		hi = ticks_since_midnight >> 16;
		__asm {
			push	ax
			push	cx
			push	dx

			mov		ah, SET_SYSTEM_CLOCK_COUNTER
			mov		cx, lo
			mov		dx, hi
			int		BIOS_RTC

			pop		dx
			pop		cx
			pop		ax
		}
	}

	/**
	 * \brief Wait in 18th of a second (55ms) chunks (approximately)
	 *
	 * Uses BIOS Get System Time - Int 1Ah AH = 00h
	 * Return: CX:DX = number of clock ticks since midnight
	 * AL = midnight flag, nonzero if midnight passed since time last read.
	 * \note 1. 1000ms per second
	 * \note 2. There are approximately 18.2 clock ticks per second, 1800B0h per 24 hrs
	 * (except on Tandy 2000, where the clock runs at 20 ticks per second).
	 * IBM and many clone BIOSes set the flag for AL rather than incrementing it
	 * leading to loss of a day if two consecutive midnights pass without a request
	 * for the time (e.g. if the system is on but idle).
	 * Since the midnight flag is cleared, if an application calls this function after
	 * midnight before DOS does, DOS will not receive the midnight flag and will fail to
	 * advance the date. Modern releases of MS-DOS/PC DOS (5.0+???) assume that AL is a
	 * day rollover counter rather than a flag, as expected by older releases.
	 * DOS 5 - 7.10 (Windows 98 SE) provide an undocumented CONFIG.SYS SWITCHES=/T option
	 * to force the old behaviour of the day advancing code, that is using a flag instead
	 * of a counter.. DR DOS 3.31 - DR-DOS 7.03 handle AL as a flag.
	 *
	 * \param n
	 */
	inline void wait_a_tick(uint16_t n = 1) {
		if (n > 0) {
			uint32_t t = read_clock_counter() + n;
			while (read_clock_counter() <= t) {}
		}
	}

}

#endif