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

#include "../../FILESYS/fsys.h"
#include "../../DOS/dos_error_messages.h"
#include "../../STR/str.h"

#include "pbm_constants.h"

// TODO:
// [ ] copy_bitmap
// [ ] make_bitmap
// [ ] free_bitmap

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
        uint16_t bytes;         // bytes of data
        uint16_t offset;        // start of data in file
        uint16_t file_size;          // file size
    };

    struct bitmap_t {

        struct header_t* header;
        char* data;

    };

    void load_bitmap(const char* file_path, bitmap_t* bmp, int type = MAGIC_P4) {
        char line[MAX_LINE_SIZE];
        bmp->header = (header_t*)malloc(sizeof(struct header_t));
        assert(bmp->header);
        bmp->header->file_path = file_path;
        bmp->header->magic_number = 0;
        bmp->header->width = bmp->header->height = bmp->header->bytes = bmp->header->offset = bmp->header->file_size = 0;
        bmp->data = NULL;

        FILE* fptr = fopen(bmp->header->file_path, "r");
        if (fptr) {
            bmp->header->file_size = (uint16_t)fsys::stream_size(fptr);
            if (bmp->header->file_size < MIN_HEADER_SIZE) { // 1. is there at least a header in the file?
                bmp->header->file_path = dos::error::messages[dos::error::INVALID_DATA];
                return;
            }
            fgets(line, sizeof(line), fptr);
            if (*(uint16_t*)line != type) { // 2. is it a valid magic number?
                bmp->header->file_path = dos::error::messages[dos::error::INVALID_FORMAT];
                return;
            }
            while (fsys::fpeek(fptr) == '#') { // 3. skip any comments
                fgets(line, sizeof(line), fptr);
            }
            // 4. process the header
            if (fscanf(fptr, "%d %d", (int*)&bmp->header->width, (int*)&bmp->header->height) == 0) {  // get the bitmap dimensions
                bmp->header->file_path = dos::error::messages[dos::error::INVALID_DATA];
                return;
            }
            bmp->header->bytes = (uint16_t)bmp->header->width / 8;              // convert width to bytes
            bmp->header->bytes += (bmp->header->width & 7) == 0 ? 0 : 1;        // need an extra byte for width remainder < 8?
            bmp->header->bytes *= bmp->header->height;                          // expected number bytes
            fsys::ignore_line(fptr);
            bmp->header->offset = (uint16_t)ftell(fptr);                        // data should start on next line
            if (bmp->header->file_size - bmp->header->offset != bmp->header->bytes) { // 4. expected amount data?
                bmp->header->file_path = dos::error::messages[dos::error::INVALID_DATA];
                bmp->header->bytes = 0;
                return;
            }
            // 5. process the data
            bmp->data = (char*)malloc(sizeof(uint8_t) * bmp->header->bytes);    // allocate data memory
            assert(bmp->data);
            assert(fgets(bmp->data, 1 + bmp->header->bytes, fptr)); // NB "Reads at most count - 1 characters"(!!!) 
            fclose(fptr);
        }
        else {
            bmp->header->file_path = strerror(errno);
        }
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
    }
    return os;
}



#endif

/*


            void read(std::istream& is) {
                is.seekg(0, is.end);                            // seek to the end
                header->size = is.tellg();                       // position of the current character ie the end character
                is.seekg(0, is.beg);                            // return to the beginning
                if (header->size < MIN_HEADER_SIZE) {     // 1. is there at least a header in the file?
                    header->file_path += dos::error::messages[dos::error::INVALID_DATA];
                    return;
                }
                char line[MAX_LINE_SIZE];
                is.getline(line, MAX_LINE_SIZE);
                if (*(uint16_t*)line != MAGIC_P4) { // 2. is it a valid magic number?
                    header->file_path += dos::error::messages[dos::error::INVALID_FORMAT];
                    return;
                }
                header->magic_number = MAGIC_P4;
                while (is.peek() == '#') is.ignore(MAX_LINE_SIZE, '\n');        // skip any comments
                is >> header->width >> header->height;
                header->bytes = (int)header->width / 8;                                   // convert width to bytes
                header->bytes += (header->width & 7) == 0 ? 0 : 1;                // need an extra byte for width remainder < 8?
                header->bytes *= header->height;                                                  // expected number bytes
                is.ignore(MAX_LINE_SIZE, '\n');                                                         // data should start on next line
                header->offset = is.tellg();                                                             // data starts here
                if (header->offset + header->bytes != header->size) {      // expected amount of data?
                    header->file_path += dos::error::messages[dos::error::INVALID_DATA];
                    return;
                }
                data = (uint8_t*)malloc(sizeof(uint8_t) * header->bytes);
                if (data == NULL) {
                    printf("\nError! memory not allocated.");
                    exit(0);
                }

                is.read((char*)data, 8);
                if (is.fail()) {
                    header->file_path += dos::error::messages[dos::error::INVALID_DATA];
                }
            }
*/