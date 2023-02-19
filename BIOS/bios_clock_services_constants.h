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



namespace bios {

#define BIOS_CLOCK_SERVICES			1Ah
#define READ_SYSTEM_CLOCK_COUNTER	0
#define SET_SYSTEM_CLOCK_COUNTER	1

#define TICKS_PER_SECOND			18.206
#define TICKS_PER_24HR				1800B0h

}

#endif