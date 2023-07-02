/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      1.07.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef BIOS_DATA_AREA_SERVICES_H
#define BIOS_DATA_AREA_SERVICES_H

#include <stdint.h>

#include "bios_data_area_services_constants.h"

namespace bios {

	template<typename T>
	T read_data_area(uint32_t p) {
		return *((T*)p);
	}

}

#endif