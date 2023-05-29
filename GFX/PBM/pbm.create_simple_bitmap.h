/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_CREATE_SIMPLE_BITMAP_H
#define PBM_CREATE_SIMPLE_BITMAP_H

#include <stdlib.h>

#include "../../FSYS/fsys.h"
#include "../gfx_bitmap_t.h"

#include "pbm_constants.h"

#define VERBOSE

namespace pbm {

    gfx::simple_bitmap_t* create_simple_bitmap(const char* file_path, int valid_magic = MAGIC_P4) {
        long file_size;
        char line[MAX_LINE_SIZE];
        // attempt to open file with sanity checks 
        FILE* fptr = fopen(file_path, "rb");
#ifndef NDEBUG
        if (fptr) {
            std::cout << "Loading " << file_path << std::endl;
#else
        assert(fptr);                                           // valid file?
#endif
            file_size = fsys::stream_size(fptr);
            assert(file_size > MIN_HEADER_SIZE);                    // is there at least a header in the file?
            assert(fgets(line, sizeof(line), fptr));                // is there a line to read?
            assert(*(uint16_t*)line == valid_magic);                // is it a valid magic number?
            while (fsys::fpeek(fptr) == '#') {                      // skip any comments
                assert(fgets(line, sizeof(line), fptr));
            }
            gfx::simple_bitmap_t* p = gfx::new_simple_bitmap();
            // process the header
            assert(fscanf(fptr, "%d %d", (int*)&p->ihdr->width, (int*)&p->ihdr->height)); // get the bitmap dimensions
            p->idat->size = (uint16_t)p->ihdr->width / 8;           // convert width to bytes
            p->idat->size += (p->ihdr->width & 7) == 0 ? 0 : 1;     // need an extra byte for width remainder < 8?
            p->idat->size *= p->ihdr->height;                       // expected number bytes
            fsys::ignore_line(fptr);
            assert(file_size - ftell(fptr) == p->idat->size);      // expected amount data?
            // process the data
            p->idat->data = (char*)malloc(sizeof(char) * p->idat->size);
            assert(p->idat->data);                                   // allocated data memory?
            int ch; // fgetc the return type is int to accommodate for the special value EOF, which indicates failure
            for (int i = 0; i < p->idat->size; ++i) {
                ch = fgetc(fptr);
                assert(ch != EOF);                                  // unexpected end of file?
                p->idat->data[i] = static_cast<char>(ch);
            }
            fclose(fptr);
            return p;
#ifndef NDEBUG
        }
        else {
            std::cout << "ERROR no such file " << file_path << std::endl;
            return NULL;
        }
#endif      
    }

}



#endif