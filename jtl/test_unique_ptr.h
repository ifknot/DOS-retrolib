/**
 *
 *  @file      test_unique_ptr.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_UNIQUE_PTR_H
#define TEST_UNIQUE_PTR_H

#include <cassert>
#include <iostream>

#include "unique_ptr.h"

namespace test_unique_ptr {

    int witness = 0;

    struct test_t { int a; int b; };

    template<typename T>
    struct test_delete {

        typedef T element_type;
        typedef T* pointer;

        inline void operator()(pointer ptr) const {
            delete ptr;
            witness = 1;
        }

    };

    void run() {
        std::cout << "test_unique_ptr... ";
        // test unique_ptr
        {
            // test constructors & destructor
            {
                // default constructor (1), and (2)
                // The object is empty(owns nothing), with value - initialized stored pointer and stored deleter.
                jtl::unique_ptr<int> u;                                     // (1)
                assert(!u & u.get() == 0);
                jtl::unique_ptr<int> v(nullptr);                            // (2)
                assert(!v & v.get() == 0);
                // construct from pointer (3)
                // The object takes ownership of p, initializing its stored pointer to p and value - initializing its stored deleter.
                int* p = new int(1);
                jtl::unique_ptr<int> w(p);                                  // (3)
                assert(w.get() == p);
                // construct from pointer + lvalue deleter (4)
                //The object takes ownership of p, initializing its stored pointer to p, and using a copy of d as deleter(unless D is a reference type, in which case, d is used directly).
                test_delete<int> del;
                jtl::unique_ptr<int, test_delete<int> > foo(new int, del);  // (4)
            }
            assert(witness == 1);
            // test operator*
            {
                jtl::unique_ptr<int> foo(new int);
                jtl::unique_ptr<int> bar(new int(100));
                *foo = *bar * 2;
                assert(*foo == 200 & *bar == 100);
            }
            // test operator->
            {
                jtl::unique_ptr<test_t> foo(new test_t);
                jtl::unique_ptr<test_t> bar;
                foo->a = 10;
                foo->b = 20;
                jtl::swap(foo, bar);
                assert(!foo);
                assert(bar->a == 10 & bar->b == 20);
            }
            // test assign null pointer 	
            {
                jtl::unique_ptr<int> foo(new int);
                assert(foo.get() != 0);
                foo = nullptr;
                assert(foo.get() == 0);
            }
            // test opertor bool
            {
                jtl::unique_ptr<int> foo;
                jtl::unique_ptr<int> bar(new int(12));
                assert(!foo & bar & *bar == 12);
            }
            // test release
            {
                jtl::unique_ptr<int> auto_pointer(new int);
                int* manual_pointer;
                *auto_pointer = 10;
                manual_pointer = auto_pointer.release();
                assert(*manual_pointer == 10 & !auto_pointer);
                delete manual_pointer;
            }
            // test reset
            {
                jtl::unique_ptr<int> up;    // empty
                up.reset(new int(5));       // takes ownership of pointer
                assert(*up == 5);
                up.reset(new int(10));      // deletes managed object, acquires new pointer
                assert(*up == 10);
                up.reset();                 // deletes managed object
                assert(!up & up.get() == 0);
            }
            // test swap
            {
                jtl::unique_ptr<int> foo(new int(10));
                jtl::unique_ptr<int> bar(new int(20));
                foo.swap(bar);
                assert(*foo == 20 & *bar == 10);
            }

        }
        std::cout << "success!\n";
    }

}

#endif