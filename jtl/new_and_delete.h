/**
 *
 *  @file      memory.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      15.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>
#include <stdlib.h>

#include <cassert>
#include <iostream>

void* operator new(size_t size) {
    std::cout << size << " Using the overloaded operator new." << std::endl;
    void* ptr;
    ptr = malloc(size);   
    assert(ptr);
    return ptr;
}

void operator delete(void* ptr) {
    std::cout << "Release memory using delete operator" << std::endl;
    free(ptr);
}

void* operator new[](size_t size) {
    void* ptr;
    std::cout << size << " Using the overloaded operator new[]." << std::endl;
    ptr = malloc(size);
    assert(ptr);
    return ptr;
}

void operator delete[](void* ptr) {
    std::cout << "Release array from memory by operator delete[]" << std::endl;
    free(ptr);
}

#endif