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

namespace test_dos_types {

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

}

#endif