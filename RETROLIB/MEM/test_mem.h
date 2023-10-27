/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_MEM_H
#define TEST_MEM_H

#include <iostream>

#include "../TEST/debug_macros.h"
#include "mem_dump_ostream.h"
#include "mem_types.h"

namespace test_lib_mem {

    void run() {
        mem::address_t addr;
        addr.memloc.segment = 0x396f;
        addr.memloc.offset = 0x0100;
        mem::dump_line_ostream(std::cout, addr);
        INFO("* PASS!");
    }

}

#endif