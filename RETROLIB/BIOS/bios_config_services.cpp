#include "bios_config_services.h"

#include <assert.h>
#include <stdint.h>

#include "bios_config_services_constants.h"

namespace bios {

	/**
	* @brief test if the ROM BIOS supports AT extended services?
	* @note The PC XT (since 1986/01/10), PC AT (since 1985/06/10), the PC XT Model 286, the PC Convertible and most PS/2 machines do support.
	*/
	bool is_support_AT_extended_services() {
		uint8_t supported = 0;
		__asm {
			.8086
			mov		ah, GET_SYSTEM_PARAMETERS
			int		AT_EXTENDED_SERVICES
			jc		END
			mov		supported, 1
	END:
		}
		return supported;
	}

	namespace ext {

		/**
		* @brief SYSTEM - GET CONFIGURATION (XT >1986/1/10,AT mdl 3x9,CONV,XT286,PS)
		* @details
		*   INT 15
		*	AH = C0h
		*	Return:
		*	CF set if BIOS doesn't support call
		*	CF clear on success
		*	ES:BX -> ROM table (see #00509)
		*	AH = status 00h successful
		*/
		void get_ROM_table_address(retro::address_t* addr) {
			__asm {
				.8086
				lds		di, addr;
				mov		ah, GET_SYSTEM_PARAMETERS
					int		AT_EXTENDED_SERVICES
					JC		END
					mov[di], bx
					mov[di + 2], es
					END :
			}
		}

	}

}