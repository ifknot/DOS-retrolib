/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.10.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DOS_INTERRUPT_VECTOR_H
#define TEST_DOS_INTERRUPT_VECTOR_H

#include "../TEST/debug_macros.h"

#include "dos.h"

namespace test_dos_interrupt_vector {

	void run() {
		INFO("* test get interupt vector");
		void* old_ivec_equip_det = dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION);
		LOG_AS(old_ivec_equip_det, std::hex);

		INFO("* test set interupt vector");
		INFO("dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, 0xF000F84D)");
		dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, (void*)0xF000F84D);
		LOG_AS(dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), std::hex);
		ASSERT(old_ivec_equip_det != dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), old_ivec_equip_det);
		
		INFO("* reset back to old vector");
		INFO("dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, old_ivec_equip_det)");
		dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, old_ivec_equip_det);
		LOG_AS(dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), std::hex);
		ASSERT(old_ivec_equip_det == dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION), old_ivec_equip_det);
		
		INFO("* PASS!");
	}

}

#endif