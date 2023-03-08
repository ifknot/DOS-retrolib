#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "BIOS/test_bios.h"
#include "GFX/HGA/test_herc.h"

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_herc::run();

}