/**
 *
 *  @brief     
 *  @details   ~
 *  @author    Jeremy Thornton
 *  @date      12.03.2023
 *  @copyright © Jeremy Thornton, 2023. All right reserved.
 *
 */
#ifndef FSYS_FIGNORE_H
#define FSYS_FIGNORE_H

#include "fsys_constants.h"

namespace fsys {

 /**
  *  @brief  Extracts characters from the input sequence and discards them, until either n characters have been extracted, or one compares equal to delim.
  *  @param  fptr  - FILE pointer argument
  *  @param  size  - Maximum number of characters to extract (and ignore) or until delim (or the end-of-file) is found
  *  @param  delim - Delimiting character: The function stops extracting characters as soon as an extracted character compares equal to this.
  *  @retval       - If a reading error happens or the end-of-file is reached while reading, the proper indicator is set (feof or ferror) and EOF is returned.
  */
	int ignore(FILE* fptr, long size = 1, int delim = EOF ) {
		return fscanf(fptr, "%*[^\n]\n");
	}

}

#endif