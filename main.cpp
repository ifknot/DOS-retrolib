#include <iostream>

//#include "ABM/test_abm.h"
#include "RND/test_rnd.h"

//TODO: timers
//TODO: integer rand shifters

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_rnd::run();

}
