/*****************************************************************//**
 * \file   test_debug_macros.h
 * \brief  general purpose debug macros disabled if NDEBUG is defined
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H

#include <cassert>
#include "../BIOS/bios_keyboard_services.h"

#define EXIT_SUCCESS 0

#ifdef NDEBUG
#define LOG(var)
#else
#define LOG(var) do { \
					std::cout << #var << '=' << var << std::endl; \
				} while(false)
#endif

#ifdef NDEBUG
#define LOG_AS(var, base)
#else
#define LOG_AS(var, base) do { \
					std::cout << #var << '=' << base << var << std::endl; \
				} while(false)
#endif

#ifdef NDEBUG
#define INFO(msg)
#else
#define INFO(msg) do { \
					std::cout << msg <<std::endl; \
				} while(false)
#endif

#ifndef VERBOSE
#define DISPLAY
#else 
define DISPLAY std::cout << '.';
#endif

#ifdef NDEBUG
#define ASSERT(test, msg)
#else
#define ASSERT(test, observe, expect) do { \
							if(test) {DISPLAY}\
							else { \
								LOG(observe); \
								LOG(expect); \
								assert(test); \
							} \
						} while(false)
#endif

#ifdef NDEBUG
#define YESNO(msg)
#else
#define YESNO(msg) test::__yesno(msg)
#endif

#ifdef NDEBUG
#define PRESSENTER(msg)
#else 
#define PRESSENTER(msg) test::__pressenter(msg)
#endif

#ifdef NDEBUG
#define ANYKEY(msg)
#else
#define ANYKEY(msg) test::__anykey(msg)
#endif

#ifndef NDEBUG
namespace test {

	bool __yesno(char* msg) {
		std::cout << msg << " Y/N" << std::endl;
		uint8_t code;
		do {
			code = bios::wait_key_scan_code();
		} while (code != SC_Y && code != SC_N);
		return (code == SC_Y) ? true : false;
	}

	void __pressenter(char* msg) {
		std::cout << msg << " Press <ENTER> " << std::endl;
		uint8_t code;
		do {
			code = bios::wait_key_scan_code();
		} while (code != SC_RTN);
	}

	void __anykey(char* msg) {
		//std::cout << msg << std::endl;
		bios::wait_key_scan_code();
	}

}
#endif

#endif