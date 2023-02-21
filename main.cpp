#include <iostream>

//#include "ABM/test_abm.h"
#include "RND/test_rnd.h"

//TODO: timers
//TODO: integer rand shifters
// [ ] splitmix64 https://rosettacode.org/wiki/Pseudo-random_numbers/Splitmix64
// [ ] xorshift32 (asm) https://en.wikipedia.org/wiki/Xorshift
// [ ] xorshift64 https://stackoverflow.com/questions/53886131/how-does-xorshift32-works

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_rnd::run();

}
