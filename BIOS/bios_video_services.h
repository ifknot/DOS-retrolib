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

#include <iostream>
#include <cassert>
#include <stdint.h>
#include <dos.h>

#include "bios_video_services_constants.h"
#include "bios_video_services_types.h"

#include "../DOS/dos_services_types.h"
#include "../DOS/dos_error_messages.h"

#include "../DEBUG/debug_macros.h"

namespace bios {

    void set_video_mode(video_mode_t mode) {
        union REGS r;
        r.h.ah = SET_VIDEO_MODE;
        r.h.al = mode;
        int86(0x10, &r, &r);
    }


    video_state_t get_video_state() {
        video_state_t video_state;
        union REGS r;
        r.h.ah = GET_VIDEO_STATE;
        int86(0x10, &r, &r);
        video_state.columns = r.h.ah;
        video_state.mode = (video_mode_t)r.h.al;
        video_state.page = r.h.bh;
        return video_state;
    }

    /**
    *  @brief read Video Display Data Area from BIOS data area (segment 40h)
    *  @details
    *		40:49	byte	Current video mode
    *		40:4A	word	Number of screen columns
    *		40:4C	word	Size of current video regen buffer in bytes
    *		40:4E	word	Offset of current video page in video regen buffer
    *		40:50  8 words	Cursor position of pages 1-8, high order byte=row low order byte=column; changing this data isn't reflected immediately on the display
    *		40:60	byte	Cursor ending (bottom) scan line (don't modify)
    *		40:61	byte	Cursor starting (top) scan line (don't modify)
    *		40:62	byte	Active display page number
    *		40:63	word	Base port address for active 6845 CRT controller 3B4h = mono, 3D4h = color
    *		40:65	byte	6845 CRT mode control register value (port 3x8h) EGA/VGA values emulate those of the MDA/CGA
    *		40:66	byte	CGA current color palette mask setting (port 3d9h) EGA and VGA values emulate the CGA
    *  @param vdda - target array for data copy
    */
    void read_VDDA_into(char* vdda) {
        __asm {
            .8086
            mov		ax, BIOS_DATA_AREA_SEGMENT
            mov		ds, ax
            mov		si, BIOS_VDDA_OFFSET    ; DS:SI = 0040:0049 (BIOS Data Area)
            les     di, vdda                ; ES:DI = array to copy data

            cld                             ; increment
            mov		cx, BIOS_VDDA_SIZE      ; 30 bytes of VDDA data
            rep		movsb                   ; copy VDDA bytes to array

        }
    }

    void print_VDDA() {

        char vdda[30];
        read_VDDA_into(vdda);
        std::cout
            << "video mode " << std::dec << (int)vdda[0] << '\n'
            << std::dec << *(int16_t*)(vdda + 1) << " columns\n"
            << std::dec << *(int16_t*)(vdda + 3) / 1024 << "K video memory\n"
            << "video page offset " << std::hex << *(int16_t*)(vdda + 5) << '\n'
            << "cursor loc page 0 " << std::hex << *(int16_t*)(vdda + 7) << '\n'
            << "cursor loc page 1 " << std::hex << *(int16_t*)(vdda + 9) << '\n'
            << "cursor loc page 2 " << std::hex << *(int16_t*)(vdda + 11) << '\n'
            << "cursor loc page 3 " << std::hex << *(int16_t*)(vdda + 13) << '\n'
            << "cursor loc page 4 " << std::hex << *(int16_t*)(vdda + 15) << '\n'
            << "cursor loc page 5 " << std::hex << *(int16_t*)(vdda + 17) << '\n'
            << "cursor loc page 6 " << std::hex << *(int16_t*)(vdda + 19) << '\n'
            << "cursor loc page 7 " << std::hex << *(int16_t*)(vdda + 21) << '\n'
            << "cursor ending (bottom) scan line " << std::dec << (int)vdda[23] << '\n'
            << "cursor starting (top) scan line  " << std::dec << (int)vdda[24] << '\n'
            << "display page #" << std::dec << (int)vdda[25] << '\n'
            << "base port address for active 6845 CRT controller " << std::hex << *(int16_t*)(vdda + 26) << " (3B4h=mono, 3D4h=color)\n"
            << "6845 CRT mode control register value " << std::dec << (int)vdda[27] << '\n'
            << "CGA current color palette mask setting (port 3d9h) " << std::dec << (int)vdda[29] << '\n'
        ;

    }

    namespace vga {

