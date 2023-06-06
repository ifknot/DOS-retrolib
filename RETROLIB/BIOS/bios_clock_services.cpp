#include "bios_clock_services.h"

#include <assert.h>

namespace bios {

    /**
    * INT 1A,0 - Read System Clock Counter
    * AH = 00
    * on return:
    * AL = midnight flag, 1 if 24 hours passed since reset
    * CX = high order word of tick count
    * DX = low order word of tick count
    * incremented approximately 18.206 times per second
    * at midnight CX:DX is zero
    */
    tick_count_t read_system_clock_counter() {
        tick_count_t ticks_since_midnight;
        __asm {
            .8086
            lea     bx, ticks_since_midnight
            mov     ah, READ_SYSTEM_CLOCK_COUNTER
            int     BIOS_CLOCK_SERVICES
            mov[bx], dx
            mov[bx + 2], cx
        }
        return ticks_since_midnight;
    }

    /**
    * examine AL = midnight flag, 1 if 24 hours passed since reset
    */
    bool is_24_hours_since_reset() {
        uint8_t midnight;
        __asm {
            .8086
            mov     ah, READ_SYSTEM_CLOCK_COUNTER
            int     BIOS_CLOCK_SERVICES
            mov     midnight, al
        }
        return midnight != 0;
    }

    /**
    * INT 1A,1 - Set System Clock Counter
    * AH = 01
	* CX = high order word of tick count
	* DX = low order word of tick count
    * returns nothing
    * @note CX:DX should be set to the number of seconds past midnight multiplied by approximately 18.206
    */
    void set_system_clock_counter(tick_count_t ticks_since_midnight) {
        __asm {
            .8086
            lea     bx, ticks_since_midnight
            mov     ah, SET_SYSTEM_CLOCK_COUNTER
            mov     cx, [bx + 2];
            mov     dx, [bx];
            int     BIOS_CLOCK_SERVICES

        }
    }

    namespace at {

        /**
        * INT 1A,2 - Read Time From Real Time Clock (XT 286,AT,PS/2)
        * AH = 02
        * on return:
        * CF = 0 if successful
        *    = 1 if error, RTC not operating
        * CH = hours in BCD
        * CL = minutes in BCD
        * DH = seconds in BCD
        * DL = 1 if daylight savings time option
        * @note - on AT with BIOS before 6/10/85, DL is not returned
        */
        void read_bcd_rtc_clock(bcd_time_t* bcd_time) {
            bcd_time->time = -1;   // error state
            __asm {
                lds     bx, bcd_time
                mov     ah, READ_REAL_TIME_CLOCK_TIME
                int     BIOS_CLOCK_SERVICES
                jc      END;
                mov[bx], ch         ; hours in BCD
                mov[bx + 1], cl     ; minutes in BCD
                mov[bx + 2], dh     ; seconds in BCD
                mov[bx + 3], dl     ; 1 if daylight savings time option
        END:
            }
            assert(bcd_time->time != -1 && "error, RTC not operating");
        }

        void string_read_rtc_clock(char* str) {
            bcd_time_t t;
            read_bcd_rtc_clock(&t);
            str[1] = (t.hmsd[0] & 0xF) + 0x30;
            str[0] = (t.hmsd[0] >> 4) + 0x30;
            str[4] = (t.hmsd[1] & 0xF) + 0x30;
            str[3] = (t.hmsd[1] >> 4) + 0x30;
            str[7] = (t.hmsd[2] & 0xF) + 0x30;
            str[6] = (t.hmsd[2] >> 4) + 0x30;
        }

    }

}