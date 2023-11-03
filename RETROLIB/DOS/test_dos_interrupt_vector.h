/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      18.10.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef TEST_DOS_INTERRUPT_VECTOR_H
#define TEST_DOS_INTERRUPT_VECTOR_H

#include "../TEST/debug_macros.h"

#include "dos.h"

namespace test_dos_interrupt_vector {

	void run() {
		INFO("* test get interupt vector");
		mem::address_t old_ivec_equip_det = dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION);
		LOG(old_ivec_equip_det);

		INFO("* test set interupt vector");
		INFO("dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, 0xF000BEEF)");
		mem::address_t new_ivec_eqip_det;
		new_ivec_eqip_det.void_ptr = (void*)0xF000BEEF;
		dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, new_ivec_eqip_det);
		LOG(dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION));
		ASSERT(old_ivec_equip_det.void_ptr, !=, dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION).void_ptr, "vector not changed");
		
		INFO("* reset back to old vector");
		INFO("dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, old_ivec_equip_det)");
		dos::set_interrupt_vector(IEQUIPMENT_DETERMINATION, old_ivec_equip_det);
		LOG(dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION));
		ASSERT(old_ivec_equip_det.void_ptr, ==, dos::get_interrupt_vector(IEQUIPMENT_DETERMINATION).void_ptr, "vector not reset to original");

	}

}

#endif