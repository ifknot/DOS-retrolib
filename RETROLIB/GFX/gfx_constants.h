/**

    @file      gfx_constants.h
    @brief     
    @details   ~
    @author    ifknot
    @date      8.08.2023
    @copyright © ifknot, 2023. All right reserved.

**/
#ifndef GFX_CONSTANTS_H
#define GFX_CONSTANTS_H

/**
* Types of video adapter.
*/
#define VIDEO_ADAPTER_UKNOWN        0
#define VIDEO_ADAPTER_MDA           1
#define VIDEO_ADAPTER_HGA           2
#define VIDEO_ADAPTER_HGA_PLUS      3
#define VIDEO_ADAPTER_HGA_INCOLOR   4
#define VIDEO_ADAPTER_HGA_CLONE     5
#define VIDEO_ADAPTER_CGA           6
#define VIDEO_ADAPTER_EGA           7
#define VIDEO_ADAPTER_MCGA          8
#define VIDEO_ADAPTER_VGA           9

namespace gfx {

    /**
    * MDA/HGA and CGA 6845 CRT Controller port numbers.
    */
    enum crtc_port_t {
        crtc_port_MDA = 0x03B4,
        crtc_port_HGA = 0x03B4,
        crtc_port_CGA = 0x03D4
    };

    static char video_adapter_names[10][32] = {
        "Unknown",
        "MDA",
        "Hercules",
        "Hercules Plus",
        "Hercules InColor",
        "Hercules Clone",
        "CGA",
        "EGA",
        "MCGA",
        "VGA"
    };

}

#endif