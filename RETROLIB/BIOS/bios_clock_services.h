/**
 *  @brief XT, PS2, PCjr namespaced BIOS clock services
 *  @details
 *  [x] INT 1A,0   Read system clock counter
 *  [x] INT 1A,1   Set system clock counter
 *  [ ] INT 1A,2   Read real time clock time (AT,PS/2)
 *  [ ] INT 1A,3   Set real time clock time (AT,PS/2)
 *  [ ] INT 1A,4   Read real time clock date (AT,PS/2)
 *  [ ] INT 1A,5   Set real time clock date (AT,PS/2)
 *  [ ] INT 1A,6   Set real time clock alarm (AT,PS/2)
 *  [ ] INT 1A,7   Reset real time clock alarm (PS/2)
 *  [ ] INT 1A,8   Set RTC activated power on mode (convertible,PS/2)
 *  [ ] INT 1A,9   Read RTC alarm time and status (convertible,PS/2)
 *  [ ] INT 1A,A   Read system day counter (PS/2)
 *  [ ] INT 1A,B   Set system day counter (PS/2)
 *  [ ] INT 1A,80  Set up sound multiplexer (PCjr only)
 * 
 *  @url https://www.stanislavs.org/helppc/int_1a.html
 *  @author    Jeremy Thornton
 *  @date      1.05.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BIOS_CLOCK_SERVICES_H
#define BIOS_CLOCK_SERVICES_H

#include "bios_clock_services_constants.h"
#include "bios_clock_services_types.h"

namespace bios {

    // ---- XT BIOS clock services ----

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
    *  @retval  - uint32_t
    */
    tick_count_t read_system_clock_counter();

    /**
    *  @brief query the midnight flag AL after a call to read system clock counter
    *  @retval bool yes/no 24hrs since reset
    *  @note 1. there are 0x1800B0 clock ticks per day.
    *  @note 2. the 32 bit system clock overflows after 10yrs 8 months
    */
    bool is_24_hours_since_reset();

    /**
    *  @brief the BIOS Data Area address 40:6C Timer Counter DWord
    *  @param ticks_since_midnight - - should be set to the number of seconds past
    *  midnight multiplied by approximately 18.206
    */
    void set_system_clock_counter(tick_count_t ticks_since_midnight);

    // ---- AT, PS/2 BIOS clock services ----

    /**
    *  @brief test if the Real Time Clock is working
    */
    bool is_rtc_working();

    // NB - on AT with BIOS before 6/10/85, DL is not returned
    //bool is_rtc_daylight_savings();

    /**
    *  @brief Read BCD Time from Real Time Clock (XT286,AT,PS/2)
    *  @note values are written as Binary Coded Decimal 
    */
    void read_rtc_clock(bcd_time_t* bcd_time);


    /**
    *  @brief Set BCD Time to Real Time Clock (XT286,AT,PS/2)
    *  @note   1. Does not work with DOSBOX
    *  @note   2. Values are expected as Binary Coded Decimal 
    */
    void set_rtc_clock(bcd_time_t* bcd_time);

    /**
    *  @brief convert bcd_time_t to string format HH:MM:SS
    */
    void convert_bcd_time_to_string(bcd_time_t* bcd_time, char* str, char delim = ':');

    /**
    *  @brief convert string format HH:MM:SS to bcd_time
    */
    void convert_string_to_bcd_time(char* str, uint8_t dlst, bcd_time_t* bcd_time);

    // ---- PS/2 only BIOS clock services ----

    // ---- convertible, PS/2 BIOS clock services ----

    // ---- PCjr only BIOS clock services ----

}

#endif