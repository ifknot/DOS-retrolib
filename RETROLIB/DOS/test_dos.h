#ifndef TEST_DOS_H
#define TEST_DOS_H

#include "../TEST/debug_macros.h"

#include "test_dos_types.h"
#include "test_dos_interrupt_vector.h"
#include "test_dos_memory.h"
#include "test_dos_files.h"

// test DOS is 100

namespace test_dos {

	void run() {	
		
		if (YESNO("101\ttest types ?")) test_dos_types::run();
		if (YESNO("102\ttest interrupt get/set ?")) test_dos_interrupt_vector::run();
		if (YESNO("103\ttest memory alloc/free ?")) test_dos_memory::run();
		if (YESNO("* 104\ttest file services ?")) test_dos_files::run();
	}

}

#endif