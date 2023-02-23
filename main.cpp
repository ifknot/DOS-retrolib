#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
#include "BIOS/test_bios.h"

//TODO: 
// [x] IBM BIOS timers
// [x] integer rand shifters 

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_bios::run();

}
