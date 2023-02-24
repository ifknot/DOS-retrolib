/*****************************************************************//**
 * \file   abm_trailing_zeros_count.h
 * \brief  8086 implemention of advanced bit manipulation - trailing zeros count
 * \note   In the abscence of dedicated instruction bs ron 368 and above processors.
 * 
 * \author ifkno
 * \date   February 2023
 *********************************************************************/
#ifndef TRAILING_ZEROS_COUNT_H
#define TRAILING_ZEROS_COUNT_H

#include "abm_types.h"
#include "abm_constants.h"

namespace abm {

	uint16_t tzcnt_lookup_64(uint64_t* ptr_value) {
		uint16_t cnt;
		__asm {
		}
		return cnt;
	}

	uint16_t trailing_zeroes(uint64_t n) {
		uint16_t bits = 0;
		while (n >= 0 && !(n & 01)) {
			++bits;
			if (n != 0) n >>= 1;
			else break;
		}
		return bits;
	}

}

#endif