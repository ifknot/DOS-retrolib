/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS_FPEEK_H
#define FSYS_FPEEK_H

#include "fsys_constants.h"

namespace fsys {

    int fpeek(FILE* fptr) {
        int chr;
        chr = getc(fptr);   // read one byte from the stream
        assert(chr != EOF); // NB the special value EOF indicates failure
        assert(fseek(fptr, -1, SEEK_CUR) != STDIO_FAIL);    // step back one byte in the stream
        return chr;         
    }

}

#endif