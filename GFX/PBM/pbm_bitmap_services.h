/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      21.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_BITMAP_SERVICES_H
#define PBM_BITMAP_SERVICES_H

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../../FSYS/fsys.h"
#include "../../DOS/dos_error_messages.h"
#include "../../STR/str.h"
#include "../gfx_bitmap_t.h"

#include "pbm_constants.h"

 // TODO:
 // [ ] use gfx::bitmap and offer these as pbm_bitmap_services
 // [ ] load_bitmap
 // [ ] link_bitmap 
 // [ ] copy_bitmap
 // [ ] make_bitmap
 // [ ] free_bitmap

namespace pbm {

    int load_bitmap(const char* file_path, gfx::simple_bitmap_t* bmp, int valid_magic = MAGIC_P4) {    
        long file_size;
        char line[MAX_LINE_SIZE];
        // attempt to open file
        FILE* fptr = fopen(file_path, "rb");
        if (!fptr) {
            LOG(file_path);
            return STDIO_FAIL;
        }
        file_size = fsys::stream_size(fptr);
        assert(file_size > MIN_HEADER_SIZE);                    // is there at least a header in the file?
        assert(fgets(line, sizeof(line), fptr));                // is there a line to read?
        assert(*(uint16_t*)line == valid_magic);                // is it a valid magic number?
        while (fsys::fpeek(fptr) == '#') {                      // skip any comments
            assert(fgets(line, sizeof(line), fptr));
        }
       
        // process the header
        assert(fscanf(fptr, "%d %d", (int*)&bmp->ihdr->width, (int*)&bmp->ihdr->height)); // get the bitmap dimensions
        bmp->idat->length = (uint16_t)bmp->ihdr->width / 8;     // convert width to bytes
        bmp->idat->length += (bmp->ihdr->width & 7) == 0 ? 0 : 1;   // need an extra byte for width remainder < 8?
        bmp->idat->length *= bmp->ihdr->height;                 // expected number bytes
        fsys::ignore_line(fptr);                                
        assert(file_size - ftell(fptr) == bmp->idat->length);   // expected amount data?
        // process the data
        bmp->idat->data = (char*)malloc(sizeof(char) * bmp->idat->length);    // allocate data memory
        assert(bmp->idat->data);
        for (int i = 0; i < bmp->idat->length; ++i) {
            bmp->idat->data[i] = fgetc(fptr);
        }
        fclose(fptr);
        return EXIT_SUCCESS;
    }

}



#endif