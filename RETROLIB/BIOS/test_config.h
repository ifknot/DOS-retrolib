/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      16.08.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include "../TEST/debug_macros.h"

#include "../MEM/mem_types.h"
#include "../MEM/mem_types_stream_operators.h"

#include "bios_config_services.h"
#include "bios_config_services_constants.h"

namespace test_config {

	void run() {
		if (YESNO("check ROM BIOS supports AT extended services?")) {
			INFO((bios::is_support_AT_extended_services() ? "YES" : "NO"));
		}
		if (bios::is_support_AT_extended_services()) {
			retro::address_t addr;
			addr.ptr = NULL;
			LOG(addr.memloc);
			bios::ext::get_ROM_table_address(&addr);
			LOG(addr.memloc);
			bios::ext::bios_sys_parms_rec_t* p = (bios::ext::bios_sys_parms_rec_t*)addr.ptr;
			LOG((uint16_t*)addr.ptr);
			LOG(p->len);
			LOG_AS((uint16_t)p->model, std::hex);
			LOG(bios::ext::config_models[p->model - 0xFB]);
			LOG_AS((uint16_t)p->sub_model, std::hex);
			LOG(bios::ext::config_sub_models[p->sub_model]);
			LOG((uint16_t)p->rev_level);
			LOG((bool)((p->features) & REAL_TIME_CLOCK_IS_PRESENT));
		}
	}

}

#endif