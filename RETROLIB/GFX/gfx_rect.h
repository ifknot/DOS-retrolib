/**

    @brief     
    @details   ~
    @author    Jeremy Thornton
    @date      3.01.2024
    @copyright © Jeremy Thornton, 2024. All right reserved.

**/
#ifndef GFX_RECT_H
#define GFX_RECT_H

#include <stdint.h>

namespace gfx {

    struct rect {
        uint16_t x;
        uint16_t y;
        uint16_t w;
        uint16_t h;
    };

    //bool contains(uint16_t x, uint16_t y);
        
    //bool intersects(rect* r);

    //void union(rect* ru, rect* r1, rect* r2);

    //void move(rect* r, uint16_t x, uint16_t y);

    //translate(rect* t, uint16_t dx, uint16_t dy);
}

#endif