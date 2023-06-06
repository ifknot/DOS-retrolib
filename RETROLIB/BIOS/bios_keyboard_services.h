/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef BIOS_KEYBOARD_SERVICES_H
#define BIOS_KEYBOARD_SERVICES_H

#include <stdint.h>

#include "bios_keyboard_constants.h"
#include "bios_keyboard_scan_codes.h"

namespace bios {

	uint8_t wait_key_ascii() {
		uint8_t ascii = 0;
		__asm {
			.8086
			mov		ah, WAIT_FOR_KEYSTROKE_AND_READ
			int		BIOS_KEYBOARD_SERVICE
			mov		ascii, al
		}
		return ascii;
	}

	uint8_t wait_key_scan_code() {
		uint8_t scan = 0;
		__asm {
			.8086
			mov		ah, WAIT_FOR_KEYSTROKE_AND_READ
			int		BIOS_KEYBOARD_SERVICE
			mov		scan, ah
		}
		return scan;
	}

}

#endif