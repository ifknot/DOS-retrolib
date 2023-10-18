#include "bios_keyboard_services.h"

#include "bios_keyboard_constants.h"
//#include "bios_keyboard_scan_codes.h"

namespace bios {

	/**
	* returns combined ascii key LSByte and unique key scan code MSByte
	*/
	uint16_t wait_key() {
		uint16_t key_scan;
		__asm {
			.8086
			mov		ah, WAIT_FOR_KEYSTROKE_AND_READ
			int		BIOS_KEYBOARD_SERVICE	
			mov		key_scan, ax
		}
		return key_scan;
	}

}
