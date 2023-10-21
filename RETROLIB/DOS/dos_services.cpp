#include "dos_services.h"

#include "dos_services_constants.h"
#include "dos_services_types.h"
#include "dos_error_messages.h"

#ifndef NDEBUG 

#include <cassert>

#endif

namespace dos {

        /**
         * @brief Provides a safe method for changing interrupt vectors
         * @note returns nothing
         * INT 21,25 - Set Interrupt Vector
         * AH = 25h
         * AL = interrupt number
         * DS:DX = pointer to interrupt handler
         *
         * @param vec_num
         * @param address
         */
        void set_interrupt_vector(uint8_t vec_num, void* address) {
            address_t addr;
            addr.ptr = address;
            uint16_t seg_intr = addr.memloc.segment;
            uint16_t off_intr = addr.memloc.offset;
            __asm {
                .8086
                mov     ax, seg_intr
                mov     ds, ax 
                mov     dx, off_intr
                mov     al, vec_num
                mov     ah, SET_INTERRUPT_VECTOR
                int     DOS_SERVICE
            }
            
        }

        /**
         * @brief Standard method for retrieving interrupt vectors
         * INT 21,35 - Get Interrupt Vector
         * AH = 35h
         * AL = interrupt vector number
         * on return:
         * ES:BX = pointer to interrupt handler.
         *
         * @param vec_num
         * @return void* segment:offset pointer to interrupt handler
         */
        void* get_interrupt_vector(uint8_t vec_num) {
            uint16_t es_segment, bx_offset;
            address_t addr;
            __asm {
                .8086
                mov     al, vec_num
                mov     ah, GET_INTERRUPT_VECTOR
                int     DOS_SERVICE
                mov     es_segment, es 
                mov     bx_offset, bx
            }
            addr.memloc.segment = es_segment;
            addr.memloc.offset = bx_offset;
            return addr.ptr;
        }

        /**
         * @breif INT 21,48 - Allocate Memory
         *
         * AH = 48h
         * BX = number of memory paragraphs requested
         * @note paragraph is a memory unit of size 16 bytes,  relevant primarily (if not exclusively) in x86 real mode
         * @url https://en.wikipedia.org/wiki/X86_memory_segmentation
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
         * @see  INT 21,49,  INT 21,4A
         *
         * @param       number of paragraphs (16 bytes) requested
         * @param   segment* pointer to segment variable
         * @return      the segment address of the reserved memory or 0 if request failed
         */
        uint16_t allocate_memory_blocks(uint16_t paragraphs) {
            uint16_t err_code, available, mem_seg = 0;
            __asm {
                .8086
                mov     bx, paragraphs              ; number requested paragraphs
                mov     ah, ALLOCATE_MEMORY_BLOCKS  ; allocate memory
                int     DOS_SERVICE                 ; dos call
                jnc     OK                          ; success CF = 0
                mov     err_code, ax                ; CF set, and AX = 08 (Not Enough Mem)
                mov     available, bx               ; size in paras of the largest block of memory available
                xor     ax, ax
        OK:     mov     mem_seg, ax

            }
#ifndef NDEBUG
            if (mem_seg == 0) {
                std::cout << dos::error::messages[err_code] << '\n';
                if (err_code == dos::error::INSUFFICIENT_MEMORY) {
                    std::cout << " largest block of memory available = " << std::hex << (available * 16) << " bytes\n";
                }
            }
#endif
            return mem_seg;
        }

        /**
         * @brief INT 21,49 - Free Allocated Memory
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
         * @note this function is unreliable in a TSR once resident, since COMMAND.COM and many
         *  other .COM files take all available memory when they load.
         * @see  INT 21,4A
         */
        uint16_t free_allocated_memory_blocks(uint16_t segment) {
            uint16_t err_code = 0;
            __asm {
                .8086
                mov     ax, segment                         ; the segment to be released
                mov     es, ax                              ; segment of the block to be returned(MCB + 1para)
                mov     ah, FREE_ALLOCATED_MEMORY_BLOCKS    ; de-allocate memory
                int     DOS_SERVICE                         ; dos call
                jnc     OK                                  ; success CF = 0
                mov     err_code, ax                        ; de-allocation failed ax is dos error code
        OK:     
            }
#ifndef NDEBUG
            if (err_code) {
                std::cout << dos::error::messages[err_code] << std::hex << segment << '\n';
                return err_code;
            }
#endif
            return err_code;
        }

        /**
         * @brief Get extended error information (3.x+)
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
         * @return std::string error message, class, action, locus
         */
        std::string get_extended_error_information() { // TODO: handle 22  Invalid disk change" ES:DI -> media ID structure
            uint16_t err_code = 0;
            uint8_t err_class, err_action, err_locus;
            __asm {
                .8086
                xor     bx, bx                              ; BX = 0 DOS versions  3.0, 3.1, 3.2
                mov     ah, GET_EXTENDED_ERROR_INFORMATION
                int     DOS_SERVICE
                mov     err_code, ax
                mov     err_class, bh
                mov     err_action, bl
                mov     err_locus, ch
            }
#ifndef NDEBUG
            std::string info(dos::error::messages[err_code]);
            if (err_code) {
                info += dos::error::classes[err_class];
                info += dos::error::actions[err_action];
                info += dos::error::locus[err_locus];
            }
#endif
            return info;
        }

}
