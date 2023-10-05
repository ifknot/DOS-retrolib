#include <iostream>

// TODO 
//[ ] general purpose memory block display taking a struct w 8,16,13,64 data size and char[] of descriptors 
//[ ] move mem consts into lower mem consts 
//[ ] .h and .cpp for mem functions 
//[ ] global bios consts for the likes of int 15h

// TODO DOS
//[x] move DOS into retrolib
//FIX:
//give option to include stream operators if desired but inc in dos.h 
//[ ] dos_types_stream_operators.h (inc types reduce types header burden)
//[ ] dos_types_stream_operators.cpp 
//[ ] add to dos.h
//[x] dos_services.h is long - close up the empty lines
//[x] dos_services.cpp
//[ ] replace int86 use asm
//[ ] extend test.h

// TODO BIOS
// [x] bios_types_stream_operators.h
// [x] bios_types_stream_operators.cpp
// [ ] seperate test for each service
//  [x] keyboard
//  [x] clock 
//  [x] config
//  [ ] bios data area 
//  [ ] memory
//  [ ] video
//[ ] combined into test bios header
// FIX
//[ ] not depend in dos.h int86

// TODO MEM
// [ ] mem arena

// TODO GFX
// [ ] rectangle_t & functions
// [ ] bitblt memory -> vram
//   [ ] HGA
//   [ ] CGA
// [ ] make gfx primitives using arena
// [ ] use swap buffers paradigm
//   [ ] HGA
//   [ ] CGA
// [ ] draw(...) primitives

#include "RETROLIB/TEST/debug_macros.h"
#include "RETROLIB/BIOS/test_bios.h"

int main() {

	if (YESNO("000\ttest bios ?")) test_bios::run();

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

