/*****************************************************************//**
 * \file   abm_leading_zeros_count.h
 * \brief  8086 implemention of advanced bit manipulation - leading zeros count
 * \note   In the abscence of dedicated instruction bsf on 368 and above processors.
 * In computer software and hardware, find first set (ffs) or find first one is a bit operation that, given an unsigned machine word,
 * designates the index or position of the least significant bit set to one in the word counting from the least significant bit position.
 * \url	   en.wikipedia.org/wiki/X86_Bit_manipulation_instruction_set
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef LEADING_ZEROS_COUNT_H
#define LEADING_ZEROS_COUNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm {

	uint16_t lzcnt_lookup_64(uint64_t* ptr_value) {
		uint16_t cnt;
		__asm {
		}
		return cnt;
	}

	uint16_t leading_zeros(uint64_t n) {
		uint64_t msb = 0x8000000000000000;
		uint16_t zeros = 0;
		for (uint16_t i = 0; i < 64; ++i) {
			if ((n << i) & msb) break; // leading set bit found	
			++zeros;
		}
		return zeros;
	}

}

#endif