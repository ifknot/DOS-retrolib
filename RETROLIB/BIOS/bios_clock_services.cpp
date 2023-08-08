#include "bios_clock_services.h"

#include <assert.h>

#include "../MEM/mem_types.h"

namespace bios {

    // ---- XT BIOS clock services ----

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
        tick_count_t ticks;
        __asm {
            .8086
            lea     bx, ticks
            mov     ah, READ_SYSTEM_CLOCK_COUNTER
            int     BIOS_CLOCK_SERVICES            
            mov     [bx + 2], cx                    ; high order word of tick count
            mov     [bx], dx                        ; low order word of tick count
        }
        return ticks;
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
            mov     cx, [bx + 2]                    ; high order word of tick count
            mov     dx, [bx]                        ; low order word of tick count
            mov     ah, SET_SYSTEM_CLOCK_COUNTER
            int     BIOS_CLOCK_SERVICES
        }
    }

    // ---- AT, PS/2 BIOS clock services ----

    bool is_rtc_working() {
        bcd_time_t bcd_time;
        int is_rtc = 0;     // false error state
         __asm {
            .8086
            lea     bx, bcd_time
            mov     ah, READ_REAL_TIME_CLOCK_TIME
            int     BIOS_CLOCK_SERVICES
            jc      END         ; carry flag set if RTC not operating
            mov     is_rtc, 1
    END:
        }
         return is_rtc;
    }

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
    void read_rtc_time(bcd_time_t* bcd_time) {
        __asm {
            .8086
            lds     bx, bcd_time
            mov     ah, READ_REAL_TIME_CLOCK_TIME
            int     BIOS_CLOCK_SERVICES
            jc      ERR         ; carry flag set if RTC not operating
            mov[bx], ch         ; hours in BCD
            mov[bx + 1], cl     ; minutes in BCD
            mov[bx + 2], dh     ; seconds in BCD
            mov[bx + 3], dl     ; 1 if daylight savings time option
    ERR:
    END:
        }
    }

    /**
    * INT 1A,3 - Set Time on Real Time Clock (XT 286,AT,PS/2)
    * AH = 03
	* CH = hours in BCD
	* CL = minutes in BCD
	* DH = seconds in BCD
	* DL = 1 if daylight savings time option
	*    = 0 if standard time
	* @note clock values must be in BCD
    */
    void set_rtc_time(bcd_time_t* bcd_time) {
        __asm {
            .8086
            lds     bx, bcd_time
            mov     ch, [bx]            ; hours in BCD
            cmp     ch, 23h             
            jg      ERR                 ; more than 23hrs
            mov     cl, [bx + 1]        ; minutes in BCD
            cmp     cl, 59h             
            jg      ERR                 ; more than 59mins
            mov     dh, [bx + 2]        ; seconds in BCD
            cmp     dh, 59h
            jg      ERR                 ; more than 59secs
            mov     dl, [bx + 3]        ; 1 if daylight savings time option 
            cmp     dl, 1
            jg      ERR                 ; invalid daylight savings time option
            mov     ah, SET_REAL_TIME_CLOCK_TIME
            int     BIOS_CLOCK_SERVICES
            jmp     END
    ERR:
    END:
        }
    }

    /**
    * AH = 04
    * on return:
	* CH = century in BCD (decimal 19 or 20)
	* CL = year in BCD
	* DH = month in BCD
	* DL = day in BCD
	* CF = 0 if successful
	*    = 1 if error or clock not operating
    * @note calling this interrupt will update the DOS maintained date and reset the BIOS Data Area date rollover flag at 40:70
    */
    void read_rtc_date(bcd_date_t* bcd_date) {
        __asm {
            .8086
            lds     bx, bcd_date
            mov     ah, READ_REAL_TIME_CLOCK_DATE
            int     BIOS_CLOCK_SERVICES
            jc      ERR         ; carry flag set if RTC not operating
            mov[bx], ch         ; century in BCD
            mov[bx + 1], cl     ; year in BCD
            mov[bx + 2], dh     ; month in BCD
            mov[bx + 3], dl     ; day in BCD
    ERR:
    END:
        }
    }

    void convert_bcd_time_to_string(bcd_time_t* bcd_time, char* str, char delim) {
        str[1] = (bcd_time->hmsd[0] & 0xF) + '0';
        str[0] = (bcd_time->hmsd[0] >> 4) + '0';
        str[2] = delim;
        str[4] = (bcd_time->hmsd[1] & 0xF) + '0';
        str[3] = (bcd_time->hmsd[1] >> 4) + '0';
        str[5] = delim;
        str[7] = (bcd_time->hmsd[2] & 0xF) + '0';
        str[6] = (bcd_time->hmsd[2] >> 4) + '0';
    }

    void convert_string_to_bcd_time(char* str, bcd_time_t* bcd_time, uint8_t dlst) {
        bcd_time->hmsd[0] = str[0] - '0';
        bcd_time->hmsd[0] <<= 4;
        bcd_time->hmsd[0] += str[1] - '0';
        bcd_time->hmsd[1] = str[3] - '0';
        bcd_time->hmsd[1] <<= 4;
        bcd_time->hmsd[1] += str[4] - '0';
        bcd_time->hmsd[2] = str[6] - '0';
        bcd_time->hmsd[2] <<= 4;
        bcd_time->hmsd[2] += str[7] - '0';
        bcd_time->hmsd[3] = dlst;
    }

    void convert_bcd_date_to_string(bcd_date_t* bcd_date, char* str, char delim) {
        str[1] = (bcd_date->cymd[3] & 0xF) + '0';
        str[0] = (bcd_date->cymd[3] >> 4) + '0';
        str[2] = delim;
        str[4] = (bcd_date->cymd[2] & 0xF) + '0';
        str[3] = (bcd_date->cymd[2] >> 4) + '0';
        str[5] = delim;
        str[7] = (bcd_date->cymd[1] & 0xF) + '0';
        str[6] = (bcd_date->cymd[1] >> 4) + '0';
    }

    void convert_string_to_bcd_date(char* str, bcd_date_t* bcd_date, uint8_t century) {
        bcd_date->cymd[0] = century;
        bcd_date->cymd[1] = str[0] - '0';
        bcd_date->cymd[1] <<= 4;
        bcd_date->cymd[1] += str[1] - '0';
        bcd_date->cymd[2] = str[3] - '0';
        bcd_date->cymd[2] <<= 4;
        bcd_date->cymd[2] += str[4] - '0';
        bcd_date->cymd[3] = str[6] - '0';
        bcd_date->cymd[3] <<= 4;
        bcd_date->cymd[3] += str[7] - '0';

    }



}