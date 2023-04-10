#include <iostream>

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "BIOS/test_bios.h"
#include "GFX/HGA/test_herc.h"
//#include "GFX/PBM/test_pbm.h"
//#include "STR/test_str.h"
//#include "FILESYS/test_fsys.h"
//#include "GFX/test_gfx.h"

// TODO:
// [ ] test with 16x16 tiles
// [ ] test with 32x32 tiles
// [ ] hga_xor_tile
// [ ] hga_paste_tile(mask)
// [ ] hga_or_tile
// [ ] hga_and_tile
// [ ] gfx::actor
// [ ] separate into chess game folder and use retrolib
// [ ] 4 character swap between and group follow rouge-dungeon

int main() {
  
    std::cout << "DOS-retrolib\nurl: github.com/ifknot/DOS-retrolib\n";

    return test_herc::run();

}