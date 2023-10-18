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

#include "dos.h"

namespace test_dos_interrupt_vector {

	void run() {
		LOG_AS(dos::get_interrupt_vector(0), std::hex);
	}

}

#endif