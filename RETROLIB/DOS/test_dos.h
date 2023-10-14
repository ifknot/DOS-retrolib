#ifndef TEST_DOS_H
#define TEST_DOS_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "test_dos_types.h"

namespace test_dos {

	void run() {	
		
		if (YESNO("\t001\ttest types ?")) test_dos_types::run();
			
		
	}

}

#endif