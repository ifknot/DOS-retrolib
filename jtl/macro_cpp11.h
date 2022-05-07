/**
 *
 *  @file      macro_cpp11.h
 *  @brief     fixes for C++11 keywords to compile under C++98
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      13.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MACRO_CPP11_H
#define MACRO_CPP11_H

#define noexcept throw()	///< throw was deprecated in C++11 in favour of noexcept

#endif