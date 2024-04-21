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
#include "kbd_set_1_scan_codes.h"

namespace test_kbd {

	void run() {

		if (YESNO("* 810\t Test keyboard hook interupt 9 ?")) {
			
			kbd::clear_key_pressed_array();

			INFO("* hook XT Model F keyboard handler ");
			kbd::install_keyboard_interrupt_handler((void*)kbd::xt::scan_code_set_1_interrupt_handler);
			//ASSERT(kbd::old_keyboard_ivec.memloc, != , dos::get_interrupt_vector(IKEYBOARD).memloc, "vector not changed");
			
			while (!kbd::key_pressed[SCAN_ESC]) {}

			INFO("* reset back to old vector");
			kbd::restore_keyboard_interupt_handler();
			//ASSERT(kbd::old_keyboard_ivec.memloc, == , dos::get_interrupt_vector(IKEYBOARD).memloc, "vector not reset to original");
			
			for (int i = 0; i < MODEL_F_SCAN_CODE_COUNT; ++i) std::cout << (int)kbd::key_pressed[i] << ' ';
		}

	}

}

#endif