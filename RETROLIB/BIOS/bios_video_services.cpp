/**
 *
 *  @file      bios_video_services.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      4.11.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#include "bios_video_services.h"

namespace bios {

	/**
	* @brief INT 10,0 - Set Video Mode
	* AH = 00
	* AL = video_mode_t 
	* @see bios_video_services_constants.h enum type
	*/
	void set_video_mode(uint8_t mode) {
		__asm {
			.8086
			mov		al, mode
			mov		ah, SET_VIDEO_MODE
			int		BIOS_VIDEO_SERVICES
		}
	}

	/**
	* @brief INT 10,F - Get Video State
	* AH = 0F
	* 
	* on return:
	* AH = number of screen columns
	* AL = mode currently set (see VIDEO MODES)
	* BH = current display page
	* 
	* @note - video modes greater than 13h on EGA, MCGA and VGA indicate
	* INT 10,0 was called with the high bit of the mode (AL) set
	* to 1, meaning the display does not need cleared
	* @note - function returns byte value at 40:49;  On EGA, MCGA and
	* VGA bit 7 of register AL is determined by bit 7 of BIOS Data
	* Area byte 40:87.   This bit is usually set by INT 10,0
	* with bit 7 of the requested mode (in AL) set to 1
	*/
	void get_video_state(video_state_t* state) {
		__asm {
			.8086
			mov		ah, GET_CURRENT_VIDEO_STATE
			int		BIOS_VIDEO_SERVICES
			lds		di, state
			mov		[di], ah						; number of screen columns
			mov		[di + 1], al					; video mode 
			mov		[di + 2], bh					; display page
		}
	}

}