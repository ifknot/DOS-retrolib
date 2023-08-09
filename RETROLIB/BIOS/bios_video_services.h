/*****************************************************************//**
 * \file   bios_video_services.h
 * \brief
 *
 * \url https://stackoverflow.com/questions/57834460/what-is-i-h-ah-o-h-ah-and-int86
 *
 * \author ifkno
 * \date   November 2021
 *********************************************************************/
//#pragma once

#ifndef BIOS_VIDEO_SERVICES_H
#define BIOS_VIDEO_SERVICES_H

#include "bios_video_services_types.h"

namespace bios {

    void set_video_mode(video_mode_t mode);


    video_state_t get_video_state();

    /**
    *  @brief read Video Display Data Area from BIOS data area (segment 40h)
    *  @details
    *           40:49   byte    Current video mode
    *           40:4A   word    Number of screen columns
    *           40:4C   word    Size of current video regen buffer in bytes
    *           40:4E   word    Offset of current video page in video regen buffer
    *           40:50  8 words  Cursor position of pages 1-8, high order byte=row low order byte=column; changing this data isn't reflected immediately on the display
    *           40:60   byte    Cursor ending (bottom) scan line (don't modify)
    *           40:61   byte    Cursor starting (top) scan line (don't modify)
    *           40:62   byte    Active display page number
    *           40:63   word    Base port address for active 6845 CRT controller 3B4h = mono, 3D4h = color
    *           40:65   byte    6845 CRT mode control register value (port 3x8h) EGA/VGA values emulate those of the MDA/CGA
    *           40:66   byte    CGA current color palette mask setting (port 3d9h) EGA and VGA values emulate the CGA
    *  @param vdda - target array for data copy
    */
    void read_VDDA_into(char* vdda);

    void print_VDDA();

    namespace vga {

            uint8_t enable_CPU_access_to_video_RAM();

            
            video_display_combination_t get_video_display_combination();
    }

    namespace ega {

        video_config_info_t get_video_configuration_information();

    }

    /**
    * Detects whether or not a given I/O address is that of a 6845 CRT Controller
    * The Cursor Location Low register of the alleged CRTC is written with an arbitrary value
    * [1] Wilton, Richard, Programmer's Guide to PC and PS/2 Video Systems.
    * Wait an arbitrary period of time then check if the value is retained?
    * In which case the CRTC is *probably* detected
    *
    */
    bool detect_CRTC_at_port(uint16_t port_number);

    /**
    * If an MDA card is detected, however, you can also distinguish between an MDA card and the Hercules cards.
    * To do this, the vertical sync bit is sampled and then for a certain time interval, is continually and frequently re-sampled.
    * + if no change is observed, the video card is assumed to be an MDA card.
    * + if the vertical sync bit changes, the video card is one of the Hercules graphics cards.
    * The specific card is identified by examining bits 4-6 of the status port:
    * + a pattern of 001 indicates a Hercules Graphics Card Plus
    * + a pattern of 101 indicates a Hercules In-Color Card
    * + any other pattern is a Hercules Graphics Card.
    *
    * Reading from port 03BAh returns vertical sync in bit 7, and a card ID in bits 6-4:
    * 000: Hercules
    * 001: Hercules Plus
    * 101: Hercules InColor
    * 111: Unknown clone
    *
    * @note Only trust this ID once you've checked that there's a vertical sync present; if bit 7 is the same for 32768 reads in succession, then there isn't.
    * @note Some Hercules cards support a light pen. Bit 1 of port 3BAh returns the lightpen sensor status; any write to port 3BBh resets the light pen status.
    *
    * \return enum video_adapter_t
    */
    video_adapter_t detect_HGA_adapter_type();

    /**
    * The Method:
    * The identification process begins with calls to the enhanced video BIOS:
    * + first a call that only a VGA or MCGA equipped system will support
    * + then one that only an EGA card should support
    * These calls will only function with a video BIOS that supports these more sophisticated video systems.
    * CGA, MDA and Hercules cards do not have enhanced video BIOS ROMs, and the calls *should* fail harmlessly with all registers preserved.
    * The enhanced BIOS calls will succeed, modifying the registers to identify the installed hardware.
    * If the calls succeed, the job is done, otherwise time to hunt for a CGA or MDA card...
    * Next the routines attempt to identify the CRT controller (CTRC) status port's address in the PC's I/O space.
    * + the MDA and Hercules cards' CRTC status port is usually found at 3B4H
    * + the CGA cards' CRTC status port at 3D4H.
    * The routines write an arbitrary value to the Cursor Location Low register (0Fh) and then, after a reasonable delay,
    * attempt to read that value back from one of the status port addresses.
    * If the value is recovered, the routines assume they have found the CTRC of the associated card.
    * In the case of the CGA cards and their clones, there is nothing left to do.
    *
    * \return enum video_adapter_t
    */
    video_adapter_t detect_video_adapter_type();

}

#endif
