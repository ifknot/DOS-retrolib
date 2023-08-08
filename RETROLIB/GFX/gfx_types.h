/**

    @file      gfx_types.h
    @brief     
    @details   ~
    @author    ifknot
    @date      8.08.2023
    @copyright © ifknot, 2023. All right reserved.

**/
#ifndef GFX_CONSTANTS_H
#define GFX_CONSTANTS_H

#include <stdint.h>

namespace gfx {

    typedef int16_t scalar_t;

    struct point_t {
        int16_t x;      // abscissa
        int16_t y;      // ordinate 
    };

    struct line_t {
        point_t a;
        point_t b;
    };

    struct circle_t {
        point_t o;
        scalar_t r;
    };

}

#endif