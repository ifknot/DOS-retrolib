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

#include "../DOS/dos_services_files.h"

#include "test_mem_utils.h"
#include "test_mem_arena.h"

namespace test_mem {

    void run() {

        if (YESNO("* 210\t Test mem utils ?")) {
            test_mem_utils::run();
        }
        if (YESNO("* 220\t Test mem arena ?")) {
            test_mem_arena::run();
        }

    }

}

#endif