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

	/**
	* @brief INT 10,12 - Video Subsystem Configuration (EGA/VGA)
	* AH = 12h
	* BL = 10  return video configuration information
	*
	* on return:
	* BH = 0 if color mode in effect
	*    = 1 if mono mode in effect
	* BL = 0 if 64k EGA memory
	*    = 1 if 128k EGA memory
	*    = 2 if 192k EGA memory
	*    = 3 if 256k EGA memory
	* CH = feature bits
	* CL = switch settings
	*
	* BL = 20  select alternate print screen routine
	*
	* BL = 30  select scan lines for alphanumeric modes
	*    AL = 0  200 scan lines
	*       = 1  350 scan lines
	*       = 2  400 scan lines
	*
	* on return: AL = 12
	*
	* BL = 31  select default palette loading
	*    AL = 0 enable default palette loading
	*       = 1 disable default palette loading
	*
	* on return: AL = 12
	*
	* BL = 32  CPU access to video RAM
	*    AL = 0  enable CPU access to video RAM and I/O ports
	*       = 1  disable CPU access to video RAM and I/O ports
	*
	* on return: AL = 12
	*
	* BL = 33  Gray scale summing
	*    AL = 0  enable gray scale summing
	*       = 2  disable gray scale summing
	*
	* on return: AL = 12
	*
	* BL = 34  cursor emulation
	*    AL = 0  enable cursor emulation
	*       = 1  disable cursor emulation
	*
	* on return: AL = 12
	*
	* BL = 35  PS/2 video display switching
	*    AL = 0 initial adapter video off
	*       = 1 initial planar video on
	*       = 2 switch active video off
	*       = 3 switch inactive video on
	*    ES:DX pointer to 128 byte save area (when AL = 0, 2 or 3)
	*
	* on return: AL = 12
	*
	* BL = 36  video refresh control
	*    AL = 0 enable refresh
	*       = 1 disable refresh
	*
	* on return: AL = 12
	*/
	video_subsystem_config_t video_subsystem_configuration(uint8_t subsystem, uint8_t option = 0) {

	}

}