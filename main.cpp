#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "BIOS/test_bios.h"
//#include "GFX/HGA/test_herc.h"
//#include "IMG/PBM/test_pbm.h"
//#include "STR/test_str.h"
#include "FILESYS/test_fsys.h"

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_fsys::run();

}