#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include "test_keyboard.h"
#include "test_clocks.h"
#include "test_config.h"
#include "test_data_area.h"
#include "test_memory.h"

namespace test_bios {

	void run() {
		if (YESNO("\t001\ttest BIOS keyboard ?")) test_keyboard::run();
		if (YESNO("\t002\ttest BIOS clocks ?")) test_clocks::run();
		if (YESNO("\t003\ttest BIOS config ?")) test_config::run();
		if (YESNO("\t004\ttest BIOS BDA ?")) test_data_area::run();
		if (YESNO("\t005\ttest BIOS memory ?")) test_memory::run();
		//if (YESNO("\t006\ttest BIOS video ?")) test_config::run();
	}

}

#endif 