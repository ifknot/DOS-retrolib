#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "BIOS/test_bios.h"
//#include "GFX/HGA/test_herc.h"
#include "GFX/PBM/test_pbm.h"
//#include "STR/test_str.h"
//#include "FILESYS/test_fsys.h"
//#include "GFX/test_gfx.h"

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_pbm::run();

}