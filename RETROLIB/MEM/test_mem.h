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
#include <fstream>

#include "../TEST/debug_macros.h"

#include "mem.h"

namespace test_lib_mem {

    void run() {
        mem::address_t addr;
        uint16_t ROM_BIOS = 0xE000;
        uint16_t ROM_BASIC = 0x6000;
        addr.segoff.segment = 0xF000;
        addr.segoff.offset = ROM_BIOS;
        char fpath[13] = "";
        FILE* fptr;
        if (YESNO("* 210\tdump first 256 bytes ROM BIOS ?")) {
            std::cout << mem::dump(addr).segoff << std::endl;
        }
        if (YESNO("* 210\tfile dump first 256 bytes ROM BIOS ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            std::ofstream f;
            f.open(fpath);
            mem::dump_page_ostream(f, addr, 256);
            f.close();
        }
        addr.segoff.offset = ROM_BASIC;
        if (YESNO("* 220\tdump first 256 bytes ROM BASIC ?")) {
            mem::dump(addr);
        }
        addr.segoff.offset = ROM_BIOS;
        if (YESNO("* 230\tsave (unformatted) first 256 bytes ROM BIOS to ostream ?")) {
            mem::save_page_ostream(std::cout, addr, 256);
        }
    }

}

#endif