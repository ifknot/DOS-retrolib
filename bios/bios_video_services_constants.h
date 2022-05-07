/*****************************************************************//**
 * \file   dos_video_services_types.h
 * \brief  
 * 
 * \author ifkno
 * \date   September 2021
 *********************************************************************/
//#pragma once

#ifndef BIOS_VIDEO_SERVICES_CONSTANTS_H
#define	BIOS_VIDEO_SERVICES_CONSTANTS_H

#include <stdint.h> // Open Watcom fails with <cstdint> 

// 
#define BIOS_VIDEO_SERVICE 0x10
// 
#define BIOS_DATA_AREA_SEGMENT 40h
// Video Display Data Area
#define BIOS_VDDA_OFFSET 49h
// Video Display Data Area size 30 bytes
#define BIOS_VDDA_SIZE 30

namespace bios {

	/**
	 * Video BIOS INT 10 video modes.
	 */
	enum video_mode_t {
		TEXT_MONOCHROME_40X25 = 0,			// 00  40x25 B/W text (CGA,EGA,MCGA,VGA)
		TEXT_16_COLOUR_40X25,				// 01  40x25 16 color text (CGA,EGA,MCGA,VGA)
		TEXT_16_GRAY_80X25,					// 02  80x25 16 shades of gray text (CGA,EGA,MCGA,VGA)
		TEXT_16_COLOUR_80x25,				// 03  80x25 16 color text (CGA,EGA,MCGA,VGA)
		GRAPHICS_4_COLOUR_320x200,			// 04  320x200 4 color graphics (CGA,EGA,MCGA,VGA)
		GRAPHICS_4_GRAY_320x200,			// 05  320x200 4 gray graphics (CGA,EGA,MCGA,VGA)
		GRAPHICS_MONOCHROME_640X200,		// 06  640x200 B/W graphics (CGA,EGA,MCGA,VGA)
		TEXT_MONOCHROME_80X25,				// 07  80x25 Monochrome text (MDA,HERC,EGA,VGA)
		PCJR_GRAPHICS_16_COLOUR_160X200,	// 08  160x200 16 color graphics (PCjr)
		PCJR_GRAPHICS_16_COLOUR_320X200,	// 09  320x200 16 color graphics (PCjr)
		PCJR_GRAPHICS_4_COLOUR_640X200,		// 0A  640x200 4 color graphics (PCjr)
		RESERVED1_EGA,						// 0B  Reserved (EGA BIOS function 11)
		RESERVED2_EGA,						// 0C  Reserved (EGA BIOS function 11)
		GRAPHICS_16_COLOUR_320X200,			// 0D  320x200 16 color graphics (EGA,VGA)
		GRAPHICS_16_COLOUR_640X200,			// 0E  640x200 16 color graphics (EGA,VGA)
		GRAPHICS_MONOCHROME_640X350,		// 0F  640x350 Monochrome graphics (EGA,VGA)
		GRAPHICS_16_COLOUR_640X350,			// 10  640x350 16 color graphics (EGA or VGA with 128K)
		GRAPHICS_MONOCHROME_640X480,		// 11  640x480 B/W graphics (MCGA,VGA)
		GRAPHICS_16_COLOUR_640X480,			// 12  640x480 16 color graphics (VGA)
		GRAPHICS_256_COLOUR_320X200			// 13  320x200 256 color graphics (MCGA,VGA)
		/*
		8x  EGA, MCGA or VGA ignore bit 7, see below
		9x  EGA, MCGA or VGA ignore bit 7, see below

		if AL bit 7=1, prevents EGA,MCGA & VGA from clearing display
		N.B. function updates byte at 40:49;  bit 7 of byte 40:87
		*/
	};

	/**
	 * Video BIOS INT 10 services.
	 */
	enum video_service_t {
		SET_VIDEO_MODE = 0,				// 0	Set video mode	
		SET_CURSOR_TYPE,				// 1	Set cursor type
		SET_CURSOR_POS,					// 2	Set cursor position
		READ_CURSOR_POS,				// 3	Read cursor position
		READ_LIGHT_PEN,					// 4	Read light pen
		SELECT_DISPLAY_PAGE,			// 5	Select active display page
		SCROLL_PAGE_UP,					// 6	Scroll active page up
		SCROLL_PAGE_DOWN,				// 7	Scroll active page down
		READ_CHAR_ATTRIB,				// 8	Read character and attribute at cursor
		WRITE_CHAR_ATTRIB,				// 9	Write character and attribute at cursor
		WRITE_CHAR,						// A	Write character at current cursor
		SET_COLOUR_PALETTE,				// B	Set color palette
		SET_PIXEL,						// C	Write graphics pixel at coordinate
		GET_PIXEL,						// D	Read graphics pixel at coordinate
		WRITE_TEXT_TELETYPE,			// E	Write text in teletype mode
		GET_VIDEO_STATE,				// F	Get current video state
		PALETTE_REGISTERS,				// 10	Set/get palette registers (EGA/VGA)
		CHAR_GENERATOR,					// 11	Character generator routine (EGA/VGA)
		VIDEO_SUB_CONFIG,				// 12	Video subsystem configuration (EGA/VGA)
		WRITE_STRING,					// 13	Write string (BIOS after 1/10/86)
		LOAD_LCD_CHAR_FONT,				// 14	Load LCD char font (convertible)
		RETURN_PHYSICAL_DISPLAY_PARMS,	// 15	Return physical display parms (convertible)
		VIDEO_DISPLAY_COMBINATION = 26,	// 1A	Video Display Combination (VGA)
		VIDEO_BIOS_STATE_INFORMATION,	// 1B	Video BIOS Functionality/State Information (MCGA/VGA)
		SAVE_RESTORE_VIDEO_STATE		// 1C	Save/Restore Video State  (VGA only)
		// INT 10,FE - Get DESQView/TopView Virtual Screen Regen Buffer
		// INT 10, FF - Update DESQView / TopView Virtual Screen Regen Buffer
	};

