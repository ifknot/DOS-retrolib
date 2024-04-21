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
		void interrupt far scan_code_set_1_interrupt_handler() {
			__asm {
				.8086
				sti						; disable interrupts

				lea		bx, key_pressed	; DS:BX points to key pressed arr
				
				in		al, PPI_PORT_B	; get current keyboard state
				mov		cl, al			; store original in CL
				or		al, 80h			; set the 7th bit
				out		PPI_PORT_B, al	; send to PPI port B (clear keyboard)
				
				in		al, PPI_PORT_A	; get key scan code
				test	al, 80h			; is bit 7 set?
				jnz		SKIP			; only count key presses
				
				add		bl, al			; index key press arr by scan code
				add		[bx], 1			; increment scan code key presses
				
	SKIP:		mov		al, cl			; original settings PPI port B
				out		PPI_PORT_B, al	; clear the 7th bit of the PPI (enable keyboard)

				mov		al, PIC_END_IRQ	; Send a "Non Specific End of Interrupt" command to the PIC
				out		PIC_OPERATION_COMMAND_PORT, al 

				cli						; re-enable interrupts
			}
		}

	}

	void clear_key_pressed_array() {
		for (int i = 0; i < MAX_SCAN_CODES; ++i) key_pressed[i] = 0;
	}

	void install_keyboard_interrupt_handler(void* new_kbd_isr_ptr) {
		mem::address_t new_kbd_isr;
		old_keyboard_ivec = dos::get_interrupt_vector(IKEYBOARD);
		new_kbd_isr.ptr = new_kbd_isr_ptr;
		dos::set_interrupt_vector(IKEYBOARD, new_kbd_isr);
	}

	void restore_keyboard_interupt_handler() {
		dos::set_interrupt_vector(IKEYBOARD, old_keyboard_ivec);
	}

}