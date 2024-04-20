/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      14.04.2024
 *  @copyright © Jeremy Thornton, 2024. All right reserved.
 *
 */
#ifndef KBD_INTERUPT_ROUTINES_H
#define KBD_INTERUPT_ROUTINES_H

#include <stdint.h>

#include "../TEST/debug_macros.h"

#include "../DOS/dos_services.h"

#include "kbd_constants.h"

namespace kbd {

	uint8_t key_pressed[];

	static mem::address_t old_kbd_isr;

	namespace xt {

		void interrupt far kdb_xt_interrupt_handler();

		mem::address_t install_simple_isr_9();

	}

	void install_keyboard_interrupt_handler(mem::address_t new_kbd_isr);

	void restore_keyboard_interupt_handler();

}

#endif