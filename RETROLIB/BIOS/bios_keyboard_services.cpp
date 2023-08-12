#include "bios_keyboard_services.h"

#include "bios_keyboard_constants.h"
//#include "bios_keyboard_scan_codes.h"

namespace bios {

	uint16_t wait_key() {
		uint16_t scan;
		__asm {
			.8086
			mov		ah, WAIT_FOR_KEYSTROKE_AND_READ
			int		BIOS_KEYBOARD_SERVICE
			mov		scan, ax
		}
		return scan;
	}

}
