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

		void interrupt far kdb_xt_interrupt_handler() {
			__asm {
				.8086
				sti; disable interrupts

				nop

				cli; enable interrupts
			}
		}

		mem::address_t install_simple_isr_9() {
			mem::address_t old_isr_9 = dos::get_interrupt_vector(IKEYBOARD);
			mem::address_t new_isr_9;
			new_isr_9.ptr = (void*)kdb_xt_interrupt_handler;
			dos::set_interrupt_vector(IKEYBOARD, new_isr_9);
			return old_isr_9;
		}

	}

}