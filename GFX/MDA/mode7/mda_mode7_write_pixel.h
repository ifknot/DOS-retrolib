/**
 *
 *  @brief
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_PLOT_POINT_H
#define MDA_MODE7_PLOT_POINT_H

#include "mda_mode7_constants.h"
#include "mda_mode7_write_character.h"

namespace mda {

    namespace mode7 {

        namespace screen_bound {

            inline void write_pixel(size_type x, size_type y, colour_t colour) {
                write_character(x, y, colour);
            }

        }

        namespace torus_bound {

        }

    }
}

#endif