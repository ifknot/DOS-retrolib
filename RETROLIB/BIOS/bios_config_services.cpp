#include "bios_config_services.h"

#include <assert.h>

namespace bios {



	retro::address_t get_ROM_table_address() {
		uint16_t segment, offset;
		retro::address_t addr;
		__asm {
			.8086

		}
		return addr;
	}

}