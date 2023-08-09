#include "bios_keyboard_services.h"

#include "bios_keyboard_constants.h"
//#include "bios_keyboard_scan_codes.h"

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
