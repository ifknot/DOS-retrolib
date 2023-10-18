/*****************************************************************//**
 * \file   bios_video_services_types.h
 * \brief  
 * 
 * \author ifkno
 * \date   November 2021
 *********************************************************************/
//#pragma once

#ifndef BIOS_VIDEO_SERVICES_TYPES_H
#define BIOS_VIDEO_SERVICES_TYPES_H

#include <stdint.h> // Open Watcom fails with <cstdint> 

#include "bios_video_services_constants.h"
#include "../dos/dos_error_messages.h"

namespace bios {

	/**
	 * Video BIOS get video mode return structure.
	 */
	struct video_state_t {
		uint8_t			columns;
		video_mode_t	mode;
		uint8_t			page;
	};

	namespace ega {

		/**
		 * video configuration information
		 * 
		 *	mode	= 0 if color mode in effect
		 *			= 1 if mono mode in effect
		 * 
		 *	memory	= 0 if 64k EGA memory
		 *			= 1 if 128k EGA memory
		 *			= 2 if 192k EGA memory
		 *			= 3 if 256k EGA memory
		 * 
		 * feature bits - on EGA these bits send signal the feature connector (lines FCO and FCl).
		 * Thus, a device attached to the feature connector may be placed under program control.
		 * The function would be defined by the attached device.
		 * \note VGA reserves the use of all 7 bits, and bit 3 must be 0.
		 * 
		 * switch settings - Switch settings (switches on the EGA card) Bits 0-3 are switches 1-4 respectively. 
		 * \note 1 = switch Off, 0 = switch On. Thus 1000b means switches 1-3 are ON and switch 4 is OFF.
		 * \note see table pg 66 "EGA/VGA A Programmers Reference Guide" Kleiwer B. D. 1990
		 */
		struct video_config_info_t {
			uint8_t		mode;
			uint8_t		memory;
			uint8_t		feature_bits;
			uint8_t		switch_settings;
		};

	}

	namespace vga {

		struct video_display_combination_t {
			bios::video_adapter_t adapter;
			bios::video_display_t display;
			//bios::video_display_t inactive_display;
		};

	}

}



#endif