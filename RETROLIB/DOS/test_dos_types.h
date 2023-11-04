/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DOS_TYPES_H
#define TEST_DOS_TYPES_H

#include "../TEST/debug_macros.h"
#include "../MEM/mem_address.h"

#include "dos.h"

namespace test_dos_types {

	void run() {
		INFO("* testing DOS services types...");
		char str[] = "hello";
		mem::address_t addr;
		addr.void_ptr = (void*)str;
		std::cout << str << '\n'
			<< addr.segoff << '\n'
			<< addr << '\n'
			<< std::hex << (uint32_t)str << '\n';
	}

}

#endif