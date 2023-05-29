/*****************************************************************//**
 * \file   dos_services.h
 * \brief
 *
 * \url http://bitsavers.informatik.uni-stuttgart.de/pdf/borland/turbo_c/Turbo_C_Reference_Guide_1987.pdf
 *
 * \author ifkno
 * \date   October 2021
 *********************************************************************/
//#pragma once

#ifndef DOS_SERVICES_H
#define DOS_SERVICES_H

#include <stdint.h>
#include <iostream>
#include <dos.h>        // Turbo C/C++

#include "dos_services_constants.h"
#include "dos_services_types.h"
#include "dos_error_messages.h"

namespace dos {

        // 0  Program terminate

        // 1  Keyboard input with echo

        // 2  Display output

        // 3  Wait for auxiliary device input

        // 4  Auxiliary output

        // 5  Printer output

        // 6  Direct console I/O

        // 7  Wait for direct console input without echo

        // 8  Wait for console input without echo

        // 9  Print string

        // A  Buffered keyboard input

        // B  Check standard input status

        // C  Clear keyboard buffer, invoke keyboard function

        // D  Disk reset

        // E  Select disk

        // F  Open file using FCB

        // 10  Close file using FCB

        // 11  Search for first entry using FCB

        // 12  Search for next entry using FCB

        // 13  Delete file using FCB

        // 14  Sequential read using FCB

        // 15  Sequential write using FCB

        // 16  Create a file using FCB

        // 17  Rename file using FCB

        // 18  DOS dummy function (CP/M) (not used/listed)

        // 19  Get current default drive

        // 1A  Set disk transfer address

        // 1B  Get allocation table information

        // 1C  Get allocation table info for specific device

        // 1D  DOS dummy function (CP/M) (not used/listed)

        // 1E  DOS dummy function (CP/M) (not used/listed)

        // 1F  Get pointer to default drive parameter table (undocumented)

        // 20  DOS dummy function (CP/M) (not used/listed)

        // 21  Random read using FCB

        // 22  Random write using FCB

        // 23  Get file size using FCB

        // 24  Set relative record field for FCB

        // 25  Set interrupt vector
        /**
         * \brief Provides a safe method for changing interrupt vectors
         * INT 21,25 - Set Interrupt Vector
         * AH = 25h
         * AL = interrupt number
         * DS:DX = pointer to interrupt handler
         *
         * \param vec_num
         * \param address
         */
        void set_interrupt_vector(uint8_t vec_num, void* address) {
            address_t addr;
            addr.ptr = address;
            union REGS r;
            struct SREGS s;
            r.h.ah = SET_INTERRUPT_VECTOR;
            r.h.al = vec_num;
            s.ds = addr.memloc.segment;
            r.x.dx = addr.memloc.offset;
            int86x(DOS_SERVICE, &r, &r, &s);
            if (r.x.cflag != 0) LOG("fail");
        }

        // 26  Create new program segment

        // 27  Random block read using FCB

        // 28  Random block write using FCB

        // 29  Parse filename for FCB

        // 2A  Get date

        // 2B  Set date

        // 2C  Get time

        // 2D  Set time

        // 2E  Set/reset verify switch

        // 2F  Get disk transfer address

        // 30  Get DOS version number

        // 31  Terminate process and remain resident

        // 32  Get pointer to drive parameter table (undocumented)

        // 33  Get/set Ctrl-Break check state & get boot drive

        // 34  Get address to DOS critical flag (undocumented)

        // 35  Get interrupt vector
        /**
         * INT 21,35 - Get Interrupt Vector
         * AH = 35h
         * AL = interrupt vector number
         * on return:
         * ES:BX = pointer to interrupt handler.
         *
         * \param vec_num
         * \return uint32_t segment:offset pointer to interrupt handler
         */
        void* get_interrupt_vector(uint8_t vec_num) {
                union REGS r;
                struct SREGS s;
                r.h.ah = GET_INTERRUPT_VECTOR;
                r.h.al = vec_num;
                int86x(DOS_SERVICE, &r, &r, &s);
                if (r.x.cflag != 0) LOG("fail");
                address_t addr;
                addr.memloc.segment = s.es;
                addr.memloc.offset = r.x.bx;
                return addr.ptr;
        }

        // 36  Get disk free space

        // 37  Get/set switch character (undocumented)

        // 38  Get/set country dependent information

        // 39  Create subdirectory (mkdir)

        // 3A  Remove subdirectory (rmdir)

        // 3B  Change current subdirectory (chdir)

        // 3C  Create file using handle

        // 3D  Open file using handle

        // 3E  Close file using handle

        // 3F  Read file or device using handle

        // 40  Write file or device using handle

        // 41  Delete file

        // 42  Move file pointer using handle

        // 43  Change file mode

        // 44  I/O control for devices (IOCTL)

        // 45  Duplicate file handle

        // 46  Force duplicate file handle

        // 47  Get current directory

