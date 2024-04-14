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

#include "../TEST/debug_macros.h"

#include "../DOS/dos_services.h"



namespace kbd {

	namespace xt {

		void interrupt far kdb_xt_interrupt_handler();

		mem::address_t install_simple_isr_9();

	}

}

#endif