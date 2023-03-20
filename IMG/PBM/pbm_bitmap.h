/**
 *
 *  @brief     Portable Bit Map -The PBM format is a lowest common denominator monochrome file format.
 *  @details   Each PBM image consists of the following:
 *  A "magic number" for identifying the file type. A pbm image's magic number is the two characters "P4".
 *  Whitespace (blanks, TABs, CRs, LFs).
 *  The width in pixels of the image, formatted as ASCII characters in decimal.
 *  Whitespace.
 *  The height in pixels of the image, again in ASCII decimal.
 *  A single whitespace character (usually a newline).
 *  A raster of Height rows, in order from top to bottom.
 *  Each row is Width bits, packed 8 to a byte, with don't care bits to fill out the last byte in the row.
 *  Each bit represents a pixel: 1 is black, 0 is white.
 *  The order of the pixels is left to right.
 *  The order of their storage within each file byte is most significant bit to least significant bit.
 *  The order of the file bytes is from the beginning of the file toward the end of the file.
 *  A row of an image is horizontal. A column is vertical.
 *  The pixels in the image are square and contiguous.
 *  Before the whitespace character that delimits the raster, any characters from a "#" through the next carriage return or newline character, is a comment and is ignored. Note that this is rather unconventional, because a comment can actually be in the middle of what you might consider a token. Note also that this means if you have a comment right before the raster, the newline at the end of the comment is not sufficient to delimit the raster.
 *  @url https://netpbm.sourceforge.net/doc/pbm.html
 *  @author    Jeremy Thornton
 *  @date      11.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_BITMAP_H
#define PBM_BITMAP_H

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../../FSYS/fsys.h"
#include "../../DOS/dos_error_messages.h"
#include "../../STR/str.h"

#include "pbm_constants.h"

// TODO:
// [ ] construct smaller within larger
// [ ] copy_bitmap
// [ ] make_bitmap
// [x] free_bitmap

namespace pbm {



    /**
    *  @struct header_t
    *  @brief  PBM is monochrome 1 bit per pixel
    */
    struct header_t {

        const char* file_path;
        uint16_t magic_number;
        uint16_t width;         // pixels
        uint16_t height;        // pixels
        uint16_t bytes;         // number bytes of image data
        uint16_t offset;        // start of data in file
        uint16_t file_size;     // file size
    };

    /**
     *  @struct tile_t
     *  @brief  a tile is a uniform sized bitmap that completely tiles the parent bitmap
     *  Usually 8x8 pixels 
     */
    struct tile_t {

        uint16_t xscale;        // x axis tile size
        uint16_t yscale;        // y axis tile size
        uint16_t width;         // bitmap width in tiles
        uint16_t height;        // bitmap height in tiles
    
    };

    /**
     *  @struct bitmap_t
     *  @brief  A device independant 1 bit monochrome bitmap data structure
     */
    struct bitmap_t {

        struct header_t* header;
        struct tile_t* tile;
        char* data;

    };

    int load_bitmap(const char* file_path, bitmap_t* bmp, int valid_magic = MAGIC_P4) {
        char line[MAX_LINE_SIZE];
        bmp->header = (header_t*)malloc(sizeof(struct header_t));
        assert(bmp->header);
        bmp->header->file_path = file_path;
        bmp->header->magic_number = 0;
        bmp->header->width = bmp->header->height = bmp->header->bytes = bmp->header->offset = bmp->header->file_size = 0;
        bmp->data = NULL;

        FILE* fptr = fopen(bmp->header->file_path, "rb");
        if (!fptr) {
            LOG(bmp->header->file_path);
            return STDIO_FAIL;
        }
        bmp->header->file_size = (uint16_t)fsys::stream_size(fptr);
        assert(bmp->header->file_size > MIN_HEADER_SIZE);   // 1. is there at least a header in the file?
          
        assert(fgets(line, sizeof(line), fptr));
        assert(*(uint16_t*)line == valid_magic);            // 2. is it a valid magic number?
        while (fsys::fpeek(fptr) == '#') {                  // 3. skip any comments
            assert(fgets(line, sizeof(line), fptr));
        }
        // process the header
        assert(fscanf(fptr, "%d %d", (int*)&bmp->header->width, (int*)&bmp->header->height)); // get the bitmap dimensions
        bmp->header->bytes = (uint16_t)bmp->header->width / 8;              // convert width to bytes
        bmp->header->bytes += (bmp->header->width & 7) == 0 ? 0 : 1;        // need an extra byte for width remainder < 8?
        bmp->header->bytes *= bmp->header->height;                          // expected number bytes
        fsys::ignore_line(fptr);
        bmp->header->offset = (uint16_t)ftell(fptr);                        // data should start on next line
        assert(bmp->header->file_size - bmp->header->offset == bmp->header->bytes);    // 4. expected amount data?
        // process the data
        bmp->data = (char*)malloc(sizeof(uint8_t) * bmp->header->bytes);    // allocate data memory
        assert(bmp->data);
        if(!fgets(bmp->data, bmp->header->bytes + 1, fptr)) {  
            fclose(fptr);
            return STDIO_FAIL;
        }
        fclose(fptr);
        return EXIT_SUCCESS;
    }

    void free_bitmap(bitmap_t* bmp) {
        if (bmp) {
            free(bmp->header);
            free(bmp->data);
        }
    }

}

std::ostream& operator<<(std::ostream& os, const pbm::bitmap_t& bmp) {
    // print header
    os << bmp.header->file_path << ' '
        << std::hex << bmp.header->magic_number << std::dec << ' '
        << bmp.header->width << ' '
        << bmp.header->height << ' '
        << bmp.header->bytes << ' '
        << bmp.header->offset << ' '
        << bmp.header->file_size << '\n';
    // print data
    if (bmp.data) {
        int byte_width = bmp.header->width >> 3;
        byte_width += (bmp.header->width & 7) == 0 ? 0 : 1;
        char binalpha[8];
        for (int i = 0; i < bmp.header->bytes; ++i) {
            if (i % byte_width == 0) {
                std::cout << '\n';
            }
            assert(str::bits_to_binary(bmp.data[i], binalpha, 8) == 0);
            std::cout << binalpha;
        }
        std::cout << std::endl;
    }
    return os;
}



#endif