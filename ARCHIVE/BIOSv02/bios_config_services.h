/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      24.06.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef BIOS_CONFIG_SERVICES_H
#define BIOS_CONFIG_SERVICES_H

#include "..\MEM\mem_types.h"

namespace bios {

	/**
	* @brief test if the ROM BIOS supports AT extended services?
	* @note The PC XT (since 1986/01/10), PC AT (since 1985/06/10), the PC XT Model 286, the PC Convertible and most PS/2 machines do support.
	*/
	bool is_support_AT_extended_services();

	namespace ext {

		/**
		*  @brief SYSTEM - GET CONFIGURATION (XT >1986/1/10,AT mdl 3x9,CONV,XT286,PS)
		*  @details
		*  @note
		*  The PC XT (since 1986/01/10), PC AT (since 1985/06/10), the PC XT Model 286, the PC Convertible and most PS/2 machines
		*  will clear the CF flag and return the table in ES:BX.
		*  The PC and PCjr return AH=80h/CF set
		*  The PC XT (1982/11/08), PC Portable, PC AT (1984/01/10), or PS/2 prior to Model 30 return AH=86h/CF set
		*  Info: This returns a pointer to a table that describes the system.
		*  @see bios_sys_parms_rec_t
		*/
		void get_ROM_table_address(retro::address_t* addr);

	}

}

#endif