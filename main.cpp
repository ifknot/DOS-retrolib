#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "BIOS/test_bios.h"
#include "GFX/HERC/test_herc.h"

// TODO: 
//  [x] Hamming Code
//  [x] trailing zeroes
//  [x] leading zeroes
//  [x] IBM BIOS timers
//  [x] integer rand shifters 
//  [x] hamming code performance
// TODO: chess::
//  [ ] bitboard_t
//  [ ] board_state_t
//  [ ] print_board
// TODO: gfx::
//  [ ] herc::enter_graphics_mode
//  [ ] herc::leave_graphics_mode
//  [ ] herc::bitmap_union
//  [ ] herc::load_bitmap
//  [ ] herc::save_bitmap

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_herc::run();

}
