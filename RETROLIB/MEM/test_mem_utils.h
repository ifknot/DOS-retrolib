/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      8.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_MEM_UTILS_H
#define TEST_MEM_UTILS_H

#include "mem.h"

namespace test_mem_utils {

    void run() {
        INFO("* testing memory utilities...");
        mem::address_t addr;
        uint16_t ROM_BIOS = 0xE000;
        uint16_t ROM_BASIC = 0x6000;
        addr.segoff.segment = 0xF000;
        addr.segoff.offset = ROM_BIOS;
        char fpath[13] = "";
        if (YESNO("* 211\t dump to SCREEN first 256 bytes ROM BIOS ?")) {
            std::cout << mem::dump(addr, 256).segoff << std::endl;
        }
        if (YESNO("* 212\tdump to FILE first 256 bytes ROM BIOS ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            std::ofstream f;
            f.open(fpath);
            mem::dump_ostream(f, addr, 256);
            f.close();
        }
        if (YESNO("* 213\tdump first 256 bytes ROM BASIC ?")) {
            addr.segoff.offset = ROM_BASIC;
            mem::dump(addr, 256);
        }
        if (YESNO("* 214\twrite (unformatted) first 256 bytes ROM BIOS to ostream ?")) {
            addr.segoff.offset = ROM_BIOS;
            mem::write_ostream(std::cout, addr, 256);
            INFO("done");
        }
        if (YESNO("* 215\twrite (unformatted) first 256 bytes ROM BIOS to ostream ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            LOG(fpath);
            std::ofstream f;
            f.open(fpath);
            mem::write_ostream(f, addr, 256);
            f.close();
            INFO("done");
        }
        if (YESNO("* 216\tsave first 256 bytes ROM BIOS to FILE ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            LOG(fpath);
            LOG(dos::create_file_using_handle(fpath, dos::file::ACCESS_WRITE_ONLY));
            ASSERT(mem::save_to_file(fpath, addr, 256), == , 256, "save bytes error");
            INFO("done");
        }
        if (YESNO("* 217\tload file to CGA screen memory ?")) {
            INFO("* Enter filename: ");
            scanf("%s", fpath);
            addr.segoff.segment = 0xB000;
            addr.segoff.offset = 0x8800;
            LOG(fpath);
            ASSERT(mem::load_from_file(fpath, addr, 256), == , 256, "load bytes error");
            INFO("done");
        }
    }

}

#endif