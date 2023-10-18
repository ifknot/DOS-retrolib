#ifndef TEST_DOS_H
#define TEST_DOS_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "test_dos_types.h"
#include "test_dos_interrupt_vector.h"

namespace test_dos {

	void run() {	
		
		if (YESNO("\t001\ttest types ?")) test_dos_types::run();
		if (YESNO("\t002\ttest interrupt get/set ?")) test_dos_interrupt_vector::run();
		
	}

}

#endif