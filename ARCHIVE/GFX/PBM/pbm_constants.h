/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      9.03.2023
 *  @copyright � Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef PBM_CONSTANTS_H
#define PBM_CONSTANTS_H

#include <stdint.h>

#include "../../TEST/debug_macros.h"

#define MAGIC_P1 0x3150		// "P1" in the byte order it would appear in memory 
#define MAGIC_P4 0x3450		// "P4" the little endian word would be reversed
#define VALID_PBM_EXT "pbm"	// important to use file extension for consitency
#define MIN_HEADER_SIZE 7

namespace pbm {

}

#endif