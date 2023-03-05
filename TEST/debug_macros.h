/*****************************************************************//**
 * \file   test_debug_macros.h
 * \brief  general purpose debug macros disabled if NDEBUG is defined
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H

#include <iostream>
#include <cassert>

#define EXIT_SUCCESS 0

#ifdef NDEBUG
#define LOG(var)
#else
#define LOG(var) do { \
					std::cout << #var << '=' << var << std::endl; \
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

namespace test {

}

#endif