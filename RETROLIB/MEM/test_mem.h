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

#include "mem.h"

namespace test_lib_mem {

    void run() {
        mem::address_t addr;
        addr.segoff.segment = 0xF000;
        addr.segoff.offset = 0xE000;
        if (YESNO("* 210\tdump first 256 bytes ROM BIOS ?")) {
            std::cout << mem::dump_ostream(std::cout, addr).segoff << std::endl;
        }
        addr.segoff.offset = 0x6000;
        if (YESNO("* 220\tdump first 256 bytes ROM BASIC ?")) {
            mem::dump(addr);
        }
        if (YESNO("* 230\tdump first 256 bytes ROM BIOS to file ?")) {
            LOG();
        }
        INFO("* PASS!");
    }

}

#endif