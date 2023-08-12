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



namespace bios {

	uint16_t wait_key();

	inline uint8_t wait_key_ascii() {
		return static_cast<uint8_t>(wait_key());
	}

	inline uint8_t wait_key_scan_code() {
		return static_cast<uint8_t>(wait_key() >> 8);
	}

}

#endif
