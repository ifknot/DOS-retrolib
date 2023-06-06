/**
 *
 *  @file      bios_clock_services_constants.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BIOS_CLOCK_SERVICES_CONSTANTS_H
#define BIOS_CLOCK_SERVICES_CONSTANTS_H

#define BIOS_CLOCK_SERVICES			1Ah
// INT 1A,0   Read system clock counter
// INT 1A,1   Set system clock counter
#define READ_SYSTEM_CLOCK_COUNTER	0
#define SET_SYSTEM_CLOCK_COUNTER	1
// INT 1A, 2   Read real time clock time(AT, PS / 2)
// INT 1A, 3   Set real time clock time(AT, PS / 2)
// INT 1A, 4   Read real time clock date(AT, PS / 2)
// INT 1A, 5   Set real time clock date(AT, PS / 2)
// INT 1A, 6   Set real time clock alarm(AT, PS / 2)
#define READ_REAL_TIME_CLOCK_TIME	2
#define SET_REAL_TIME_CLOCK_TIME	3
#define READ_REAL_TIME_CLOCK_DATE	4
#define SET_REAL_TIME_CLOCK_DATE	5
#define SET_REAL_TIME_CLOCK_ALARM	6
// INT 1A, 7   Reset real time clock alarm(PS / 2)
// INT 1A, 8   Set RTC activated power on mode(convertible, PS / 2)
// INT 1A, 9   Read RTC alarm time and status(convertible, PS / 2)
// INT 1A, A   Read system day counter(PS / 2)
// INT 1A, B   Set system day counter(PS / 2)
// INT 1A, 80  Set up sound multiplexer(PCjr only)

#define TICKS_PER_SECOND			18.206
#define TICKS_PER_24HR				1800B0h

#endif