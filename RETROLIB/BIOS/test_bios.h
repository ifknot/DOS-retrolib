#ifndef TEST_BIOS_H
#define TEST_BIOS_H

#include "test_keyboard.h"
#include "test_clocks.h"
#include "test_config.h"
#include "test_memory.h"

namespace test_bios {

	void run() {
		if (YESNO("\t001\ttest keyboard ?")) test_keyboard::run();
		if (YESNO("\t002\ttest clocks ?")) test_clocks::run();
		if (YESNO("\t003\ttest config ?")) test_config::run();
		if (YESNO("\t003\ttest memory ?")) test_memory::run();
	}

}

#endif 