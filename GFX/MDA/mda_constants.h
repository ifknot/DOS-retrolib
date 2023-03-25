/**
 *
 *  @brief     MDA constants 
 *  @details   The original MDA is a full-length 8-bit ISA card containing the display controller and a printer port. 
 *  When present in a computer, it requires the following system resources:
 *  + 4k of RAM at address 0B0000h for its display buffer - this address is not completely decoded; the entire 32k from 0B0000h to 0B7FFFh is filled with repeats of this 4k area.
 *  + I/O addresses 03B0h-03BFh
 *  + The printer port uses IRQ7
 *  @url http://www.seasip.info/VintagePC/mda.html
 *  @author    Jeremy Thornton
 *  @date      20.07.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef MDA_CONSTANTS_H
#define MDA_CONSTANTS_H

#include <stdint.h>

#define MDA_VIDEO_RAM_SEGMENT	0B000h

namespace mda {

	typedef uint16_t size_type;

	typedef uint8_t colour_t;

	typedef uint8_t attribute_t;

	static const uint16_t VIDEO_RAM_SEGMENT = 0xB000;

}

#endif