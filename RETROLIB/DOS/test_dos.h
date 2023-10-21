#ifndef TEST_DOS_H
#define TEST_DOS_H

#include "../TEST/debug_macros.h"

// 001
#include "test_dos_types.h"
// 002
#include "test_dos_interrupt_vector.h"
// 003
#include "test_dos_memory.h"

namespace test_dos {

	void run() {	
		
		if (YESNO("\t001\ttest types ?")) test_dos_types::run();
		if (YESNO("\t002\ttest interrupt get/set ?")) test_dos_interrupt_vector::run();
		if (YESNO("\t003\ttest memory alloc/free ?")) test_dos_memory::run();

	}

}

#endif