	/**
	 * INT 10,12 - Video Subsystem Configuration (EGA/VGA).
	 * BL = 10  return video configuration information
		on return:
		BH = 0 if color mode in effect
		   = 1 if mono mode in effect
		BL = 0 if 64k EGA memory
		   = 1 if 128k EGA memory
		   = 2 if 192k EGA memory
		   = 3 if 256k EGA memory
		CH = feature bits
		CL = switch settings

		BL = 20  select alternate print screen routine

		BL = 30  select scan lines for alphanumeric modes
		   AL = 0  200 scan lines
			  = 1  350 scan lines
			  = 2  400 scan lines
		on return:
		AL = 12

		BL = 31  select default palette loading
		AL = 0 enable default palette loading
		   = 1 disable default palette loading
		on return:
		AL = 12

		BL = 32  CPU access to video RAM
		AL = 0  enable CPU access to video RAM and I/O ports
		   = 1  disable CPU access to video RAM and I/O ports
		on return:
		AL = 12

		BL = 33  Gray scale summing
		AL = 0  enable gray scale summing
		   = 2  disable gray scale summing
		on return:
		AL = 12

		BL = 34  cursor emulation
		AL = 0  enable cursor emulation
		   = 1  disable cursor emulation
		on return:
		AL = 12

		BL = 35  PS/2 video display switching
		AL = 0 initial adapter video off
		   = 1 initial planar video on
		   = 2 switch active video off
		   = 3 switch inactive video on
		   ES:DX pointer to 128 byte save area (when AL = 0, 2 or 3)
		on return:
		AL = 12

		BL = 36  video refresh control
		AL = 0 enable refresh
		   = 1 disable refresh
		on return:
		AL = 12
	 */
	enum video_subsystem_t {
		GET_VIDEO_CONFIG_INFO = 0x10,
		SELECT_ALTERNATE_PRINT_SCREEN_ROUTINE = 0x20,
		SELECT_SCAN_LINES_FOR_ALPHANUMERIC_MODES = 0x30,
		SELECT_DEFAULT_PALETTE_LOADING,
		CPU_ACCESS_TO_VIDEO_RAM,
		GRAY_SCALE_SUMMING,
		CURSOR_EMULATION,
		PS2_VIDEO_DISPLAY_SWITCHING,
		VIDEO_REFRESH_CONTROL
	};

	/**
	 * MDA/HGA and CGA 6845 CRT Controller port numbers.
	 */
	enum crtc_port_t {
		MDA_crtc_port	= 0x03B4,
		CGA_crtc_port	= 0x03D4
	};

	/**
	 * Types of video adapter.
	 */
	enum video_adapter_t {
		UNKNOWN = 0,
		MDA,			// 1
		HGC,			// 2
		HGC_PLUS,		// 3
		HGC_INCOLOR,	// 4	
		CGA,
		EGA,
		MCGA,
		VGA
	};

	/**
	 * Types of display.
	 */
	enum video_display_t {
		NO_DISPLAY = 0,
		MONOCHROME,
		COLOR,
		ANALOG_MONO,
		ANALOG_COLOR,
		DIGITAL_COLOR,
		UNRECOGNIZED
	};

	static char video_mode_names[20][64] = {
		"00  40x25 B/W text (CGA)",
		"01  40x25 16 color text (CGA)",
		"02  80x25 16 shades of gray text (CGA)",
		"03  80x25 16 color text (CGA)",
		"04  320x200 4 color graphics (CGA)",
		"05  320x200 4 color graphics (CGA)",
		"06  640x200 B/W graphics (CGA)",
		"07  80x25 Monochrome text (MDA,HERC)",
		"08  160x200 16 color graphics (PCjr)",
		"09  320x200 16 color graphics (PCjr)",
		"0A  640x200 4 color graphics (PCjr)",
		"0B	 Reserved (EGA BIOS function 11)",
		"0C	 Reserved (EGA BIOS function 11)",
		"0D	 320x200 16 color graphics (EGA)",
		"0E	 640x200 16 color graphics (EGA)",
		"0F	 640x350 Monochrome graphics (EGA)",
		"10	 640x350 16 color graphics (EGA)",
		"11	 640x480 B/W graphics (MCGA)",
		"12	 640x480 16 color graphics (VGA)",
		"13  320x200 256 color graphics (MCGA, VGA)"
	};

	static char video_adapter_names[10][255] = {
		"Unknown Adapter", 
		"MDA",
		"Hercules",
		"Hercules Plus",
		"Hercules InColor",
		"CGA",
		"EGA",
		"MCGA",
		"VGA"
	};

	static char video_display_names[7][255] = {
		"no display",
		"monochrome",
		"color",
		"analog_mono",
		"analaog colour",
		"digital_color",
		"unrecognized"
	};

}

#endif