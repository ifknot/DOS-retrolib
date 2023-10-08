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
	T read_BDA(uint32_t bda_addr) {
		bda_addr += BDA_START_ADDR;
		return *((T*)bda_addr);
	}

}

#endif