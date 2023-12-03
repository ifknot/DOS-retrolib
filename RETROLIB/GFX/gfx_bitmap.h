/****/
#ifndef GFX_BITMAP_H
#define GFX_BITMAP_H

#include "../MEM/mem.h"

namespace gfx {

	namespace bmp {

		const char PBM_EXT[] = "PBM";

		struct bitmap_t {

		};

		void load_file_pbm(const char* file_path, bitmap_t* bmp, mem::arena::arena_t* arena);

	}

}

#endif
