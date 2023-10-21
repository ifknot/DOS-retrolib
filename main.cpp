#include <iostream>


#include "RETROLIB/TEST/debug_macros.h"
// 000
#include "RETROLIB/TEST/test_debug_macros.h"
// 001
#include "RETROLIB/DOS/test_dos.h"
// 002
#include "RETROLIB/MEM/test_mem.h"

//TODO:
//###MEM 
//- [ ] mcb_t operator<< 
//- [ ] get_max_alloc_low_mem()
//- [ ] get_total_low_mem()
//- [ ] get_ram_top_segment()

int main() {
	std::cout<< "test functions..." << std::endl;
	//if (YESNO("000\ttest debug ?")) test_debug_macros::run();
	if (YESNO("001\ttest DOS ?")) test_dos::run();
	if (YESNO("002\ttest MEM ?")) test_lib_mem::run();

	return 0;

}
