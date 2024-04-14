/**

@file      test_kbd.h
@brief     
@details   ~
@author    ifknot
@date      9.04.2024
@copyright © ifknot, 2024. All right reserved.

**/
#ifndef TEST_KBD_H
#define TEST_KBD_H

#include "../TEST/debug_macros.h"

#include "kbd_interupt_routines.h"

namespace test_kbd {

	void run() {

		if (YESNO("* 810\t Test keyboard hook interupt 9 ?")) {
			INFO("* hook simple isr 9 handler ");
			INFO("kbd::xt::install_simple_isr_9()");
			
			mem::address_t old_ivec_keyboard = kbd::xt::install_simple_isr_9();
			LOG_AS(old_ivec_keyboard, std::hex);
			INFO("installed");
			LOG(dos::get_interrupt_vector(IKEYBOARD));
			ASSERT(old_ivec_keyboard.memloc, != , dos::get_interrupt_vector(IKEYBOARD).memloc, "vector not changed");
			
			YESNO("***");

			INFO("* reset back to old vector");
			INFO("dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, old_ivec_keyboard)");
			dos::set_interrupt_vector(IKEYBOARD, old_ivec_keyboard);
			LOG(dos::get_interrupt_vector(IKEYBOARD));
			ASSERT(old_ivec_keyboard.memloc, == , dos::get_interrupt_vector(IKEYBOARD).memloc, "vector not reset to original");
			
		}

	}

}

#endif