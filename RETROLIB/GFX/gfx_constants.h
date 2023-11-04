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
#define VIDEO_ADAPTER_HGC           2
#define VIDEO_ADAPTER_HGC_PLUS      3
#define VIDEO_ADAPTER_HGC_INCOLOR   4
#define VIDEO_ADAPTER_HGC_CLONE     5
#define VIDEO_ADAPTER_CGA           6
#define VIDEO_ADAPTER_EGA           7
#define VIDEO_ADAPTER_MCGA          8
#define VIDEO_ADAPTER_VGA           9

namespace gfx {

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