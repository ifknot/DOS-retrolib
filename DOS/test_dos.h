#ifndef TEST_DOS_H
#define TEST_DOS_H

#include <cassert>
#include <iostream>

#include "../TEST/debug_macros.h"

#include "dos.h"

namespace test_dos {

	int run() {
		{
			INFO("0. test DOS services types");
			char str[] = "hello";
			dos::address_t addr;
			addr.ptr = (void*)str;
			std::cout << str << '\n'
				<< addr.memloc << '\n' 
				<< addr << '\n'
				<< std::hex << (uint32_t)str << '\n';
		}

		return EXIT_SUCCESS;
	}

}

#endif