            /**
            * INT 10,12 - Video Subsystem Configuration (EGA/VGA)
            *      BL  = 32  CPU access to video RAM
            *      AL  = 0  enable CPU access to video RAM and I/O ports
            *          = 1  disable CPU access to video RAM and I/O ports
            *      on return:
            *      AL  = 12.
            *
            * \return
            */
            uint8_t enable_CPU_access_to_video_RAM() {
                    union REGS r;
                    r.h.ah = VIDEO_SUB_CONFIG;
                    r.h.bl = CPU_ACCESS_TO_VIDEO_RAM;
                    r.h.al = 0x00;  //enable CPU access to video RAM and I/O ports
                    int86(BIOS_VIDEO_SERVICE, &r, &r);
                    if (r.x.cflag != 0) {
                            LOG("fail");//LOG(dos::error::messages[_doserrno]);
                    }
                    return r.h.al;
            }

            /**
                * INT 10,1A - Video Display Combination (VGA)
                * AH   = 1A
                * AL   = 00 get video display combination
                *      = 01 set video display combination
                * BL   = active display  (see table below)
                * BH  = inactive display
                * on return:
                * AL  = 1A, if a valid function was requested in AH
                * BL  = active display  (AL=00, see table below)
                * BH  = inactive display  (AL=00)
                *
                * Valid display codes:
                *
                * FF  Unrecognized video system
                * 00  No display
                * 01  MDA with monochrome display
                * 02  CGA with color display
                * 03  Reserved
                * 04  EGA with color display
                * 05  EGA with monochrome display
                * 06  Professional graphics controller
                * 07  VGA with analog monochrome display
                * 08  VGA with analog color display
                * 09  Reserved
                * 0A  MCGA with digital color display
                * 0B  MCGA with analog monochrome display
                * 0C  MCGA with analog color display
                *
                * \return
                */
            video_display_combination_t get_video_display_combination() {
                video_display_combination_t combo;
                union REGS r;
                r.h.ah = bios::VIDEO_DISPLAY_COMBINATION;
                r.h.al = 0;     // 0 = get video display combination
                int86(BIOS_VIDEO_SERVICE, &r, &r);
                assert(r.h.al == bios::VIDEO_DISPLAY_COMBINATION);
                switch (r.h.bl) {
                case 0:
                    combo.adapter = UNKNOWN;
                    combo.display = NO_DISPLAY;
                    break;
                case 1:     // 01  MDA with monochrome display
                    combo.adapter = MDA;
                    combo.display = MONOCHROME;
                    break;
                case 2:     // 02  CGA with color display
                    combo.adapter = CGA;
                    combo.display = COLOR;
                    break;
                case 4:     // 04  EGA with color display
                    combo.adapter = EGA;
                    combo.display = COLOR;
                    break;
                case 5:     // 05  EGA with monochrome display
                    combo.adapter = EGA;
                    combo.display = MONOCHROME;
                    break;
                case 7:     //  07  VGA with analog monochrome display
                    combo.adapter = VGA;
                    combo.display = ANALOG_MONO;
                    break;
                case 8:     // 08  VGA with analog color display
                    combo.adapter = VGA;
                    combo.display = ANALOG_COLOR;
                    break;
                case 10:    // 0A  MCGA with digital color display
                    combo.adapter = MCGA;
                    combo.display = DIGITAL_COLOR;
                    break;
                case 11:    // 0B   MCGA with analog monochrome display
                    combo.adapter = MCGA;
                    combo.display = ANALOG_MONO;
                    break;
                case 12:    // 0C  MCGA with analog color display
                    combo.adapter = MCGA;
                    combo.display = ANALOG_COLOR;
                    break;
                default:
                    combo.adapter = UNKNOWN;
                    combo.display = UNRECOGNIZED;
                }
                return combo;
            }

    }

    namespace ega {

        //using namespace bios;

        /**
        * INT 10,12 - Video Subsystem Configuration (EGA/VGA)
        *      BL  = 10  return video configuration information, on return:
        *      BH  = 0 if color mode in effect
        *          = 1 if mono mode in effect
        *      BL  = 0 if 64k EGA memory
        *          = 1 if 128k EGA memory
        *          = 2 if 192k EGA memory
        *          = 3 if 256k EGA memory
        *      CH  = feature bits
        *      CL  = switch settings.
        *
        * \return
        */
        video_config_info_t get_video_configuration_information() {
                video_config_info_t info;
                union REGS r;
                r.h.ah = VIDEO_SUB_CONFIG;
                r.h.bl = GET_VIDEO_CONFIG_INFO;
                int86(BIOS_VIDEO_SERVICE, &r, &r);
                if (r.x.cflag != 0) {
                        LOG("fail");//LOG(dos::error::messages[_doserrno]);
                }
                info.mode = r.h.bh;
                info.memory = r.h.bl;
                info.feature_bits = r.h.ch;
                info.switch_settings = r.h.cl;
                return info;
        }

    }

