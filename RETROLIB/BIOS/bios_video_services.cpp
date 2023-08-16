#include "bios_video_services.h" 

#include <iostream>
#include <cassert>
#include <stdint.h>
#include <dos.h>

#include "bios_video_services_constants.h"
#include "bios_video_services_types.h"

#include "../DOS/dos_services_types.h"
#include "../DOS/dos_error_messages.h"

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

    void read_VDDA_into(char* vdda) {
        __asm {
            .8086
            mov         ax, BIOS_DATA_AREA_SEGMENT
            mov         ds, ax
            mov         si, BIOS_VDDA_OFFSET    ; DS:SI = 0040:0049 (BIOS Data Area)
            les     di, vdda                ; ES:DI = array to copy data

            cld                             ; increment
            mov         cx, BIOS_VDDA_SIZE      ; 30 bytes of VDDA data
            rep         movsb                   ; copy VDDA bytes to array

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
                          //LOG("fail");//LOG(dos::error::messages[_doserrno]);
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
                        //LOG("fail");//LOG(dos::error::messages[_doserrno]);
                }
                info.mode = r.h.bh;
                info.memory = r.h.bl;
                info.feature_bits = r.h.ch;
                info.switch_settings = r.h.cl;
                return info;
        }

    }

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


    video_adapter_t detect_HGA_adapter_type() {
        video_adapter_t adapter = UNKNOWN;
        if (detect_CRTC_at_port(MDA_crtc_port)) {
            __asm {
                .8086

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
                mov     adapter, 1  ; MDA
                jmp     EXIT

        HGA:    in      al, dx      ; read status port again
                and     al, 70h     ; isolate bits 4-6

                cmp     al, 70h     ; Unknown clone bit pattern
                jne     L2
                mov     adapter, 0  ; UKNOWN
                jmp     exit

        L2:     cmp     al, 50h     ; Hercules InColor bit pattern
                jne     L3
                mov     adapter, 4  ; HGC_INCOLOR
                jmp     exit

        L3:     cmp     al, 10h     ; Hercules Plus bit pattern
                jne     L4
                mov     adapter, 3  ; HGC_PLUS
                jmp     exit

        L4:     mov     adapter, 2  ; HGC

        EXIT:   

            }
        }
        return adapter;
    }

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
