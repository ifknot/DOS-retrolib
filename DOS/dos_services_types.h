/*****************************************************************//**
 * \file   dos_services_types.h
 * \brief  
 * 
 * \author ifkno
 * \date   November 2021
 *********************************************************************/
//#pragma once

#ifndef DOS_SERVICES_TYPES_H
#define DOS_SERVICES_TYPES_H

#include <stdint.h>
#include <iostream>
#include <iomanip>

#define PARAGRAPH_SIZE 16

namespace dos {

	struct segoff_t {

		uint16_t offset, segment;

	};

	union address_t {

		uint32_t address;
		segoff_t memory;
		uint16_t words[2];
		uint8_t bytes[4];

		address_t() : address(0) {}

		address_t(uint32_t address) : address(address) {}

		address_t(uint16_t segment, uint16_t offset) {
			memory.segment = segment;
			memory.offset = offset;
		}

	};

}

#endif