        // 48  Allocate memory blocks
        /**
         * \breif INT 21,48 - Allocate Memory
         *
         * AH = 48h
         * BX = number of memory paragraphs requested
         * \note paragraph is a memory unit of size 16 bytes,  relevant primarily (if not exclusively) in x86 real mode
         * \url https://en.wikipedia.org/wiki/X86_memory_segmentation
         * on return:
         * AX = segment address of allocated memory block (MCB + 1para)
         *    = error code if CF set  (see DOS ERROR CODES)
         * BX = size in paras of the largest block of memory available
         *      if CF set, and AX = 08 (Not Enough Mem)
         * CF = 0 if successful
         *    = 1 if error
         *
         * - returns segment address of allocated memory block AX:0000
         * - each allocation requires a 16 byte overhead for the MCB
         * - returns maximum block size available if error
         *
         * \see  INT 21,49,  INT 21,4A
         *
         * \param       number of paragraphs (16 bytes) requested
         * \param   segment* pointer to segment variable
         * \return      the segment address of the reserved memory or 0 if request failed
         */
        uint16_t allocate_memory_blocks(uint16_t paragraphs) {
            uint16_t err_code, available, mem_seg;
            __asm {
                .8086
                push    ax
                push    bx

                mov             bx, paragraphs      ; number requested paragraphs
                mov             ah, 48h             ; allocate memory
                int             0x21                ; dos call
                jnc             OK                  ; success CF = 0
                mov             err_code, ax        ; CF set, and AX = 08 (Not Enough Mem)
                mov             available, bx       ; size in paras of the largest block of memory available
                xor     ax, ax
        OK:     mov             mem_seg, ax

                pop             bx
                pop             ax

            }
            if (mem_seg == 0) {
                std::cout << dos::error::messages[err_code] << '\n';
                if (err_code == dos::error::INSUFFICIENT_MEMORY) {
                    std::cout << " largest block of memory available = " << std::hex << (available * 16) << " bytes\n";
                }
            }
            return mem_seg;
        }

        // 49  Free allocated memory blocks
        /**
         * \brief INT 21,49 - Free Allocated Memory
         *
         * AH = 49h
         * ES = segment of the block to be returned (MCB + 1para)
         *
         * on return:
         * AX = error code if CF set  (see DOS ERROR CODES)
         *
         * - releases memory and MCB allocated by INT 21,48
         * - may cause unpredictable results if memory wasn't allocated using INT 21,48
         * or if memory wasn't allocated by the current process
         * - checks for valid MCB id, but does NOT check for process ownership care must be
         * taken when freeing the memory of another process to assure the segment isn't in use
         * by a TSR or ISR
         * \note this function is unreliable in a TSR once resident, since COMMAND.COM and many
         *  other .COM files take all available memory when they load.
         * \see  INT 21,4A
         */
        bool free_allocated_memory_blocks(uint16_t segment) {
            uint16_t err_code = 0;
            __asm {
                .8086
                push    ax
                push    es

                mov             ax, segment     ; the segment to be released
                mov             es, ax          ; segment of the block to be returned(MCB + 1para)
                mov             ah, 49h         ; de-allocate memory
                int             0x21            ; dos call
                jnc             OK              ; success CF = 0
                mov             err_code, ax    ; de-allocation failed ax is dos error code

        OK:     pop             es
                pop             ax

            }
            if (err_code) {
                std::cout << dos::error::messages[err_code] << std::hex << segment << '\n';
                return false;
            }
            else {
                return true;
            }
        }

        // 4A  Modify allocated memory blocks

        // 4B  EXEC load and execute program (func 1 undocumented)

        // 4C  Terminate process with return code

        // 4D  Get return code of a sub-process

        // 4E  Find first matching file

        // 4F  Find next matching file

        // 50  Set current process id (undocumented)

        // 51  Get current process id (undocumented)

        // 52  Get pointer to DOS "INVARS" (undocumented)

        // 53  Generate drive parameter table (undocumented)

        // 54  Get verify setting

        // 55  Create PSP (undocumented)

        // 56  Rename file

        // 57  Get/set file date and time using handle

        // 58  Get/set memory allocation strategy (3.x+, undocumented)

        // 59  Get extended error information (3.x+)
        /**
         *
         * Turbo-C/C++'s int86 function is used to make system interrupt calls to DOS and BIOS services.
         *
         * AH = 59h
         * BX = 00 for versions  3.0, 3.1, 3.2
         * on return:
         * AX = extended error code (see DOS ERROR CODES)
         *    = 0 if no error
         * BH = error class
         * BL = suggested action
         * CH = locus
         *
         * - may be called after any  INT 21  function or from
         *   INT 24 when an error is returned
         * - must be called immediately after the error occurs
         * - registers CX, DX, DI, SI, BP, DS and ES are destroyed.
         *
         * \return
         */
        std::string get_extended_error_information() { // TODO: handle 22  Invalid disk change" ES:DI -> media ID structure

                union REGS r;           // the REGS union is a way to address individual registers in the interrupt context data structure
                r.h.ah = GET_EXTENDED_ERROR_INFORMATION;
                r.x.bx = 0;             // 0 for versions  3.0, 3.1, 3.2
                int86(DOS_SERVICE, &r, &r);
                if (r.x.cflag != 0) LOG("fail");
                if (r.x.ax) {
                        std::string info(dos::error::messages[r.x.ax]);
                        info += dos::error::classes[r.h.bh];
                        info += dos::error::actions[r.h.bl];
                        info += dos::error::locus[r.h.ch];
                        return info;
                }
                return "no error";
        }

        // 5A  Create temporary file (3.x+)

        // 5B  Create new file (3.x+)

        // 5C  Lock/unlock file access (3.x+)

        // 5D  Critical error information (undocumented 3.x+)

        // 5E  Network services (3.1+)

        // 5F  Network redirection (3.1+)

        // 60  Get fully qualified file name (undocumented 3.x+)

        // 62  Get address of program segment prefix (3.x+)

        // 63  Get system lead byte table (MSDOS 2.25 only)

        // 64  Set device driver look ahead  (undocumented 3.3+)

        // 65  Get extended country information (3.3+)

        // 66  Get/set global code page (3.3+)

        // 67  Set handle count (3.3+)

        // 68  Flush buffer (3.3+)

        // 69  Get/set disk serial number (undocumented DOS 4.0+)

        // 6A  DOS reserved (DOS 4.0+)

        // 6B  DOS reserved

        // 6C  Extended open/create (4.x+)

        // F8  Set OEM INT 21 handler (functions F9-FF) (undocumented)

}

#endif