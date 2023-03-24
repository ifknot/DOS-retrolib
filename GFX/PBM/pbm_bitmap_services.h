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
        // setup the bitmap
        bmp->ihdr = (gfx::ihdr_t*)malloc(sizeof(struct gfx::ihdr_t));
        assert(bmp->ihdr);
        bmp->plte = (gfx::plte_t*)malloc(sizeof(struct gfx::plte_t));   // PBM format is 1bit monochrome *but* CGA monochrome can have a single palette entry for one of the 16 colours
        assert(bmp->plte);
        bmp->idat = (gfx::idat_t*)malloc(sizeof(struct gfx::idat_t));
        assert(bmp->idat);
        // set chunk default values
        bmp->ihdr->width = bmp->ihdr->height = 0;
        bmp->ihdr->bit_depth = bmp->ihdr->colour_type = 0;
        bmp->plte->length = 0;
        bmp->plte->data = NULL;
        bmp->idat->length = 0;
        bmp->idat->data = NULL;
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

    void free_bitmap(gfx::simple_bitmap_t* bmp) {
        if (bmp) {
            if (bmp->idat) {
                free(bmp->idat->data);  // free the image data
                free(bmp->idat);        // free the IDAT chunk
            }
            if (bmp->plte) {
                free(bmp->plte->data);  // free the palette data
                free(bmp->plte);        // free the PLTE chunk
            }
            free(bmp->ihdr);            // free the IHDR chunk
        }
    }

}

#endif