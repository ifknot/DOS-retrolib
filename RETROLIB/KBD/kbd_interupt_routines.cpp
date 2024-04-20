/**
 *
 *  @file      kbd_interupt_routines.cpp
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      14.04.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#include "kbd_interupt_routines.h"

namespace kbd {

	namespace xt {

		/**
		* @note 1. On the IBM PC and XT and compatibles, you MUST clear the keyboard
		* after reading the scancode by reading the value at port 0x61,
		* flipping the 7th bit to a 1, and writing that value back to port 0x61.
		* After that is done, flip the 7th bit back to 0 to re-enable the keyboard.
		* @note 2. On IBM PC ATs and newer, writing and reading port 0x61 does nothing 
		*(onstensibly), and using it to clear the keyboard isn't necessary.
		*/
		void interrupt far interrupt_handler() {
			__asm {
				.8086
				sti						; disable interrupts
				pushf

				lea		bx, key_pressed

				in		al, PPI_PORT_B	; get current keyboard state
				mov		cl, al			; store in CL
				in		al, PPI_PORT_A	; get key scan code
				
				add		bl, al
				mov		[bx], al
				
				mov		al, cl			; current settings PPI port B
				or		al, 80h			; set the 7th bit of PPI port B (clear keyboard)
				out		PPI_PORT_B, al
				mov		al, cl 
				out		PPI_PORT_B, al	; clear the 7th bit of the PPI (enable keyboard)
				mov		al, 20h
				out		PIC_OPERATION_COMMAND_PORT, al ; Send a "Non Specific End of Interrupt" command to the PIC

				popf
				cli						; enable interrupts
			}
		}

		mem::address_t install_simple_isr_9() {
			mem::address_t old_isr_9 = dos::get_interrupt_vector(IKEYBOARD);
			mem::address_t new_isr_9;
			new_isr_9.ptr = (void*)interrupt_handler;
			dos::set_interrupt_vector(IKEYBOARD, new_isr_9);
			return old_isr_9;
		}

	}

	void clear_key_pressed_array() {
		for (int i = 0; i < MAX_SCAN_CODES; ++i) key_pressed[i] = 0;
	}

	void install_keyboard_interrupt_handler(void* new_kbd_isr_ptr) {
		mem::address_t new_kbd_isr;
		old_kbd_isr = dos::get_interrupt_vector(IKEYBOARD);
		new_kbd_isr.ptr = new_kbd_isr_ptr;
		dos::set_interrupt_vector(IKEYBOARD, new_kbd_isr);
	}

	void restore_keyboard_interupt_handler() {
		dos::set_interrupt_vector(IKEYBOARD, old_kbd_isr);
	}

}