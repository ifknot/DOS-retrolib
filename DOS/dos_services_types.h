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

		void* ptr;
		segoff_t memloc;
		uint16_t words[2];
		uint8_t bytes[4];

		address_t() : ptr(NULL) {}

		address_t(void* ptr) : ptr(ptr) {}

		address_t(uint16_t segment, uint16_t offset) {
			memloc.segment = segment;
			memloc.offset = offset;
		}

	};

}

std::ostream& operator<< (std::ostream& os, const dos::segoff_t& memloc) {
	os << std::hex << std::setfill('0')
		<< std::setw(4) << memloc.segment << ':' << std::setw(4) << memloc.offset
		<< std::dec;
	return os;
}


std::ostream& operator<< (std::ostream& os, const dos::address_t& addr) {
	os << std::hex << std::setfill('0')
		<< std::setw(8) << (uint32_t)addr.ptr
		<< std::dec;
	return os;
}

#endif