    /**
    * Detects whether or not a given I/O address is that of a 6845 CRT Controller
    * The Cursor Location Low register of the alleged CRTC is written with an arbitrary value
    * [1] Wilton, Richard, Programmer's Guide to PC and PS/2 Video Systems.
    * Wait an arbitrary period of time then check if the value is retained?
    * In which case the CRTC is *probably* detected
    *
    */
    bool detect_CRTC_at_port(uint16_t port_number) {
        uint8_t found = 0;
        __asm {
            .8086
            push ax
            push dx

            mov     ax, 0Fh             ; cursor low register
            mov     dx, port_number
            out     dx, al              ; select 6845 cursor low reg
            inc     dx
            in      al, dx              ; AL is old Cursor Low value
            mov     ah, al              ; preserve old value in AH
            mov     al, 66h             ; AL = arbitrary new value
            out     dx, al              ; try to write new value to 6845

            mov     cx, 100h            ; deemed adequate in the literature
    WAIT:   loop    WAIT                ; wait for 6845 to respond

            in      al, dx              ; read back value
            xchg    ah, al              ; AL becomes old Cursor Low value
            out     dx, al              ; restore old value

            cmp     ah, 66h             ; test whether 6845 responded with new value?
            jne     EXIT                ; jump if it did not, leaving found as 0

            mov     found, 1

    EXIT:   pop dx
            pop ax
        }
        return static_cast<bool>(found);
    }

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
    video_adapter_t detect_HGA_adapter_type() {
        video_adapter_t type = UNKNOWN;
        if (detect_CRTC_at_port(MDA_crtc_port)) {
            __asm {
                .8086
                push ax
                push cx
                push dx

                mov     dx, 3BAh    ; DX: = 3BAh(MDA/Hercules status port)
                in      al, dx      ; read status port
                and     al, 80h     ; mask off only bit 7
                mov     ah, al      ; copy al into ah = bit 7 (vertical sync on HGC)

                mov     cx, 8000h   ; 32768 samples - deemed adequate in the literature
        L1:     in      al, dx      ; read status port
                and     al, 80h     ; isolate bit 7
                cmp     ah, al      ; has the vertical sync bit changed?
                loope   L1          ; no sample again yes leave loop

                jne     HGA         ; bit 7 changed, it's a Hercules
                mov     type, 1     ; MDA
                jmp     EXIT

        HGA:    in      al, dx      ; read status port again
                and     al, 70h     ; isolate bits 4-6

                cmp     al, 70h     ; Unknown clone bit pattern
                jne     L2
                mov     type, 0     ; UKNOWN
                jmp     exit

        L2:     cmp     al, 50h     ; Hercules InColor bit pattern
                jne     L3
                mov     type, 4     ; HGC_INCOLOR
                jmp     exit

        L3:     cmp     al, 10h     ; Hercules Plus bit pattern
                jne     L4
                mov     type, 3     ; HGC_PLUS
                jmp     exit

        L4:     mov     type, 2     ; HGC

        EXIT:   pop dx
                pop cx
                pop ax
            }
        }
        return type;
    }

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
    video_adapter_t detect_video_adapter_type() {
        video_adapter_t card_type = UNKNOWN;
        // detect VGA by attempting to use a VGA specific Video Subsystem Configuration (EGA/VGA) function
        if (vga::enable_CPU_access_to_video_RAM() == VIDEO_SUB_CONFIG) {
            // detect if MCGA or VGA
            return vga::get_video_display_combination().adapter;
        }
        // not VGA so detect EGA by attempting to use an EGA specific Video Subsystem Configuration (EGA/VGA) function
        ega::video_config_info_t info = bios::ega::get_video_configuration_information();
        if (info.memory != GET_VIDEO_CONFIG_INFO) { // if not enhanced video bios the fail harmlessly with all registers preserved
            return EGA;
        }
        // not EGA so detect CGA by attempting to write and read from CRTC port on CGA cards
        if (detect_CRTC_at_port(CGA_crtc_port)) {
            return CGA;
        }
        // not CGA so detect if MDA or Hercules or unknown?
        return detect_HGA_adapter_type();
    }

}

#endif