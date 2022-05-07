/**
 *
 *  @file      bios_clock_services.h
 *  @brief     
 *  @details   
 * 
 *  INT 1A,0   Read system clock counter
 *  INT 1A,1   Set system clock counter
 *	INT 1A,2   Read real time clock time (AT,PS/2)
 *	INT 1A,3   Set real time clock time (AT,PS/2)
 *	INT 1A,4   Read real time clock date (AT,PS/2)
 *	INT 1A,5   Set real time clock date (AT,PS/2)
 *	INT 1A,6   Set real time clock alarm (AT,PS/2)
 *	INT 1A,7   Reset real time clock alarm (PS/2)
 *	INT 1A,8   Set RTC activated power on mode (convertible,PS/2)
 *	INT 1A,9   Read RTC alarm time and status (convertible,PS/2)
 *	INT 1A,A   Read system day counter (PS/2)
 *	INT 1A,B   Set system day counter (PS/2)
 *	INT 1A,80  Set up sound multiplexer (PCjr only)
 * 
 *  @author    Jeremy Thornton
 *  @date      1.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BIOS_CLOCK_SERVICES_H
#define BIOS_CLOCK_SERVICES_H

#include <stdint.h>

#include "bios_clock_services_constants.h"

namespace bios {

 /**
  *  @brief  INT 1A,0 - Read System Clock Counter
  *  @details Reads the BIOS Data Area address 40:6C Timer Counter DWord as updated by the INT 08 routine.
  * INT 08 Timer (IRQ 0)  This interrupt is issued 18.2 times per second and is responsibl for updating the 
  * system timer at 40:6C, resetting diskette drive motors, and issuing INT 1C.
  * @note The reality is that vector 08h wasn't "unused".
  * In fact it was listed as reserved all the way back to Intel's design specification documents.
  * Intel on the 8086/8088 reserved the first 32 interrurpt vectors.
  * The problem is that IBM ignored Intel and actually used reserved vectors for the 8259.
  * This caused the problems when the 80286 and 80386 came out (Coprocessor vector clashed and the 8259A clashed).
  * Had IBM not designed a flawed system from the start and conformed to Intel this clash wouldn't have happened – as per the iAPX 86 and 88 Intel manual from 1981, page 4-17
  * "...the first five interrupt vectors are associated with the software-initiated interrupts and the hardware non-maskable interrupt (NMI).
  * The next 27 interrupt vectors are reserved by Intel and should not be used if compatibility with future Intel products is to be maintained..."
  * 
  * AH = 00
  * on return:
  * AL = midnight flag, 1 if 24 hours passed since reset
  * CX = high order word of tick count
  * DX = low order word of tick count
  * incremented approximately 18.206 times per second
  * at midnight CX:DX is zero
  *  @retval  - uint32_t
  */
	uint32_t read_system_clock_counter() {
		uint16_t hi, lo;
		uint32_t ticks_since_midnight;
		__asm {
			.8086

			mov		ah, READ_SYSTEM_CLOCK_COUNTER
			int		BIOS_CLOCK_SERVICES
			mov		hi, cx
			mov		lo, dx

		}
		ticks_since_midnight = hi;
		ticks_since_midnight <<= 16;
		ticks_since_midnight |= lo;
		return ticks_since_midnight;
	}

 /**
  *  @brief the BIOS Data Area address 40:6C Timer Counter DWord
  *  @param ticks_since_midnight - - should be set to the number of seconds past
  * midnight multiplied by approximately 18.206
  */
	void set_system_clock_counter(uint32_t ticks_since_midnight) {
		uint16_t hi, lo;
		lo = ticks_since_midnight;
		hi = ticks_since_midnight >> 16;
		__asm {
			.8086

			mov		ah, SET_SYSTEM_CLOCK_COUNTER
			mov		cx, lo
			mov		dx, hi
			int		BIOS_CLOCK_SERVICES

		}

	}

}

#endif