/**
 *
 *  @brief     semigraphics for MDA
 *  @details   use text mode video hardware code page 437 to emulate raster graphics
 *  @url https://en.wikipedia.org/wiki/Semigraphics
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_MODE7_CONSTANTS_H
#define MDA_MODE7_CONSTANTS_H

#include "../../gfx_code_page_437_constants.h"

#include "../mda_constants.h"

#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 80
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 25
#define BYTES_PER_LINE 160 
#define CHARS_PER_SCREEN 2000
#define BYTES_PER_SCREEN 4000
#define COLOUR_DEPTH 16			// 8 bits for the ascii char and 8 bits for the attribute

#define ENABLE_MUL

#define DEFAULT_ATTRIBUTE attribute::normal;

namespace mda {

	namespace mode7 {

		namespace colour {

			/**
			*  @enum  mda::mode7::colour::inks
			*  @brief for cross mode compatibility a minimum 2 "colours" black and white
			*/
			enum inks {
				black = SPACE,
				dark_gray = LIGHT_SHADE,
				gray,
				light_gray,
				white = FULL_BLOCK
			};

		}

		namespace attribute {

			/**
			* The attribute bytes mostly behave like a bitmap:
			* 
			* Bits 0-2: 1 => underline, other values => no underline.
			* Bit 3: High intensity.
			* Bit 7: Blink
			*
			* but there are eight exceptions:
			*
			* Attributes 00h, 08h, 80h and 88h display as black space.
			* Attribute 70h displays as black on green.
			* Attribute 78h displays as dark green on green. In fact, depending on timing and on the design of the monitor, it may have a bright green 'halo' where the dark green and bright green bits meet.
			* Attribute F0h displays as a blinking version of 70h (if blinking is enabled); as black on bright green otherwise.
			* Attribute F8h displays as a blinking version of 78h (if blinking is enabled); as dark green on bright green otherwise.
			*/
			enum attributes {
				invisible,
				underline,
				normal,
				bright	= 0x0A,
				reverse = 0x70,
				blink	= 0x82,
				bright_blink	= 0x8A,
				reverse_bright	= 0x7A,
				reverse_blink	= 0xF0,
				reverse_bright_blink = 0xF8
			};

		}

	}

}

#endif