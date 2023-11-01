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

#include "../DOS/dos_services_files.h"

namespace test_lib_mem {

    void run() {
        mem::address_t addr;
        uint16_t ROM_BIOS = 0xE000;
        uint16_t ROM_BASIC = 0x6000;
        addr.segoff.segment = 0xF000;
        addr.segoff.offset = ROM_BIOS;
        char fpath[13] = "";
        if (YESNO("* 210\t dump to SCREEN first 256 bytes ROM BIOS ?")) {
            std::cout << mem::dump(addr, 256).segoff << std::endl;
        }
        if (YESNO("* 210\tdump to FILE first 256 bytes ROM BIOS ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            std::ofstream f;
            f.open(fpath);
            mem::dump_ostream(f, addr, 256);
            f.close();
        }
        addr.segoff.offset = ROM_BASIC;
        if (YESNO("* 220\tdump first 256 bytes ROM BASIC ?")) {
            mem::dump(addr, 256);
        }
        addr.segoff.offset = ROM_BIOS;
        if (YESNO("* 230\twrite (unformatted) first 256 bytes ROM BIOS to ostream ?")) {
            mem::write_ostream(std::cout, addr, 256);
            INFO("done");
        }
        if (YESNO("* 240\twrite (unformatted) first 256 bytes ROM BIOS to FILE ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            LOG(fpath);
            std::ofstream f;
            f.open(fpath);
            mem::write_ostream(f, addr, 256);
            f.close();
            INFO("done");
        }
        if (YESNO("* 250\tsave first 256 bytes ROM BIOS to FILE ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            LOG(fpath);
            dos::create_file_using_handle(fpath, dos::file::ACCESS_WRITE_ONLY);
            assert(mem::save_to_file(fpath, addr, 256) == 256);
            INFO("done");
        }
    }

}

#endif