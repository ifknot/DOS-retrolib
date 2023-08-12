#include <iostream>

#include "RETROLIB/TEST/debug_macros.h"
#include "RETROLIB/BIOS/test_keyboard.h"

// TODO DOS
//[x] move DOS into retrolib
//FIX:
//give option to include stream operators if desired but inc in dos.h 
//[ ] dos_services_streams.h (inc types reduce types header burden)
//[ ] dos_services_streams.cpp 
//[ ] add to dos.h
//[x] dos_services.h is long - close up the empty lines
//[x] dos_services.cpp
//[ ] replace int86 use asm
//[ ] extend test.h

// TODO BIOS
//[ ] seperate test for each service
//  [x] keyboard
//  [ ] clock 
//  [ ] config
//  [ ] bios data area 
//  [ ] memory
//  [ ] video
//[ ] combined into test bios header
// FIX
//[ ] not depend in dos.h int86


// TODO
// [ ] mem arena
// [ ] make gfx primitives using arena
// [ ] draw(...) primitives
//      [ ] HGA
// [ ] test vram buffer

int main() {

	test_keyboard::run();

	return 0;

}

//#include "ABM/test_abm.h"
//#include "RND/test_rnd.h"
//#include "MEM/test_mem.h"
//#include "DOS/test_dos.h"

//#include "GFX/HGA/test_herc.h"
//#include "GFX/PBM/test_pbm.h"
//#include "STR/test_str.h"
//#include "FILESYS/test_fsys.h"
//#include "GFX/test_gfx.h"
//#include "GFX/HGA/test_vram_buffer.h"

