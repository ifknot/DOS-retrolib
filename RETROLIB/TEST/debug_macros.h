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
#include <iostream>
#include <stdint.h>
#include <stdio.h>

#define EXIT_SUCCESS 0

#ifdef NDEBUG
#define INFO(msg)
#else
#define INFO(msg) do { \
					std::cout << msg <<std::endl; \
				} while(false)
#endif

#ifdef NDEBUG
#define LOG(var)
#else
#define LOG(var) do { \
					std::cout << #var << '=' << std::dec << var << std::endl; \
				} while(false)
#endif

#ifdef NDEBUG
#define LOG_AS(var, base)
#else
#define LOG_AS(var, base) do { \
					std::cout << #var << '=' << base << var << std::dec << std::endl; \
				} while(false)
#endif

#ifndef VERBOSE
#define DOT
#else 
define DOT std::cout << '.';
#endif

#ifdef NDEBUG
#define ASSERT(test, observe, expect)
#else
#define ASSERT(test, compare, expected, msg) do { \
				std::cout << "assert "<< #test << ' ' << #compare << ' ' << expected << std::endl; \
				if(test compare expected) { \
					DOT;\
				} \
				else { \
					std::cout << "ERROR! "<< #test << ' ' << #compare << ' ' << std::dec << test << std::endl; \
					assert(false && msg); \
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

	static bool __yesno(char* msg) {
		std::cout << msg << " Y/N" << std::endl;
		char key;
		return scanf(" %c", &key) == 1 && key == 'Y' || key == 'y';
	}

	static void __pressenter(char* msg) {
		std::cout << msg << " Press <ENTER> " << std::endl;
		while (getchar() != '\n');
	}

	static char __anykey(char* msg) {
		std::cout << msg << std::endl;
		return getchar();
	}

}
#endif

#endif // DEBUG_MACROS_H


