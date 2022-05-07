/**
 *
 *  @file      cga_mode6_constants.h
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      2.04.2022
 *  @copyright © Jeremy Thornton, 2022. All right reserved.
 *
 */
#ifndef CGA_MODE6_CONSTANTS_H
#define CGA_MODE6_CONSTANTS_H

#include <stdint.h>

 /**
  * Mode 6 macro definitions for assembly
  * 
  * Graphic Mode: 640x200, 1-bit Color - few programs used this mode because it was monochrome, but the higher resolution allowed for more detailed interfaces. 
  * The resolution is 640x200 pixels, but has a dramatic pixel ratio of 1:2.4 (visually 640x480). 
  * When displayed on a CRT monitor, the display was visibly stretched in height, scanlines would be present, and a curved distortion would be noticeable near the edges of the display. 
  * Games like SimCity supported this mode.
  *
  * Everything is hard coded to shave a few clock cycles off the execution time
  * Using #define enables immediate addressing mode - in which the data operand is a part of the instruction itself
  * This matters on an 8088 where reg,imm is only 4 clock cycles as opposed to 12+EA for reg,mem
  * This advantage dwindles on the 286 (2:5) and 386 (2:4), vanishing on the 486(1:1) and beyond
  */
#define SCREEN_X_MIN 0
#define SCREEN_X_MAX 640
#define SCREEN_Y_MIN 0
#define SCREEN_Y_MAX 200
#define SCREEN_Y_SCALE 0.3125
#define PIXELS_PER_BYTE		8

namespace cga {

	typedef uint8_t colour_t;

	namespace mode6 {

		namespace colour {

			static const colour_t paper = 0x00;
			static const colour_t ink = 0x80;

   /**
    *  @enum  cga::mode6::colour::inks
    *  @brief 16 colour hardware palette
	*  @note Color 6 is treated differently - rather than dark yellow (#AAAA00) in order to achieve a more pleasing brown tone
	*  special circuitry in most RGBI monitors, including the IBM 5153 color display, makes an exception for color 6 and changes 
	*  its hue from dark yellow to brown by halving the analogue green signal's amplitude. 
	*  @details 
	*		colour		RGB				colour			RGB
	*	0	black	   #000000		8	gray		  #555555
	*	1	blue	   #0000AA		9	light blue	  #5555FF
	*	2	green	   #00AA00		10	light green	  #55FF55
	*	3	cyan	   #00AAAA		11	light cyan	  #55FFFF
	*	4	red		   #AA0000		12	light red	  #FF5555
	*	5	magenta	   #AA00AA		13	light magenta #FF55FF
	*	6	brown	   #AA5500		14	yellow		  #FFFF55
	*	7	light gray #AAAAAA		15	white		  #FFFFFF
	* 
	*  @note The background and border cannot be changed from black.
    */
			enum inks {
				black, blue, green, cyan, red, 
				magenta, brown, light_gray, 
				gray, light_blue, light_green, light_cyan,
				light_red, light_magenta, yellow, white
			};

		}

	}

}

#endif