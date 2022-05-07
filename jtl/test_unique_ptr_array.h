/**
 *
 *  @file      test_unique_ptr_array.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.02.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef TEST_UNIQUE_PTR_ARRAY_H
#define TEST_UNIQUE_PTR_ARRAY_H

#include <iostream>
#include <cassert>

#include "unique_ptr.h"

namespace test_unique_ptr_array {

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

    template<typename T>
    struct test_delete <T[]> {

        typedef T element_type;
        typedef T* pointer;

        inline void operator()(pointer ptr) const {
            delete[] ptr;
            witness = 2;
        }

    };

    void run() {
        std::cout << "test_unique_ptr_array... ";
        // test array specialisation
        {
            // test constructors
            {
                // default constructor (1), and (2)
                // The object is empty(owns nothing), with value - initialized stored pointer and stored deleter.
                jtl::unique_ptr<int[]> u;                                   // (1)
                assert(!u & u.get() == 0);
                jtl::unique_ptr<int[]> v(nullptr);                          // (2)
                assert(!v & v.get() == 0);
                // construct from pointer (3)
                // The object takes ownership of p, initializing its stored pointer to p and value - initializing its stored deleter.
                int* p = new int[5];
                jtl::unique_ptr<int[]> w(p);                                  // (3)
                assert(w.get() == p);
                // construct from pointer + lvalue deleter (4)
                //The object takes ownership of p, initializing its stored pointer to p, and using a copy of d as deleter(unless D is a reference type, in which case, d is used directly).
                test_delete<int[]> del;
                jtl::unique_ptr<int[], test_delete<int[]> > foo(new int[5], del);  // (4)
            }
            assert(witness == 2);
            //test operator[]
            {
                jtl::unique_ptr<int[]> a(new int[5]);
                for (int i = 0; i < 5; ++i) a[i] = i;
                for (int i = 0; i < 5; ++i) assert(a[i] == i);
            }
            // test assign null pointer
            {
                jtl::unique_ptr<int> p(new int[5]);
                assert(p.get() != 0);
                p = nullptr;
                assert(p.get() == 0);
            }
            // test opertor bool
            {
                jtl::unique_ptr<int[]> foo;
                jtl::unique_ptr<int[]> bar(new int[5]);
                bar[3] = 12;
                assert(!foo & bar & bar[3] == 12);
            }
            
            // test release
            {
                jtl::unique_ptr<int[]> auto_pointer(new int[5]);
                int* manual_pointer;
                auto_pointer[0] = 10;
                manual_pointer = auto_pointer.release();
                assert(*manual_pointer == 10 & !auto_pointer);
                delete manual_pointer;
            }
            // test swap
            {
                jtl::unique_ptr<int[]> foo(new int[5]);
                jtl::unique_ptr<int[]> bar(new int[3]);
                foo[3] = 10;
                bar[3] = 20;
                bar.swap(foo);
                assert(foo[3] == 20 & bar[3] == 10);
            }
            // test reset
            {
                jtl::unique_ptr<int[]> up;  // empty
                assert(!up);
                up.reset(new int[5]);       // takes ownership of pointer
                up[3] = 5;
                assert(up[3] == 5);
                up.reset(new int[10]);    // deletes managed object, acquires new pointer
                up[3] = 15;
                assert(up[3] == 15);
                up.reset();               // deletes managed object
                assert(!up & up.get() == 0);
            }
            // test swap
            {
                jtl::unique_ptr<int[]> foo(new int[5]);
                jtl::unique_ptr<int[]> bar(new int[3]);
                foo[3] = 10;
                bar[3] = 20;
                bar.swap(foo);
                assert(foo[3] == 20 & bar[3] == 10);
            }
        }
        std::cout << "success!\n";
    }

}

#endif