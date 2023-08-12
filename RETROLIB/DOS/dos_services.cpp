#include "dos_services.h"

namespace dos {

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

}
